#pragma once
#ifndef GEODESUKA_ENGINE_H
#define GEODESUKA_ENGINE_H

/* Standard C Libraries*/

/* Standard C++ Libraries*/
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>

/* Third Party Libraries */
#include <vulkan/vulkan.h>

/* Engine Configuration */
#include "config.h"

/* Math Library */
#include "core/math.h"

/* Engine Utility Library */
#include "core/util.h"

/* Input/Output File System Library*/
#include "core/io.h"

/* Human Interface Device Library */
#include "core/hid.h"

/* Sound Library */
#include "core/sound.h"

/* Graphics & Computation Library */
#include "core/gcl.h"

/* Graphics */
#include "core/graphics.h"

/* Object Library */
#include "core/object.h"

/* Stage Library */
#include "core/stage.h"

/* Application Interface */
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

		// TODO: Reference Pools?
		//const char* get_process_directory();
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

		const version Version = { 0, 1, 0 }; // Major, Minor, Revision
		const int Date = 20220529; //YYYYMMDD
		std::vector<const char*> Layer;
		std::vector<const char*> Extension;
		vk_application_info AppInfo{};
		vk_instance_create_info CreateInfo{};
		vk_instance Handle;

		// ------------------------------ Engine State ------------------------------ //
		
		std::mutex Mutex;
		state::id StateID;
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
		core::util::str CurrentWorkingDirectory;
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

		void update(double aTimeStep);		// 
		void render();						// Thread honors frame rates of respective targets.
		void audio();						// Thread Handles audio streams.
		void terminal();					// Thread handles terminal input to the engine.

	};

}

#endif // !GEODESUKA_ENGINE_H
