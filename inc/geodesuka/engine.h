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
//#include <chrono>

#include <thread>

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

// ------------------------- File System Manager ------------------------- //
#include "core/io/file.h"
#include "core/io/dynalib.h"

// ------------------------- Graphics & Computation API ------------------------- //


// May Change to "vertex.h", manages memory layout of
#include "core/gcl/variable.h"

// Needed for all graphics/computation objects
#include "core/gcl/device.h"
#include "core/gcl/device_context.h"

// Data Objects, used for meshes, models, materials and
// and so on. 
#include "core/gcl/buffer.h"
#include "core/gcl/shader.h"
#include "core/gcl/texture.h"

// The objects are for linking various inputs, uniforms, and outputs
// of shaders, buffers and textures.
#include "core/gcl/vertex_array.h"
#include "core/gcl/shader_program.h"
#include "core/gcl/frame_buffer.h"

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

		struct version {
			int Major;
			int Minor;
			int Patch;
		};

		const version Version = { 0, 0, 13 };

		//friend class core::object::system_display;
		friend class core::object::system_window;

		// Use for main game loop. Set true if client wished to make app close.
		// Will also set true if there is a terminal error.
		bool ExitApp;

		// "t" is the total time (seconds) elapsed, while "dt" is the time step.
		double t, dt;

		engine(int argc, char* argv[]);
		~engine();

		core::object::system_display* get_primary_display();
		std::vector<core::object::system_display*> get_display_list();

		// Intended to be used to create and register new objects. Can be used for debuging memory leaks
		// and extending object.h for user choice.
		// Example: "Engine, create a new sword.".
		// Object* Sword = Engine.create(new sword());
		core::object_t* create(core::object_t* aNewObject);
		core::object::window* create(core::object::window* aNewWindow);
		core::object::system_window* create(core::object::system_window* aNewSystemWindow);
		core::object::virtual_window* create(core::object::virtual_window* aNewWindow);
		//core::object::camera* create(core::object::camera* aNewWindow);
		core::math::integer destroy(core::object_t* aDestroyObject);

		double get_time();

	//private:

		// Make internal engine flags.
		bool isDebuggingEnabled;


		VkResult ErrorCode;
		VkInstance Instance;

		// It is the job of the engine to query for physical devices and displays.
		std::vector<core::gcl::device*> DeviceList;
		std::vector<core::object::system_display*> Display;
		// Find a way to map devices to system_displays.


		// Keeps track of important System and OS objects.
		core::object::system_display* PrimaryDisplay;

		// Abstract Window Type
		std::vector<core::object::window*> Window;
		std::vector<core::object::system_window*> SystemWindow;			// Automatically managed by engine.
		std::vector<core::object::virtual_window*> VirtualWindow;		
		std::vector<core::object::camera*> Camera;

		// These are gameplay objects. Cannot be created/destroyed until everything is initialized.
		std::vector<core::object_t*> Object;

		
		const char *get_er_str(VkResult Res);

		
		std::thread UpdateThread;
		std::thread RenderThread;
		std::thread AudioThread;

		void tupdate();
		void trender();
		void taudio();

	};

}

#endif // !GEODESUKA_ENGINE_H
