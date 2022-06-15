#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */
#include <cstdlib>
#include <cstring>
#include <cassert>

/* --------------- Standard C++ Libraries --------------- */
#include <iostream>

#include <vector>
#include <chrono>

#include <filesystem>

/* --------------- Third Party Libraries --------------- */

#include <GLFW/glfw3.h>

namespace geodesuka {
	
	using namespace core;

	using namespace gcl;
	using namespace hid;
	using namespace io;
	using namespace logic;
	using namespace math;
	using namespace object;
	using namespace stage;
	using namespace util;

	engine::engine(int aCmdArgCount, const char** aCmdArgList, int aLayerCount, const char** aLayerList, int aExtensionCount, const char** aExtensionList) {

		StateID = state::CREATION;
		Shutdown.store(false);
		Handle = VK_NULL_HANDLE;

		bool isGLSLANGReady = false;
		bool isGLFWReady = false;
		bool isVulkanReady = false;
		bool isSystemDisplayAvailable = false;
		bool isGCDeviceAvailable = false;

		// --------------- Initialization Process --------------- //

		// Init Process:
		// Start glslang
		// Start glfw
		// Start vulkan
		// Query for Monitors (No primary monitor = Start up failure)
		// Query for gcl devices (No discrete gpu = Start up failure)
		//

		CurrentWorkingDirectory = std::filesystem::current_path().string().c_str();

		// (GLSLang)
		isGLSLANGReady = shader::initialize();

		// (GLFW) Must be initialized first for OS extensions.
		isGLFWReady = system_window::initialize();

		// (Vulkan) Load required window extensions.
		if (isGLFWReady) {

			// Adds WSI instance extensions to list.
			for (size_t i = 0; i < system_window::RequiredInstanceExtension.size(); i++) {
				Extension.push_back(system_window::RequiredInstanceExtension[i]);
			}

			// Adds proposed layers to list.
			for (int i = 0; i < aLayerCount; i++) {
				Layer.push_back(aLayerList[i]);
			}

			// Adds proposed extensions.
			for (int i = 0; i < aExtensionCount; i++) {
				Extension.push_back(aExtensionList[i]);
			}

			//"VK_KHR_display";
			// Does not work on Windows OS right now, only Linux
			//this->Extension.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);		

			AppInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			AppInfo.pNext						= NULL;
			AppInfo.pApplicationName			= "";
			AppInfo.applicationVersion			= VK_MAKE_VERSION(0, 0, 1);
			AppInfo.pEngineName					= "Geodesuka Engine";
			AppInfo.engineVersion				= VK_MAKE_VERSION(Version.Major, Version.Minor, Version.Revision);
			AppInfo.apiVersion					= VK_MAKE_VERSION(1, 2, 0);

			CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			CreateInfo.pNext					= NULL;
			CreateInfo.flags					= 0;
			CreateInfo.pApplicationInfo			= &AppInfo;
			CreateInfo.enabledLayerCount		= (uint32_t)Layer.size();
			CreateInfo.ppEnabledLayerNames		= Layer.data();
			CreateInfo.enabledExtensionCount	= (uint32_t)Extension.size();
			CreateInfo.ppEnabledExtensionNames	= Extension.data();

			VkResult Result = vkCreateInstance(&CreateInfo, NULL, &Handle);
			if (Result == VK_SUCCESS) {
				isVulkanReady = true;
			}
			else {
				isVulkanReady = false;
			}
		}

		// APIs initialized, query for hardware options.
		if (isGLSLANGReady && isGLFWReady && isVulkanReady) {

			// Represent System Terminal
			SystemTerminal = new system_terminal(this, nullptr, nullptr);
			PrimaryDevice = nullptr;
			PrimaryDisplay = nullptr;

			// Gathers Graphics & Compute devices
			VkResult Result = VK_SUCCESS;
			uint32_t PhysicalDeviceCount = 0;
			Result = vkEnumeratePhysicalDevices(Handle, &PhysicalDeviceCount, NULL);
			std::vector<VkPhysicalDevice> PhysicalDevice(PhysicalDeviceCount);
			Result = vkEnumeratePhysicalDevices(Handle, &PhysicalDeviceCount, PhysicalDevice.data());
			if (PhysicalDeviceCount > 0) {
				for (uint32_t i = 0; i < PhysicalDeviceCount; i++) {
					Device.push_back(new device(Handle, PhysicalDevice[i]));
				}
			}

			//vkGetPhysicalDeviceDisplayPropertiesKHR;

			// Gathers current display setup
			if (glfwGetPrimaryMonitor() != NULL) {
				PrimaryDisplay = new system_display(this, nullptr, glfwGetPrimaryMonitor());
				int MonitorCount;
				GLFWmonitor** Monitors = glfwGetMonitors(&MonitorCount);
				for (int i = 0; i < MonitorCount; i++) {
					if (Monitors[i] != glfwGetPrimaryMonitor()) {
						this->Display.push_back(new system_display(this, nullptr, Monitors[i]));
					}
					else {
						this->Display.push_back(PrimaryDisplay);
					}
				}
			}

			// Associate devices with slave system_display. Can only be done with extension VK_KHR_display

			// Load SystemTerminal, SystemDisplay[0], SystemDisplay[1], ... SystemDisplay[n-1]. 
			Object.push_back(SystemTerminal);
			for (size_t i = 0; i < Display.size(); i++) {
				Object.push_back(Display[i]);
			}

			// Construct Desktop Stages.
			for (size_t i = 0; i < Display.size(); i++) {
				desktop* Desktop = new desktop(this, nullptr, Display[i]);
				Display[i]->Stage = Desktop;
				Stage.push_back(Desktop);
			}

			isGCDeviceAvailable = Device.size() > 0;
			isSystemDisplayAvailable = Display.size() > 0;
		}

		// Store main thread ID.
		this->MainThreadID = std::this_thread::get_id();

		// Is ready if startup condition = success.
		StateID = isGLSLANGReady && isGLFWReady && isVulkanReady && isGCDeviceAvailable && isSystemDisplayAvailable ? state::id::READY : state::id::FAILURE;

	}

	engine::~engine() {

		StateID = state::id::DESTRUCTION;

		SystemTerminal = nullptr;
		PrimaryDevice = nullptr;
		PrimaryDisplay = nullptr;
		Display.clear();
		SystemWindow.clear();

		for (size_t i = 0; i < Stage.size(); i++) {
			delete Stage[i];
		}

		for (size_t i = 0; i < Object.size(); i++) {
			delete Object[i];
		}

		for (size_t i = 0; i < Context.size(); i++) {
			delete Context[i];
		}

		for (size_t i = 0; i < File.size(); i++) {
			delete File[i];
		}

		Stage.clear();
		Object.clear();
		Context.clear();
		File.clear();

		for (size_t i = 0; i < Device.size(); i++) {
			delete Device[i];
		}

		Device.clear();

		vkDestroyInstance(Handle, NULL);

		system_window::terminate();

		shader::terminate();

	}

	file* engine::open(const char* aFilePath) {
		std::filesystem::path FilePath = aFilePath;

		// Check if Relative Path, or absolute.
		if (FilePath.is_relative()) {
			FilePath = std::filesystem::absolute(FilePath);
		}

		// Check if File has already been loaded.
		for (size_t i = 0; i < File.size(); i++) {
			if (File[i]->get_path() == FilePath.string().c_str()) {
				return File[i];
			}
		}

		// Check if file path exists.
		if (!std::filesystem::exists(FilePath)) {
			return nullptr;
		}

		// If File Exists, open it.
		file* NewFile = file::open(FilePath.string().c_str());

		File.push_back(NewFile);

		return NewFile;
	}

	void engine::close(file* aFile) {

	}

	device** engine::get_device_list(size_t* aListSize) {
		*aListSize = Device.size();
		return Device.data();
	}

	device* engine::get_primary_device() {
		return PrimaryDevice;
	}

	system_display** engine::get_display_list(size_t* aListSize) {
		*aListSize = Display.size();
		return Display.data();
	}

	system_display* engine::get_primary_display() {
		return PrimaryDisplay;
	}

	VkInstance engine::handle() {
		return Handle;
	}

	bool engine::is_ready() {
		return (StateID == state::id::READY);
	}

	engine::version engine::get_version() {
		return Version;
	}

	int engine::get_date() {
		return Date;
	}

	int engine::run(app* aApp) {

		StateID						= state::id::RUNNING;
		MainThreadID				= std::this_thread::get_id();
		RenderThread				= std::thread(&engine::render, this);
		SystemTerminalThread		= std::thread(&engine::terminal, this);
		AppThread					= std::thread(&app::prerun, aApp);

		this->update(aApp->TimeStep);

		RenderThread.join();
		SystemTerminalThread.join();
		AppThread.join();
		StateID = state::id::READY;

		return 0;
	}

	// --------------- Engine Main Thread --------------- //
	// The main thread is used to spawn backend threads along
	// with the app thread.
	// --------------- Engine Main Thread --------------- //
	void engine::update(double aTimeStep) {

		double DeltaTime = 0.0;
		time_step TimeStep(aTimeStep);

		// The update thread is the main thread.
		while (!Shutdown.load()) {
			// Suspend thread if called.
			ThreadTrap.door();

			// Start TimeStep Enforcer.
			TimeStep.start();

			// Process system_window constructor calls.
			system_window::mtcd_process_window_handle_call();

			// Poll Input Events.
			system_window::poll_events();

			// ----- ----- Host Work is done here... ----- -----

			// Update all objects independent of stage, and acquire all transfer operations.
			for (size_t i = 0; i < Context.size(); i++) {
				if (!Context[i]->isReadyToBeProcessed.load()) continue;
				for (size_t j = 0; j < Object.size(); j++) {
					if ((Object[j]->isReadyToBeProcessed.load()) && (Object[j]->Context == Context[i])) {
						Context[i]->BackBatch[0] += Object[i]->update(DeltaTime);
						Context[i]->BackBatch[1] += Object[i]->compute();
					}
				}
			}

			// Update all stages, and acquire all transfer operations.
			for (size_t i = 0; i < Context.size(); i++) {
				if (!Context[i]->isReadyToBeProcessed.load()) continue;
				for (size_t j = 0; j < Stage.size(); j++) {
					for (size_t k = 0; k < Stage[j]->RenderTarget.size(); k++) {
						Stage[j]->RenderTarget[k]->FrameRateTimer.update(DeltaTime);
					}
					if ((Stage[j]->isReadyToBeProcessed.load()) && (Stage[j]->Context == Context[i])) {
						Context[i]->BackBatch[0] += Stage[i]->update(DeltaTime);
						Context[i]->BackBatch[1] += Stage[i]->compute();
					}
				}
			}

			// Per Context/GPU works is submitted in this section.
			VkResult Result = VkResult::VK_SUCCESS;
			for (size_t i = 0; i < Context.size(); i++) {
				// Go to next context if not ready.
				if (!Context[i]->isReadyToBeProcessed.load()) continue;

				// Lock Context for execution.
				Context[i]->ExecutionMutex.lock();

				// Iterate through all workbatches and search for inflight operations.
				for (int j = 0; j < 3; j++) {
					if (Context[i]->WorkBatch[j].SubmissionCount > 0) {
						vkWaitForFences(Context[i]->Handle, 1, &Context[i]->ExecutionFence[j], VK_TRUE, UINT64_MAX);
						vkResetFences(Context[i]->Handle, 1, &Context[i]->ExecutionFence[j]);
						Context[i]->WorkBatch[j].clear();
					}
				}

				// Check if either transfer back batch, or compute back batch have accumulated submission.
				if ((Context[i]->BackBatch[0].SubmissionCount > 0) || (Context[i]->BackBatch[1].SubmissionCount > 0)) {
					// Loads back batch, ready for execution.
					Context[i]->WorkBatch[0] = Context[i]->BackBatch[0];
					Context[i]->WorkBatch[1] = Context[i]->BackBatch[1];

					// Clears back batch for another run through.
					Context[i]->BackBatch[0].clear();
					Context[i]->BackBatch[1].clear();

					// Submit Current Transfer Workload.
					if (Context[i]->WorkBatch[0].SubmissionCount > 0) {
						Context[i]->execute(device::qfs::TRANSFER, Context[i]->WorkBatch[0], Context[i]->ExecutionFence[0]);
					}

					// Submit Current Compute Workload.
					if (Context[i]->WorkBatch[1].SubmissionCount > 0) {
						Context[i]->execute(device::qfs::COMPUTE, Context[i]->WorkBatch[1], Context[i]->ExecutionFence[1]);
					}
				}

				// Release context from execution lock.
				Context[i]->ExecutionMutex.unlock();
			}

			// Enforce Time Step, and calculate dt.
			DeltaTime = TimeStep.stop();
		}

	}

	// --------------- Render Thread --------------- //
	// The job of the render thread is to honor and schedule draw
	// calls of respective render targets stored in memory.
	// --------------- Render Thread --------------- //
	void engine::render() {

		while (!Shutdown.load()) {
			// Suspend thread if called.
			ThreadTrap.door();

			// Aggregate all render operations from each stage to each context.
			for (size_t i = 0; i < Context.size(); i++) {
				// Go to next context if not ready.
				if (!Context[i]->isReadyToBeProcessed.load()) continue;
				for (size_t j = 1; j < Stage.size(); j++) {
					// Go to next stage if stage is not ready.
					if ((Stage[j]->isReadyToBeProcessed.load()) && (Stage[j]->Context == Context[i])) {
						Context[i]->BackBatch[2] += Stage[j]->render();
					}
				}				
			}

			// Per Context/GPU works is submitted in this section.
			VkResult Result = VkResult::VK_SUCCESS;
			for (size_t i = 0; i < Context.size(); i++) {
				// Go to next context if not ready.
				if (!Context[i]->isReadyToBeProcessed.load()) continue;

				// If no operations, continue and check next context.
				if ((Context[i]->BackBatch[2].SubmissionCount == 0) && (Context[i]->BackBatch[2].PresentationCount == 0)) continue;

				// Lock Context for execution.
				Context[i]->ExecutionMutex.lock();

				// Iterate through all workbatches and search for inflight operations.
				for (int j = 0; j < 3; j++) {
					if (Context[i]->WorkBatch[j].SubmissionCount > 0) {
						vkWaitForFences(Context[i]->Handle, 1, &Context[i]->ExecutionFence[j], VK_TRUE, UINT64_MAX);
						vkResetFences(Context[i]->Handle, 1, &Context[i]->ExecutionFence[j]);
						Context[i]->WorkBatch[j].clear();
					}
				}

				// Check for Graphics & Compute operations accumulated.
				if (Context[i]->BackBatch[2].SubmissionCount > 0) {
					// Loads back batch, ready for execution.
					Context[i]->WorkBatch[2] = Context[i]->BackBatch[2];

					// Clears back batch for another run through.
					Context[i]->BackBatch[2].clear();

					// Submit Current Graphics & Compute Workloads.
					if (Context[i]->WorkBatch[2].SubmissionCount > 0) {
						Context[i]->execute(device::qfs::GRAPHICS_AND_COMPUTE, Context[i]->WorkBatch[2], Context[i]->ExecutionFence[2]);
					}

					// Submit All Presentation Commands. (Note: this should not be very often unless lots of system_windows)
					if (Context[i]->WorkBatch[2].PresentationCount > 0) {
						Context[i]->execute(device::qfs::PRESENT, Context[i]->WorkBatch[2], Context[i]->ExecutionFence[2]);
					}
				}
				// Release context from executin lock.
				Context[i]->ExecutionMutex.unlock();
			}

		}

	}

	void engine::audio() {
		// Does nothing currently.
		while (!Shutdown.load()) {
			//waitfor(1);
		}

	}

	// --------------- System Terminal Thread --------------- //
	// Will be used for runtime debugging of engine using terminal.
	// --------------- System Terminal Thread --------------- //
	void engine::terminal() {

		while (!Shutdown.load()) {
			//waitfor(1.0);
		}

	}

}
