#include <geodesuka/core/gcl/swapchain.h>

#include <algorithm>

#include <vulkan/vulkan.h>

namespace geodesuka::core::gcl {


	swapchain::prop::prop() {
		this->Count				= 1;
		this->Format			= VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
		this->ColorSpace		= VkColorSpaceKHR::VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		//this->Resolution		= { 640, 480 };
		this->Usage				= texture::usage::COLOR_ATTACHMENT;
		this->CompositeAlpha	= swapchain::composite::ALPHA_OPAQUE;
		this->PresentMode		= swapchain::mode::FIFO;
		this->Clipped			= true;		
	}


	swapchain::swapchain(context* aContext, VkSurfaceKHR aSurface, prop aProperty, uint32_t aWidth, uint32_t aHeight, swapchain* aOldSwapchain) {

		// Queries Available formats.
		uint32_t lFormatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(aContext->parent()->handle(), aSurface, &lFormatCount, NULL);
		std::vector<VkSurfaceFormatKHR> lFormat(lFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(aContext->parent()->handle(), aSurface, &lFormatCount, lFormat.data());
		
		// Queries Surface Capabilities.
		VkSurfaceCapabilitiesKHR lSurfaceCapabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(aContext->parent()->handle(), aSurface, &lSurfaceCapabilities);

		// Queries presentation modes.
		uint32_t lPresentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), aSurface, &lPresentModeCount, NULL);
		std::vector<VkPresentModeKHR> lPresentMode(lPresentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), aSurface, &lPresentModeCount, lPresentMode.data());

		// 0 - Format
		// 1 - ColorSpace
		// 2 - Usage
		// 3 - CompositeAlpha
		// 4 - PresentMode

		bool isSupported[5];
		for (size_t i = 0; i < 5; i++) {
			isSupported[i] = false;
		}

		for (size_t i = 0; i < lFormat.size(); i++) {
			// Check if Format is supported.
			if (lFormat[i].format == aProperty.Format) {
				isSupported[0] = true;
			}
			// Check if ColorSpace is supported by Device
			if (lFormat[i].colorSpace == aProperty.ColorSpace) {
				isSupported[1] = true;
			}
		}

		// Check it proposed usage flags are supported.
		if ((lSurfaceCapabilities.supportedUsageFlags & aProperty.Usage) == aProperty.Usage) {
			isSupported[2] = true;
		}
		
		// Check if proposed composite alpha is supported.
		if ((lSurfaceCapabilities.supportedCompositeAlpha & aProperty.CompositeAlpha) == aProperty.CompositeAlpha) {
			isSupported[3] = true;
		}

		// Check if proposed Present Mode is supported.
		for (size_t i = 0; i < lPresentMode.size(); i++) {
			if (lPresentMode[i] == aProperty.PresentMode) {
				isSupported[4] = true;
			}
		}

		// If all proposed values are supported.
		bool Success = true;
		for (size_t i = 0; i < 5; i++) {
			Success &= isSupported[i];
		}

		// If success, then create swapchain.
		if (Success) {

			VkExtent2D lExtent2D;
			lExtent2D.width = std::clamp((uint32_t)aWidth, lSurfaceCapabilities.minImageExtent.width, lSurfaceCapabilities.maxImageExtent.width);
			lExtent2D.height = std::clamp((uint32_t)aHeight, lSurfaceCapabilities.minImageExtent.height, lSurfaceCapabilities.maxImageExtent.height);
			// After properties have been validated above.

			this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			this->CreateInfo.pNext						= NULL;
			this->CreateInfo.flags						= 0;
			this->CreateInfo.surface					= aSurface;
			this->CreateInfo.minImageCount				= std::clamp((uint32_t)aProperty.Count, lSurfaceCapabilities.minImageCount, lSurfaceCapabilities.maxImageCount);
			this->CreateInfo.imageFormat				= (VkFormat)aProperty.Format;
			this->CreateInfo.imageColorSpace			= (VkColorSpaceKHR)aProperty.ColorSpace;
			this->CreateInfo.imageExtent				= lExtent2D;
			this->CreateInfo.imageArrayLayers			= 1; // Maybe support later.
			this->CreateInfo.imageUsage					= (VkImageUsageFlags)aProperty.Usage;
			this->CreateInfo.imageSharingMode			= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
			this->CreateInfo.queueFamilyIndexCount		= 0;
			this->CreateInfo.pQueueFamilyIndices		= NULL;
			this->CreateInfo.preTransform				= VkSurfaceTransformFlagBitsKHR::VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
			this->CreateInfo.compositeAlpha				= (VkCompositeAlphaFlagBitsKHR)aProperty.CompositeAlpha;
			this->CreateInfo.presentMode				= (VkPresentModeKHR)aProperty.PresentMode;
			this->CreateInfo.clipped					= (VkBool32)aProperty.Clipped;
			if (aOldSwapchain == nullptr) {
				this->CreateInfo.oldSwapchain = VK_NULL_HANDLE;
			}
			else {
				this->CreateInfo.oldSwapchain = aOldSwapchain->Handle;
			}

			VkResult Result = vkCreateSwapchainKHR(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
		}
		else {
			this->Handle = VK_NULL_HANDLE;
		}

	}

	swapchain::~swapchain() {
		vkDestroySwapchainKHR(Context->handle(), this->Handle, NULL);
		this->Handle = VK_NULL_HANDLE;
	}

}
