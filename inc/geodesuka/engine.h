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
#include <atomic>

// ------------------------- Mathematics Library ------------------------- //
#include "core/math.h"

// ------------------------- Utility Classes ------------------------- //
// Simple replacement for std::string, extended functionality.
#include "core/util/log.h"
#include "core/util/text.h"
#include "core/util/variable.h"

#include "core/logic/timer.h"
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
#include "core/object/vtext.h"

#include "core/stage.h"
#include "core/stage/canvas.h"
#include "core/stage/scene2d.h"
#include "core/stage/scene3d.h"

#include "core/stage/desktop.h"

#include "core/app.h"

namespace geodesuka {

	class engine {
	public:

		friend class core::gcl::context;
		friend class core::object_t;
		friend class core::object::system_window;
		friend class core::stage_t;
		friend class core::app;

		struct version {
			int Major;
			int Minor;
			int Patch;
		};

		engine(int argc, char* argv[]/*, int aExtensionCount, const char** aExtension*/);
		~engine();

		int run(core::app* aApp);

		core::io::file* open(const char* aFilePath);
		void close(core::io::file* aFile);

		core::gcl::device** get_device_list(int* aListSize);
		core::object::system_display** get_display_list(int* aListSize);
		core::object::system_display* get_primary_display();

		VkInstance handle();
		bool is_ready();
		version get_version();
		int get_date();

	private:

		enum state {
			CREATION,						// Engine instance is being constructed.
			READY,							// Engine instance is active, and ready to be used.
			RUNNING,
			DESTRUCTION						// Engine is currently in destruction phase.
		};

		struct workload {
			core::gcl::context*						Context;
			std::mutex								Mutex;
			core::stage_t::batch					TransferBatch;
			VkFence									TransferFence;
			core::stage_t::batch					ComputeBatch;
			VkFence									ComputeFence;
			core::stage_t::batch					GraphicsBatch;
			VkFence									GraphicsFence;
			//core::object::system_window::present	Presentation;
			workload(core::gcl::context* aContext);
			~workload();
			VkResult waitfor(core::gcl::device::qfs aQFS);
			VkResult reset(core::gcl::device::qfs aQFS);
		};

		const version			Version = { 0, 0, 17 };
		const int				Date = 20211120;

		std::mutex				Mutex;

		// I hate std::vector
		std::vector<const char*> RequiredExtension;
		std::vector<const char*> EnabledLayer;

		state					State;
		bool					isReady;
		std::atomic<bool>		Shutdown;
		//std::atomic<bool>		ThreadsLaunched;

		VkApplicationInfo		AppInfo{};
		VkInstanceCreateInfo	CreateInfo{};
		VkInstance				Handle;

		// -------------------------------------------------- //

		core::object::system_terminal*		SystemTerminal;
		core::object::system_display*		PrimaryDisplay;

		// -------------------------------------------------- //

		int									DeviceCount;
		core::gcl::device*					Device[512];

		int									DisplayCount;
		core::object::system_display*		Display[512];

		int									SystemWindowCount;
		core::object::system_window*		SystemWindow[512];

		int									DesktopCount;
		core::stage::desktop*				Desktop[512];

		// -------------------------------------------------- //

		int						FileCount;
		core::io::file**		File;

		int						ContextCount;
		core::gcl::context*		Context[512];
		workload*				Workload[512];

		int						ObjectCount;
		core::object_t**		Object;

		int						StageCount;
		core::stage_t**			Stage;

		// ----------------------------------------------------------------- //

		void submit(core::gcl::context* aContext);
		void remove(core::gcl::context* aContext);

		void submit(core::object_t* aObject);
		void remove(core::object_t* aObject);

		void submit(core::object::system_window* aSystemWindow);
		void remove(core::object::system_window* aSystemWindow);

		void submit(core::stage_t* aStage);
		void remove(core::stage_t* aStage);

		// Signals to update thread to create window handle
		// because glfw is written by lobotomites.
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

		// Returns index of of pointer, -1 if doesn't exist. 
		int filidx(core::io::file* aFile);
		int ctxidx(core::gcl::context* aCtx);
		int objidx(core::object_t* aObj);
		int winidx(core::object::system_window* aWin);
		int stgidx(core::stage_t* aStg);

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

		core::logic::trap RenderUpdateTrap;

		void trender();			// Thread honors frame rates of respective targets.
		void taudio();			// Thread Handles audio streams.
		void tsterminal();		// Thread handles terminal input to the engine.


	};

}

#endif // !GEODESUKA_ENGINE_H
