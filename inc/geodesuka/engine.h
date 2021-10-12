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

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

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

#include "core/stage.h"
#include "core/stage/canvas.h"
#include "core/stage/scene2d.h"

namespace geodesuka {

	class engine {
	public:

		enum state {
			ENGINE_CREATION_STATE,			// Engine instance is being constructed.
			ENGINE_ACTIVE_STATE,			// Engine instance is active, and ready to be used.
			ENGINE_DESTRUCTION_STATE		// Engine is currently in destruction phase.
		};

		struct version {
			int Major;
			int Minor;
			int Patch;
		};

		friend class core::gcl::context;

		// Objects can interect with engine internals.
		friend class core::object_t;

		engine(int argc, char* argv[]);
		~engine();

		// Gets current primary display.
		core::object::system_display* get_primary_display();

		// Gets list of all currently available displays.
		core::object::system_display** get_display_list(size_t* aListSize);

		// Gets list of all currently available gpus.
		core::gcl::device** get_device_list(size_t* aListSize);

		// When an engine instance is passed into an object
		// constructor, it uses these methods to load required
		// assets.
		core::io::file* open(const char* aFilePath);		// Opens file using provided path string.
		void close(core::io::file* aFile);				// Closes previously loaded file held by engine.



		// These calls are neccesary for time scheduled update of all active
		// objects in existence.
		void submit(core::object_t* aObject);		// Submit created object to engine.
		void remove(core::object_t* aObject);		// Remove object from engine.

		VkInstance handle();
		bool is_ready();
		version get_version();
		double get_time();
		void tsleep(double aSeconds);

	private:

		state State;

		std::vector<const char*> RequiredExtension;

		// Engine Mutex
		std::mutex Mutex;

		// Maintain versioning system.
		const version Version = { 0, 0, 14 };

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

		// It is the job of the engine to query for physical devices
		// and display from the system.
		std::vector<core::gcl::device*> DeviceList;
		std::vector<core::object::system_display*> Display;
		std::vector<core::object::system_window*> SystemWindow;
		// Find a way to map devices to system_displays.

		// Keeps track of important System and OS objects.
		core::object::system_display* PrimaryDisplay;

		// Reduce redundant file loading by matching paths.
		// If current working directory changes, 
		std::vector<core::io::file*> File;

		// All created device contexts are held by engine. Needed for graphics/compute.
		std::vector<core::gcl::context*> Context;

		// All objects are managed by engine regardless of stage.
		std::vector<core::object_t*> Object;


		// Active stage represent a collection of objects
		// sharing the same space, object interaction, rendering
		std::vector<core::stage_t*> Stage;

		
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
