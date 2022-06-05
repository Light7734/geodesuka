#include <geodesuka/engine.h>
#include <geodesuka/core/object/system_window.h>

#include <assert.h>

#include <vector>
#include <algorithm>

#include <GLFW/glfw3.h>

#include <iostream>
//#include <intrin.h>
//__stosb(NULL, 0x00, 1024);

namespace geodesuka::core::object {

	using namespace gcl;

	std::vector<const char*> system_window::RequiredInstanceExtension;
	std::vector<const char*> system_window::RequiredContextExtension = { /*VK_KHR_SURFACE_EXTENSION_NAME,*/ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	std::thread::id system_window::MainThreadID;
	std::atomic<bool> system_window::SignalCreate = false;
	std::atomic<bool> system_window::WindowCreated = false;
	system_window::glfwargs system_window::WindowTempData = { window::option(), 0, 0, NULL, NULL, NULL };
	GLFWwindow* system_window::ReturnWindow = NULL;
	std::atomic<GLFWwindow*> system_window::DestroyWindow = NULL;

	system_window::swapchain::prop::prop() {
		FrameCount			= 1;
		FrameRate			= 30.0;
		ColorSpace			= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		Usage				= image::usage::COLOR_ATTACHMENT;
		CompositeAlpha		= system_window::composite::ALPHA_OPAQUE;
		PresentMode			= system_window::present_mode::FIFO;
		Clipped				= true;
	}

	system_window::property::property() {
		Window = window::option();
		Swapchain = swapchain::prop();
		PixelFormat = VK_FORMAT_B8G8R8A8_SRGB;
		Position = float3(0.0f, 0.0f, 0.0f);
		Size = float2(0.08f, 0.08f);
		Title = NULL;
	}

	system_window::propertyvsc::propertyvsc() {
		Window = window::option();
		Swapchain = swapchain::prop();
		PixelFormat = VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
		Position = int2(0, 0);
		Size = int2(640, 480);
		Title = NULL;
	}

	/*
	system_window::system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, const property& aProperty) : window(aEngine, aContext, aSystemDisplay->Stage) {
		if ((aEngine == nullptr) || (aContext == nullptr) || (aSystemDisplay == nullptr)) return;

		Position = aProperty.Position;

		FrameCount = aProperty.Swapchain.FrameCount;
		FrameRate = aProperty.Swapchain.FrameRate;
		FrameRateTimer.set(1.0 / aProperty.Swapchain.FrameRate);
		//Resolution; // Determined after window creation.

		FrameAttachmentCount = 1;
		FrameAttachmentDescription = (VkAttachmentDescription*)malloc(FrameAttachmentCount*sizeof(VkAttachmentDescription));
		FrameAttachment = (VkImageView**)malloc(FrameCount * sizeof(VkImageView*));
		for (uint32_t i = 0; i < FrameCount; i++) {
			FrameAttachment[i] = (VkImageView*)malloc(FrameAttachmentCount * sizeof(VkImageView));
			if (FrameAttachment[i] != NULL) {
				FrameAttachment[i][0] = VK_NULL_HANDLE;
			}
		}

		// Describes the format of system_window frames
		FrameAttachmentDescription[0].flags				= 0;
		FrameAttachmentDescription[0].format			= aProperty.PixelFormat;
		FrameAttachmentDescription[0].samples			= VK_SAMPLE_COUNT_1_BIT;
		FrameAttachmentDescription[0].loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
		FrameAttachmentDescription[0].storeOp			= VK_ATTACHMENT_STORE_OP_STORE;
		FrameAttachmentDescription[0].stencilLoadOp		= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		FrameAttachmentDescription[0].stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
		FrameAttachmentDescription[0].initialLayout		= VK_IMAGE_LAYOUT_UNDEFINED; // Depends on swapchain
		FrameAttachmentDescription[0].finalLayout		= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		// Place Null handle on views
		for (uint32_t i = 0; i < FrameCount; i++) {
			if (FrameAttachment[i] != NULL) {
				FrameAttachment[i][0] = VK_NULL_HANDLE;
			}
		}

		FrameDrawIndex = 0;

		DrawCommandCount = (uint32_t*)malloc(FrameCount * sizeof(uint32_t));
		DrawCommandList = (VkCommandBuffer**)malloc(FrameCount * sizeof(VkCommandBuffer*));

		if ((DrawCommandCount != NULL) && (DrawCommandList != NULL)) {
			for (uint32_t i = 0; i < FrameCount; i++) {
				DrawCommandCount[i] = 0;
				DrawCommandList[i] = NULL;
			}
		}

		Title = aProperty.Title;
		Size = aProperty.Size;// Convert to Physical Coordinates.
		Option = aProperty.Window;

		Display = aSystemDisplay;
		//Display->Stage->Render;

		SizeVSC.x = (((float)aSystemDisplay->SizeVSC.x) / (aSystemDisplay->Size.x)) * aProperty.Size.x;
		SizeVSC.y = (((float)aSystemDisplay->SizeVSC.y) / (aSystemDisplay->Size.y)) * aProperty.Size.y;
		PositionVSC = this->phy2vsc(aProperty.Position, SizeVSC, aSystemDisplay->PositionVSC, aSystemDisplay->SizeVSC, aSystemDisplay->Size);

		NextImageSemaphoreIndex = 0;
		NextImageSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
		RenderOperationSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
		PresentIndex = (uint32_t*)malloc(FrameCount * sizeof(uint32_t));
		PresentResult = (VkResult*)malloc(FrameCount * sizeof(VkResult));
		Presentation = (VkPresentInfoKHR*)malloc(FrameCount * sizeof(VkPresentInfoKHR));
		PipelineStageFlags = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		assert(!((NextImageSemaphore == NULL) || (RenderOperationSemaphore == NULL) || (PresentResult == NULL)));

		memset(PresentResult, 0x00, FrameCount * sizeof(VkResult));

		//// Create Window Handle.
		//this->Handle = glfwCreateWindow(aWidth, aHeight, aTitle, NULL, NULL);
		Handle = create_window_handle(Option, SizeVSC.x, SizeVSC.y, Title.ptr(), NULL, NULL);

		glfwSetWindowPos(Handle, PositionVSC.x, PositionVSC.y);

		// Check if handle is NULL.
		if (Handle == NULL) return;

		// User pointer to forward input stream.
		glfwSetWindowUserPointer(Handle, (void*)this);

		// system_window callbacks
		glfwSetWindowPosCallback(Handle, system_window::position_callback);
		glfwSetWindowSizeCallback(Handle, system_window::size_callback);
		glfwSetWindowCloseCallback(Handle, system_window::close_callback);
		glfwSetWindowRefreshCallback(Handle, system_window::refresh_callback);
		glfwSetWindowFocusCallback(Handle, system_window::focus_callback);
		glfwSetWindowIconifyCallback(Handle, system_window::iconify_callback);
		glfwSetWindowMaximizeCallback(Handle, system_window::maximize_callback);
		glfwSetWindowContentScaleCallback(Handle, system_window::content_scale_callback);

		// framebuffer callbacks
		glfwSetFramebufferSizeCallback(Handle, system_window::framebuffer_size_callback);

		// Mouse callbacks
		glfwSetMouseButtonCallback(Handle, system_window::mouse_button_callback);
		glfwSetCursorPosCallback(Handle, system_window::cursor_position_callback);
		glfwSetCursorEnterCallback(Handle, system_window::cursor_enter_callback);
		glfwSetScrollCallback(Handle, system_window::scroll_callback);

		// Keyboard callbacks
		glfwSetKeyCallback(Handle, system_window::key_callback);
		glfwSetCharCallback(Handle, system_window::character_callback);

		// File drop
		glfwSetDropCallback(Handle, system_window::file_drop_callback);

		//glfwGetWindowFrameSize(this->Context->Handle, system_window::framebuffer_size_callback);

		int lWidth, lHeight;
		glfwGetFramebufferSize(Handle, &lWidth, &lHeight);
		Resolution = uint3(lWidth, lHeight, 1u);

		// Create Surface Handle.
		VkResult Result = VkResult::VK_SUCCESS;
		Result = glfwCreateWindowSurface(Engine->handle(), Handle, NULL, &Surface);

		//TODO: Move to glfwGetPhysicalDevicePresentationSupport.
		//int isSupported = glfwGetPhysicalDevicePresentationSupport(Engine->Handle, Context->parent()->handle(), this->Context->qfi(device::qfs::PRESENT));

		// Check for presentation support for new window.
		VkBool32 isSupported = VK_FALSE;
		Result = vkGetPhysicalDeviceSurfaceSupportKHR(Context->parent()->handle(), Context->qfi(device::qfs::PRESENT), Surface, &isSupported);
		if (isSupported == VK_FALSE) {
			// Destroys suface.
			vkDestroySurfaceKHR(Engine->handle(), Surface, NULL);
			// Destroys window handle.
			glfwDestroyWindow(Handle);
			return;
		}

		// Queries Surface Capabilities.
		VkSurfaceCapabilitiesKHR SurfaceCapabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Context->parent()->handle(), Surface, &SurfaceCapabilities);

		// Swapchain create info.
		CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		CreateInfo.pNext					= NULL;
		CreateInfo.flags					= 0; // Add function later?
		CreateInfo.surface					= Surface;
		CreateInfo.minImageCount			= std::clamp((uint32_t)FrameCount, SurfaceCapabilities.minImageCount, SurfaceCapabilities.maxImageCount);
		CreateInfo.imageFormat				= aProperty.PixelFormat;
		CreateInfo.imageColorSpace			= (VkColorSpaceKHR)aProperty.Swapchain.ColorSpace;
		CreateInfo.imageExtent.width		= std::clamp((uint32_t)Resolution.x, SurfaceCapabilities.minImageExtent.width, SurfaceCapabilities.maxImageExtent.width);
		CreateInfo.imageExtent.height		= std::clamp((uint32_t)Resolution.y, SurfaceCapabilities.minImageExtent.height, SurfaceCapabilities.maxImageExtent.height);
		CreateInfo.imageArrayLayers			= std::clamp((uint32_t)Resolution.z, 1u, SurfaceCapabilities.maxImageArrayLayers);
		CreateInfo.imageUsage				= (VkImageUsageFlags)aProperty.Swapchain.Usage;
		CreateInfo.imageSharingMode			= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount	= 0;
		CreateInfo.pQueueFamilyIndices		= NULL;
		CreateInfo.preTransform				= SurfaceCapabilities.currentTransform;
		CreateInfo.compositeAlpha			= (VkCompositeAlphaFlagBitsKHR)aProperty.Swapchain.CompositeAlpha;
		CreateInfo.presentMode				= (VkPresentModeKHR)aProperty.Swapchain.PresentMode;
		CreateInfo.clipped					= (VkBool32)aProperty.Swapchain.Clipped;
		CreateInfo.oldSwapchain				= VK_NULL_HANDLE;

		Result = vkCreateSwapchainKHR(Context->handle(), &CreateInfo, NULL, &Swapchain);

		Result = vkGetSwapchainImagesKHR(this->Context->handle(), Swapchain, &FrameCount, NULL);
		std::vector<VkImage> Image(FrameCount);
		Result = vkGetSwapchainImagesKHR(this->Context->handle(), Swapchain, &FrameCount, Image.data());

		Frame = new image[FrameCount];

		// Load images into texture class.
		for (uint32_t i = 0; i < FrameCount; i++) {

			Frame[i].CreateInfo.sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Frame[i].CreateInfo.pNext								= NULL;
			Frame[i].CreateInfo.flags								= 0;
			Frame[i].CreateInfo.imageType							= VkImageType::VK_IMAGE_TYPE_2D;
			Frame[i].CreateInfo.format								= CreateInfo.imageFormat;
			Frame[i].CreateInfo.extent								= { CreateInfo.imageExtent.width, CreateInfo.imageExtent.height, 1u };
			Frame[i].CreateInfo.mipLevels							= 1;
			Frame[i].CreateInfo.arrayLayers							= CreateInfo.imageArrayLayers;
			Frame[i].CreateInfo.samples								= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT; // Unknown.
			Frame[i].CreateInfo.tiling								= VkImageTiling::VK_IMAGE_TILING_LINEAR; // Unknown.
			Frame[i].CreateInfo.usage								= CreateInfo.imageUsage;
			Frame[i].CreateInfo.sharingMode							= CreateInfo.imageSharingMode;
			Frame[i].CreateInfo.queueFamilyIndexCount				= 0;
			Frame[i].CreateInfo.pQueueFamilyIndices					= NULL;
			Frame[i].CreateInfo.initialLayout						= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED; // Unknown.
			Frame[i].Handle											= Image[i];

			VkImageViewCreateInfo ImageViewCreateInfo{};

			ImageViewCreateInfo.sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ImageViewCreateInfo.pNext								= NULL;
			ImageViewCreateInfo.flags								= 0;
			ImageViewCreateInfo.image								= Image[i];
			ImageViewCreateInfo.viewType							= VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
			ImageViewCreateInfo.format								= aProperty.PixelFormat;
			ImageViewCreateInfo.components.r						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.g						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.b						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.a						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.subresourceRange.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			ImageViewCreateInfo.subresourceRange.baseMipLevel		= 0;
			ImageViewCreateInfo.subresourceRange.levelCount			= 1;
			ImageViewCreateInfo.subresourceRange.baseArrayLayer		= 0;
			ImageViewCreateInfo.subresourceRange.layerCount			= 1;

			Result = vkCreateImageView(Context->handle(), &ImageViewCreateInfo, NULL, &FrameAttachment[i][0]);

			VkSemaphoreCreateInfo SemaphoreCreateInfo{};
			SemaphoreCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			SemaphoreCreateInfo.pNext = NULL;
			SemaphoreCreateInfo.flags = 0;
			Result = vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &NextImageSemaphore[i]);
			Result = vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &RenderOperationSemaphore[i]);

			PresentIndex[i] = i;
			PresentResult[i] = VkResult::VK_SUCCESS;
			Presentation[i].sType					= VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			Presentation[i].pNext					= NULL;
			Presentation[i].waitSemaphoreCount		= 1;
			Presentation[i].pWaitSemaphores			= &RenderOperationSemaphore[i];
			Presentation[i].swapchainCount			= 1;
			Presentation[i].pSwapchains				= &Swapchain;
			Presentation[i].pImageIndices			= &PresentIndex[i];
			Presentation[i].pResults				= &PresentResult[i];

		}

		isReadyToBeProcessed.store(true);

	}

	system_window::system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, const propertyvsc& aProperty) : window(aEngine, aContext, aSystemDisplay->Stage) {
		if ((aEngine == nullptr) || (aContext == nullptr) || (aSystemDisplay == nullptr)) return;

		Position = this->vsc2phy(aProperty.Position, aProperty.Size, aSystemDisplay->PositionVSC, aSystemDisplay->SizeVSC, aSystemDisplay->Size);

		FrameCount = aProperty.Swapchain.FrameCount;
		FrameRate = aProperty.Swapchain.FrameRate;
		FrameRateTimer.set(1.0 / aProperty.Swapchain.FrameRate);
		//Resolution; // Determined after window creation.

		FrameAttachmentCount = 1;
		FrameAttachmentDescription = (VkAttachmentDescription*)malloc(FrameAttachmentCount*sizeof(VkAttachmentDescription));
		FrameAttachment = (VkImageView**)malloc(FrameCount * sizeof(VkImageView*));
		for (uint32_t i = 0; i < FrameCount; i++) {
			FrameAttachment[i] = (VkImageView*)malloc(FrameAttachmentCount * sizeof(VkImageView));
			if (FrameAttachment[i] != NULL) {
				FrameAttachment[i][0] = VK_NULL_HANDLE;
			}
		}

		// Describes the format of system_window frames
		FrameAttachmentDescription[0].flags				= 0;
		FrameAttachmentDescription[0].format			= aProperty.PixelFormat;
		FrameAttachmentDescription[0].samples			= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		FrameAttachmentDescription[0].loadOp			= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;
		FrameAttachmentDescription[0].storeOp			= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE;
		FrameAttachmentDescription[0].stencilLoadOp		= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		FrameAttachmentDescription[0].stencilStoreOp	= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
		FrameAttachmentDescription[0].initialLayout		= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED; // Depends on swapchain
		FrameAttachmentDescription[0].finalLayout		= VkImageLayout::VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		// Place Null handle on views
		for (uint32_t i = 0; i < FrameCount; i++) {
			if (FrameAttachment[i] != NULL) {
				FrameAttachment[i][0] = VK_NULL_HANDLE;
			}
		}

		FrameDrawIndex = 0;

		DrawCommandCount = (uint32_t*)malloc(FrameCount * sizeof(uint32_t));
		DrawCommandList = (VkCommandBuffer**)malloc(FrameCount * sizeof(VkCommandBuffer*));

		if ((DrawCommandCount != NULL) && (DrawCommandList != NULL)) {
			for (uint32_t i = 0; i < FrameCount; i++) {
				DrawCommandCount[i] = 0;
				DrawCommandList[i] = NULL;
			}
		}

		Title = aProperty.Title;
		Size;// Convert to Physical Coordinates.
		Option = aProperty.Window;

		Display = aSystemDisplay;
		//Display->Stage->Render;

		PositionVSC = aProperty.Position;
		SizeVSC = aProperty.Size;

		NextImageSemaphoreIndex = 0;
		NextImageSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
		RenderOperationSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
		PresentResult = (VkResult*)malloc(FrameCount * sizeof(VkResult));
		PipelineStageFlags = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		assert(!((NextImageSemaphore == NULL) || (RenderOperationSemaphore == NULL) || (PresentResult == NULL)));

		memset(PresentResult, 0x00, FrameCount * sizeof(VkResult));

		// Create Window Handle.
		//this->Handle = glfwCreateWindow(aWidth, aHeight, aTitle, NULL, NULL);
		Handle = create_window_handle(Option, SizeVSC.x, SizeVSC.y, Title.ptr(), NULL, NULL);

		// Check if handle is NULL.
		if (Handle == NULL) return;

		// User pointer to forward input stream.
		glfwSetWindowUserPointer(Handle, (void*)this);

		// system_window callbacks
		glfwSetWindowPosCallback(Handle, system_window::position_callback);
		glfwSetWindowSizeCallback(Handle, system_window::size_callback);
		glfwSetWindowCloseCallback(Handle, system_window::close_callback);
		glfwSetWindowRefreshCallback(Handle, system_window::refresh_callback);
		glfwSetWindowFocusCallback(Handle, system_window::focus_callback);
		glfwSetWindowIconifyCallback(Handle, system_window::iconify_callback);
		glfwSetWindowMaximizeCallback(Handle, system_window::maximize_callback);
		glfwSetWindowContentScaleCallback(Handle, system_window::content_scale_callback);

		// framebuffer callbacks
		glfwSetFramebufferSizeCallback(Handle, system_window::framebuffer_size_callback);

		// Mouse callbacks
		glfwSetMouseButtonCallback(Handle, system_window::mouse_button_callback);
		glfwSetCursorPosCallback(Handle, system_window::cursor_position_callback);
		glfwSetCursorEnterCallback(Handle, system_window::cursor_enter_callback);
		glfwSetScrollCallback(Handle, system_window::scroll_callback);

		// Keyboard callbacks
		glfwSetKeyCallback(Handle, system_window::key_callback);
		glfwSetCharCallback(Handle, system_window::character_callback);

		// File drop
		glfwSetDropCallback(Handle, system_window::file_drop_callback);

		int lWidth, lHeight;
		glfwGetFramebufferSize(Handle, &lWidth, &lHeight);
		Resolution = uint3(lWidth, lHeight, 1u);

		// Create Surface Handle.
		VkResult Result = VkResult::VK_SUCCESS;
		Result = glfwCreateWindowSurface(Engine->handle(), Handle, NULL, &Surface);

		//TODO: Move to glfwGetPhysicalDevicePresentationSupport.
		//int isSupported = glfwGetPhysicalDevicePresentationSupport(Engine->Handle, Context->parent()->handle(), this->Context->qfi(device::qfs::PRESENT));

		// Check for presentation support for new window.
		VkBool32 isSupported = VK_FALSE;
		Result = vkGetPhysicalDeviceSurfaceSupportKHR(Context->parent()->handle(), Context->qfi(device::qfs::PRESENT), Surface, &isSupported);
		if (isSupported == VK_FALSE) {
			// Destroys suface.
			vkDestroySurfaceKHR(Engine->handle(), Surface, NULL);
			// Destroys window handle.
			glfwDestroyWindow(Handle);
			return;
		}

		// Queries Surface Capabilities.
		VkSurfaceCapabilitiesKHR SurfaceCapabilities{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Context->parent()->handle(), Surface, &SurfaceCapabilities);

		// Swapchain create info.
		CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		CreateInfo.pNext					= NULL;
		CreateInfo.flags					= 0; // Add function later?
		CreateInfo.surface					= Surface;
		CreateInfo.minImageCount			= std::clamp((uint32_t)FrameCount, SurfaceCapabilities.minImageCount, SurfaceCapabilities.maxImageCount);
		CreateInfo.imageFormat				= aProperty.PixelFormat;
		CreateInfo.imageColorSpace			= (VkColorSpaceKHR)aProperty.Swapchain.ColorSpace;
		CreateInfo.imageExtent.width		= std::clamp((uint32_t)Resolution.x, SurfaceCapabilities.minImageExtent.width, SurfaceCapabilities.maxImageExtent.width);
		CreateInfo.imageExtent.height		= std::clamp((uint32_t)Resolution.y, SurfaceCapabilities.minImageExtent.height, SurfaceCapabilities.maxImageExtent.height);
		CreateInfo.imageArrayLayers			= std::clamp((uint32_t)Resolution.z, 1u, SurfaceCapabilities.maxImageArrayLayers);
		CreateInfo.imageUsage				= (VkImageUsageFlags)aProperty.Swapchain.Usage;
		CreateInfo.imageSharingMode			= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount	= 0;
		CreateInfo.pQueueFamilyIndices		= NULL;
		CreateInfo.preTransform				= SurfaceCapabilities.currentTransform;
		CreateInfo.compositeAlpha			= (VkCompositeAlphaFlagBitsKHR)aProperty.Swapchain.CompositeAlpha;
		CreateInfo.presentMode				= (VkPresentModeKHR)aProperty.Swapchain.PresentMode;
		CreateInfo.clipped					= (VkBool32)aProperty.Swapchain.Clipped;
		CreateInfo.oldSwapchain				= VK_NULL_HANDLE;

		Result = vkCreateSwapchainKHR(Context->handle(), &CreateInfo, NULL, &Swapchain);

		Result = vkGetSwapchainImagesKHR(Context->handle(), Swapchain, &FrameCount, NULL);
		std::vector<VkImage> Image(FrameCount);
		Result = vkGetSwapchainImagesKHR(Context->handle(), Swapchain, &FrameCount, Image.data());

		Frame = new image[FrameCount];

		// Load images into texture class.
		for (uint32_t i = 0; i < FrameCount; i++) {

			Frame[i].CreateInfo.sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Frame[i].CreateInfo.pNext								= NULL;
			Frame[i].CreateInfo.flags								= 0;
			Frame[i].CreateInfo.imageType							= VkImageType::VK_IMAGE_TYPE_2D;
			Frame[i].CreateInfo.format								= CreateInfo.imageFormat;
			Frame[i].CreateInfo.extent								= { CreateInfo.imageExtent.width, CreateInfo.imageExtent.height, 1u };
			Frame[i].CreateInfo.mipLevels							= 1;
			Frame[i].CreateInfo.arrayLayers							= CreateInfo.imageArrayLayers;
			Frame[i].CreateInfo.samples								= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT; // Unknown.
			Frame[i].CreateInfo.tiling								= VkImageTiling::VK_IMAGE_TILING_LINEAR; // Unknown.
			Frame[i].CreateInfo.usage								= CreateInfo.imageUsage;
			Frame[i].CreateInfo.sharingMode							= CreateInfo.imageSharingMode;
			Frame[i].CreateInfo.queueFamilyIndexCount				= 0;
			Frame[i].CreateInfo.pQueueFamilyIndices					= NULL;
			Frame[i].CreateInfo.initialLayout						= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED; // Unknown.
			Frame[i].Handle											= Image[i];

			VkImageViewCreateInfo ImageViewCreateInfo{};

			ImageViewCreateInfo.sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ImageViewCreateInfo.pNext								= NULL;
			ImageViewCreateInfo.flags								= 0;
			ImageViewCreateInfo.image								= Image[i];
			ImageViewCreateInfo.viewType							= VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
			ImageViewCreateInfo.format								= aProperty.PixelFormat;
			ImageViewCreateInfo.components.r						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.g						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.b						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.components.a						= VkComponentSwizzle::VK_COMPONENT_SWIZZLE_IDENTITY;
			ImageViewCreateInfo.subresourceRange.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			ImageViewCreateInfo.subresourceRange.baseMipLevel		= 0;
			ImageViewCreateInfo.subresourceRange.levelCount			= 1;
			ImageViewCreateInfo.subresourceRange.baseArrayLayer		= 0;
			ImageViewCreateInfo.subresourceRange.layerCount			= 1;

			Result = vkCreateImageView(Context->handle(), &ImageViewCreateInfo, NULL, &FrameAttachment[i][0]);

			VkSemaphoreCreateInfo SemaphoreCreateInfo{};
			SemaphoreCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			SemaphoreCreateInfo.pNext = NULL;
			SemaphoreCreateInfo.flags = 0;
			vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &NextImageSemaphore[i]);
			vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &RenderOperationSemaphore[i]);

			PresentIndex[i] = i;
			PresentResult[i] = VkResult::VK_SUCCESS;
			Presentation[i].sType					= VkStructureType::VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			Presentation[i].pNext					= NULL;
			Presentation[i].waitSemaphoreCount		= 1;
			Presentation[i].pWaitSemaphores			= &RenderOperationSemaphore[i];
			Presentation[i].swapchainCount			= 1;
			Presentation[i].pSwapchains				= &Swapchain;
			Presentation[i].pImageIndices			= &PresentIndex[i];
			Presentation[i].pResults				= &PresentResult[i];
		}

		isReadyToBeProcessed.store(true);
	}
	*/

	system_window::system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, const property& aProperty) : window(aEngine, aContext, aSystemDisplay->Stage) {
		// Debug window constructor
		
		/*
		Construction List
		1 - Preinitialize Variables
		2 - Create Window Handle
		3 - Set System Window Callbacks

		*/

		this->make_default();

		// Number of back buffered frames in the swapchain.
		FrameCount = aProperty.Swapchain.FrameCount;
		// Only one color attachment.
		FrameAttachmentCount = 1;
		// FrameRate
		FrameRate = aProperty.Swapchain.FrameRate;

		Display = aSystemDisplay;

		Size		= aProperty.Size;
		Position	= aProperty.Position;
		SizeVSC.x	= (((float)aSystemDisplay->SizeVSC.x) / (aSystemDisplay->Size.x)) * Size.x;
		SizeVSC.y	= (((float)aSystemDisplay->SizeVSC.y) / (aSystemDisplay->Size.y)) * Size.y;
		PositionVSC = this->phy2vsc(Position, SizeVSC, aSystemDisplay->PositionVSC, aSystemDisplay->SizeVSC, aSystemDisplay->Size);
		Option		= aProperty.Window;
		Title		= aProperty.Title;

		Handle = create_window_handle(Option, SizeVSC.x, SizeVSC.y, Title.ptr(), NULL, NULL);

		if (Handle != NULL) {

			// User pointer to forward input stream.
			glfwSetWindowUserPointer(Handle, (void*)this);

			// system_window callbacks
			glfwSetWindowPosCallback(Handle, system_window::position_callback);
			glfwSetWindowSizeCallback(Handle, system_window::size_callback);
			glfwSetWindowCloseCallback(Handle, system_window::close_callback);
			glfwSetWindowRefreshCallback(Handle, system_window::refresh_callback);
			glfwSetWindowFocusCallback(Handle, system_window::focus_callback);
			glfwSetWindowIconifyCallback(Handle, system_window::iconify_callback);
			glfwSetWindowMaximizeCallback(Handle, system_window::maximize_callback);
			glfwSetWindowContentScaleCallback(Handle, system_window::content_scale_callback);

			// framebuffer callbacks
			glfwSetFramebufferSizeCallback(Handle, system_window::framebuffer_size_callback);

			// Mouse callbacks
			glfwSetMouseButtonCallback(Handle, system_window::mouse_button_callback);
			glfwSetCursorPosCallback(Handle, system_window::cursor_position_callback);
			glfwSetCursorEnterCallback(Handle, system_window::cursor_enter_callback);
			glfwSetScrollCallback(Handle, system_window::scroll_callback);

			// Keyboard callbacks
			glfwSetKeyCallback(Handle, system_window::key_callback);
			glfwSetCharCallback(Handle, system_window::character_callback);

			// File drop
			glfwSetDropCallback(Handle, system_window::file_drop_callback);

			int sWidth, sHeight;
			glfwGetFramebufferSize(Handle, &sWidth, &sHeight);
			Resolution = uint3(sWidth, sHeight, 1u);

			glfwCreateWindowSurface(Engine->Handle, Handle, NULL, &Surface);
		}

		if (Surface != VK_NULL_HANDLE) {
			// Queries Available formats.
			uint32_t sSurfaceFormatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(Context->parent()->handle(), Surface, &sSurfaceFormatCount, NULL);
			std::vector<VkSurfaceFormatKHR> sSurfaceFormatList(sSurfaceFormatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(Context->parent()->handle(), Surface, &sSurfaceFormatCount, sSurfaceFormatList.data());

			// Queries Surface Capabilities.
			VkSurfaceCapabilitiesKHR sSurfaceCapabilities{};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Context->parent()->handle(), Surface, &sSurfaceCapabilities);

			// Queries presentation modes.
			uint32_t sSurfacePresentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), Surface, &sSurfacePresentModeCount, NULL);
			std::vector<VkPresentModeKHR> sSurfacePresentModeList(sSurfacePresentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(aContext->parent()->handle(), Surface, &sSurfacePresentModeCount, sSurfacePresentModeList.data());

			CreateInfo.sType					= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			CreateInfo.surface					= Surface;
			CreateInfo.minImageCount			= std::clamp(FrameCount, sSurfaceCapabilities.minImageCount, sSurfaceCapabilities.maxImageCount); // change maybe later?
			CreateInfo.imageFormat				= VK_FORMAT_B8G8R8A8_SRGB;
			CreateInfo.imageColorSpace			= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
			for (uint32_t i = 0; i < sSurfaceFormatCount; i++) {
				if ((aProperty.PixelFormat == sSurfaceFormatList[i].format) && (aProperty.Swapchain.ColorSpace == sSurfaceFormatList[i].colorSpace)) {
					CreateInfo.imageFormat			= aProperty.PixelFormat;
					CreateInfo.imageColorSpace		= (VkColorSpaceKHR)aProperty.Swapchain.ColorSpace;
				}
			}
			CreateInfo.imageExtent.width		= std::clamp((uint32_t)Resolution.x, sSurfaceCapabilities.minImageExtent.width, sSurfaceCapabilities.maxImageExtent.width);
			CreateInfo.imageExtent.height		= std::clamp((uint32_t)Resolution.y, sSurfaceCapabilities.minImageExtent.height, sSurfaceCapabilities.maxImageExtent.height);
			CreateInfo.imageArrayLayers			= 1;
			if ((sSurfaceCapabilities.supportedUsageFlags & aProperty.Swapchain.Usage) == aProperty.Swapchain.Usage) {
				CreateInfo.imageUsage				= aProperty.Swapchain.Usage;
			}
			else {
				CreateInfo.imageUsage				= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			}
			CreateInfo.imageSharingMode			= VK_SHARING_MODE_EXCLUSIVE;
			CreateInfo.queueFamilyIndexCount	= 0;
			CreateInfo.pQueueFamilyIndices		= NULL;
			CreateInfo.preTransform				= sSurfaceCapabilities.currentTransform;
			if ((sSurfaceCapabilities.supportedCompositeAlpha & aProperty.Swapchain.CompositeAlpha) == aProperty.Swapchain.CompositeAlpha) {
				CreateInfo.compositeAlpha			= (VkCompositeAlphaFlagBitsKHR)aProperty.Swapchain.CompositeAlpha;
			}
			else {
				CreateInfo.compositeAlpha			= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			}
			CreateInfo.presentMode				= VK_PRESENT_MODE_MAILBOX_KHR;
			for (uint32_t i = 0; i < sSurfacePresentModeCount; i++) {
				if (sSurfacePresentModeList[i] == aProperty.Swapchain.PresentMode) {
					CreateInfo.presentMode			= (VkPresentModeKHR)aProperty.Swapchain.PresentMode;
				}
			}
			CreateInfo.clipped					= VK_TRUE;

			vkCreateSwapchainKHR(Context->handle(), &CreateInfo, NULL, &Swapchain);
		}

		if (Swapchain != VK_NULL_HANDLE) {
			vkGetSwapchainImagesKHR(Context->handle(), Swapchain, &FrameCount, NULL);
			std::vector<VkImage> sImage(FrameCount);
			vkGetSwapchainImagesKHR(Context->handle(), Swapchain, &FrameCount, sImage.data());

			FrameRateTimer.set(1.0 / FrameRate);

			FrameAttachmentDescription = (VkAttachmentDescription*)malloc(FrameAttachmentCount * sizeof(VkAttachmentDescription));
			FrameAttachment = (VkImageView**)malloc(FrameCount * sizeof(VkImageView*));
			DrawCommandCount = (uint32_t*)malloc(FrameCount * sizeof(uint32_t));
			DrawCommandList = (VkCommandBuffer**)malloc(FrameCount * sizeof(VkCommandBuffer*));
			NextImageSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
			RenderOperationSemaphore = (VkSemaphore*)malloc(FrameCount * sizeof(VkSemaphore));
			PresentIndex = (uint32_t*)malloc(FrameCount * sizeof(uint32_t));
			PresentResult = (VkResult*)malloc(FrameCount * sizeof(VkResult));
			Presentation = (VkPresentInfoKHR*)malloc(FrameCount * sizeof(VkPresentInfoKHR));
			PipelineStageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

			if (FrameAttachment != NULL) {
				for (int i = 0; i < FrameCount; i++) {
					DrawCommandCount[i] = 0;
					DrawCommandList[i] = NULL;
					FrameAttachment[i] = (VkImageView*)malloc(FrameAttachmentCount * sizeof(VkImageView));
					if (FrameAttachment[i] != NULL) {
						for (int j = 0; j < FrameAttachmentCount; j++) {
							FrameAttachment[i][j] = VK_NULL_HANDLE;
						}
					}
				}
			}

			FrameAttachmentDescription[0].format			= CreateInfo.imageFormat;
			FrameAttachmentDescription[0].samples			= VK_SAMPLE_COUNT_1_BIT;
			FrameAttachmentDescription[0].loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
			FrameAttachmentDescription[0].storeOp			= VK_ATTACHMENT_STORE_OP_STORE;
			FrameAttachmentDescription[0].stencilLoadOp		= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			FrameAttachmentDescription[0].stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
			FrameAttachmentDescription[0].initialLayout		= VK_IMAGE_LAYOUT_UNDEFINED;
			FrameAttachmentDescription[0].finalLayout		= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			for (int i = 0; i < FrameCount; i++) {
				VkImageViewCreateInfo ImageViewCreateInfo{};
				ImageViewCreateInfo.sType									= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				ImageViewCreateInfo.image									= sImage[i];
				ImageViewCreateInfo.viewType								= VK_IMAGE_VIEW_TYPE_2D;
				ImageViewCreateInfo.format									= CreateInfo.imageFormat;
				ImageViewCreateInfo.components.r							= VK_COMPONENT_SWIZZLE_IDENTITY;
				ImageViewCreateInfo.components.g							= VK_COMPONENT_SWIZZLE_IDENTITY;
				ImageViewCreateInfo.components.b							= VK_COMPONENT_SWIZZLE_IDENTITY;
				ImageViewCreateInfo.components.a							= VK_COMPONENT_SWIZZLE_IDENTITY;
				ImageViewCreateInfo.subresourceRange.aspectMask				= VK_IMAGE_ASPECT_COLOR_BIT;
				ImageViewCreateInfo.subresourceRange.baseMipLevel			= 0;
				ImageViewCreateInfo.subresourceRange.levelCount				= 1;
				ImageViewCreateInfo.subresourceRange.baseArrayLayer			= 0;
				ImageViewCreateInfo.subresourceRange.layerCount				= 1;

				vkCreateImageView(Context->handle(), &ImageViewCreateInfo, NULL, &FrameAttachment[i][0]);

				VkSemaphoreCreateInfo SemaphoreCreateInfo{};
				SemaphoreCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
				SemaphoreCreateInfo.pNext = NULL;
				SemaphoreCreateInfo.flags = 0;
				vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &NextImageSemaphore[i]);
				vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &RenderOperationSemaphore[i]);

				PresentIndex[i]		= i;
				PresentResult[i]	= VkResult::VK_SUCCESS;

				Presentation[i].sType					= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
				Presentation[i].pNext					= NULL;
				Presentation[i].waitSemaphoreCount		= 1;
				Presentation[i].pWaitSemaphores			= &RenderOperationSemaphore[i];
				Presentation[i].swapchainCount			= 1;
				Presentation[i].pSwapchains				= &Swapchain;
				Presentation[i].pImageIndices			= &PresentIndex[i];
				Presentation[i].pResults				= &PresentResult[i];

			}
		}

		isReadyToBeProcessed.store(true);

	}

	system_window::~system_window() {
		isReadyToBeProcessed.store(false);
		this->Mutex.lock();
		this->clear_all();
		this->Mutex.unlock();
	}

	void system_window::set_position(float3 aPosition) {
		Mutex.lock();
		Position = aPosition;
		PositionVSC = this->phy2vsc(Position, SizeVSC, Display->PositionVSC, Display->SizeVSC, Display->Size);
		glfwSetWindowPos(Handle, PositionVSC.x, PositionVSC.y);
		Mutex.unlock();
	}

	//VkCommandBuffer system_window::draw(rendertarget* aRenderTarget) {}

	int system_window::rtid() {
		return RTID;
	}

	void system_window::next_frame() {
		Mutex.lock();
		// I hate this...
		NextImageSemaphoreIndex = ((NextImageSemaphoreIndex == (FrameCount - 1)) ? 0 : (NextImageSemaphoreIndex + 1));
		// This function is fucking retarded when it comes to semaphores. Because I cannot know that the next frame index is before setting a signal
		// semaphore, I have iterate through an unmatched semaphore array to 
		vkAcquireNextImageKHR(Context->handle(), Swapchain, UINT64_MAX, NextImageSemaphore[NextImageSemaphoreIndex], VK_NULL_HANDLE, &FrameDrawIndex);
		Mutex.unlock();
	}

	VkSubmitInfo system_window::draw(size_t aObjectCount, object_t** aObject) {
		VkSubmitInfo DrawBatch{};
		DrawBatch.sType	= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		DrawBatch.pNext	= NULL;
		this->Mutex.lock();

		// If memory container not the same size, change size.
		if (DrawCommandCount[FrameDrawIndex] != aObjectCount) {
			void* nptr = NULL;
			if (DrawCommandList[FrameDrawIndex] == NULL) {
				nptr = malloc(aObjectCount * sizeof(VkCommandBuffer));
			}
			else if (DrawCommandCount[FrameDrawIndex] != aObjectCount) {
				nptr = realloc(DrawCommandList[FrameDrawIndex], aObjectCount * sizeof(VkCommandBuffer));
			}

			// Check if NULL.	
			assert(nptr != NULL);

			if (nptr != this->DrawCommandList[this->FrameDrawIndex]) this->DrawCommandList[this->FrameDrawIndex] = (VkCommandBuffer*)nptr;
			DrawCommandCount[FrameDrawIndex] = aObjectCount;
		}		

		// Segfault anyways if mem alloc failure.
		for (size_t i = 0; i < aObjectCount; i++) {
			DrawCommandList[FrameDrawIndex][i] = aObject[i]->draw(this);
		}

		DrawBatch.waitSemaphoreCount	= 1;
		DrawBatch.pWaitSemaphores		= &this->NextImageSemaphore[this->NextImageSemaphoreIndex];
		DrawBatch.pWaitDstStageMask		= &this->PipelineStageFlags;
		DrawBatch.commandBufferCount	= this->DrawCommandCount[this->FrameDrawIndex];
		DrawBatch.pCommandBuffers		= this->DrawCommandList[this->FrameDrawIndex];
		DrawBatch.signalSemaphoreCount	= 1;
		DrawBatch.pSignalSemaphores		= &this->RenderOperationSemaphore[this->FrameDrawIndex];
		this->Mutex.unlock();
		return DrawBatch;
	}

	VkPresentInfoKHR system_window::present_frame() {
		this->Mutex.lock();
		VkPresentInfoKHR PresentInfo = Presentation[FrameDrawIndex];
		this->Mutex.unlock();
		return PresentInfo;
	}

	void system_window::set_size(float2 aSize) {
		Mutex.lock();
		SizeVSC.x = aSize.x * ((float)Display->SizeVSC.x / Display->Size.x);
		SizeVSC.y = aSize.y * ((float)Display->SizeVSC.y / Display->Size.y);
		glfwSetWindowSize(Handle, SizeVSC.x, SizeVSC.y);
		Mutex.unlock();
		this->set_position(this->Position);
	}

	void system_window::set_resolution(uint2 aResolution) {
		Mutex.lock();
		Size.x = aResolution.x * (Display->Size.x / (float)Display->SizeVSC.x);
		Size.y = aResolution.y * (Display->Size.y / (float)Display->SizeVSC.y);
		glfwSetWindowSize(Handle, aResolution.x, aResolution.y);
		Mutex.unlock();
		this->set_position(Position);
	}

	void system_window::set_position_vsc(int2 aPositionVSC) {
		Mutex.lock();
		PositionVSC = aPositionVSC;
		Position = this->vsc2phy(PositionVSC, SizeVSC, Display->PositionVSC, Display->SizeVSC, Display->Size);
		glfwSetWindowPos(Handle, PositionVSC.x, PositionVSC.y);
		Mutex.unlock();
	}

	void system_window::set_size_vsc(int2 aSizeVSC) {
		Mutex.lock();
		Size.x = aSizeVSC.x * (Display->Size.x / (float)Display->SizeVSC.x);
		Size.y = aSizeVSC.y * (Display->Size.y / (float)Display->SizeVSC.y);
		glfwSetWindowSize(Handle, SizeVSC.x, SizeVSC.y);
		Mutex.unlock();
		this->set_position(Position);
	}

	void system_window::set_option(option::id, bool aValue) {

	}

	VkSubmitInfo system_window::update(double aDeltaTime) {
		VkSubmitInfo TransferBatch{};
		TransferBatch.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		TransferBatch.pNext					= NULL;
		TransferBatch.waitSemaphoreCount	= 0;
		TransferBatch.pWaitSemaphores		= NULL;
		TransferBatch.pWaitDstStageMask		= NULL;
		TransferBatch.commandBufferCount	= 0;
		TransferBatch.pCommandBuffers		= NULL;
		TransferBatch.signalSemaphoreCount	= 0;
		TransferBatch.pSignalSemaphores		= NULL;
		this->Mutex.lock();
		this->Time += aDeltaTime;
		this->Mutex.unlock();
		return TransferBatch;
	}

	void system_window::make_default() {
		//Engine = nullptr;
		//Context = nullptr;
		//Stage = nullptr;
		//Display = nullptr;

		InputVelocity	= float3(0.0, 0.0, 0.0);
		InputForce		= float3(0.0, 0.0, 0.0);
		Mass			= 1.0;
		Time			= logic::get_time();
		Position		= float3(0.0, 0.0, 0.0);
		Momentum		= float3(0.0, 0.0, 0.0);
		Force			= float3(0.0, 0.0, 0.0);
		DirectionX		= float3(1.0, 0.0, 0.0);
		DirectionY		= float3(0.0, 1.0, 0.0);
		DirectionZ		= float3(0.0, 0.0, 1.0);

		FrameCount = 0;
		FrameRate = 0.0;
		Resolution = uint3(0u, 0u, 0u);
		FrameAttachmentCount = 0;
		FrameAttachmentDescription = NULL;
		FrameAttachment = NULL;
		FrameDrawIndex = 0;
		DrawCommandCount = NULL;
		DrawCommandList = NULL;

		Title = "";
		Size = float2(0.0, 0.0);
		Option = window::option();

		memset(&CreateInfo, 0x00, sizeof(VkSwapchainCreateInfoKHR));
		Handle = NULL;
		Surface = VK_NULL_HANDLE;
		CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		Swapchain = VK_NULL_HANDLE;
		PositionVSC = int2(0, 0);
		SizeVSC = int2(0, 0);
		NextImageSemaphoreIndex = 0;
		NextImageSemaphore = NULL;
		RenderOperationSemaphore = NULL;
		PresentIndex = NULL;
		PresentResult = NULL;
		PipelineStageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		Presentation = NULL;
	}

	void system_window::clear_all() {
		if (Context != nullptr) {
			for (int i = 0; i < FrameCount; i++) {
				vkDestroySemaphore(Context->handle(), RenderOperationSemaphore[i], NULL);
				vkDestroySemaphore(Context->handle(), NextImageSemaphore[i], NULL);
				vkDestroyImageView(Context->handle(), FrameAttachment[i][0], NULL);
			}
			vkDestroySwapchainKHR(Context->handle(), Swapchain, NULL);
			vkDestroySurfaceKHR(Engine->handle(), Surface, NULL);
			system_window::destroy_window_handle(Handle);
		}

		free(Presentation);
		free(PresentResult);
		free(PresentIndex);
		free(RenderOperationSemaphore);
		free(NextImageSemaphore);

		if (DrawCommandList != NULL) {
			for (int i = 0; i < FrameCount; i++) {
				free(DrawCommandList[i]);
			}
		}
		free(DrawCommandList);
		free(DrawCommandCount);
		if (FrameAttachment != NULL) {
			for (int i = 0; i < FrameAttachmentCount; i++) {
				free(FrameAttachment);
			}
		}
		free(FrameAttachmentDescription);
	}

	float3 system_window::vsc2phy(int2 aRvscw, int2 aSvscw, int2 aRvscm, int2 aSvscm, float2 aSphym) {
		//tex:
		// Centers system_display and system_window.
		// $$ \vec{r}_{vsc}^{w} = \vec{r}_{scr}^{w} + \frac{\vec{s}_{scr}^{w}}{2} - \Big(\vec{r}_{scr}^{m} + \frac{\vec{s}_{scr}^{m}}{2} \Big) $$

		int2 RV1;
		RV1.x = ((aRvscw.x + (int)(((double)aSvscw.x) / 2.0)) - (aRvscm.x + (int)(((double)aSvscm.x) / 2.0)));
		RV1.y = ((aRvscw.y + (int)(((double)aSvscw.y) / 2.0)) - (aRvscm.y + (int)(((double)aSvscm.y) / 2.0)));
		float3 RV2;
		RV2.x = (aSphym.x / (float)aSvscm.x) * (float)RV1.x;
		RV2.y = -(aSphym.y / (float)aSvscm.y) * (float)RV1.y;
		RV2.z = 0.0f;
		return RV2;
	}

	int2 system_window::phy2vsc(float3 aRphyw, int2 aSvscw, int2 aRvscm, int2 aSvscm, float2 aSphym) {
		//tex:
		// Centers system_display and system_window.
		// $$ \vec{r}_{scr}^{w} = \vec{r}_{vsc}^{w} - \frac{\vec{s}_{scr}^{w}}{2} + \Big(\vec{r}_{scr}^{m} + \frac{\vec{s}_{scr}^{m}}{2} \Big) $$

		float2 RV1;
		RV1.x = ((float)aSvscm.x / aSphym.x) * (float)aRphyw.x;
		RV1.y = -((float)aSvscm.y / aSphym.y) * (float)aRphyw.y;
		int2 RV2;
		RV2.x = ((aRphyw.x - (int)(((double)aSvscw.x) / 2.0)) + (aRvscm.x + (int)(((double)aSvscm.x) / 2.0)));
		RV2.y = ((aRphyw.y - (int)(((double)aSvscw.y) / 2.0)) + (aRvscm.y + (int)(((double)aSvscm.y) / 2.0)));
		return RV2;
	}

	bool system_window::initialize() {
		if (glfwInit() == GLFW_TRUE) {
			MainThreadID = std::this_thread::get_id();
			uint32_t TempCount = 0;
			const char** Temp = glfwGetRequiredInstanceExtensions(&TempCount);

			for (uint32_t i = 0; i < TempCount; i++) {
				RequiredInstanceExtension.push_back(Temp[i]);
			}

			return true;
		}
		else {
			return false;
		}
	}

	void system_window::terminate() {
		glfwTerminate();
	}

	void system_window::poll_events() {
		glfwPollEvents();
	}

	GLFWwindow* system_window::create_window_handle(window::option aProperty, int aWidth, int aHeight, const char* aTitle, GLFWmonitor* aMonitor, GLFWwindow* aWindow) {
		GLFWwindow* Temp = NULL;
		if (MainThreadID == std::this_thread::get_id()) {
			glfwWindowHint(GLFW_RESIZABLE,			aProperty.Resizable);
			glfwWindowHint(GLFW_DECORATED,			aProperty.Decorated);
			glfwWindowHint(GLFW_FOCUSED,			aProperty.UserFocused);
			glfwWindowHint(GLFW_AUTO_ICONIFY,		aProperty.AutoMinimize);
			glfwWindowHint(GLFW_FLOATING,			aProperty.Floating);
			glfwWindowHint(GLFW_MAXIMIZED,			aProperty.Maximized);
			glfwWindowHint(GLFW_VISIBLE,			aProperty.Visible);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR,	aProperty.ScaleToMonitor);
			glfwWindowHint(GLFW_CENTER_CURSOR,		aProperty.CenterCursor);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW,		aProperty.FocusOnShow);
			//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
			glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
			glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE);

			Temp = glfwCreateWindow(aWidth, aHeight, aTitle, aMonitor, aWindow);
		}
		else {
			WindowTempData.Property = aProperty;
			WindowTempData.Width = aWidth;
			WindowTempData.Height = aHeight;
			WindowTempData.Title = aTitle;
			WindowTempData.Monitor = aMonitor;
			WindowTempData.Window = aWindow;

			WindowCreated.store(false);
			SignalCreate.store(true);
			// Wait for window to be created.
			while (!WindowCreated.load()) {}
			Temp = ReturnWindow;
		}
		return Temp;
	}

	void system_window::destroy_window_handle(GLFWwindow* aWindow) {
		if (MainThreadID == std::this_thread::get_id()) {
			glfwDestroyWindow(aWindow);
		}
		else {
			while (DestroyWindow.load() != NULL) {}
			DestroyWindow.store(aWindow);
		}
	}

	void system_window::mtcd_process_window_handle_call() {
		if (SignalCreate.load()) {
			glfwWindowHint(GLFW_RESIZABLE,			WindowTempData.Property.Resizable);
			glfwWindowHint(GLFW_DECORATED,			WindowTempData.Property.Decorated);
			glfwWindowHint(GLFW_FOCUSED,			WindowTempData.Property.UserFocused);
			glfwWindowHint(GLFW_AUTO_ICONIFY,		WindowTempData.Property.AutoMinimize);
			glfwWindowHint(GLFW_FLOATING,			WindowTempData.Property.Floating);
			glfwWindowHint(GLFW_MAXIMIZED,			WindowTempData.Property.Maximized);
			glfwWindowHint(GLFW_VISIBLE,			WindowTempData.Property.Visible);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR,	WindowTempData.Property.ScaleToMonitor);
			glfwWindowHint(GLFW_CENTER_CURSOR,		WindowTempData.Property.CenterCursor);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW,		WindowTempData.Property.FocusOnShow);
			glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
			glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE);

			ReturnWindow = glfwCreateWindow(WindowTempData.Width, WindowTempData.Height, WindowTempData.Title, WindowTempData.Monitor, WindowTempData.Window);
			WindowCreated.store(true);
			SignalCreate.store(false);
		}
		
		// Check if window needs to be destroyed.
		GLFWwindow* temp = DestroyWindow.load();
		if (temp != NULL) {
			glfwDestroyWindow(temp);
			DestroyWindow.store(NULL);
		}		
	}

	// --------------- These are the system_window callbacks --------------- //

	void system_window::position_callback(GLFWwindow* aWindowHandle, int aPosX, int aPosY) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
		Window->Mutex.lock();
		Window->Position = Window->vsc2phy(int2(aPosX, aPosY), Window->SizeVSC, Window->Display->PositionVSC, Window->Display->SizeVSC, Window->Display->Size);
		Window->PositionVSC = int2(aPosX, aPosY);
		Window->Mutex.unlock();
	}

	void system_window::size_callback(GLFWwindow* aWindowHandle, int aSizeX, int aSizeY) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
		Window->Mutex.lock();
		Window->Size.x = ((Window->Display->Size.x) / ((float)Window->Display->SizeVSC.x)) * aSizeX;
		Window->Size.y = ((Window->Display->Size.y) / ((float)Window->Display->SizeVSC.y)) * aSizeY;
		Window->SizeVSC.x = aSizeX;
		Window->SizeVSC.y = aSizeY;
		Window->Mutex.unlock();
	}

	void system_window::close_callback(GLFWwindow* aWindowHandle) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
		Window->Mutex.lock();
		Window->Option.ShouldClose = GLFW_TRUE;
		Window->Mutex.unlock();
	}

	// 
	void system_window::refresh_callback(GLFWwindow* aWindowHandle) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::focus_callback(GLFWwindow* aWindowHandle, int aFocused) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::iconify_callback(GLFWwindow* aWindowHandle, int aIconified) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::maximize_callback(GLFWwindow* aWindowHandle, int aMaximized) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);


	}

	void system_window::content_scale_callback(GLFWwindow* aWindowHandle, float aXScale, float aYScale) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
	}

	// framebuffer callbacks

	void system_window::framebuffer_size_callback(GLFWwindow* aWindowHandle, int aFrameSizeX, int aFrameSizeY) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	// Mouse callbacks

	void system_window::mouse_button_callback(GLFWwindow* aWindowHandle, int aButton, int aAction, int aMods) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
	}

	void system_window::cursor_position_callback(GLFWwindow* aWindowHandle, double aPosX, double aPosY) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::cursor_enter_callback(GLFWwindow* aWindowHandle, int aEntered) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::scroll_callback(GLFWwindow* aWindowHandle, double aOffsetX, double aOffsetY) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	void system_window::key_callback(GLFWwindow* aWindowHandle, int aKey, int aScancode, int aAction, int aMods) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);
	}

	void system_window::character_callback(GLFWwindow* aWindowHandle, unsigned int aCodepoint) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

	// File Drops

	void system_window::file_drop_callback(GLFWwindow* aWindowHandle, int aPathCount, const char** aPath) {
		system_window* Window = (system_window*)glfwGetWindowUserPointer(aWindowHandle);

	}

}
