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

#include <glslang/Public/ShaderLang.h>


namespace geodesuka {
	
	using namespace core;
	using namespace gcl;
	using namespace object;
	using namespace logic;

	engine::state::state(engine* aEngine) {

		this->ID = id::CREATION;

		this->SystemTerminal = nullptr;
		this->PrimaryDevice = nullptr;
		this->PrimaryDisplay = nullptr;

		// Represent System Terminal
		this->SystemTerminal = new system_terminal(aEngine, nullptr, nullptr);

		// Gathers Graphics & Compute devices
		VkResult Result = VK_SUCCESS;
		uint32_t PhysicalDeviceCount = 0;
		Result = vkEnumeratePhysicalDevices(aEngine->Handle, &PhysicalDeviceCount, NULL);
		std::vector<VkPhysicalDevice> PhysicalDevice(PhysicalDeviceCount);
		Result = vkEnumeratePhysicalDevices(aEngine->Handle, &PhysicalDeviceCount, PhysicalDevice.data());
		if (PhysicalDeviceCount > 0) {
			for (uint32_t i = 0; i < PhysicalDeviceCount; i++) {
				this->Device.push_back(new device(aEngine->Handle, PhysicalDevice[i]));
			}
		}

		// Gathers current display setup
		if (glfwGetPrimaryMonitor() != NULL) {
			this->PrimaryDisplay = new system_display(aEngine, nullptr, glfwGetPrimaryMonitor());
			int MonitorCount;
			GLFWmonitor** Monitors = glfwGetMonitors(&MonitorCount);
			for (int i = 0; i < MonitorCount; i++) {
				if (Monitors[i] != glfwGetPrimaryMonitor()) {
					this->Display[i] = new system_display(aEngine, nullptr, Monitors[i]);
				}
				else {
					this->Display[i] = this->PrimaryDisplay;
				}
			}
		}

		// Construct Desktop Stages.
		for (size_t i = 0; i < this->Display.size(); i++) {
			stage::desktop* Desktop = new stage::desktop(aEngine, nullptr, this->Display[i]);
			this->Display[i]->Stage;
			this->Stage.push_back(this->Display[i]->Stage);
		}

	}

	engine::state::~state() {
		
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

	}

	//void engine::state::submit(core::gcl::context* aContext) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	//
	//	this->Context[this->ContextCount] = aContext;
	//	this->Workload[this->ContextCount] = new workload(aContext);
	//	this->ContextCount += 1;
	//
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	//
	//void engine::state::remove(core::gcl::context* aContext) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	//
	//	int CtxIdx = this->ctxidx(aContext);
	//	int MoveCount = (this->ContextCount - 1) - CtxIdx;
	//
	//	delete this->Workload[CtxIdx];
	//	this->Context[CtxIdx] = nullptr;
	//	this->Workload[CtxIdx] = nullptr;
	//
	//	memmove(&this->Context[CtxIdx], &this->Context[CtxIdx + 1], MoveCount * sizeof(context*));
	//	memmove(&this->Workload[CtxIdx], &this->Workload[CtxIdx + 1], MoveCount * sizeof(context*));
	//
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	//
	//void engine::state::submit(core::object_t* aObject) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	//
	//	void* nptr = NULL;
	//
	//	if (this->Object == NULL) {
	//		nptr = malloc(sizeof(object_t*));
	//	}
	//	else {
	//		nptr = realloc(this->Object, (this->ObjectCount + 1) * sizeof(object_t*));
	//	}
	//
	//	assert(!(nptr == NULL));
	//
	//	this->Object = (object_t**)nptr;
	//	this->Object[this->ObjectCount] = aObject;
	//	this->ObjectCount += 1;
	//
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	//
	//void engine::state::remove(core::object_t* aObject) {
	//	// Should be fine?
	//	//if (this->State != state::READY) return;
	//
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	//
	//	int ObjIdx = this->objidx(aObject);
	//	if (ObjIdx >= 0) {
	//		if (this->ObjectCount == 1) {
	//			free(this->Object);
	//			this->Object = NULL;
	//			this->ObjectCount = 0;
	//		}
	//		else {
	//			this->Object[ObjIdx] = nullptr;
	//			int MoveCount = (this->ObjectCount - 1) - ObjIdx;
	//			if (MoveCount > 0) {
	//				memmove(&this->Object[ObjIdx], &this->Object[ObjIdx + 1], MoveCount * sizeof(object_t*));
	//			}
	//			void* nptr = realloc(this->Object, (this->ObjectCount - 1) * sizeof(object_t*));
	//			assert(!(nptr == NULL));
	//			this->Object = (object_t**)nptr;
	//			this->ObjectCount -= 1;
	//		}
	//	}
	//
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	//
	//void engine::state::submit(core::object::system_window* aSystemWindow) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	// 
	//	// Put at end of SystemWindow List.
	//	int Offset = 1 + this->DisplayCount + this->SystemWindowCount;
	//	int MoveCount = (this->ObjectCount - 1) - Offset;
	// 
	//	void* nptr = NULL;
	// 
	//	if (this->Object == NULL) {
	//		nptr = malloc(sizeof(object_t*));
	//	}
	//	else {
	//		nptr = realloc(this->Object, (this->ObjectCount + 1) * sizeof(object_t*));
	//	}
	// 
	//	// If this dereferences a null pointer, oh well.
	//	assert(!(nptr == NULL));
	// 
	//	this->Object = (object_t**)nptr;
	// 
	//	this->SystemWindow[this->SystemWindowCount] = aSystemWindow;
	//	if (MoveCount > 0) {
	//		memmove(&this->Object[Offset], &this->Object[Offset + 1], MoveCount * sizeof(object_t*));
	//	}
	//	this->Object[Offset] = aSystemWindow;
	// 
	//	this->SystemWindowCount += 1;
	//	this->ObjectCount += 1;
	// 
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	// 
	//void engine::state::remove(core::object::system_window* aSystemWindow) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	// 
	//	int WinIdx = this->winidx(aSystemWindow);
	//	if (WinIdx >= 0) {
	//		int MoveCount = (this->SystemWindowCount - 1) - WinIdx;
	//		this->SystemWindow[WinIdx] = nullptr;
	//		if (MoveCount > 0) {
	//			memmove(&this->SystemWindow[WinIdx], &this->SystemWindow[WinIdx + 1], MoveCount * sizeof(system_window*));
	//		}
	//		this->SystemWindow[this->SystemWindowCount - 1] = nullptr;
	//		this->SystemWindowCount -= 1;
	//	}
	// 
	//	int ObjIdx = this->objidx(aSystemWindow);
	//	if (ObjIdx >= 0) {
	//		int MoveCount = (this->ObjectCount - 1) - ObjIdx;
	//		this->Object[ObjIdx] = nullptr;
	//		if (MoveCount > 0) {
	//			memmove(&this->Object[ObjIdx], &this->Object[ObjIdx + 1], MoveCount * sizeof(object_t*));
	//		}
	//		this->Object[this->ObjectCount - 1] = nullptr;
	//		this->ObjectCount -= 1;
	//	}
	// 
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	// 
	//void engine::state::submit(core::stage_t* aStage) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	// 
	//	void* nptr = NULL;
	//	if (this->Stage == NULL) {
	//		nptr = malloc(sizeof(core::stage_t*));
	//	}
	//	else {
	//		nptr = realloc(this->Stage, (this->StageCount + 1) * sizeof(core::stage_t*));
	//	}
	// 
	//	assert(!(nptr == NULL));
	// 
	//	this->Stage[this->StageCount] = aStage;
	//	this->StageCount += 1;
	// 
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}
	// 
	//void engine::state::remove(core::stage_t* aStage) {
	//	if (!((this->State == state::READY) || (this->State == state::RUNNING))) return;
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(true);
	//		this->RenderUpdateTrap.wait_until(2);
	//	}
	// 
	//	int StgIdx = this->stgidx(aStage);
	//	if (StgIdx >= 0) {
	//		if (this->StageCount == 1) {
	//			free(this->Stage);
	//			this->Stage = NULL;
	//			this->StageCount = 0;
	//		}
	//		else {
	//			int MoveCount = (this->StageCount - 1) - StgIdx;
	//			if (MoveCount) {
	//				memmove(&this->Stage[StgIdx], &this->Stage[StgIdx + 1], MoveCount * sizeof(core::stage_t*));
	//			}
	//			void* nptr = realloc(this->Stage, (this->StageCount - 1) * sizeof(core::stage_t*));
	//			assert(!(nptr == NULL));
	//			this->Stage = (core::stage_t**)nptr;
	//			this->StageCount -= 1;
	//		}
	//	}
	// 
	//	if (this->State == state::RUNNING) {
	//		this->RenderUpdateTrap.set(false);
	//	}
	//}

	int engine::state::winidx(core::object::system_window* aWin) {
		for (int i = 0; i < this->SystemWindow.size(); i++) {
			if (this->SystemWindow[i] == aWin) return i;
		}
		return 0;
	}

	int engine::state::filidx(core::io::file* aFile) {
		for (int i = 0; i < this->File.size(); i++) {
			if (this->File[i] == aFile) return i;
		}
		return -1;
	}

	int engine::state::ctxidx(core::gcl::context* aCtx) {
		for (int i = 0; i < this->Context.size(); i++) {
			if (this->Context[i] == aCtx) return i;
		}
		return -1;
	}

	int engine::state::objidx(core::object_t* aObj) {
		for (int i = 0; i < this->Object.size(); i++) {
			if (this->Object[i] == aObj) return i;
		}
		return -1;
	}

	int engine::state::stgidx(core::stage_t* aStg) {
		for (int i = 0; i < this->Stage.size(); i++) {
			if (this->Stage[i] == aStg) return i;
		}
		return -1;
	}

	engine::engine(int aCmdArgCount, const char** aCmdArgList, int aLayerCount, const char** aLayerList, int aExtensionCount, const char** aExtensionList) /*: State(this)*/ {

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
		isGLSLANGReady = glslang::InitializeProcess();

		// (GLFW) Must be initialized first for OS extensions.
		isGLFWReady = glfwInit();

		// (Vulkan) Load required window extensions.
		if (isGLFWReady) {

			// Adds proposed layers to list.
			for (int i = 0; i < aLayerCount; i++) {
				this->Layer.push_back(aLayerList[i]);
			}

			// Adds proposed extensions.
			for (int i = 0; i < aExtensionCount; i++) {
				this->Extension.push_back(aExtensionList[i]);
			}

			// Acquires WSI instance extensions from GLFW.
			uint32_t OSExtensionCount = 0;
			const char** OSExtensionList = glfwGetRequiredInstanceExtensions(&OSExtensionCount);

			// Adds WSI instance extensions to list.
			for (uint32_t i = 0; i < OSExtensionCount; i++) {
				this->Extension.push_back(OSExtensionList[i]);
			}

			//"VK_KHR_display";
			// Does not work on Windows OS right now, only Linux
			//this->Extension.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);		

			this->AppInfo.sType							= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			this->AppInfo.pNext							= NULL;
			this->AppInfo.pApplicationName				= "";
			this->AppInfo.applicationVersion			= VK_MAKE_VERSION(0, 0, 1);
			this->AppInfo.pEngineName					= "Geodesuka Engine";
			this->AppInfo.engineVersion					= VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Patch);
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
			this->State = new state(this);
			isGCDeviceAvailable = this->State->Device.size() > 0;
			isSystemDisplayAvailable = this->State->Display.size() > 0;
		}

		// Store main thread ID.
		this->MainThreadID = std::this_thread::get_id();

		this->SignalCreate.store(false);
		this->WindowCreated.store(false);
		// Window Temp Data?
		this->ReturnWindow = NULL;
		this->DestroyWindow.store(NULL);

		this->isReady = isGLSLANGReady && isGLFWReady && isVulkanReady && isGCDeviceAvailable && isSystemDisplayAvailable;
		this->State->ID = this->isReady ? state::id::READY : state::id::FAILURE;

	}

	engine::~engine() {

		delete this->State;

		vkDestroyInstance(this->Handle, NULL);

		glfwTerminate();

		glslang::FinalizeProcess();

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
		*aListSize = this->State->Device.size();
		return this->State->Device.data();
	}

	core::gcl::device* engine::get_primary_device() {
		return this->State->PrimaryDevice;
	}

	core::object::system_display** engine::get_display_list(size_t* aListSize) {
		*aListSize = this->State->Display.size();
		return this->State->Display.data();
	}

	core::object::system_display* engine::get_primary_display() {
		return this->State->PrimaryDisplay;
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

		this->State->ID					= state::RUNNING;
		this->MainThreadID				= std::this_thread::get_id();
		this->RenderThread				= std::thread(&engine::trender, this);
		this->SystemTerminalThread		= std::thread(&engine::tsterminal, this);
		this->AppThread					= std::thread(&core::app::run, aApp);

		double t1, t2;
		double wt, ht;
		double /*t,*/ dt;
		double ts = 0.01;
		dt = 0.0;

		// Used for scheduling compute operations dependent on transfer operations.
		uint32_t WaitSemaphoreCount = 0;
		VkSemaphore* WaitSemaphore = NULL;
		VkPipelineStageFlags* WaitSemaphoreStage = NULL;


		VkResult Result = VkResult::VK_SUCCESS;

		// The update thread is the main thread.
		while (!this->Shutdown.load()) {
			this->State->ThreadTrap.door();

			t1 = core::logic::get_time();
			this->mtcd_process_window_handle_call();
			glfwPollEvents();

			// Work is done here...

			t2 = core::logic::get_time();


			wt = t2 - t1;
			if (wt < ts) {
				ht = ts - wt;
				core::logic::waitfor(ht);
			}
			else {
				ht = 0.0;
			}
			dt = wt + ht;
		}

		// This is redundant. Only the App thread can shutdown all other threads.
		this->Shutdown.store(true);

		this->RenderThread.join();
		this->SystemTerminalThread.join();
		this->AppThread.join();
		this->State->ID = state::READY;

		return 0;
	}

	// --------------- Render Thread --------------- //
	// The job of the render thread is to honor and schedule draw
	// calls of respective render targets stored in memory.
	// --------------- Render Thread --------------- //
	void engine::trender() {

		while (!this->Shutdown.load()) {
			this->State->ThreadTrap.door();

		}
	}

	void engine::taudio() {
		// Does nothing currently.
		while (!this->Shutdown.load()) {
			core::logic::waitfor(1);
		}
	}

	// --------------- System Terminal Thread --------------- //
	// Will be used for runtime debugging of engine using terminal.
	// --------------- System Terminal Thread --------------- //
	void engine::tsterminal() {

		while (!this->Shutdown.load()) {
			core::logic::waitfor(1.0);
		}
	}

}
