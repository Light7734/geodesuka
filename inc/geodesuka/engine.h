#pragma once
#ifndef GEODESUKA_ENGINE_H
#define GEODESUKA_ENGINE_H

/*
// ------------------------- Notes ------------------------- \\
As of right now geodesuka is the primary namespace. Engine
is the factory manager of all objects, including memory. Can
be used to 

\\ ------------------------- Notes ------------------------- //
*/

/* --------------- System Macros (Tweak) --------------- */

/*
Disabled Warnings:
C4244
C6386
C26451
*/

// Disables Terminal Window, for windows only
#if defined(_WIN32) || defined(_WIN64)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

/* --------------- Standard C Libraries --------------- */

/* --------------- Standard C++ Libraries --------------- */
#include <vector>

#include <chrono>
#include <thread>
#include <mutex>

/* --------------- Third Party Libraries --------------- */

/* Vulkan API */
#include <vulkan/vulkan.h>

/* GLFW API */
//#define VK_USE_PLATFORM_WIN32_KHR
//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

// ------------------------- Mathematics Library ------------------------- //
#include "core/math.h"

// ------------------------- Utility Classes ------------------------- //
// Simple replacement for std::string, extended functionality.
#include "core/util/text.h"
#include "core/util/variable.h"

// ------------------------- File System Manager ------------------------- //
#include "core/io/file.h"
#include "core/io/dynalib.h"
//#include "core/io/image.h"
//#include "core/io/font.h"
// ------------------------- Graphics & Computation API ------------------------- //

// Needed for all graphics/computation objects
#include "core/gcl/device.h"
#include "core/gcl/context.h"
#include "core/gcl/buffer.h"
#include "core/gcl/shader.h"
#include "core/gcl/texture.h"
//#include "core/gcl/renderpass.h"
#include "core/gcl/framebuffer.h"
//#include "core/gcl/pipeline.h"

// ------------------------- Human Interface Devices ------------------------- //

// Human Interface devices go here.
#include "core/hid/keyboard.h"
#include "core/hid/mouse.h"
#include "core/hid/joystick.h"

// ------------------------- Objects ------------------------- //
/*
* The classes included here are built in objects for the core game engine.
* They will be used for setting up guis and interfaces.
*/
#include "core/object.h"

//#include "core/object/render_target.h"

#include "core/object/window.h"
#include "core/object/system_display.h"
#include "core/object/system_window.h"
#include "core/object/virtual_window.h"

// camera.h is the base class for extendable cameras
// that will perform deferred rendering. 
#include "core/object/camera.h"
#include "core/object/camera2d.h"
#include "core/object/camera3d.h"

// This section is for GUI sh... stuff!
#include "core/object/vtext.h"

// Cube is supposed to be a simple template
// example for extending object.h
//#include "core/object/cube.h"

namespace geodesuka {

	/*
	* Maybe run engine internals on secondary thread? If that is the
	* case, the
	* 
	*/
	class engine {
	public:

		enum ecode {
			GE_SUCCESS = 0,
			GE_ERROR_CODE_STARTUP_FAILURE = -1,
		};

		struct version {
			int Major;
			int Minor;
			int Patch;
		};

		//friend class core::object::system_display;
		friend class core::object::system_window;

		engine(int argc, char* argv[]);
		~engine();

		// Query functions
		core::object::system_display* get_primary_display();
		core::object::system_display** get_display_list(size_t* ListSize);
		core::gcl::device** get_device_list(size_t* ListSize);

		// File management system.
		core::io::file* open(const char* FilePath);
		core::math::integer close(core::io::file* FileHandle);

		// Intended to be used to create and register new objects. Can be used for debuging memory leaks
		// and extending object.h for user choice.
		// Example: "Engine, create a new sword.".
		// Object* Sword = Engine.create(new sword());
		core::object_t* create(core::object_t* aNewObject);
		core::object_t* create(core::object::system_window* aNewSystemWindow);
		core::math::integer destroy(core::object_t* aDestroyObject);

		bool is_ready();
		ecode error_code();
		version get_version();
		double get_time();
		void tsleep(double Seconds);

	private:

		std::vector<const char*> RequiredExtension;

		// Engine Mutex
		std::mutex Mutex;

		// Maintain versioning system.
		const version Version = { 0, 0, 13 };

		ecode ErrorCode;

		// Engine Startup Conditions
		bool isGLSLANGReady;
		bool isGLFWReady;
		bool isVulkanReady;
		bool isSystemDisplayAvailable;
		bool isGCDeviceAvailable;

		bool isReady;
		bool Shutdown;

		VkApplicationInfo AppProp{};
		VkInstanceCreateInfo InstProp{};
		VkInstance Instance;
		


		// It is the job of the engine to query for physical devices and displays.
		std::vector<core::gcl::device*> DeviceList;
		std::vector<core::object::system_display*> Display;
		// Find a way to map devices to system_displays.


		// Keeps track of important System and OS objects.
		core::object::system_display* PrimaryDisplay;

		// Abstract Window Type
		//std::vector<core::object::window*> Window;
		std::vector<core::object::system_window*> SystemWindow;			// Automatically managed by engine.
		//std::vector<core::object::virtual_window*> VirtualWindow;		
		//std::vector<core::object::camera*> Camera;

		// These are gameplay objects. Cannot be created/destroyed until everything is initialized.
		std::vector<core::object_t*> Object;

		// Reduce redundant file loading by matching paths.
		// If current working directory changes, 
		std::vector<core::io::file*> File;
		
		// ------------------------------ Back end runtime ------------------------------ //

		std::thread UpdateThread;
		std::thread RenderThread;
		std::thread AudioThread;

		void tupdate();
		void trender();
		void taudio();

	};

}

#endif // !GEODESUKA_ENGINE_H
