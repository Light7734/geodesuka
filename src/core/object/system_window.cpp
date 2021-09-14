#include <geodesuka/core/object/system_window.h>

#include <algorithm>

#include <geodesuka/core/math.h>

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include <geodesuka/core/object.h>
#include <geodesuka/core/object/window.h>
#include <geodesuka/core/object/system_display.h>
#include <geodesuka/core/object/system_window.h>
#include <geodesuka/core/object/virtual_window.h>

#include <geodesuka/core/object/camera.h>
#include <geodesuka/core/object/camera2d.h>
#include <geodesuka/core/object/camera3d.h>

namespace geodesuka {
	namespace core {
		namespace object {

			// ------------------------- Instance Methods ------------------------- \\

			
			//system_window::system_window(
			//	gcl::context* aContext, gcl::frame_buffer::prop* aFrameBufferProp, prop* aWindowProp, 
			//	math::real aWidth, math::real aHeight, const char* aName,
			//	system_display* aDisplay
			//) {

			//	// Use this to forward input data to object.
			//	this->InputStreamTarget = nullptr;

			//	this->ParentDisplay = aDisplay;
			//	// The context doesn't actually get created until here.
			//	if (aContext->Handle != NULL) {
			//		// Already active context, implies sharing.
			//		this->ParentDeviceContext = aContext;
			//		// TODO: This is not safe...
			//		this->Context = new gcl::context(aContext, &aContext->Property);
			//	}
			//	else {
			//		// Inactive context.
			//		this->ParentDeviceContext = nullptr;
			//		this->Context = aContext;
			//	}

			//	// Sets up Default Framebuffer, do NOT use constructor method.
			//	this->FrameBuffer.Context = aContext;
			//	this->FrameBuffer.Property = *aFrameBufferProp;
			//	this->FrameBuffer.ID = 0;
			//	this->Property = *aWindowProp;

			//	//this->Resolution.x = aWidth;
			//	//this->Resolution.y = aHeight;
			//	this->Size = math::real2(aWidth, aHeight);
			//	this->Resolution.x = this->Size.x * ((double)this->ParentDisplay->Resolution.x / (double)this->ParentDisplay->Size.x);
			//	this->Resolution.y = this->Size.y * ((double)this->ParentDisplay->Resolution.y / (double)this->ParentDisplay->Size.y);

			//	// Copies window name.
			//	this->Name = aName;
			//	//if (aName != NULL) {
			//	//	size_t NameSize = strlen(aName);
			//	//	this->Name = (char*)malloc((NameSize + 1) * sizeof(char));
			//	//	if (this->Name != NULL) {
			//	//		memcpy(this->Name, aName, NameSize * sizeof(char));
			//	//		this->Name[NameSize] = '\0';
			//	//	}
			//	//}

			//	// Loads all context, window, and frame hints.
			//	glfwWindowHint(GLFW_RED_BITS					, this->FrameBuffer.Property.ColorBits[0]			);
			//	glfwWindowHint(GLFW_GREEN_BITS					, this->FrameBuffer.Property.ColorBits[1]			);
			//	glfwWindowHint(GLFW_BLUE_BITS					, this->FrameBuffer.Property.ColorBits[2]			);
			//	glfwWindowHint(GLFW_ALPHA_BITS					, this->FrameBuffer.Property.ColorBits[3]			);
			//	glfwWindowHint(GLFW_DEPTH_BITS					, this->FrameBuffer.Property.DepthBits				);
			//	glfwWindowHint(GLFW_STENCIL_BITS				, this->FrameBuffer.Property.StencilBits			);
			//	glfwWindowHint(GLFW_ACCUM_RED_BITS				, this->FrameBuffer.Property.AccumColorBits[0]		);
			//	glfwWindowHint(GLFW_ACCUM_GREEN_BITS			, this->FrameBuffer.Property.AccumColorBits[1]		);
			//	glfwWindowHint(GLFW_ACCUM_BLUE_BITS				, this->FrameBuffer.Property.AccumColorBits[2]		);
			//	glfwWindowHint(GLFW_ACCUM_ALPHA_BITS			, this->FrameBuffer.Property.AccumColorBits[3]		);
			//	glfwWindowHint(GLFW_AUX_BUFFERS					, this->FrameBuffer.Property.AuxBuffers				);
			//	//glfwWindowHint(GLFW_STEREO						, this->FrameBuffer.Property.Stereo					);
			//	glfwWindowHint(GLFW_DOUBLEBUFFER				, this->FrameBuffer.Property.DoubleBuffer			);
			//	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER		, this->FrameBuffer.Property.Transparent			);
			//	glfwWindowHint(GLFW_SAMPLES						, this->FrameBuffer.Property.Samples				);
			//	glfwWindowHint(GLFW_SRGB_CAPABLE				, this->FrameBuffer.Property.sRGBCapable			);
			//	glfwWindowHint(GLFW_RESIZABLE					, this->Property.Resizable							);
			//	glfwWindowHint(GLFW_DECORATED					, this->Property.Decorated							);
			//	glfwWindowHint(GLFW_FOCUSED						, this->Property.UserFocused						);
			//	glfwWindowHint(GLFW_AUTO_ICONIFY				, this->Property.AutoMinimize						);
			//	glfwWindowHint(GLFW_FLOATING					, this->Property.Floating							);
			//	glfwWindowHint(GLFW_MAXIMIZED					, this->Property.Maximized							);
			//	glfwWindowHint(GLFW_VISIBLE						, this->Property.Visible							);
			//	//glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER	, 0 );
			//	//glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING	, 0 );
			//	glfwWindowHint(GLFW_SCALE_TO_MONITOR			, this->Property.ScaleToMonitor						);
			//	glfwWindowHint(GLFW_CENTER_CURSOR				, this->Property.CenterCursor						);
			//	glfwWindowHint(GLFW_FOCUS_ON_SHOW				, this->Property.FocusOnShow						);
			//	glfwWindowHint(GLFW_CLIENT_API					, this->Context->Property.ClientAPI					);
			//	glfwWindowHint(GLFW_CONTEXT_CREATION_API		, this->Context->Property.CreationAPI				);
			//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR		, this->Context->Property.Version[0]				);
			//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR		, this->Context->Property.Version[1]				);
			//	glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS			, this->Context->Property.Robustness				);
			//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT		, this->Context->Property.ForwardCompat				);
			//	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT		, this->Context->Property.DebugMode					);
			//	glfwWindowHint(GLFW_CONTEXT_NO_ERROR			, this->Context->Property.NoError					);
			//	glfwWindowHint(GLFW_OPENGL_PROFILE				, this->Context->Property.Profile					);
			//	glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR	, this->Context->Property.ReleaseBehavior			);
			//	glfwWindowHint(GLFW_REFRESH_RATE				, this->Property.RefreshRate						);

			//	// Actually creates the context/window. Is treated the same by GLFW.
			//	if (this->ParentDeviceContext != nullptr) {
			//		this->Context->Handle = glfwCreateWindow(this->Resolution.x, this->Resolution.y, this->Name.str(), NULL/*this->ParentDisplay->Handle*/, this->ParentDeviceContext->Handle);
			//	}
			//	else {
			//		this->Context->Handle = glfwCreateWindow(this->Resolution.x, this->Resolution.y, this->Name.str(), NULL/*this->ParentDisplay->Handle*/, NULL);
			//	}

			//	glfwMakeContextCurrent(this->Context->Handle);
			//	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			//	glfwSwapInterval(0);

			//	// Should be at center of display.
			//	this->set_position(math::real3(0.0, 0.0, 0.0));

			//	// User pointer to forward input stream.
			//	glfwSetWindowUserPointer(this->Context->Handle, (void*)this);

			//	// system_window callbacks
			//	glfwSetWindowPosCallback(this->Context->Handle, system_window::position_callback);
			//	glfwSetWindowSizeCallback(this->Context->Handle, system_window::size_callback);
			//	glfwSetWindowCloseCallback(this->Context->Handle, system_window::close_callback);
			//	glfwSetWindowRefreshCallback(this->Context->Handle, system_window::refresh_callback);
			//	glfwSetWindowFocusCallback(this->Context->Handle, system_window::focus_callback);
			//	glfwSetWindowIconifyCallback(this->Context->Handle, system_window::iconify_callback);
			//	glfwSetWindowMaximizeCallback(this->Context->Handle, system_window::maximize_callback);
			//	glfwSetWindowContentScaleCallback(this->Context->Handle, system_window::content_scale_callback);

			//	// framebuffer callbacks
			//	glfwSetFramebufferSizeCallback(this->Context->Handle, system_window::framebuffer_size_callback);

			//	// Mouse callbacks
			//	glfwSetMouseButtonCallback(this->Context->Handle, system_window::mouse_button_callback);
			//	glfwSetCursorPosCallback(this->Context->Handle, system_window::cursor_position_callback);
			//	glfwSetCursorEnterCallback(this->Context->Handle, system_window::cursor_enter_callback);
			//	glfwSetScrollCallback(this->Context->Handle, system_window::scroll_callback);

			//	// Keyboard callbacks
			//	glfwSetKeyCallback(this->Context->Handle, system_window::key_callback);
			//	glfwSetCharCallback(this->Context->Handle, system_window::character_callback);

			//	// File drop
			//	glfwSetDropCallback(this->Context->Handle, system_window::file_drop_callback);
			//	
			//	//glfwGetWindowFrameSize(this->Context->Handle, system_window::framebuffer_size_callback);

			//	// Should create the first framebuffer with the newly active context.
			//}

			system_window::system_window(gcl::device_context* aDeviceContext, system_display* aDisplay, gcl::frame_buffer::prop aFrameBufferProp, prop aWindowProp,
				math::real3 aPosition, math::real2 aSize, util::text aTitle) {
				// Check for required extensions, if not met, terminate window
				// creation.

				this->isValid = true;
				if (this->isValid) {

					for (size_t i = 0; i < RequiredExtension.size(); i++) {
						// Extension not found, terminate window creation.
						if (!aDeviceContext->ext_supported(RequiredExtension[i])) {
							this->isValid = false;
							break;
						}
					}

					// Required extension found and validated.
					if (this->isValid) this->ParentDC = aDeviceContext;
				}

				if (this->isValid) {
					// Get Parent Display.
					this->ParentDisplay = aDisplay;
					if (this->ParentDisplay == nullptr) this->isValid = false;
				}

				// Create OS window Stage.
				if (this->isValid) {

					// Loads window properties.
					this->Property = aWindowProp;
					// Loads all context, window, and frame hints.
					//glfwWindowHint(GLFW_RED_BITS					, this->FrameBuffer.Property.ColorBits[0]			);
					//glfwWindowHint(GLFW_GREEN_BITS					, this->FrameBuffer.Property.ColorBits[1]			);
					//glfwWindowHint(GLFW_BLUE_BITS					, this->FrameBuffer.Property.ColorBits[2]			);
					//glfwWindowHint(GLFW_ALPHA_BITS					, this->FrameBuffer.Property.ColorBits[3]			);
					//glfwWindowHint(GLFW_DEPTH_BITS					, this->FrameBuffer.Property.DepthBits				);
					//glfwWindowHint(GLFW_STENCIL_BITS				, this->FrameBuffer.Property.StencilBits			);
					//glfwWindowHint(GLFW_ACCUM_RED_BITS				, this->FrameBuffer.Property.AccumColorBits[0]		);
					//glfwWindowHint(GLFW_ACCUM_GREEN_BITS			, this->FrameBuffer.Property.AccumColorBits[1]		);
					//glfwWindowHint(GLFW_ACCUM_BLUE_BITS				, this->FrameBuffer.Property.AccumColorBits[2]		);
					//glfwWindowHint(GLFW_ACCUM_ALPHA_BITS			, this->FrameBuffer.Property.AccumColorBits[3]		);
					//glfwWindowHint(GLFW_AUX_BUFFERS					, this->FrameBuffer.Property.AuxBuffers				);
					////glfwWindowHint(GLFW_STEREO						, this->FrameBuffer.Property.Stereo					);
					//glfwWindowHint(GLFW_DOUBLEBUFFER				, this->FrameBuffer.Property.DoubleBuffer			);
					//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER		, this->FrameBuffer.Property.Transparent			);
					//glfwWindowHint(GLFW_SAMPLES						, this->FrameBuffer.Property.Samples				);
					//glfwWindowHint(GLFW_SRGB_CAPABLE				, this->FrameBuffer.Property.sRGBCapable			);
					glfwWindowHint(GLFW_RESIZABLE					, this->Property.Resizable							);
					glfwWindowHint(GLFW_DECORATED					, this->Property.Decorated							);
					glfwWindowHint(GLFW_FOCUSED						, this->Property.UserFocused						);
					glfwWindowHint(GLFW_AUTO_ICONIFY				, this->Property.AutoMinimize						);
					glfwWindowHint(GLFW_FLOATING					, this->Property.Floating							);
					glfwWindowHint(GLFW_MAXIMIZED					, this->Property.Maximized							);
					glfwWindowHint(GLFW_VISIBLE						, this->Property.Visible							);
					//glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER	, 0 );
					//glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING	, 0 );
					glfwWindowHint(GLFW_SCALE_TO_MONITOR			, this->Property.ScaleToMonitor						);
					glfwWindowHint(GLFW_CENTER_CURSOR				, this->Property.CenterCursor						);
					glfwWindowHint(GLFW_FOCUS_ON_SHOW				, this->Property.FocusOnShow						);
					glfwWindowHint(GLFW_CLIENT_API					, GLFW_NO_API										);
					//glfwWindowHint(GLFW_CONTEXT_CREATION_API		, this->Context->Property.CreationAPI				);
					//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR		, this->Context->Property.Version[0]				);
					//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR		, this->Context->Property.Version[1]				);
					//glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS			, this->Context->Property.Robustness				);
					//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT		, this->Context->Property.ForwardCompat				);
					//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT		, this->Context->Property.DebugMode					);
					//glfwWindowHint(GLFW_CONTEXT_NO_ERROR			, this->Context->Property.NoError					);
					//glfwWindowHint(GLFW_OPENGL_PROFILE				, this->Context->Property.Profile					);
					//glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR	, this->Context->Property.ReleaseBehavior			);
					glfwWindowHint(GLFW_REFRESH_RATE				, this->Property.RefreshRate						);


					this->Size = aSize;
					this->Resolution.x = this->Size.x * ((double)this->ParentDisplay->Resolution.x / (double)this->ParentDisplay->Size.x);
					this->Resolution.y = this->Size.y * ((double)this->ParentDisplay->Resolution.y / (double)this->ParentDisplay->Size.y);
					this->Handle = glfwCreateWindow(this->Resolution.x, this->Resolution.y, "I hate OpenGL", NULL, NULL);
					
					if (this->Handle != NULL) {

						this->set_position(aPosition);
						// Get frame_buffer size. Will be same as SizeSC except on retina display. (Mac is Garbage)

						// User pointer to forward input stream.
						glfwSetWindowUserPointer(this->Handle, (void*)this);

						// system_window callbacks
						glfwSetWindowPosCallback(this->Handle, system_window::position_callback);
						glfwSetWindowSizeCallback(this->Handle, system_window::size_callback);
						glfwSetWindowCloseCallback(this->Handle, system_window::close_callback);
						glfwSetWindowRefreshCallback(this->Handle, system_window::refresh_callback);
						glfwSetWindowFocusCallback(this->Handle, system_window::focus_callback);
						glfwSetWindowIconifyCallback(this->Handle, system_window::iconify_callback);
						glfwSetWindowMaximizeCallback(this->Handle, system_window::maximize_callback);
						glfwSetWindowContentScaleCallback(this->Handle, system_window::content_scale_callback);

						// framebuffer callbacks
						glfwSetFramebufferSizeCallback(this->Handle, system_window::framebuffer_size_callback);

						// Mouse callbacks
						glfwSetMouseButtonCallback(this->Handle, system_window::mouse_button_callback);
						glfwSetCursorPosCallback(this->Handle, system_window::cursor_position_callback);
						glfwSetCursorEnterCallback(this->Handle, system_window::cursor_enter_callback);
						glfwSetScrollCallback(this->Handle, system_window::scroll_callback);

						// Keyboard callbacks
						glfwSetKeyCallback(this->Handle, system_window::key_callback);
						glfwSetCharCallback(this->Handle, system_window::character_callback);

						// File drop
						glfwSetDropCallback(this->Handle, system_window::file_drop_callback);

						//glfwGetWindowFrameSize(this->Context->Handle, system_window::framebuffer_size_callback);

					}

					// If OS window creation failed, abort following steps.
					if (this->Handle == NULL) this->isValid = false;


				}

				// Create Vulkan Surface.
				if (this->isValid) {
					// Creates respective Vulkan surface with operating system window.
					this->ErrorCode = glfwCreateWindowSurface(*this->ParentDC->get_inst(), this->Handle, NULL, &this->Surface);
					// If Vulkan Surface not created from OS window, abort following operations.
					if (this->ErrorCode != VK_SUCCESS) this->isValid = false;
				}

				// Create Swapchain.
				if (this->isValid) {

					// Queuries for surface capabilities.
					this->ErrorCode = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->ParentDC->get_pdevice()->get_handle(), this->Surface, &this->SurfaceCapabilities);

					// Queries for Surface Formats.
					uint32_t FormatCount = 0;
					vkGetPhysicalDeviceSurfaceFormatsKHR(this->ParentDC->get_pdevice()->get_handle(), this->Surface, &FormatCount, NULL);
					std::vector<VkSurfaceFormatKHR> Format(FormatCount);
					if (FormatCount > 0) {
						vkGetPhysicalDeviceSurfaceFormatsKHR(this->ParentDC->get_pdevice()->get_handle(), this->Surface, &FormatCount, Format.data());
					}

					// Queries for Presentation Modes.
					uint32_t PresentModeCount = 0;
					vkGetPhysicalDeviceSurfacePresentModesKHR(this->ParentDC->get_pdevice()->get_handle(), this->Surface, &PresentModeCount, NULL);
					std::vector<VkPresentModeKHR> PresentMode(PresentModeCount);
					if (PresentModeCount > 0) {
						vkGetPhysicalDeviceSurfacePresentModesKHR(this->ParentDC->get_pdevice()->get_handle(), this->Surface, &PresentModeCount, PresentMode.data());
					}
					

					/*
					* User Control:
					* Min Image Count
					* Image Format
					* Image Color Space
					* Image Layers?
					* Image Usage
					* Presentation Mode
					*/

					FrameBuffer.Property = aFrameBufferProp;

					// Gets appropriate resolution.
					int FrameBufferResolutionX, FrameBufferResolutionY;
					glfwGetFramebufferSize(this->Handle, &FrameBufferResolutionX, &FrameBufferResolutionY);

					// Make sure Image Count is within range.
					this->FrameBuffer.Property.Count			= std::clamp(this->FrameBuffer.Property.Count, this->SurfaceCapabilities.minImageCount, this->SurfaceCapabilities.maxImageCount);
					//FrameBuffer.Property.Format				= VK_FORMAT_R8G8B8A8_SRGB;
					//FrameBuffer.Property.ColorSpace			= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
					this->FrameBuffer.Property.Extent2D.width	= std::clamp((uint32_t)FrameBufferResolutionX, this->SurfaceCapabilities.minImageExtent.width, this->SurfaceCapabilities.maxImageExtent.width);
					this->FrameBuffer.Property.Extent2D.height	= std::clamp((uint32_t)FrameBufferResolutionY, this->SurfaceCapabilities.minImageExtent.height, this->SurfaceCapabilities.maxImageExtent.height);
					this->FrameBuffer.Resolution				= { (math::natural)FrameBufferResolutionY, (math::natural)FrameBufferResolutionY };

					// validate format.
					bool isValidFormat = false;
					bool isValidColorSpace = false;
					for (size_t i = 0; i < Format.size(); i++) {
						if (FrameBuffer.Property.Format == Format[i].format) {
							isValidFormat = true;
						}
						if (FrameBuffer.Property.ColorSpace == Format[i].colorSpace) {
							isValidColorSpace = true;
						}
					}

					bool isValidPresentMode = false;
					for (size_t i = 0; i < PresentMode.size(); i++) {
						if (Property.PresentationMode == PresentMode[i]) {
							isValidPresentMode = true;
						}
					}

					if (!isValidFormat) {
						std::cout << "Error: Unsupported format" << std::endl;
					}

					if (!isValidColorSpace) {
						std::cout << "Error: Unsupported color space" << std::endl;
					}

					if (!isValidPresentMode) {
						std::cout << "Error: Unsupported presentation mode" << std::endl;
					}

					this->SwapChainProp.sType						= VkStructureType::VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
					this->SwapChainProp.pNext						= NULL;
					this->SwapChainProp.flags						= 0;
					this->SwapChainProp.surface						= this->Surface;
					this->SwapChainProp.minImageCount				= FrameBuffer.Property.Count;
					this->SwapChainProp.imageFormat					= FrameBuffer.Property.Format;
					this->SwapChainProp.imageColorSpace				= FrameBuffer.Property.ColorSpace;
					this->SwapChainProp.imageExtent					= FrameBuffer.Property.Extent2D;
					this->SwapChainProp.imageArrayLayers			= 1; // Number of Layers per Vulkan Image.
					this->SwapChainProp.imageUsage					= VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // 
					if (true/*If GraphicsQueue == PresentationQueue*/) {
						// Assumes that Queue has Graphcis and Presentation Capability. (Fix This Later)
						this->SwapChainProp.imageSharingMode			= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
						this->SwapChainProp.queueFamilyIndexCount		= 0;
						this->SwapChainProp.pQueueFamilyIndices			= NULL;
					}
					else {
						this->SwapChainProp.imageSharingMode			= VkSharingMode::VK_SHARING_MODE_CONCURRENT;
						this->SwapChainProp.queueFamilyIndexCount		= 2;
						this->SwapChainProp.pQueueFamilyIndices			= NULL; // Change to QueueFamily Indices
					}
					this->SwapChainProp.preTransform				= this->SurfaceCapabilities.currentTransform; // Matches it with current surface transform. (Fucking stupid option)
					this->SwapChainProp.compositeAlpha				= VkCompositeAlphaFlagBitsKHR::VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; // 
					this->SwapChainProp.presentMode					= this->Property.PresentationMode; // Presentation Mode. 
					this->SwapChainProp.clipped						= VK_TRUE; // Pixels obscured by other windows will not be drawn.
					this->SwapChainProp.oldSwapchain				= VK_NULL_HANDLE; // No old swapchain in window creation. (Use for window resizing)

					this->ErrorCode = vkCreateSwapchainKHR(this->ParentDC->get_handle(), &this->SwapChainProp, NULL, &this->SwapChain);

					uint32_t lImageCount;
					std::vector<VkImage> Image;
					vkGetSwapchainImagesKHR(this->ParentDC->get_handle(), this->SwapChain, &lImageCount, NULL);
					Image.resize(lImageCount);
					vkGetSwapchainImagesKHR(this->ParentDC->get_handle(), this->SwapChain, &lImageCount, Image.data());
					//this->Texture.resize(lImageCount);

					for (size_t i = 0; i < Image.size(); i++) {
						VkImageCreateInfo tempci;
						tempci.sType					= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
						tempci.pNext					= NULL;
						tempci.flags					= 0;
						tempci.imageType				= VkImageType::VK_IMAGE_TYPE_2D;
						tempci.format					= FrameBuffer.Property.Format;
						tempci.extent					= { FrameBuffer.Property.Extent2D.width, FrameBuffer.Property.Extent2D.height, 1 };
						tempci.mipLevels				= 1;
						tempci.arrayLayers				= 1;
						tempci.samples					= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
						tempci.tiling					= VkImageTiling::VK_IMAGE_TILING_OPTIMAL;
						tempci.usage					= VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
						tempci.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
						tempci.queueFamilyIndexCount	= 0;
						tempci.pQueueFamilyIndices		= NULL;
						tempci.initialLayout			= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
						// Just stores swapchain images.
						this->Texture.push_back(gcl::texture(this, this->ParentDC, Image[i], tempci));
					}
				}
			}

			system_window::~system_window() {
				// Destroys 
				if (this->isValid) {
					// Destroys swapchain.
					vkDestroySwapchainKHR(this->ParentDC->get_handle(), this->SwapChain, NULL);
					// Destroys suface.
					vkDestroySurfaceKHR(*this->ParentDC->get_inst(), this->Surface, NULL);
					// Destroys window handle.
					glfwDestroyWindow(this->Handle);
				}
			}

			math::integer system_window::input(const hid::keyboard& aKeyboard) {
				return 0;
			}

			math::integer system_window::input(const hid::mouse& aMouse) {
				return 0;
			}

			math::integer system_window::update(math::real aDt) {
				return 0;
			}

			math::integer system_window::draw(system_display* aTargetSystemDisplay) {
				// To be consistent with the api, this represents a system_window
				// defining how it will be drawn to a system_display.
				// I. Make Context Current.
				//glfwMakeContextCurrent(this->Context->Handle);
				////gladLoadGL(glfwGetProcAddress);
				//gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
				//glClear(GL_COLOR_BUFFER_BIT);
				////glClearColor(0.0, 0.0, 0.0, 0.0);

				//// II. flush all previously issued graphics commands.
				//this->Context->finish();
				//// III. swap buffers to present to display.
				//glfwSwapBuffers(this->Context->Handle);
				return 0;
			}

			math::integer system_window::draw(system_window* aTargetSystemWindow) {
				// Perhaps just copy frame_buffer contents to 
				return 0;
			}

			math::integer system_window::draw(virtual_window* aTargetVirtualWindow) {
				return 0;
			}

			math::integer system_window::draw(camera2d* aTargetCamera2D) { return 0; }

			math::integer system_window::draw(camera3d* aTargetCamera3D) { return 0; }

			math::integer system_window::draw(object_t* aObject) {
				if ((object_t*)this == aObject) return -1;
				return aObject->draw(this);
			}

			math::integer system_window::set_position(math::real3 aPosition) {
				//tex:
				// Centers system_display and system_window.
				// $$ \vec{r}_{tmp} = \vec{r}_{sc}^{w} + \frac{\vec{s}_{sc}^{w}}{2} - \Big(\vec{r}_{sc}^{m} + \frac{\vec{s}_{sc}^{m}}{2} \Big) $$
				// $$ x_{tmp} = $$
				
				// Converts Direction and length.
				this->Position = aPosition;
				math::integer2 r_tmp = math::integer2(
					(math::integer)(this->Position.x * (((math::real)(ParentDisplay->Resolution.x)) / (ParentDisplay->Size.x))),
					(math::integer)(-this->Position.y * (((math::real)(ParentDisplay->Resolution.y)) / (ParentDisplay->Size.y)))
				);

				// Compensate for shift.
				PositionSC = 
					r_tmp
					- math::integer2(((double)Resolution.x / 2.0), ((double)Resolution.y / 2.0))
					+ ParentDisplay->PositionSC
					+ math::integer2(((double)ParentDisplay->Resolution.x / 2.0), ((double)ParentDisplay->Resolution.y / 2.0));

				glfwSetWindowPos(this->Handle, this->PositionSC.x, this->PositionSC.y);
				return 0;
			}

			math::integer system_window::set_size(math::real2 aSize) {
				this->Resolution.x = aSize.x * ((double)this->ParentDisplay->Resolution.x/(double)this->ParentDisplay->Size.x);
				this->Resolution.y = aSize.y * ((double)this->ParentDisplay->Resolution.y / (double)this->ParentDisplay->Size.y);
				glfwSetWindowSize(this->Handle, this->Resolution.x, this->Resolution.y);
				// TODO: make more efficient
				this->set_position(this->Position);
				return 0;
			}

			math::integer system_window::set_resolution(math::natural2 aResolution) {
				this->Size.x = aResolution.x * ((double)this->ParentDisplay->Size.x / (double)this->ParentDisplay->Resolution.x);
				this->Size.y = aResolution.y * ((double)this->ParentDisplay->Size.y / (double)this->ParentDisplay->Resolution.y);
				glfwSetWindowSize(this->Handle, aResolution.x, aResolution.y);
				// TODO: make more efficient
				this->set_position(this->Position);
				return 0;
			}

			math::integer system_window::set_parent_display(system_display* aParentDisplay) {
				this->ParentDisplay = aParentDisplay;
				return 0;
			}

			math::integer system_window::set_input_stream_target(object_t* aTargetObject) {
				this->InputStreamTarget = aTargetObject;
				return 0;
			}

			// --------------- These are the system_window callbacks --------------- //

			// system_window callbacks

			void system_window::position_callback(GLFWwindow* ContextHandle, int PosX, int PosY) {
				//tex:
				// Centers system_display and system_window.
				// $$ \vec{r}_{tmp} = \vec{r}_{sc}^{w} + \frac{\vec{s}_{sc}^{w}}{2} - \Big(\vec{r}_{sc}^{m} + \frac{\vec{s}_{sc}^{m}}{2} \Big) $$
				// $$ x_{tmp} = $$

				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
				
				// Shifts to new origin at parent display center.
				math::integer2 r_tmp =
					math::integer2(PosX, PosY)
					+ math::integer2((double)Win->Resolution.x / 2.0, (double)Win->Resolution.y / 2.0)
					- Win->ParentDisplay->PositionSC
					- math::integer2((double)Win->ParentDisplay->Resolution.x / 2.0, (double)Win->ParentDisplay->Resolution.y / 2.0);

				// Converts to physical position on display (meters)
				Win->Position = math::real3(
					(double)r_tmp.x * ((double)Win->ParentDisplay->Size.x / (double)Win->ParentDisplay->Resolution.x),
					-(double)r_tmp.y * ((double)Win->ParentDisplay->Size.y / (double)Win->ParentDisplay->Resolution.y),
					0.0
				);
				
				// Debug position.
				//std::cout << Win->Name << ".Position =\t" << Win->Position.x << ", " << Win->Position.y << std::endl;
			}

			void system_window::size_callback(GLFWwindow* ContextHandle, int SizeX, int SizeY) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);			

				Win->Resolution.x = SizeX;
				Win->Resolution.y = SizeY;

			}

			void system_window::close_callback(GLFWwindow* ContextHandle) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
				std::cout << Win->Name.str() << " wants to fucking close" << std::endl;
				Win->CloseMe = true;
			}

			void system_window::refresh_callback(GLFWwindow* ContextHandle) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::focus_callback(GLFWwindow* ContextHandle, int Focused) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::iconify_callback(GLFWwindow* ContextHandle, int Iconified) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::maximize_callback(GLFWwindow* ContextHandle, int Maximized) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);


			}

			void system_window::content_scale_callback(GLFWwindow* ContextHandle, float XScale, float YScale) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
			}

			// framebuffer callbacks

			void system_window::framebuffer_size_callback(GLFWwindow* ContextHandle, int FrameSizeX, int FrameSizeY) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			// Mouse callbacks

			void system_window::mouse_button_callback(GLFWwindow* ContextHandle, int Button, int Action, int Mods) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
			}

			void system_window::cursor_position_callback(GLFWwindow* ContextHandle, double PosX, double PosY) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::cursor_enter_callback(GLFWwindow* ContextHandle, int Entered) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::scroll_callback(GLFWwindow* ContextHandle, double OffsetX, double OffsetY) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			void system_window::key_callback(GLFWwindow* ContextHandle, int Key, int Scancode, int Action, int Mods) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
			}

			void system_window::character_callback(GLFWwindow* ContextHandle, unsigned int Codepoint) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

			// File Drops

			void system_window::file_drop_callback(GLFWwindow* ContextHandle, int PathCount, const char** Path) {
				system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

			}

		}
	}
}




//
//system_window::system_window() {
//	this->Property = this->m_default_window_properties();
//	//this->CTX = NULL;
//
//	this->Title = NULL;
//
//	this->Time = 0.0f;
//	this->PositionVS = { 0, 0 };
//	this->SizeVS = { 0, 0 };
//
//	this->SwapInterval = 1;
//	this->PositionPX = { 0, 0 };
//	this->SizePX = { 0, 0 };
//	this->FrameColor = { 0.0f, 0.0f, 0.0f, 0.0f };
//
//	this->ExitCall = false;
//	this->RefreshCall = false;
//
//	this->LockBoundary = false;
//	this->LowBound = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//	this->HighBound = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//
//	this->LockAspectRatio = false;
//	this->AspectRatio = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//
//	this->PositionMM = { 0.0f, 0.0f };
//	this->SizeMM = { 0.0f, 0.0f };
//}
//
//system_window::~system_window() {
//
//}
//
//void system_window::set_context(integer ContextAPI, integer ContextMajor, integer ContextMinor, integer ContextProfile, integer ContextForwardCompat, integer ContextDebugMode) {
//	Property.Context.ClientAPI = ContextAPI;
//	Property.Context.Version = { ContextMajor, ContextMinor };
//	Property.Context.Profile = ContextProfile;
//	Property.Context.ForwardCompat = ContextForwardCompat;
//	Property.Context.DebugMode = ContextDebugMode;
//}
//
//integer system_window::create(integer WindowWidth, integer WindowHeight, const char* WindowTitle, GLFWmonitor* WindowDisplay, GLFWwindow* WindowShare) {
//	this->annihilate();
//
//	if ((WindowWidth > 0) && (WindowHeight > 0)) { SizeVS = { WindowWidth, WindowHeight }; }
//	if (WindowTitle != NULL) { this->set_title(WindowTitle); }
//	//if (WindowDisplay != nullptr) { Display = WindowDisplay; }
//	//if (WindowShare != nullptr) { SharingContext = WindowShare->Context; }
//
//	// --------------- Window Creation --------------- //
//
//	CTX = gcl::create_ctx(&Property, SizeVS.x, SizeVS.y, Title, WindowDisplay, WindowShare);
//
//	if (Property.Minimized) {
//		glfwIconifyWindow(CTX);
//	}
//	glfwWindowHint();
//	// Minimized > FullScreen > Maximized
//	if (!(ParentDisplay != NULL) && !Property.Maximized && !Property.Minimized) {
//		glfwGetWindowSize(CTX, &SizeVS.x, &SizeVS.y);
//		glfwGetFramebufferSize(CTX, &SizePX.x, &SizePX.y);
//		glfwSetWindowPos(CTX, PositionVS.x, PositionVS.y);
//	}
//
//	if (CTX != NULL) {
//		void* nptr = reinterpret_cast<void*>(this);
//		glfwSetWindowUserPointer(CTX, nptr);
//	}
//
//	//if (Display != nullptr) {
//	//	PositionMM = {
//	//		((float)PositionVS.x + (float)SizeVS.x / 2.0f - (float)Display->Position.x - (float)Display->Size.x / 2.0f)*((float)Display->SizeMM.x / (float)Display->Size.x),
//	//		((float)PositionVS.y + (float)SizeVS.y / 2.0f - (float)Display->Position.y - (float)Display->Size.y / 2.0f)*((float)Display->SizeMM.y / (float)Display->Size.y)
//	//	};
//	//	SizeMM = {
//	//		(float)SizeVS.x*(float)Display->SizeMM.x / (float)Display->Size.x,
//	//		(float)SizeVS.y*(float)Display->SizeMM.y / (float)Display->Size.y
//	//	};
//	//}
//
//	return 0;
//}
//
//integer system_window::annihilate() {
//	if (CTX != NULL) {
//		glfwDestroyWindow(CTX); CTX = NULL;
//	}
//	return 0;
//}
//
//integer system_window::set_title(const char* Str) {
//	if (Str == NULL) { return true; }
//	if (Title != NULL) {
//		free(Title); Title = NULL;
//	}
//
//	Title = (char*)malloc((strlen(Str) + 1) * sizeof(char));
//	if (Title != NULL) {
//		memcpy(Title, Str, strlen(Str) * sizeof(char));
//		Title[strlen(Str)] = '\0';
//	}
//
//	if ((CTX != NULL) && (Title != NULL)) {
//		glfwSetWindowTitle(CTX, Title);
//	}
//	return 0;
//}
//
//integer system_window::set_pos(integer x, integer y) {
//	if (ParentDisplay != NULL) { return -1; }
//	glfwSetWindowPos(CTX, x, y);
//	glfwGetWindowPos(CTX, &PositionVS.x, &PositionVS.y);
//	//if (Display != nullptr) {
//	//	PositionMM = {
//	//		((float)PositionVS.x + (float)SizeVS.x / 2.0f - (float)Display->Position.x - (float)Display->Size.x / 2.0f)*((float)Display->SizeMM.x / (float)Display->Size.x),
//	//		((float)PositionVS.y + (float)SizeVS.y / 2.0f - (float)Display->Position.y - (float)Display->Size.y / 2.0f)*((float)Display->SizeMM.y / (float)Display->Size.y)
//	//	};
//	//}
//	return 0;
//}
//
//integer system_window::set_size(integer w, integer h) {
//	if (ParentDisplay != NULL) { return -1; }
//	glfwSetWindowSize(CTX, w, h);
//	glfwGetWindowSize(CTX, &SizeVS.x, &SizeVS.y);
//	//if (Display != nullptr) {
//	//	SizeMM = {
//	//		(float)SizeVS.x*(float)Display->SizeMM.x / (float)Display->Size.x,
//	//		(float)SizeVS.y*(float)Display->SizeMM.y / (float)Display->Size.y
//	//	};
//	//}
//	return 0;
//}
//
//integer system_window::set_size_limits(integer x1, integer y1, integer x2, integer y2) {
//	LowBound = { x1, y1 }; HighBound = { x2, y2 };
//	if (LockBoundary) {
//		glfwSetWindowSizeLimits(CTX, x1, y1, x2, y2);
//	}
//	else {
//		glfwSetWindowSizeLimits(CTX, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
//	}
//	return 0;
//}
//
//integer system_window::set_aspect_ratio(integer Numerator, integer Denominator) {
//	AspectRatio = { Numerator, Denominator };
//	if (LockAspectRatio) {
//		glfwSetWindowAspectRatio(CTX, Numerator, Denominator);
//	}
//	else {
//		glfwSetWindowAspectRatio(CTX, GLFW_DONT_CARE, GLFW_DONT_CARE);
//	}
//	return 0;
//}
//
//integer system_window::swap_interval(integer NewInterval) {
//	glfwSwapInterval(NewInterval);
//	return 0;
//}
//
//integer system_window::swap_buffers() {
//	glfwSwapBuffers(CTX);
//	return 0;
//}
//
//
//integer system_window::set(integer pname, integer pval) {
//	if (this->CTX == NULL) {
//		return this->m_set_hint(pname, pval);
//	}
//	else {
//		if (this->m_set_attrib(pname, pval) == 0) {
//			glfwSetWindowAttrib(this->CTX, pname, pval);
//		}
//		else {
//			switch (pname) {
//			default: return -1;
//			case GLFW_FOCUSED:
//				if ((Property.UserFocused == GLFW_FALSE) && (pval == GLFW_TRUE)) {
//					glfwFocusWindow(CTX);
//					Property.UserFocused = GLFW_TRUE;
//				}
//				break;
//			case GLFW_VISIBLE:
//				if (Property.Visible != pval) {
//					if (pval) {
//						glfwShowWindow(CTX);
//					}
//					else {
//						glfwHideWindow(CTX);
//					}
//					Property.Visible = pval;
//				}
//				break;
//			case GLFW_ICONIFIED:
//				if (this->Property.Minimized != pval) {
//					if (pval) {
//						glfwIconifyWindow(this->CTX);
//					}
//					else {
//						glfwRestoreWindow(this->CTX);
//					}
//				}
//				break;
//			case GLFW_MAXIMIZED:
//				if (this->Property.Maximized != pval) {
//					if (pval) {
//						glfwMaximizeWindow(this->CTX);
//					}
//					else {
//						glfwRestoreWindow(this->CTX);
//					}
//				}
//				break;
//			}
//
//		}
//	}
//	return 0;
//}
//
//integer system_window::get(integer pname) {
//	if (CTX == NULL) {
//		return this->m_get_hint(pname);
//	}
//	return -1;
//}
//
//gl_frame_properties system_window::m_default_frame_properties() {
//	gl_frame_properties temp;
//	temp.ColorBits.r				= 8							   ;
//	temp.ColorBits.g				= 8							   ;
//	temp.ColorBits.b				= 8							   ;
//	temp.ColorBits.a				= 8							   ;
//	temp.DepthBits					= 24						   ;
//	temp.StencilBits				= 8							   ;
//	temp.AccumColorBits.r			= 0							   ;
//	temp.AccumColorBits.g			= 0							   ;
//	temp.AccumColorBits.b			= 0							   ;
//	temp.AccumColorBits.a			= 0							   ;
//	temp.AuxBuffers					= 0							   ;
//	temp.Stereo						= GLFW_FALSE				   ;
//	temp.DoubleBuffer				= GLFW_TRUE					   ;
//	temp.Transparent				= GLFW_FALSE				   ;
//	temp.Samples					= 0							   ;
//	temp.sRGBCapable				= GLFW_FALSE				   ;
//	return temp;
//}
//
//gl_context_properties system_window::m_default_context_properties() {
//	gl_context_properties temp;
//	temp.ClientAPI						= GLFW_OPENGL_API			   ;
//	temp.CreationAPI					= GLFW_NATIVE_CONTEXT_API	   ;
//	temp.Version.x						= 1							   ;
//	temp.Version.y						= 0							   ;
//	temp.Robustness						= GLFW_NO_ROBUSTNESS		   ;
//	temp.ForwardCompat					= GLFW_FALSE				   ;
//	temp.DebugMode						= GLFW_FALSE				   ;
//	temp.NoError						= GLFW_FALSE				   ;
//	temp.Profile						= GLFW_OPENGL_ANY_PROFILE	   ;
//	temp.ReleaseBehavior				= GLFW_ANY_RELEASE_BEHAVIOR	   ;
//	return temp;
//}
//
//gl_window_properties system_window::m_default_window_properties() {
//	gl_window_properties temp;
//	temp.Frame = this->m_default_frame_properties();
//	temp.Resizable								= GLFW_TRUE					   ;
//	temp.Decorated								= GLFW_TRUE					   ;
//	temp.UserFocused							= GLFW_TRUE					   ;
//	temp.AutoMinimize							= GLFW_TRUE					   ;
//	temp.Floating								= GLFW_FALSE				   ;
//	temp.Maximized								= GLFW_FALSE				   ;
//	temp.Minimized								= GLFW_FALSE				   ;
//	temp.Visible								= GLFW_TRUE					   ;
//	temp.ScaleToMonitor							= GLFW_FALSE				   ;
//	temp.CenterCursor							= GLFW_TRUE					   ;
//	temp.FocusOnShow							= GLFW_TRUE					   ;
//	temp.Hovered								= GLFW_FALSE				   ;
//	temp.Context = this->m_default_context_properties();
//	temp.RefreshRate							= GLFW_DONT_CARE			   ;
//	return temp;
//}
//
//integer system_window::m_set_attrib(integer aname, integer aval) {
//	switch (aname) {
//	default: return -1;
//	case GLFW_AUTO_ICONIFY		:	Property.AutoMinimize		= aval;		break;
//	case GLFW_RESIZABLE			:	Property.Resizable			= aval;		break;
//	case GLFW_DECORATED			:	Property.Decorated			= aval;		break;
//	case GLFW_FLOATING			:	Property.Floating			= aval;		break;
//	case GLFW_FOCUS_ON_SHOW		:	Property.FocusOnShow		= aval;		break;
//	}
//	return 0;
//}
//
//integer system_window::m_get_attrib(integer aname) {
//	switch (aname) {
//	default: return -1;
//	case GLFW_FOCUSED:							return Property.UserFocused					;
//	case GLFW_ICONIFIED:						return Property.Minimized					;
//	case GLFW_VISIBLE:							return Property.Visible						;
//	case GLFW_MAXIMIZED:						return Property.Maximized					;
//	case GLFW_HOVERED:							return Property.Hovered						;
//	case GLFW_FOCUS_ON_SHOW:					return Property.FocusOnShow					;
//	case GLFW_TRANSPARENT_FRAMEBUFFER:			return Property.Frame.Transparent			;
//	case GLFW_RESIZABLE:						return Property.Resizable					;
//	case GLFW_DECORATED:						return Property.Decorated					;
//	case GLFW_FLOATING:							return Property.Floating					;
//	case GLFW_AUTO_ICONIFY:						return Property.AutoMinimize				;
//	case GLFW_CLIENT_API:						return Property.Context.ClientAPI			;
//	case GLFW_CONTEXT_CREATION_API:				return Property.Context.CreationAPI			;
//	case GLFW_CONTEXT_VERSION_MAJOR:			return Property.Context.Version.x			;
//	case GLFW_CONTEXT_VERSION_MINOR:			return Property.Context.Version.y			;
//	case GLFW_CONTEXT_ROBUSTNESS:				return Property.Context.Robustness			;
//	case GLFW_OPENGL_FORWARD_COMPAT:			return Property.Context.ForwardCompat		;
//	case GLFW_OPENGL_DEBUG_CONTEXT:				return Property.Context.DebugMode			;
//	case GLFW_OPENGL_PROFILE:					return Property.Context.Profile				;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR:			return Property.Context.ReleaseBehavior		;
//	case GLFW_CONTEXT_NO_ERROR:					return Property.Context.NoError				;
//    }
//}
//
//integer system_window::m_set_hint(integer hname, integer hval) {
//	switch(hname) {
//	default: return -1;
//	case GLFW_RED_BITS						: Property.Frame.ColorBits.r					= hval	;	break;
//	case GLFW_GREEN_BITS					: Property.Frame.ColorBits.g					= hval	;	break;
//	case GLFW_BLUE_BITS						: Property.Frame.ColorBits.b					= hval	;	break;
//	case GLFW_ALPHA_BITS					: Property.Frame.ColorBits.a					= hval	;	break;
//	case GLFW_DEPTH_BITS					: Property.Frame.DepthBits						= hval	;	break;
//	case GLFW_STENCIL_BITS					: Property.Frame.StencilBits					= hval	;	break;
//	case GLFW_ACCUM_RED_BITS				: Property.Frame.AccumColorBits.r				= hval  ;   break;
//	case GLFW_ACCUM_GREEN_BITS				: Property.Frame.AccumColorBits.g				= hval  ;   break;
//	case GLFW_ACCUM_BLUE_BITS				: Property.Frame.AccumColorBits.b				= hval  ;   break;
//	case GLFW_ACCUM_ALPHA_BITS				: Property.Frame.AccumColorBits.a				= hval  ;   break;
//	case GLFW_AUX_BUFFERS					: Property.Frame.AuxBuffers						= hval  ;   break;
//	case GLFW_STEREO						: Property.Frame.Stereo							= hval	;	break;
//	case GLFW_DOUBLEBUFFER					: Property.Frame.DoubleBuffer					= hval	;	break;
//	case GLFW_TRANSPARENT_FRAMEBUFFER		: Property.Frame.Transparent					= hval  ;   break;
//	case GLFW_SAMPLES						: Property.Frame.Samples						= hval	;	break;
//	case GLFW_SRGB_CAPABLE					: Property.Frame.sRGBCapable					= hval	;	break;
//	case GLFW_RESIZABLE						: Property.Resizable							= hval	;	break;
//	case GLFW_DECORATED						: Property.Decorated							= hval	;	break;
//	case GLFW_FOCUSED						: Property.UserFocused							= hval	;	break;
//	case GLFW_AUTO_ICONIFY					: Property.AutoMinimize							= hval	;	break;
//	case GLFW_FLOATING						: Property.Floating								= hval	;	break;
//	case GLFW_MAXIMIZED						: Property.Maximized							= hval	;	break;
//	case GLFW_VISIBLE						: Property.Visible								= hval	;	break;
//	case GLFW_SCALE_TO_MONITOR				: Property.ScaleToMonitor						= hval  ;   break;
//	case GLFW_CENTER_CURSOR					: Property.CenterCursor							= hval  ;   break;
//	case GLFW_FOCUS_ON_SHOW					: Property.FocusOnShow							= hval  ;   break;
//	case GLFW_CLIENT_API             		: Property.Context.ClientAPI					= hval	;	break;
//	case GLFW_CONTEXT_CREATION_API   		: Property.Context.CreationAPI					= hval	;	break;
//	case GLFW_CONTEXT_VERSION_MAJOR  		: Property.Context.Version.x					= hval	;	break;
//	case GLFW_CONTEXT_VERSION_MINOR  		: Property.Context.Version.y					= hval	;	break;
//	case GLFW_CONTEXT_ROBUSTNESS     		: Property.Context.Robustness					= hval	;	break;
//	case GLFW_OPENGL_FORWARD_COMPAT  		: Property.Context.ForwardCompat				= hval	;	break;
//	case GLFW_OPENGL_DEBUG_CONTEXT   		: Property.Context.DebugMode					= hval	;	break;
//	case GLFW_CONTEXT_NO_ERROR       		: Property.Context.NoError						= hval	;	break;
//	case GLFW_OPENGL_PROFILE         		: Property.Context.Profile						= hval	;	break;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR		: Property.Context.ReleaseBehavior				= hval	;	break;
//	case GLFW_REFRESH_RATE					: Property.RefreshRate							= hval	;	break;
//	}
//	return 0;
//}
//
//integer system_window::m_get_hint(integer hname) {
//	switch(hname) {
//	default: return -1;
//	case GLFW_RED_BITS						: return Property.Frame.ColorBits.r				;
//	case GLFW_GREEN_BITS					: return Property.Frame.ColorBits.g				;
//	case GLFW_BLUE_BITS						: return Property.Frame.ColorBits.b				;
//	case GLFW_ALPHA_BITS					: return Property.Frame.ColorBits.a				;
//	case GLFW_DEPTH_BITS					: return Property.Frame.DepthBits				;
//	case GLFW_STENCIL_BITS					: return Property.Frame.StencilBits				;
//	case GLFW_ACCUM_RED_BITS				: return Property.Frame.AccumColorBits.r		;
//	case GLFW_ACCUM_GREEN_BITS				: return Property.Frame.AccumColorBits.g		;
//	case GLFW_ACCUM_BLUE_BITS				: return Property.Frame.AccumColorBits.b		;
//	case GLFW_ACCUM_ALPHA_BITS				: return Property.Frame.AccumColorBits.a		;
//	case GLFW_AUX_BUFFERS					: return Property.Frame.AuxBuffers				;
//	case GLFW_STEREO						: return Property.Frame.Stereo					;
//	case GLFW_DOUBLEBUFFER					: return Property.Frame.DoubleBuffer			;
//	case GLFW_TRANSPARENT_FRAMEBUFFER		: return Property.Frame.Transparent				;
//	case GLFW_SAMPLES						: return Property.Frame.Samples					;
//	case GLFW_SRGB_CAPABLE					: return Property.Frame.sRGBCapable				;
//	case GLFW_RESIZABLE						: return Property.Resizable						;
//	case GLFW_DECORATED						: return Property.Decorated						;
//	case GLFW_FOCUSED						: return Property.UserFocused					;
//	case GLFW_AUTO_ICONIFY					: return Property.AutoMinimize					;
//	case GLFW_FLOATING						: return Property.Floating						;
//	case GLFW_MAXIMIZED						: return Property.Maximized						;
//	case GLFW_VISIBLE						: return Property.Visible						;
//	case GLFW_SCALE_TO_MONITOR				: return Property.ScaleToMonitor				;
//	case GLFW_CENTER_CURSOR					: return Property.CenterCursor					;
//	case GLFW_FOCUS_ON_SHOW					: return Property.FocusOnShow					;
//	case GLFW_CLIENT_API             		: return Property.Context.ClientAPI				;
//	case GLFW_CONTEXT_CREATION_API   		: return Property.Context.CreationAPI			;
//	case GLFW_CONTEXT_VERSION_MAJOR  		: return Property.Context.Version.x				;
//	case GLFW_CONTEXT_VERSION_MINOR  		: return Property.Context.Version.y				;
//	case GLFW_CONTEXT_ROBUSTNESS     		: return Property.Context.Robustness			;
//	case GLFW_OPENGL_FORWARD_COMPAT  		: return Property.Context.ForwardCompat			;
//	case GLFW_OPENGL_DEBUG_CONTEXT   		: return Property.Context.DebugMode				;
//	case GLFW_CONTEXT_NO_ERROR       		: return Property.Context.NoError				;
//	case GLFW_OPENGL_PROFILE         		: return Property.Context.Profile				;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR		: return Property.Context.ReleaseBehavior		;
//	case GLFW_REFRESH_RATE					: return Property.RefreshRate					;
//	}
//}
