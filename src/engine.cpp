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

/* --------------- Internal --------------- */

//#include <geodesuka/core/object.h>
//#include <geodesuka/core/object/window.h>
//#include <geodesuka/core/object/system_display.h>
//#include <geodesuka/core/object/system_window.h>
//#include <geodesuka/core/object/virtual_window.h>
//#include <geodesuka/core/object/camera.h>

/* --------------- Internal Callback Methods (Input Handling) --------------- */

namespace geodesuka {

	/*
	* Initializes the whole engine, and all backend APIs.
	* needed for context creation. Will manage all created objects
	* and loaded assets.
	*/
	engine::engine(int argc, char* argv[]) {

		this->isGLSLANGReady = false;
		this->isGLFWReady = false;
		this->isVulkanReady = false;
		this->isSystemDisplayAvailable = false;
		this->isGCDeviceAvailable = false;

		this->isReady = false;
		this->Shutdown = false;

		this->PrimaryDisplay = nullptr;

		// --------------- Initialization Process --------------- //

		// Init Process:
		// Start glslang
		// Start glfw
		// Start vulkan
		// Query for Monitors (No primary monitor = Start up failure)
		// Query for gcl devices (No discrete gpu = Start up failure)
		//

		// (GLSLang)
		this->isGLSLANGReady = glslang::InitializeProcess();

		// (GLFW) Must be initialized first for OS extensions.
		this->isGLFWReady = glfwInit();

		// (Vulkan) Load required window extensions.
		if (this->isGLFWReady) {
			// Certain extensions needed for interacting with Operating System window system.
			uint32_t OSExtensionCount = 0;
			const char** OSExtensionList = glfwGetRequiredInstanceExtensions(&OSExtensionCount);

			this->AppProp.sType = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			this->AppProp.pNext = NULL;
			this->AppProp.pApplicationName = "No Name";
			this->AppProp.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
			this->AppProp.pEngineName = "Geodesuka Engine";
			this->AppProp.engineVersion = VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Patch);
			this->AppProp.apiVersion = VK_MAKE_VERSION(1, 2, 0);

			this->InstProp.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			this->InstProp.pNext = NULL;
			this->InstProp.flags = 0;
			this->InstProp.pApplicationInfo = &AppProp;
			this->InstProp.enabledLayerCount = 0;
			this->InstProp.ppEnabledLayerNames = NULL;
			this->InstProp.enabledExtensionCount = OSExtensionCount;
			this->InstProp.ppEnabledExtensionNames = OSExtensionList;

			VkResult Result = vkCreateInstance(&InstProp, NULL, &this->Instance);
			if (Result == VK_SUCCESS) {
				this->isVulkanReady = true;
			}
			else {
				this->isVulkanReady = false;
			}
		}

		if (this->isGLSLANGReady && this->isGLFWReady && this->isVulkanReady) {

			// Queries for monitors.
			if (glfwGetPrimaryMonitor() != NULL) {
				// Get System displays.
				core::object::system_display* tmpDisplay = new core::object::system_display(glfwGetPrimaryMonitor());
				this->PrimaryDisplay = tmpDisplay;
				this->Display.push_back(tmpDisplay);
				this->Object.push_back(tmpDisplay);
				int lCount;
				GLFWmonitor** lMon = glfwGetMonitors(&lCount);
				for (int i = 0; i < lCount; i++) {
					if (PrimaryDisplay->Handle != lMon[i]) {
						// Excludes already cached primary monitor.
						tmpDisplay = new core::object::system_display(lMon[i]);
						this->Display.push_back(tmpDisplay);
						this->Object.push_back(tmpDisplay);
					}
				}
				this->isSystemDisplayAvailable = true;
			}

			// Query for gcl devices
			uint32_t PhysicalDeviceCount = 0;
			vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, NULL);
			if (PhysicalDeviceCount > 0) {
				std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
				vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
				for (size_t i = 0; i < PhysicalDeviceList.size(); i++) {
					this->DeviceList.push_back(new core::gcl::device(&this->Instance, PhysicalDeviceList[i]));
				}
				this->isGCDeviceAvailable = true;
			}

		}

		this->isReady = this->isGLSLANGReady && this->isGLFWReady && this->isVulkanReady && this->isSystemDisplayAvailable && this->isGCDeviceAvailable;

		// Engine is ready, initialize loops.
		if (this->isReady) {

			// Initialize update thread for all objects.
			this->UpdateThread = std::thread(&engine::tupdate, this);

		}

		// ------------------------- Debug Print Info ------------------------- //

		// Will print out display info.
		for (size_t i = 0; i < Display.size(); i++) {
			std::cout << "Display Name:\t\t" << Display[i]->Name.str() << std::endl;
			std::cout << "Display Size:\t\t" << Display[i]->Size.x << ", " << Display[i]->Size.y << "\t[m]" << std::endl;
			std::cout << "Display Resolution:\t" << Display[i]->Resolution.x << ", " << Display[i]->Resolution.y << "\t[pixels]" << std::endl;
			std::cout << "Display Refresh Rate:\t" << Display[i]->Property.RefreshRate << "\t\t[1/s]" << std::endl;
			std::cout << std::endl;
		}

		// Just simply prints out device info.
		for (size_t i = 0; i < this->DeviceList.size(); i++) {
			std::cout << "Device ID:\t" << this->DeviceList[i]->Properties.deviceID << std::endl;
			std::cout << "Device Name:\t" << this->DeviceList[i]->Properties.deviceName << std::endl;
			std::cout << "Device Type:\t";
			switch (this->DeviceList[i]->Properties.deviceType) {
			case VK_PHYSICAL_DEVICE_TYPE_OTHER:
				std::cout << "Unknown" << std::endl;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
				std::cout << "Integrated GPU" << std::endl;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
				std::cout << "Discrete GPU" << std::endl;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
				std::cout << "Virtual GPU" << std::endl;
				break;
			case VK_PHYSICAL_DEVICE_TYPE_CPU:
				std::cout << "CPU" << std::endl;
				break;
			}
			std::cout << std::endl;
			for (size_t j = 0; j < this->DeviceList[i]->QueueFamilyProperties.size(); j++) {
				std::cout << "Family Index:\t" << j << std::endl;
				std::cout << "Queue Count:\t" << this->DeviceList[i]->QueueFamilyProperties[j].queueCount << std::endl;
				std::cout << "Graphics:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) >> 0) << std::endl;
				std::cout << "Compute:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) >> 1) << std::endl;
				std::cout << "Transfer:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) >> 2) << std::endl;
				// No idea what sparse binding is..
				//std::cout << "Sparse Binding:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT) >> 3) << std::endl << std::endl;
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

	}

	/*
	* Since the engine manages all created objects, it is the responsibility of the engine.
	* Also must shut down backend API. 
	*/
	engine::~engine() {
		// Begin termination, stop threads.
		this->Mutex.lock();
		this->Shutdown = true;
		this->Mutex.unlock();

		this->UpdateThread.join();

		// Clears all objects from memory.
		for (size_t i = 1; i <= this->Object.size(); i++) {
			size_t Index = this->Object.size() - i;
			if (this->Object[Index] != nullptr) {
				delete this->Object[Index];
				this->Object[Index] = nullptr;
			}
		}
		this->Object.clear();

		// Clears all loaded resources from memory.
		for (size_t i = 0; i < this->File.size(); i++) {
			if (this->File[i] != nullptr) {
				delete this->File[i];
				this->File[i] = nullptr;
			}
		}
		this->File.clear();

		vkDestroyInstance(this->Instance, NULL);

		glfwTerminate();

		glslang::FinalizeProcess();
	}

	core::object::system_display* engine::get_primary_display() {
		return this->PrimaryDisplay;
	}

	core::object::system_display** engine::get_display_list(size_t* ListSize) {
		*ListSize = this->Display.size();
		return this->Display.data();
	}

	core::gcl::device** engine::get_device_list(size_t* ListSize) {
		*ListSize = this->DeviceList.size();
		return this->DeviceList.data();
	}

	core::io::file* engine::open(const char* FilePath) {

		return nullptr;
	}

	core::math::integer engine::close(core::io::file* FileHandle) {
		return core::math::integer();
	}

	core::object_t* engine::create(core::object_t* aNewObject) {
		// Checks for redundant elements.
		for (size_t i = 0; i < Object.size(); i++) {
			if (Object[i] == aNewObject) return aNewObject;
		}
		// Pushes onto list if not on list.
		Object.push_back(aNewObject);
		return aNewObject;
	}

	core::object_t* engine::create(core::object::system_window* aNewWindow) {
		// Checks for redundant elements.
		for (size_t i = 0; i < this->Object.size(); i++) {
			if (this->Object[i] == aNewWindow) return aNewWindow;
		}
		size_t Offset = this->Display.size() + this->SystemWindow.size();
		this->Object.insert(this->Object.begin() + Offset, aNewWindow);
		this->SystemWindow.push_back(aNewWindow);
		return aNewWindow;
	}

	core::math::integer engine::destroy(core::object_t* aDestroyObject) {
		// Searches for object in list, then erases if it exists.
		for (size_t i = 0; i < Object.size(); i++) {
			if (Object[i] == aDestroyObject) {
				Object.erase(Object.begin() + i);
				return 0;
			}
		}
		return -1;
	}

	bool engine::is_ready() {
		return this->isReady;
	}

	engine::ecode engine::error_code() {
		return this->ErrorCode;
	}

	engine::version engine::get_version() {
		return this->Version;
	}

	double engine::get_time() {
		return glfwGetTime();
	}

	void engine::tsleep(double Seconds) {
		double Microseconds = 1000.0 * Seconds;
#if defined(_WIN32) || defined(_WIN64)
		DWORD Duration = (DWORD)std::floor(Microseconds);
		Sleep(Duration);
#elif defined(__APPLE__) || defined(MACOSX)

#elif defined(__linux__) && !defined(__ANDROID__)
		int Duration = (int)std::floor(Microseconds);
		usleep(Duration);
#elif defined(__ANDROID__)

#endif
	}

	// --------------- Update Loop --------------- //
	// Updates all objects that have been created asynchronously.
	// --------------- Update Loop --------------- //
	void engine::tupdate() {
		bool ExitCondition = false;
		double t1, t2;
		double wt, ht;
		double t, dt;
		double ts = 1.0 / 2.0;
		dt = 0.0;
		while (!ExitCondition) {
			t1 = this->get_time();
			// glfw
			//
			// Update object list.
			//for (size_t i = 0; i < this->Object.size(); i++) {
			//	this->Object[i]->update(dt);
			//}
			//std::cout << "Loop Time:\t" << dt << std::endl;

			t2 = this->get_time();
			wt = t2 - t1;
			if (wt < ts) {
				ht = ts - wt;
				this->tsleep(ht);
			}
			else {
				ht = 0.0;
			}
			dt = wt + ht;
			this->Mutex.lock();
			ExitCondition = this->Shutdown;
			this->Mutex.unlock();
		}
		//std::cout << "Update Thread has exited." << std::endl;
	}

	void engine::trender() {

	}

	void engine::taudio() {

	}




}
