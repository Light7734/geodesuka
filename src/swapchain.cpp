#include <geodesuka/core/gcl/swapchain.h>

#include <algorithm>

namespace geodesuka::core::gcl {



	swapchain::swapchain(context* aContext, VkSurfaceKHR aSurface, prop aProperty, swapchain* aOldSwapchain) {
		
		// Queries Surface Capabilities.
		VkSurfaceCapabilitiesKHR SurfaceCapabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(aContext->parent()->handle(), aSurface, &SurfaceCapabilities);

		// Queries Available formats.
		uint32_t FormatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(aContext->parent()->handle(), aSurface, &FormatCount, NULL);
		std::vector<VkSurfaceFormatKHR> Format(FormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(aContext->parent()->handle(), aSurface, &FormatCount, Format.data());

		// Queries presentation modes.
		uint32_t PresentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), aSurface, &PresentModeCount, NULL);
		std::vector<VkPresentModeKHR> PresentMode(PresentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), aSurface, &PresentModeCount, PresentMode.data());

		bool isFormatSupported = false;
		bool isPresentModeSupported = false;
		bool isCompositeAlphaSupported = false;

		bool isSupported[5];
		// 0 - Format Supported
		// 1 - 
		if (true) {

		}

		VkExtent2D lExtent2D;
		lExtent2D.width = std::clamp((uint32_t)aProperty.Resolution.width, SurfaceCapabilities.minImageExtent.width, SurfaceCapabilities.maxImageExtent.width);
		lExtent2D.height = std::clamp((uint32_t)aProperty.Resolution.height, SurfaceCapabilities.minImageExtent.height, SurfaceCapabilities.maxImageExtent.height);
		// After properties have been validated above.

		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0;
		this->CreateInfo.surface					= aSurface;
		this->CreateInfo.minImageCount				= std::clamp((uint32_t)aProperty.Count, SurfaceCapabilities.minImageCount, SurfaceCapabilities.maxImageCount);
		this->CreateInfo.imageFormat				= (VkFormat)aProperty.Format;
		this->CreateInfo.imageColorSpace			= (VkColorSpaceKHR)aProperty.ColorSpace;
		this->CreateInfo.imageExtent				= aProperty.Resolution;
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

	swapchain::~swapchain() {

	}

}
