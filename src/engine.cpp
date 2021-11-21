#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */

/* --------------- Standard C++ Libraries --------------- */

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

	/*
	* Initializes the whole engine, and all backend APIs.
	* needed for context creation. Will manage all created objects
	* and loaded assets.
	*/

	engine::engine(int argc, char* argv[]) : SystemTerminal(*(new core::object::system_terminal(this, nullptr))) {
		this->State = state::ENGINE_CREATION_STATE;
		this->isReady = false;
		this->Shutdown.store(false);
		this->ThreadsLaunched.store(false);

		this->Handle = VK_NULL_HANDLE;

		// First initialized object is the system terminal.
		this->Object.push_back(&SystemTerminal);

		this->PrimaryDisplay = nullptr;

		this->SignalCreate.store(false);
		this->WindowCreated.store(false);

		// Store main thread ID.
		this->MainThreadID = std::this_thread::get_id();


		bool isGLSLANGReady				= false;
		bool isGLFWReady				= false;
		bool isVulkanReady				= false;
		bool isSystemDisplayAvailable	= false;
		bool isGCDeviceAvailable		= false;



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
			// Validation Layers.
			this->EnabledLayer.push_back("VK_LAYER_KHRONOS_validation");

			// Certain extensions needed for interacting with Operating System window system.
			uint32_t OSExtensionCount = 0;
			const char** OSExtensionList = glfwGetRequiredInstanceExtensions(&OSExtensionCount);

			for (uint32_t i = 0; i < OSExtensionCount; i++) {
				this->RequiredExtension.push_back(OSExtensionList[i]);
			}
			//this->RequiredExtension.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);		

			//for (size_t i = 0; i < this->RequiredExtension.size(); i++) {
			//	std::cout << this->RequiredExtension[i] << std::endl;
			//}

			this->AppInfo.sType							= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			this->AppInfo.pNext							= NULL;
			this->AppInfo.pApplicationName				= "No Name";
			this->AppInfo.applicationVersion			= VK_MAKE_VERSION(0, 0, 1);
			this->AppInfo.pEngineName					= "Geodesuka Engine";
			this->AppInfo.engineVersion					= VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Patch);
			this->AppInfo.apiVersion					= VK_MAKE_VERSION(1, 2, 0);

			this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			this->CreateInfo.pNext						= NULL;
			this->CreateInfo.flags						= 0;
			this->CreateInfo.pApplicationInfo			= &this->AppInfo;
			this->CreateInfo.enabledLayerCount			= (uint32_t)this->EnabledLayer.size();
			this->CreateInfo.ppEnabledLayerNames		= this->EnabledLayer.data();
			this->CreateInfo.enabledExtensionCount		= (uint32_t)this->RequiredExtension.size();
			this->CreateInfo.ppEnabledExtensionNames	= this->RequiredExtension.data();

			VkResult Result = vkCreateInstance(&this->CreateInfo, NULL, &this->Handle);
			if (Result == VK_SUCCESS) {
				isVulkanReady = true;
			}
			else {
				isVulkanReady = false;
			}
		}

		if (isGLSLANGReady && isGLFWReady && isVulkanReady) {

			// Queries for monitors.
			if (glfwGetPrimaryMonitor() != NULL) {
				// Get System displays.
				core::object::system_display* tmpDisplay = new core::object::system_display(this, nullptr, glfwGetPrimaryMonitor());
				this->PrimaryDisplay = tmpDisplay;
				this->Display.push_back(tmpDisplay);
				this->Object.push_back(tmpDisplay);
				int lCount;
				GLFWmonitor** lMon = glfwGetMonitors(&lCount);
				for (int i = 0; i < lCount; i++) {
					if (PrimaryDisplay->Handle != lMon[i]) {
						// Excludes already cached primary monitor.
						tmpDisplay = new core::object::system_display(this, nullptr, lMon[i]);
						this->Display.push_back(tmpDisplay);
						this->Object.push_back(tmpDisplay);
					}
				}
				isSystemDisplayAvailable = true;
			}

			// Query for gcl devices
			uint32_t PhysicalDeviceCount = 0;
			vkEnumeratePhysicalDevices(this->Handle, &PhysicalDeviceCount, NULL);
			if (PhysicalDeviceCount > 0) {
				std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
				vkEnumeratePhysicalDevices(this->Handle, &PhysicalDeviceCount, PhysicalDeviceList.data());
				for (size_t i = 0; i < PhysicalDeviceList.size(); i++) {
					this->DeviceList.push_back(new core::gcl::device(this->Handle, PhysicalDeviceList[i]));
				}
				isGCDeviceAvailable = true;
			}

		}

		this->isReady = isGLSLANGReady && isGLFWReady && isVulkanReady && isSystemDisplayAvailable && isGCDeviceAvailable;

		//std::cout << "Geodesuka Engine";
		//std::cout << " - Version: " << this->Version.Major << "." << this->Version.Minor << "." << this->Version.Patch;
		//std::cout << " - Date: " << this->Date << std::endl;

		this->State = state::ENGINE_ACTIVE_STATE;
	}

	/*
	* Since the engine manages all created objects, it is the responsibility of the engine.
	* Also must shut down backend API. 
	*/
	engine::~engine() {

		this->State = state::ENGINE_DESTRUCTION_STATE;

		// Destroys all active stages.
		for (size_t i = 1; i <= this->Stage.size(); i++) {
			size_t Index = this->Stage.size() - i;
			if (this->Stage[Index] != nullptr) {
				delete this->Stage[Index];
				this->Stage[Index] = nullptr;
			}
		}
		this->Stage.clear();

		// Clears all objects from memory.
		for (size_t i = 1; i <= this->Object.size(); i++) {
			size_t Index = this->Object.size() - i;
			if (this->Object[Index] != nullptr) {
				delete this->Object[Index];
				this->Object[Index] = nullptr;
			}
		}
		this->Object.clear();

		// Destroys all device contexts.
		for (size_t i = 1; i <= this->Context.size(); i++) {
			size_t Index = this->Context.size() - i;
			if (this->Context[Index] != nullptr) {
				delete this->Context[Index];
				this->Context[Index] = nullptr;
			}
		}
		this->Context.clear();

		// Clears all loaded resources from memory.
		for (size_t i = 0; i < this->File.size(); i++) {
			if (this->File[i] != nullptr) {
				delete this->File[i];
				this->File[i] = nullptr;
			}
		}
		this->File.clear();

		vkDestroyInstance(this->Handle, NULL);

		glfwTerminate();

		glslang::FinalizeProcess();
	}

	int engine::run(core::app* aApp) {

		// Store main thread ID.
		this->MainThreadID				= std::this_thread::get_id();

		this->SystemTerminalThread		= std::thread(&engine::tsterminal, this);
		this->RenderThread				= std::thread(&engine::trender, this);
		this->AppThread					= std::thread(&core::app::run, aApp);

		double t1, t2;
		double wt, ht;
		double t, dt;
		double ts = 0.01;
		dt = 0.0;

		// The update thread is the main thread.
		while (!this->Shutdown.load()) {
			this->RenderUpdateTrap.door();

			// So fucking dumb...
			this->mtcd_process_window_handle_call();

			glfwPollEvents();

			t1 = core::logic::get_time();
			// Update object list.
			for (size_t i = 0; i < this->Object.size(); i++) {
				this->Object[i]->update(dt);
			}

			// Update stage logic.
			for (size_t i = 0; i < this->Stage.size(); i++) {
				this->Stage[i]->update(dt);
			}

			// Wait for render operations to complete before transfer.
			//vkWaitForFences();

			//// Execute all host to device transfer operations.
			//for (size_t i = 0; i < this->Context.size(); i++) {
			//	this->Context[i]->submit(core::gcl::device::qfs::TRANSFER, 0, NULL, VK_NULL_HANDLE);
			//}
			//
			//// Execute all device compute operations.
			//for (size_t i = 0; i < this->Context.size(); i++) {
			//	this->Context[i]->submit(core::gcl::device::qfs::COMPUTE, 0, NULL, VK_NULL_HANDLE);
			//}

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


		this->Shutdown.store(true);

		this->SystemTerminalThread.join();
		this->RenderThread.join();
		this->AppThread.join();

		return 0;
	}

	core::object::system_display* engine::get_primary_display() {
		return this->PrimaryDisplay;
	}

	core::object::system_display** engine::get_display_list(size_t* aListSize) {
		*aListSize = this->Display.size();
		return this->Display.data();
	}

	core::gcl::device** engine::get_device_list(size_t* aListSize) {
		*aListSize = this->DeviceList.size();
		return this->DeviceList.data();
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

	void engine::submit(core::gcl::context* aContext) {
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}
		this->Context.push_back(aContext);
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
	}

	void engine::remove(core::gcl::context* aContext) {
		// Should be fine?
		if (this->State != ENGINE_ACTIVE_STATE) return;

		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}
		for (size_t i = 0; i < this->Context.size(); i++) {
			if (this->Context[i] == aContext) {
				this->Context.erase(this->Context.begin() + i);
			}
		}
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
	}

	void engine::submit(core::object_t* aObject) {
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}
		this->Object.push_back(aObject);
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
	}
	// TODO: Fix these two methods.
	void engine::remove(core::object_t* aObject) {
		// Should be fine?
		if (this->State != ENGINE_ACTIVE_STATE) return;

		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}
		for (size_t i = 0; i < this->Object.size(); i++) {
			if (this->Object[i] == aObject) {
				this->Object.erase(this->Object.begin() + i);
			}
		}
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
	}

	void engine::submit(core::object::system_window *aSystemWindow) {
		size_t Offset = 1 + this->Display.size() + this->SystemWindow.size();
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}
		// Put at end of SystemWindow List.
		this->SystemWindow.push_back(aSystemWindow);
		this->Object.insert(this->Object.begin() + Offset, aSystemWindow);
		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
	}

	void engine::remove(core::object::system_window* aSystemWindow) {
		// Should be fine?
		if (this->State != ENGINE_ACTIVE_STATE) return;

		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(true);
			this->RenderUpdateTrap.wait_until(2);
		}

		for (size_t i = 0; i < this->Object.size(); i++) {
			if (this->Object[i] == aSystemWindow) {
				this->Object.erase(this->Object.begin() + i);
			}
		}

		for (size_t i = 0; i < this->SystemWindow.size(); i++) {
			if (this->SystemWindow[i] == aSystemWindow) {
				this->SystemWindow.erase(this->SystemWindow.begin() + i);
			}
		}

		if (this->ThreadsLaunched.load()) {
			this->RenderUpdateTrap.set(false);
		}
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

	//void engine::tupdate() {
	//	double t1, t2;
	//	double wt, ht;
	//	double t, dt;
	//	double ts = 0.01;
	//	dt = 0.0;
	//	
	//
	//	std::vector<std::vector<VkSubmitInfo>> TransferSubmission;
	//	std::vector<std::vector<VkSubmitInfo>> ComputeSubmission;
	//
	//	//uint32_t TransferSubmissionCount = 0;
	//	//VkSubmitInfo *TransferSubmission = NULL;
	//
	//	//core::object::window::prop TempProperty = core::object::window::prop();
	//	//glfwWindowHint(GLFW_RESIZABLE,			TempProperty.Resizable);
	//	//glfwWindowHint(GLFW_DECORATED,			TempProperty.Decorated);
	//	//glfwWindowHint(GLFW_FOCUSED,			TempProperty.UserFocused);
	//	//glfwWindowHint(GLFW_AUTO_ICONIFY,		TempProperty.AutoMinimize);
	//	//glfwWindowHint(GLFW_FLOATING,			TempProperty.Floating);
	//	//glfwWindowHint(GLFW_MAXIMIZED,			TempProperty.Maximized);
	//	//glfwWindowHint(GLFW_VISIBLE,			TempProperty.Visible);
	//	//glfwWindowHint(GLFW_SCALE_TO_MONITOR,	TempProperty.ScaleToMonitor);
	//	//glfwWindowHint(GLFW_CENTER_CURSOR,		TempProperty.CenterCursor);
	//	//glfwWindowHint(GLFW_FOCUS_ON_SHOW,		TempProperty.FocusOnShow);
	//	//glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
	//	//glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE); // TODO: Change to GLFW_DONT_CARE, and remove option.
	//
	//	//GLFWwindow* TempWindow = glfwCreateWindow(640, 480, "thread", NULL, NULL);
	//
	//
	//	while (!this->Shutdown.load()) {
	//		this->RenderUpdateTrap.door();
	//
	//		// So fucking dumb...
	//		this->ut_create_window_handle_call();
	//		glfwPollEvents();
	//
	//		t1 = this->get_time();
	//		// Update object list.
	//		for (size_t i = 0; i < this->Object.size(); i++) {
	//			this->Object[i]->update(dt);
	//		}
	//
	//		// Update stage logic.
	//		for (size_t i = 0; i < this->Stage.size(); i++) {
	//			this->Stage[i]->update(dt);
	//		}
	//
	//		// Wait for render operations to complete before transfer.
	//		//vkWaitForFences();
	//
	//		//// Execute all host to device transfer operations.
	//		//for (size_t i = 0; i < this->Context.size(); i++) {
	//		//	this->Context[i]->submit(core::gcl::device::qfs::TRANSFER, 0, NULL, VK_NULL_HANDLE);
	//		//}
	//		//
	//		//// Execute all device compute operations.
	//		//for (size_t i = 0; i < this->Context.size(); i++) {
	//		//	this->Context[i]->submit(core::gcl::device::qfs::COMPUTE, 0, NULL, VK_NULL_HANDLE);
	//		//}
	//
	//		t2 = this->get_time();
	//		wt = t2 - t1;
	//		if (wt < ts) {
	//			ht = ts - wt;
	//			this->tsleep(ht);
	//		}
	//		else {
	//			ht = 0.0;
	//		}
	//		dt = wt + ht;
	//	}
	//	//std::cout << "Update Thread has exited." << std::endl;
	//
	//	//glfwDestroyWindow(TempWindow);
	//}

	// --------------- System Terminal Thread --------------- //
	// Will be used for runtime debugging of engine using terminal.
	// --------------- System Terminal Thread --------------- //
	void engine::tsterminal() {

		while (!this->Shutdown.load()) {
			core::logic::waitfor(1.0);
		}
	}

	// --------------- Render Thread --------------- //
	// The job of the render thread is to honor and schedule draw
	// calls of respective render targets stored in memory.
	// --------------- Render Thread --------------- //
	void engine::trender() {
		//bool ExitCondition = false;
		double t1, t2;
		double dt;


		// Represents gathered submissions per context.
		// Insure that all render operations to system_window
		// images wait for Acquire semaphore to be signalled.
		std::vector<std::vector<VkSubmitInfo>> Submission;

		// A context can create multiple windows, and since
		// the present queue belongs to a specific context,
		// it would be wise to group presentation updates
		std::vector<VkPresentInfoKHR> Presentation;

		while (!this->Shutdown.load()) {
			this->RenderUpdateTrap.door();

			t1 = core::logic::get_time();

			// Generates Submissions per stage.
			for (size_t i = 0; i < this->Stage.size(); i++) {
				//this->Stage[i]->render();
			}

			// Alter submission size to match number of contexts.
			//Submission.resize(this->Context.size());


			// Reverse order of aggregation.
			// Gather all submissions by stages.
			for (size_t i = 0; i < this->Stage.size(); i++) {
				for (size_t j = 0; j < this->Context.size(); j++) {
					if (this->Stage[i]->parent_context() == this->Context[j]) {
						// When matching context is found, extract all submissions.
						for (size_t k = 0; k < this->Stage[i]->Submission.size(); k++) {
							//Submission[j].push_back(this->Stage[i]->Submission[k]);
						}
					}
				}
			}

			// Wait for transfer and compute operations to complete.
			//vkWaitForFences()
			
			//// Execute all draw commands per context.
			//for (size_t i = 0; i < this->Context.size(); i++) {
			//	//this->Context[i]->submit(core::gcl::context::qid::GRAPHICS, Submission[i].size(), Submission[i].data(), VK_NULL_HANDLE);
			//	this->Context[i]->submit(core::gcl::device::qfs::GRAPHICS, 0, NULL, VK_NULL_HANDLE);
			//}
			//
			//// Wait for render operations to complete for system_window presentation.
			//
			//// Present aggregated image indices.
			//for (size_t i = 0; i < this->Context.size(); i++) {
			//	this->Context[i]->present(/*&Presentation[i]*/NULL);
			//
			//	// After presentation has been called for system_windows, update
			//	// image indices ready to be acquired.
			//	//vkAcquireNextImageKHR()
			//}

			t2 = core::logic::get_time();
			dt = t2 - t1;
			core::logic::waitfor(0.6);
		}
	}

	void engine::taudio() {

	}




}
