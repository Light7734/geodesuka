#pragma once
#ifndef SYSTEM_WINDOW_H
#define SYSTEM_WINDOW_H

#include "../gcl/gcl.h"

#include "../math/gmath.h"

#include "../gcl/device.h"
#include "../gcl/device_context.h"
#include "../gcl/context.h"
#include "../gcl/frame_buffer.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "object.h"
#include "window.h"
//#include "system_display.h"
//#include "system_window.h"
//#include "virtual_window.h"
//#include "camera.h"



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

namespace geodesuka {
	namespace core {
		namespace object {

			class system_window : public window {
			public:

				VkResult ErrorCode;

				//friend class system_display;

				math::boolean CloseMe;

				//TODO: Resolve context sharing ambiguities.
				// Opens window with default settings.
				//system_window(gcl::context *aContext, gcl::frame_buffer::prop *aFrameBufferProp, prop *aWindowProp,
				//	math::real aWidth, math::real aHeight, const char* aName, system_display* aDisplay);

				//system_window(gcl::context* aRenderingContext, gcl::frame_buffer::prop* aFrameBufferProp, prop* aWindowProp,
				//	math::real2 &aPos, math::real2 &aSize, util::text &aTitle, system_display* aDisplay);

				//system_window(math::integer Width, math::integer Height, const char* Name, const system_display&);

				// Provide a device_context to create an associated rendering context with it.
				system_window(gcl::device_context* aDeviceContext, system_display* aDisplay, gcl::frame_buffer::prop aFrameBufferProp, prop aWindowProp,
					math::real3 aPosition, math::real2 aSize, util::text aTitle);

				// Opens window
				system_window(const system_window* aWindow);

				// Converts virtual window into a system window.
				system_window(const virtual_window* aWindow);

				// Clears entire window out.
				~system_window();

				// overriden fron object.h
				// Should be called if input stream is directed to it
				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;
				//virtual math::integer process_input(const hid::joystick& Joystick)		override;

				// Update the object in time, requires implementation in child
				virtual math::integer update(math::real aDeltaTime)						override;

				// Target specific methods for windows being drawn to.
				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				// Does Nothing
				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

				// Mandatory implementation required by window.h
				virtual math::integer draw(object* aObject)								override;

				virtual math::integer set_position(math::real3 aPosition)				override;
				virtual math::integer set_size(math::real2 aSize)						override; // Do not rapidly change size or lag will happen.
				virtual math::integer set_resolution(math::natural2 aResolution)		override;



				math::integer set_parent_display(system_display* aParentDisplay);
				//system_display* get_parent_display() { return this->ParentDisplay; }
				math::integer set_input_stream_target(object* aTargetObject);

			private:

				// The target object where polled input will be streamed to.
				object* InputStreamTarget;

				system_display* ParentDisplay;
				//gcl::context* ParentDeviceContext;
				//gcl::context* Context;

				math::integer2 PositionSC;
				//math::integer2 SizeSC;

				gcl::device_context* ParentDeviceContext;

				VkSurfaceCapabilitiesKHR SurfaceCapabilities;
				VkSwapchainCreateInfoKHR SwapChainProp{};

				math::boolean isValid;
				GLFWwindow* Handle;
				VkSurfaceKHR Surface;
				VkSwapchainKHR SwapChain; 

				const std::vector<const char *> RequiredExtension = { "VK_KHR_swapchain" };


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
	}
}

#endif // !SYSTEM_WINDOW_H
