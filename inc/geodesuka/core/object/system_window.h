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
#include "../gcl/swapchain.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "../object.h"
#include "window.h"
//#include "system_display.h"
//#include "system_window.h"
//#include "virtual_window.h"
//#include "camera.h"

// Interact with windowing system.
#include <GLFW/glfw3.h>

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
		//friend class system_display;

		//// TODO: Abandoned Idea.
		//// Will be used to aggregate presentation.
		//struct present {
		//
		//	present();
		//	present(VkSwapchainKHR aSwapchain, uint32_t aPresentImageIndex);
		//	~present();
		//
		//	// Use to 
		//	uint32_t count();
		//	VkPresentInfoKHR handle();
		//	VkResult *results();
		//
		//private:
		//	uint32_t Count;
		//	VkSwapchainKHR* Swapchains;
		//	uint32_t* ImageIndices;
		//	VkResult* Results;
		//};

		// Required Extensions for the class
		static const std::vector<const char*> RequiredExtension;
		gcl::texture* FrameTexture;


		//math::boolean CloseMe;

		system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, window::prop aWindowProperty, gcl::swapchain::prop aSwapchainProperty, int aPixelFormat, int aWidth, int aHeight, const char* aTitle);

		~system_window();

		virtual void set_position(math::real3 aPosition) override;
		virtual void set_size(math::real2 aSize) override; // Do not rapidly change size or lag will happen.
		virtual void set_resolution(math::natural2 aResolution) override;

	protected:
		// Only accessible to engine backend.

		virtual VkSubmitInfo update(double aDeltaTime);

		virtual VkCommandBuffer draw(system_display* aTargetDisplay) override;

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

	private:
		// Local variables only accessed by instance of class.

		system_display* Display;			// Parent Display of this system_window.

		GLFWwindow* Handle;						// GLFW OS window handle abstraction.
		VkSurfaceKHR Surface;					// Vulkan window handle.

		gcl::swapchain* Swapchain;


		math::integer2 PositionSC;
		//math::integer2 SizeSC;



		// Internal Utils, Physical coordinates to Screen coordinates
		math::integer2 phys2scrn(math::real2 R);
		math::real2 scrn2phys(math::integer2 R);

		// ------------------------------ Callbacks (Internal, Do Not Use) ------------------------------ //

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
