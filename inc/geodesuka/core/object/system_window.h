#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SYSTEM_WINDOW_H
#define GEODESUKA_CORE_OBJECT_SYSTEM_WINDOW_H

/*
* Windows API
* Wayland
* X11
* Android
*/

#include <vector>

#include "../math.h"

#include "../gcl.h"
#include "../gcl/device.h"
#include "../gcl/context.h"
#include "../gcl/texture.h"
#include "../gcl/framebuffer.h"
//#include "../gcl/swapchain.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "../object.h"
#include "window.h"
#include "system_display.h"
//#include "system_window.h"
//#include "virtual_window.h"
//#include "camera.h"

// Interact with windowing system.
//#include <GLFW/glfw3.h>
struct GLFWwindow;

// system_window: This object exists in the display space exclusively.
// It interfaces with the operating system and holds the context for for
// the graphics API being used. All system windows must be managed by the
// engine itself.
//
//
//

// A system_window by default should have the default framebuffer. All proceeding
// draw calls will be towards the window itself. If the contents of the system_window 
// are to be streamed to another destination, create a seperate frame_buffer, and forward
// its outputs to the target. For intensive draw operations and windows that are due to
// send their contents to multiple targets, it would be wise to stream the contents rather
// than direct the draw operations to the intended targets.


namespace geodesuka::core::object {

	class system_window : public window {
	public:

		friend class engine;

		enum colorspace {
			SRGB_NONLINEAR			= 0,
			DISPLAY_P3_NONLINEAR	= 1000104001,
			EXTENDED_SRGB_LINEAR	= 1000104002,
			DISPLAY_P3_LINEAR		= 1000104003,
			DCI_P3_NONLINEAR		= 1000104004,
			BT709_LINEAR			= 1000104005,
			BT709_NONLINEAR			= 1000104006,
			BT2020_LINEAR			= 1000104007,
			HDR10_ST2084			= 1000104008,
			DOLBYVISION				= 1000104009,
			HDR10_HLG				= 1000104010,
			ADOBERGB_LINEAR			= 1000104011,
			ADOBERGB_NONLINEAR		= 1000104012,
			PASS_THROUGH			= 1000104013,
			EXTENDED_SRGB_NONLINEAR = 1000104014,
			DISPLAY_NATIVE_AMD		= 1000213000,
		};

		enum composite {
			ALPHA_OPAQUE			= 0x00000001,
			ALPHA_PRE_MULTIPLIED	= 0x00000002,
			ALPHA_POST_MULTIPLIED	= 0x00000004,
			ALPHA_INHERIT			= 0x00000008,
		};

		enum mode {
			IMMEDIATE		= 0,
			MAILBOX			= 1,
			FIFO			= 2,
			FIFO_RELAXED	= 3
		};

		struct swapchain {

			struct prop {
				//int Flags;
				int Count;
				int ColorSpace;
				int Usage;
				int CompositeAlpha;
				int PresentMode;
				bool Clipped;

				prop();
			};

		};

		// Required Extensions for the class
		static std::vector<const char*> RequiredInstanceExtension;
		static std::vector<const char*> RequiredContextExtension;
		static const int RTID;

		gcl::texture* Frame;


		//math::boolean CloseMe;

		system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, window::prop aWindowProperty, swapchain::prop aSwapchainProperty, VkFormat aPixelFormat, int aWidth, int aHeight, const char* aTitle);

		~system_window();

		// ----- object_t inheritance ----- //

		virtual void set_position(float3 aPosition) override;
		//virtual VkCommandBuffer draw(rendertarget* aRenderTarget) override;

		// ----- rendertarget inheritance ----- //

		virtual int rtid() override;
		virtual void next_frame() override;
		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;
		virtual VkPresentInfoKHR present_frame() override;

		// ----- window inheritance ----- //

		// ----- system_window methods ----- //

		virtual void set_size(float2 aSize) override; // Do not rapidly change size or lag will happen.
		virtual void set_resolution(uint2 aResolution) override;

		// ----- Used in Stage Render Logic ----- //


	protected:
		// Only accessible to engine backend.

		virtual VkSubmitInfo update(double aDeltaTime) override;

		//virtual VkSubmitInfo compute() override;

	private:

		system_display* Display;			// Parent Display of this system_window.

		GLFWwindow* Handle;						// GLFW OS window handle abstraction.
		VkSurfaceKHR Surface;					// Vulkan window handle.
		VkSwapchainCreateInfoKHR CreateInfo{};
		VkSwapchainKHR Swapchain;
		//gcl::swapchain* Swapchain;
		//VkImage* Frame;


		// Fill out in constructor
		int NextImageSemaphoreIndex;
		VkSemaphore* NextImageSemaphore;
		VkSemaphore* RenderOperationSemaphore;
		VkResult* PresentResult;
		VkPipelineStageFlags PipelineStageFlags;
		//uint32_t* DrawCommandCount;
		//VkCommandBuffer** DrawCommandList;
		//VkPresentInfoKHR* PresentInfo;


		int2 PositionSC;
		//math::integer2 SizeSC;



		// Internal Utils, Physical coordinates to Screen coordinates
		int2 phys2scrn(float2 R);
		float2 scrn2phys(int2 R);

		// ------------------------------ Callbacks (Internal, Do Not Use) ------------------------------ //

		static bool initialize();
		static void terminate();

		// Window Callbacks
		static void position_callback(GLFWwindow* ContextHandle, int PosX, int PosY);
		static void size_callback(GLFWwindow* ContextHandle, int SizeX, int SizeY);
		static void close_callback(GLFWwindow* ContextHandle);
		static void refresh_callback(GLFWwindow* ContextHandle);
		static void focus_callback(GLFWwindow* ContextHandle, int Focused);
		static void iconify_callback(GLFWwindow* ContextHandle, int Iconified);
		static void maximize_callback(GLFWwindow* ContextHandle, int Maximized);
		static void content_scale_callback(GLFWwindow* ContextHandle, float XScale, float YScale);

		// Framebuffer Callbacks
		static void framebuffer_size_callback(GLFWwindow* ContextHandle, int FrameSizeX, int FrameSizeY);

		// Cursor Callback
		static void mouse_button_callback(GLFWwindow* ContextHandle, int Button, int Action, int Mods);
		static void cursor_position_callback(GLFWwindow* ContextHandle, double PosX, double PosY);
		static void cursor_enter_callback(GLFWwindow* ContextHandle, int Entered);
		static void scroll_callback(GLFWwindow* ContextHandle, double OffsetX, double OffsetY);

		// Keyboard Callback
		static void key_callback(GLFWwindow* ContextHandle, int Key, int Scancode, int Action, int Mods);
		static void character_callback(GLFWwindow* ContextHandle, unsigned int Codepoint);

		// File drop
		static void file_drop_callback(GLFWwindow* ContextHandle, int PathCount, const char** Path);

	};

}

#endif // !GEODESUKA_CORE_OBJECT_SYSTEM_WINDOW_H
