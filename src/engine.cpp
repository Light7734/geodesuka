#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */
#include <cstdlib>
#include <cstring>
#include <cassert>

/* --------------- Standard C++ Libraries --------------- */
#include <iostream>

#include <vector>
#include <chrono>

/* --------------- Platform Dependent Libraries --------------- */
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif defined(__APPLE__) || defined(MACOSX)

#elif defined(__linux__) && !defined(__ANDROID__)
#include <unistd.h>
#elif defined(__ANDROID__)
#include <unistd.h>
#endif

/* --------------- Third Party Libraries --------------- */

#include <GLFW/glfw3.h>

namespace geodesuka {
	
	using namespace core;
	using namespace gcl;
	using namespace object;
	using namespace logic;

	engine::engine(int aCmdArgCount, const char** aCmdArgList, int aLayerCount, const char** aLayerList, int aExtensionCount, const char** aExtensionList) {

		//this->State = state::CREATION;
		this->isReady = false;
		this->Shutdown.store(false);
		//this->ThreadsLaunched.store(false);
		this->Handle = VK_NULL_HANDLE;

		this->WindowTempData.Property = window::prop();
		this->WindowTempData.Width = 0;
		this->WindowTempData.Height = 0;
		this->WindowTempData.Title = NULL;
		this->WindowTempData.Monitor = NULL;
		this->WindowTempData.Window = NULL;
		this->ReturnWindow = NULL;


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

		// (GLSLang)
		isGLSLANGReady = shader::initialize();

		// (GLFW) Must be initialized first for OS extensions.
		isGLFWReady = system_window::initialize();

		// (Vulkan) Load required window extensions.
		if (isGLFWReady) {

			// Adds WSI instance extensions to list.
			for (size_t i = 0; i < system_window::RequiredInstanceExtension.size(); i++) {
				this->Extension.push_back(system_window::RequiredInstanceExtension[i]);
			}

			// Adds proposed layers to list.
			for (int i = 0; i < aLayerCount; i++) {
				this->Layer.push_back(aLayerList[i]);
			}

			// Adds proposed extensions.
			for (int i = 0; i < aExtensionCount; i++) {
				this->Extension.push_back(aExtensionList[i]);
			}

			//"VK_KHR_display";
			// Does not work on Windows OS right now, only Linux
			//this->Extension.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);		

			this->AppInfo.sType							= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			this->AppInfo.pNext							= NULL;
			this->AppInfo.pApplicationName				= "";
			this->AppInfo.applicationVersion			= VK_MAKE_VERSION(0, 0, 1);
			this->AppInfo.pEngineName					= "Geodesuka Engine";
			this->AppInfo.engineVersion					= VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Revision);
			this->AppInfo.apiVersion					= VK_MAKE_VERSION(1, 2, 0);

			this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			this->CreateInfo.pNext						= NULL;
			this->CreateInfo.flags						= 0;
			this->CreateInfo.pApplicationInfo			= &this->AppInfo;
			this->CreateInfo.enabledLayerCount			= (uint32_t)this->Layer.size();
			this->CreateInfo.ppEnabledLayerNames		= this->Layer.data();
			this->CreateInfo.enabledExtensionCount		= (uint32_t)this->Extension.size();
			this->CreateInfo.ppEnabledExtensionNames	= this->Extension.data();

			VkResult Result = vkCreateInstance(&this->CreateInfo, NULL, &this->Handle);
			if (Result == VK_SUCCESS) {
				isVulkanReady = true;
			}
			else {
				isVulkanReady = false;
			}
		}

		if (isGLSLANGReady && isGLFWReady && isVulkanReady) {
			this->ID = state::id::CREATION;

			this->SystemTerminal = nullptr;
			this->PrimaryDevice = nullptr;
			this->PrimaryDisplay = nullptr;

			// Represent System Terminal
			this->SystemTerminal = new system_terminal(this, nullptr, nullptr);

			// Gathers Graphics & Compute devices
			VkResult Result = VK_SUCCESS;
			uint32_t PhysicalDeviceCount = 0;
			Result = vkEnumeratePhysicalDevices(this->Handle, &PhysicalDeviceCount, NULL);
			std::vector<VkPhysicalDevice> PhysicalDevice(PhysicalDeviceCount);
			Result = vkEnumeratePhysicalDevices(this->Handle, &PhysicalDeviceCount, PhysicalDevice.data());
			if (PhysicalDeviceCount > 0) {
				for (uint32_t i = 0; i < PhysicalDeviceCount; i++) {
					this->Device.push_back(new device(this->Handle, PhysicalDevice[i]));
				}
			}

			//vkGetPhysicalDeviceDisplayPropertiesKHR;

			// Gathers current display setup
			if (glfwGetPrimaryMonitor() != NULL) {
				this->PrimaryDisplay = new system_display(this, nullptr, glfwGetPrimaryMonitor());
				int MonitorCount;
				GLFWmonitor** Monitors = glfwGetMonitors(&MonitorCount);
				for (int i = 0; i < MonitorCount; i++) {
					if (Monitors[i] != glfwGetPrimaryMonitor()) {
						this->Display[i] = new system_display(this, nullptr, Monitors[i]);
					}
					else {
						this->Display[i] = this->PrimaryDisplay;
					}
				}
			}

			// Associate devices with slave system_display. Can only be done with extension VK_KHR_display

			// Construct Desktop Stages.
			for (size_t i = 0; i < this->Display.size(); i++) {
				stage::desktop* Desktop = new stage::desktop(this, nullptr, this->Display[i]);
				this->Display[i]->Stage;
				this->Stage.push_back(this->Display[i]->Stage);
			}

			// Load SystemTerminal, SystemDisplay[0], SystemDisplay[1], ... SystemDisplay[n-1]. 
			Object.push_back(SystemTerminal);
			for (size_t i = 0; i < Display.size(); i++) {
				Object.push_back(Display[i]);
			}

			isGCDeviceAvailable = this->Device.size() > 0;
			isSystemDisplayAvailable = this->Display.size() > 0;
		}

		// Store main thread ID.
		this->MainThreadID = std::this_thread::get_id();

		this->SignalCreate.store(false);
		this->WindowCreated.store(false);
		// Window Temp Data?
		this->ReturnWindow = NULL;
		this->DestroyWindow.store(NULL);

		this->isReady = isGLSLANGReady && isGLFWReady && isVulkanReady && isGCDeviceAvailable && isSystemDisplayAvailable;
		this->ID = this->isReady ? state::id::READY : state::id::FAILURE;

	}

	engine::~engine() {

		this->ID = state::id::DESTRUCTION;

		this->SystemTerminal = nullptr;
		this->PrimaryDevice = nullptr;
		this->PrimaryDisplay = nullptr;
		this->Display.clear();
		this->SystemWindow.clear();

		for (size_t i = 0; i < this->Stage.size(); i++) {
			delete this->Stage[i];
		}

		for (size_t i = 0; i < this->Object.size(); i++) {
			delete this->Object[i];
		}

		for (size_t i = 0; i < this->Stage.size(); i++) {
			delete this->Context[i];
		}

		for (size_t i = 0; i < this->Stage.size(); i++) {
			delete this->File[i];
		}

		this->Stage.clear();
		this->Object.clear();
		this->Context.clear();
		this->File.clear();

		for (size_t i = 0; i < this->Device.size(); i++) {
			delete this->Device[i];
		}

		this->Device.clear();

		vkDestroyInstance(this->Handle, NULL);

		system_window::terminate();

		shader::terminate();

	}

	core::io::file* engine::open(const char* aFilePath) {
		// utilizes singleton.
		core::io::file* lFileHandle = core::io::file::open(aFilePath);
		if (lFileHandle != nullptr) {

		}

		return nullptr;
	}

	void engine::close(core::io::file* aFile) {

	}

	core::gcl::device** engine::get_device_list(size_t* aListSize) {
		*aListSize = this->Device.size();
		return this->Device.data();
	}

	core::gcl::device* engine::get_primary_device() {
		return this->PrimaryDevice;
	}

	core::object::system_display** engine::get_display_list(size_t* aListSize) {
		*aListSize = this->Display.size();
		return this->Display.data();
	}

	core::object::system_display* engine::get_primary_display() {
		return this->PrimaryDisplay;
	}

	VkInstance engine::handle() {
		return this->Handle;
	}

	bool engine::is_ready() {
		return this->isReady;
	}

	engine::version engine::get_version() {
		return this->Version;
	}

	int engine::get_date() {
		return this->Date;
	}

	/*
	
	update and render thread pseudo code.

	// Rules.

	// Graphics DEPENDS ON Transfer & Compute to finish.
	// Compute DEPENDS ON Transfer.

	update() {
		
		// GPU Context State Transfer -> Compute -> Graphics -> Transfer -> .. (Repeat)

		// step 1
		// Wait for all context transfer operations to complete before 
		// doing host updates and transfer and compute command polling

		// step 2
		// update all host objects and host stages, then aggregate next
		// transfer and compute operations.

		// step 3
		// Use semaphores to make gpu dependency on

		// step 4 
		// Wait for all graphics and compute operations to finish executing
		// on all contexts before the submission of transfer operation commands.
		
		// step 5
		// (Mutual Exclusion) begin transfer operations 

	}

	render() {
		
		// step 1
		// Aggregate all draw commands from ready rendertargets.

		// step 2
		// wait for graphics operations to complete for previous draw.

		// step 3
		// 

	}

	*/


	// --------------- Engine Main Thread --------------- //
	// The main thread is used to spawn backend threads along
	// with the app thread.
	// --------------- Engine Main Thread --------------- //
	int engine::run(core::app* aApp) {

		// Store main thread ID.

		this->ID						= state::RUNNING;
		this->MainThreadID				= std::this_thread::get_id();
		this->RenderThread				= std::thread(&engine::render, this);
		this->SystemTerminalThread		= std::thread(&engine::terminal, this);
		this->AppThread					= std::thread(&core::app::run, aApp);

		this->update();

		this->RenderThread.join();
		this->SystemTerminalThread.join();
		this->AppThread.join();
		this->ID = state::READY;

		return 0;
	}

	//int engine::winidx(core::object::system_window* aWin) {
	//	for (int i = 0; i < this->SystemWindow.size(); i++) {
	//		if (this->SystemWindow[i] == aWin) return i;
	//	}
	//	return 0;
	//}
	//
	//int engine::filidx(core::io::file* aFile) {
	//	for (int i = 0; i < this->File.size(); i++) {
	//		if (this->File[i] == aFile) return i;
	//	}
	//	return -1;
	//}
	//
	//int engine::ctxidx(core::gcl::context* aCtx) {
	//	for (int i = 0; i < this->Context.size(); i++) {
	//		if (this->Context[i] == aCtx) return i;
	//	}
	//	return -1;
	//}
	//
	//int engine::objidx(core::object_t* aObj) {
	//	for (int i = 0; i < this->Object.size(); i++) {
	//		if (this->Object[i] == aObj) return i;
	//	}
	//	return -1;
	//}
	//
	//int engine::stgidx(core::stage_t* aStg) {
	//	for (int i = 0; i < this->Stage.size(); i++) {
	//		if (this->Stage[i] == aStg) return i;
	//	}
	//	return -1;
	//}

	void engine::update() {

		double DeltaTime = 0.0;
		time_step TimeStep(0.01);

		// The update thread is the main thread.
		while (!this->Shutdown.load()) {
			// Suspend thread if called.
			this->ThreadTrap.door();

			// Start TimeStep Enforcer.
			TimeStep.start();

			// Process system_window constructor calls.
			this->mtcd_process_window_handle_call();

			// Poll Input Events.
			glfwPollEvents();

			// ----- ----- Host Work is done here... ----- -----

			// Update all objects independent of stage, and acquire all transfer operations.
			for (size_t i = 0; i < Context.size(); i++) {
				for (size_t j = 0; j < Object.size(); j++) {
					if (Context[i] == Object[j]->Context) {
						Context[i]->BackBatch[0] += Object[i]->update(DeltaTime);
						Context[i]->BackBatch[1] += Object[i]->compute();
					}
				}
			}

			// Update all stages, and acquire all transfer operations.
			for (size_t i = 0; i < Context.size(); i++) {
				for (size_t j = 0; j < Stage.size(); j++) {
					if (Context[i] == Stage[j]->Context) {
						Context[i]->BackBatch[0] += Stage[i]->update(DeltaTime);
						Context[i]->BackBatch[1] += Stage[i]->compute();
					}
				}
			}

			// Per Context/GPU works is submitted in this section.
			VkResult Result = VkResult::VK_SUCCESS;
			for (size_t i = 0; i < this->Context.size(); i++) {
				// Lock Context for execution.
				this->Context[i]->ExecutionMutex.lock();

				// Iterate through all workbatches and search for inflight operations.
				for (int j = 0; j < 3; j++) {
					if (this->Context[i]->WorkBatch[j].SubmissionCount > 0) {
						vkWaitForFences(this->Context[i]->Handle, 1, &this->Context[i]->ExecutionFence[j], VK_TRUE, UINT64_MAX);
						vkResetFences(this->Context[i]->Handle, 1, &this->Context[i]->ExecutionFence[j]);
						this->Context[i]->WorkBatch[j].clear();
					}
				}

				// Check if either transfer back batch, or compute back batch have accumulated submission.
				if ((this->Context[i]->BackBatch[0].SubmissionCount > 0) || (this->Context[i]->BackBatch[1].SubmissionCount > 0)) {
					// Loads back batch, ready for execution.
					this->Context[i]->WorkBatch[0] = this->Context[i]->BackBatch[0];
					this->Context[i]->WorkBatch[1] = this->Context[i]->BackBatch[1];

					// Clears back batch for another run through.
					this->Context[i]->BackBatch[0].clear();
					this->Context[i]->BackBatch[1].clear();

					// Submit Current Transfer Workload.
					if (this->Context[i]->WorkBatch[0].SubmissionCount > 0) {
						this->Context[i]->execute(device::qfs::TRANSFER, this->Context[i]->WorkBatch[0], this->Context[i]->ExecutionFence[0]);
					}

					// Submit Current Compute Workload.
					if (this->Context[i]->WorkBatch[1].SubmissionCount > 0) {
						this->Context[i]->execute(device::qfs::COMPUTE, this->Context[i]->WorkBatch[1], this->Context[i]->ExecutionFence[1]);
					}
				}

				// Release context from execution lock.
				this->Context[i]->ExecutionMutex.unlock();
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

		while (!this->Shutdown.load()) {
			// Suspend thread if called.
			this->ThreadTrap.door();

			// Aggregate all render operations from each stage to each context.
			for (size_t i = 0; i < this->Context.size(); i++) {
				for (size_t j = 1; j < this->Stage.size(); j++) {
					if (this->Context[i] == this->Stage[j]->Context) {
						this->Context[i]->BackBatch[2] += this->Stage[j]->render();
					}
				}				
			}

			// Per Context/GPU works is submitted in this section.
			VkResult Result = VkResult::VK_SUCCESS;
			for (size_t i = 0; i < this->Context.size(); i++) {
				// If no operations, continue and check next context.
				if ((this->Context[i]->BackBatch[2].SubmissionCount == 0) && (this->Context[i]->BackBatch[2].PresentationCount == 0)) continue;

				// Lock Context for execution.
				this->Context[i]->ExecutionMutex.lock();

				// Iterate through all workbatches and search for inflight operations.
				for (int j = 0; j < 3; j++) {
					if (this->Context[i]->WorkBatch[j].SubmissionCount > 0) {
						vkWaitForFences(this->Context[i]->Handle, 1, &this->Context[i]->ExecutionFence[j], VK_TRUE, UINT64_MAX);
						vkResetFences(this->Context[i]->Handle, 1, &this->Context[i]->ExecutionFence[j]);
						this->Context[i]->WorkBatch[j].clear();
					}
				}

				// Check for Graphics & Compute operations accumulated.
				if (this->Context[i]->BackBatch[2].SubmissionCount > 0) {
					// Loads back batch, ready for execution.
					this->Context[i]->WorkBatch[2] = this->Context[i]->BackBatch[2];

					// Clears back batch for another run through.
					this->Context[i]->BackBatch[2].clear();

					// Submit Current Graphics & Compute Workloads.
					if (this->Context[i]->WorkBatch[2].SubmissionCount > 0) {
						this->Context[i]->execute(device::qfs::GRAPHICS_AND_COMPUTE, this->Context[i]->WorkBatch[2], this->Context[i]->ExecutionFence[2]);
					}

					// Submit All Presentation Commands. (Note: this should not be very often unless lots of system_windows)
					if (this->Context[i]->WorkBatch[2].PresentationCount > 0) {
						this->Context[i]->execute(device::qfs::PRESENT, this->Context[i]->WorkBatch[2], this->Context[i]->ExecutionFence[2]);
					}
				}
				// Release context from executin lock.
				this->Context[i]->ExecutionMutex.unlock();
			}

		}

	}

	void engine::audio() {
		// Does nothing currently.
		while (!this->Shutdown.load()) {
			core::logic::waitfor(1);
		}

	}

	// --------------- System Terminal Thread --------------- //
	// Will be used for runtime debugging of engine using terminal.
	// --------------- System Terminal Thread --------------- //
	void engine::terminal() {

		while (!this->Shutdown.load()) {
			core::logic::waitfor(1.0);
		}

	}

	GLFWwindow* engine::create_window_handle(core::object::window::prop aProperty, int aWidth, int aHeight, const char* aTitle, GLFWmonitor* aMonitor, GLFWwindow* aWindow) {
		GLFWwindow* Temp = NULL;
		if (this->MainThreadID == std::this_thread::get_id()) {
			glfwWindowHint(GLFW_RESIZABLE,			aProperty.Resizable);
			glfwWindowHint(GLFW_DECORATED,			aProperty.Decorated);
			glfwWindowHint(GLFW_FOCUSED,			aProperty.UserFocused);
			glfwWindowHint(GLFW_AUTO_ICONIFY,		aProperty.AutoMinimize);
			glfwWindowHint(GLFW_FLOATING,			aProperty.Floating);
			glfwWindowHint(GLFW_MAXIMIZED,			aProperty.Maximized);
			glfwWindowHint(GLFW_VISIBLE,			aProperty.Visible);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR,	aProperty.ScaleToMonitor);
			glfwWindowHint(GLFW_CENTER_CURSOR,		aProperty.CenterCursor);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW,		aProperty.FocusOnShow);
			glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
			glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE); // TODO: Change to GLFW_DONT_CARE, and remove option.

			Temp = glfwCreateWindow(aWidth, aHeight, aTitle, aMonitor, aWindow);
		}
		else {
			this->WindowTempData.Property = aProperty;
			this->WindowTempData.Width = aWidth;
			this->WindowTempData.Height = aHeight;
			this->WindowTempData.Title = aTitle;
			this->WindowTempData.Monitor = aMonitor;
			this->WindowTempData.Window = aWindow;

			this->WindowCreated.store(false);
			this->SignalCreate.store(true);
			// Wait for window to be created.
			while (!this->WindowCreated.load()) {}
			Temp = this->ReturnWindow;
		}
		return Temp;
	}

	void engine::destroy_window_handle(GLFWwindow* aWindow) {
		if (this->MainThreadID == std::this_thread::get_id()) {
			glfwDestroyWindow(aWindow);
		}
		else {
			while (this->DestroyWindow.load() != NULL) {}
			this->DestroyWindow.store(aWindow);
		}
	}

	void engine::mtcd_process_window_handle_call() {
		if (this->SignalCreate.load()) {
			glfwWindowHint(GLFW_RESIZABLE,			WindowTempData.Property.Resizable);
			glfwWindowHint(GLFW_DECORATED,			WindowTempData.Property.Decorated);
			glfwWindowHint(GLFW_FOCUSED,			WindowTempData.Property.UserFocused);
			glfwWindowHint(GLFW_AUTO_ICONIFY,		WindowTempData.Property.AutoMinimize);
			glfwWindowHint(GLFW_FLOATING,			WindowTempData.Property.Floating);
			glfwWindowHint(GLFW_MAXIMIZED,			WindowTempData.Property.Maximized);
			glfwWindowHint(GLFW_VISIBLE,			WindowTempData.Property.Visible);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR,	WindowTempData.Property.ScaleToMonitor);
			glfwWindowHint(GLFW_CENTER_CURSOR,		WindowTempData.Property.CenterCursor);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW,		WindowTempData.Property.FocusOnShow);
			glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
			glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE); // TODO: Change to GLFW_DONT_CARE, and remove option.

			this->ReturnWindow = glfwCreateWindow(WindowTempData.Width, WindowTempData.Height, WindowTempData.Title, WindowTempData.Monitor, WindowTempData.Window);
			this->WindowCreated.store(true);
			this->SignalCreate.store(false);
		}
		
		// Check if window needs to be destroyed.
		GLFWwindow* temp = this->DestroyWindow.load();
		if (temp != NULL) {
			glfwDestroyWindow(temp);
			this->DestroyWindow.store(NULL);
		}		
	}

}
