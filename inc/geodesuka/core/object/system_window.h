#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SYSTEM_WINDOW_H
#define GEODESUKA_CORE_OBJECT_SYSTEM_WINDOW_H

#include <vector>
#include <thread>

#include "../math.h"

#include "../gcl.h"
#include "../gcl/device.h"
#include "../gcl/context.h"
#include "../gcl/image.h"

#include "../object.h"
#include "window.h"
#include "system_display.h"

struct GLFWwindow;


/// <summary>
/// system_window.h is an object that will represent Operating System (OS) managed windows, managed
/// by a window manager like Wayland, X11, win32, and so on. It will also be a render target that
/// can be used by other objects to create render commands for. Position and Size will accept
/// two units for modifying the state of a SystemWindow instance. It will take physical coordinates
/// in units of meters which the position and size will be in reference to the parent display it
/// is a child of.
/// </summary>
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

		enum present_mode {
			IMMEDIATE		= 0,
			MAILBOX			= 1,
			FIFO			= 2,
			FIFO_RELAXED	= 3
		};

		struct swapchain {

			struct prop {
				//int Flags;
				int FrameCount;
				double FrameRate;
				int ColorSpace;
				int Usage;
				int CompositeAlpha;
				int PresentMode;
				bool Clipped;

				prop();
			};

		};

		struct property {
			// Window Options.
			option Window;
			swapchain::prop Swapchain;
			VkFormat PixelFormat;
			float3 Position;
			float2 Size;
			const char* Title;

			property();
		};

		struct propertyvsc {
			// Window Options.
			option Window;
			swapchain::prop Swapchain;
			VkFormat PixelFormat;
			int2 Position;
			int2 Size;
			const char* Title;

			propertyvsc();
		};


		// Required Extensions for the class
		static std::vector<const char*> RequiredInstanceExtension;
		static std::vector<const char*> RequiredContextExtension;
		static constexpr int ID = 2;

		gcl::image* Frame;
		
		system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, const property& aProperty);
		system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay, const propertyvsc& aProperty);
		//system_window(engine* aEngine, gcl::context* aContext, system_display* aSystemDisplay);
		~system_window();

		// ----- object_t inheritance ----- //

		virtual void set_position(float3 aPosition) override;
		//virtual VkCommandBuffer draw(rendertarget* aRenderTarget) override;

		// ----- rendertarget inheritance ----- //

		virtual int id() override;
		virtual void next_frame() override;
		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;
		virtual VkPresentInfoKHR present_frame() override;

		// ----- window inheritance ----- //

		virtual void set_size(float2 aSize) override; // Do not rapidly change size or lag will happen.
		virtual void set_resolution(uint2 aResolution) override;

		// ----- system_window methods ----- //

		void set_position_vsc(int2 aPositionVSC);
		void set_size_vsc(int2 aSizeVSC);
		void set_option(option::id, bool aValue);

	protected:

		virtual VkSubmitInfo update(double aDeltaTime) override;

		//virtual VkSubmitInfo compute() override;

	private:

		system_display* Display;			// Parent Display of this system_window.

		GLFWwindow* Handle;						// GLFW OS window handle abstraction.
		VkSurfaceKHR Surface;					// Vulkan window handle.
		VkSwapchainCreateInfoKHR CreateInfo{};
		VkSwapchainKHR Swapchain;
		int2 PositionVSC;
		int2 SizeVSC;

		// Fill out in constructor
		int NextImageSemaphoreIndex;
		VkSemaphore* NextImageSemaphore;
		VkSemaphore* RenderOperationSemaphore;
		uint32_t* PresentIndex;
		VkResult* PresentResult;
		VkPresentInfoKHR* Presentation;
		VkPipelineStageFlags PipelineStageFlags;
		// Semaphores are even fucking dumber than I thought they were.
		// It turns out that there is no way to unsignal a semaphore other than recreating it.
		// Which is beyond fucking stupid. Thanks Khronos Group.

		// ------------------------------ Utility (Internal, Do Not Use) ------------------------------ //

		void make_default();
		void clear_all();
		//void make_swapchain();
		//void remake_swapchain();

		// Position vector conversions for system_window.
		float3 vsc2phy(int2 aRscrw, int2 aSscrw, int2 aRscrm, int2 aSscrm, float2 aSphy);
		int2 phy2vsc(float3 aRphyw, int2 aSvscw, int2 aRvscm, int2 aSvscm, float2 aSphy);

		struct glfwargs {
			window::option Property;
			int Width;
			int Height;
			const char* Title;
			GLFWmonitor* Monitor;
			GLFWwindow* Window;
		};

		static bool initialize();
		static void terminate();
		static void poll_events();

		// Signals to update thread to create window handle
		// Needed backend for system window creation
		static std::thread::id MainThreadID;
		static std::atomic<bool> SignalCreate;
		static std::atomic<bool> WindowCreated;
		static glfwargs WindowTempData;
		static GLFWwindow* ReturnWindow;
		static std::atomic<GLFWwindow*> DestroyWindow;

		// This is necessary for main thread to create window handles.
		static GLFWwindow* create_window_handle(core::object::window::option aProperty, int aWidth, int aHeight, const char* aTitle, GLFWmonitor* aMonitor, GLFWwindow* aWindow); 

		static void destroy_window_handle(GLFWwindow* aWindow);
		// This function is by the engine update thread to create and destroy handles.
		static void mtcd_process_window_handle_call();

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
