#pragma once
#ifndef GEODESUKA_ENGINE_H
#define GEODESUKA_ENGINE_H

/*

// ------------------------- TODO: ------------------------- \\

// ------------------------- Notes ------------------------- \\
As of right now geodesuka is the primary namespace. Engine
is the factory manager of all objects, including memory. Can
be used to 

TODO: Fix context.h queues.

\\ ------------------------- Notes ------------------------- //
*/

/* --------------- System Macros (Tweak) --------------- */

/*
Disabled Warnings:
C4244
C6386
C26451

Include: $(ProjectDir)..\glslang

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
#include <atomic>

// ------------------------- Mathematics Library ------------------------- //
#include "core/math.h"

// ------------------------- Utility Classes ------------------------- //
// Simple replacement for std::string, extended functionality.
#include "core/util/log.h"
#include "core/util/str.h"
#include "core/util/variable.h"

#include "core/logic/timer.h"
#include "core/logic/time_step.h"
#include "core/logic/trap.h"

// ------------------------- File System Manager ------------------------- //
#include "core/io/file.h"
#include "core/io/dynalib.h"
//#include "core/io/image.h"
//#include "core/io/font.h"

// ------------------------- Graphics & Computation API ------------------------- //
#include "core/gcl.h"
#include "core/gcl/device.h"
#include "core/gcl/context.h"
#include "core/gcl/command_list.h"
#include "core/gcl/command_pool.h"
#include "core/gcl/command_batch.h"
#include "core/gcl/buffer.h"
#include "core/gcl/shader.h"
#include "core/gcl/texture.h"
#include "core/gcl/renderpass.h"
#include "core/gcl/framebuffer.h"
#include "core/gcl/pipeline.h"

// ------------------------- Human Interface Devices ------------------------- //

// Human Interface devices go here.
#include "core/hid/keyboard.h"
#include "core/hid/mouse.h"
#include "core/hid/joystick.h"

// ------------------------- Component Classes ------------------------- //
//#include "core/component/...h"

// ------------------------- Objects ------------------------- //
/*
* The classes included here are built in objects for the core game engine.
* They will be used for setting up guis and interfaces.
*/
#include "core/object.h"

// Do not mistake with system window.
#include "core/object/system_terminal.h"

// Might change this later into something else.
#include "core/object/rendertarget.h"

// Includes window primitives which can be drawn to.
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
#include "core/object/text.h"

#include "core/stage.h"
#include "core/stage/canvas.h"
#include "core/stage/scene2d.h"
#include "core/stage/scene3d.h"
#include "core/stage/desktop.h"

#include "core/app.h"

namespace geodesuka {

	class engine {
	public:

		// So Engine internals can be accessed.
		friend class core::gcl::context;
		friend class core::object_t;
		friend class core::object::system_window;
		friend class core::stage_t;
		friend class core::app;

		struct version {
			int Major;
			int Minor;
			int Revision;
		};

		// TODO: Stupid Object, Remove Later
		struct state {
			enum id {
				FAILURE = -1,
				CREATION,						// Engine instance is being constructed.
				READY,							// Engine instance is active, and ready to be used.
				RUNNING,						// Threads are launched and running backend.
				DESTRUCTION						// Engine is currently in destruction phase.
			};
		};

		engine(int aCmdArgCount, const char** aCmdArgList, int aLayerCount, const char** aLayerList, int aExtensionCount, const char** aExtensionList);
		~engine();

		core::io::file* open(const char* aFilePath);
		void close(core::io::file* aFile);
		core::gcl::device** get_device_list(size_t* aListSize);
		core::gcl::device* get_primary_device();
		core::object::system_display** get_display_list(size_t* aListSize);
		core::object::system_display* get_primary_display();

		VkInstance handle();
		bool is_ready();
		version get_version();
		int get_date();

		int run(core::app* aApp);

	private:

		const version Version = { 0, 0, 20 }; // Major, Minor, Revision
		const int Date = 20220521; //YYYYMMDD
		std::vector<const char*> Layer;
		std::vector<const char*> Extension;
		VkApplicationInfo AppInfo{};
		VkInstanceCreateInfo CreateInfo{};
		VkInstance Handle;

		// ------------------------------ Engine State ------------------------------ //
		
		std::mutex Mutex;
		state::id StateID;
		//bool isReady;
		std::atomic<bool> Shutdown;
		core::logic::trap ThreadTrap;

		// ----- References Only ----- //

		core::object::system_terminal* SystemTerminal;
		core::gcl::device* PrimaryDevice;
		core::object::system_display* PrimaryDisplay;
		std::vector<core::gcl::device*> Device;
		std::vector<core::object::system_display*> Display;
		std::vector<core::object::system_window*> SystemWindow;

		// ----- Memory Managed Items ----- //

		// Maybe make shared pointers?
		std::vector<core::io::file*> File;
		std::vector<core::gcl::context*> Context;
		std::vector<core::object_t*> Object;
		std::vector<core::stage_t*> Stage;

		// ------------------------------ Back end runtime ------------------------------ //

		std::thread::id MainThreadID;
		std::thread::id RenderThreadID;
		std::thread::id AudioThreadID;
		std::thread::id SystemTerminalThreadID;
		std::thread::id AppThreadID;

		std::thread RenderThread;
		std::thread AudioThread;
		std::thread SystemTerminalThread;
		std::thread AppThread;

		void update();
		void render();			// Thread honors frame rates of respective targets.
		void audio();			// Thread Handles audio streams.
		void terminal();		// Thread handles terminal input to the engine.

		// ----- Back End Garbage ----- //
		
		// Signals to update thread to create window handle
		// Needed backend for system window creation
		std::atomic<bool> SignalCreate;
		std::atomic<bool> WindowCreated;
		struct {
			core::object::window::prop Property;
			int Width;
			int Height;
			const char* Title;
			GLFWmonitor* Monitor;
			GLFWwindow* Window;
		} WindowTempData;
		GLFWwindow* ReturnWindow;
		std::atomic<GLFWwindow*> DestroyWindow;

		GLFWwindow* create_window_handle(core::object::window::prop aProperty, int aWidth, int aHeight, const char* aTitle, GLFWmonitor* aMonitor, GLFWwindow* aWindow);
		void destroy_window_handle(GLFWwindow* aWindow);
		void mtcd_process_window_handle_call();

	};

}

#endif // !GEODESUKA_ENGINE_H
