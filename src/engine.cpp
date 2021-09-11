#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */

/* --------------- Standard C++ Libraries --------------- */
#include <vector>
#include <chrono>

/* --------------- Third Party Libraries --------------- */
#include "dep/glslang/glslang/Public/ShaderLang.h"

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

		this->ExitApp = false;
		this->dt = 0.0;
		this->t = 0.0;
		this->PrimaryDisplay = nullptr;

		glslang::InitializeProcess();

		// GLFW must be initialized first for OS extensions.
		glfwInit();

		// This function will initialize the engine as a whole, and
		// all the backend libraries it depends upon such as GLFW.

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
		}
		else {
			// No primary monitors found!
			this->ExitApp = true;
		}

		// Will print out display info.
		for (size_t i = 0; i < Display.size(); i++) {
			std::cout << "Display Name:\t\t" << Display[i]->Name.str() << std::endl;
			std::cout << "Display Size:\t\t" << Display[i]->Size.x << ", " << Display[i]->Size.y << "\t[m]" << std::endl;
			std::cout << "Display Resolution:\t" << Display[i]->Resolution.x << ", " << Display[i]->Resolution.y << "\t[pixels]" << std::endl;
			std::cout << "Display Refresh Rate:\t" << Display[i]->Property.RefreshRate << "\t\t[1/s]" << std::endl;
			std::cout << std::endl;
		}

		// Certain extensions needed for interacting with Operating System window system.
		uint32_t OSExtensionCount = 0;
		const char** OSExtensionList = glfwGetRequiredInstanceExtensions(&OSExtensionCount);

		VkApplicationInfo AppProp{};
		AppProp.sType					= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
		//AppProp.pNext					= NULL;
		AppProp.pApplicationName		= "No Name";
		AppProp.applicationVersion		= VK_MAKE_VERSION(0, 0, 1);
		AppProp.pEngineName				= "Geodesuka Engine";
		AppProp.engineVersion			= VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Patch);
		AppProp.apiVersion				= VK_MAKE_VERSION(1, 2, 0);

		VkInstanceCreateInfo InstanceCreateProp{};
		InstanceCreateProp.sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		InstanceCreateProp.pNext						= NULL;
		InstanceCreateProp.flags						= 0;
		InstanceCreateProp.pApplicationInfo				= &AppProp;
		InstanceCreateProp.enabledLayerCount			= 0;
		InstanceCreateProp.ppEnabledLayerNames			= NULL;
		InstanceCreateProp.enabledExtensionCount		= OSExtensionCount;
		InstanceCreateProp.ppEnabledExtensionNames		= OSExtensionList;

		this->ErrorCode = vkCreateInstance(&InstanceCreateProp, NULL, &this->Instance);

		uint32_t PhysicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, NULL);
		if (PhysicalDeviceCount > 0) {
			std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
			vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
			for (size_t i = 0; i < PhysicalDeviceList.size(); i++) {
				this->DeviceList.push_back(new core::gcl::device(&this->Instance, PhysicalDeviceList[i]));
			}
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
		// The destructor will insure that all memory allocating objects are cleared from memory.
		//core::gcl::terminate();
		
		// Clear all active objects, starting from the end.
		for (size_t i = 1; i <= Object.size(); i++) {
			size_t ind = Object.size() - i;
			if (Object[ind] != nullptr) {
				delete Object[ind];
				Object[ind] = nullptr;
				Object.pop_back();
			}
		}

		vkDestroyInstance(this->Instance, NULL);

		glfwTerminate();

		glslang::FinalizeProcess();
	}

	//int engine::input() {
	//	// This will conduct system wide input polling and deliver input polls to respective objects in focus.
	//	glfwPollEvents();

	//	for (size_t i = 0; i < SystemWindow.size(); i++) {

	//		// Check if window wants to close.
	//

	//		// Check if system_window has entered new display region.

	//	}

	//	return 0;
	//}

	//int engine::update(core::math::real adt) {
	//	// This will conduct the time step interval and evaluate input poll from last section.

	//	for (size_t i = 0; i < Display.size(); i++) {
	//		Display[i]->update(dt);
	//	}

	//	

	//	for (size_t i = 0; i < Object.size(); i++) {
	//		Object[i]->update(dt);
	//	}

	//	return 0;
	//}

	//int engine::render() {
	//	// This will conduct all final draw calls required by the engine internally.

	//	// Should first submit all obj

	//	//for (core::math::integer i = 0; i < Object.size(); i++) {
	//	//	PrimaryDisplay->draw(Object[i]);
	//	//}

	//	
	//	// Will draw to (means update) system_displays.
	//	//for (int i = 0; i < this->SystemWindow.size(); i++) {
	//	//	core::object::system_display* ParentDisplay = this->SystemWindow[i]->get_parent_display();
	//	//	ParentDisplay->draw(this->SystemWindow[i]);
	//	//}

	//	return 0;
	//}

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

	core::object_t* engine::create(core::object_t* aNewObject) {
		// Checks for redundant elements.
		for (size_t i = 0; i < Object.size(); i++) {
			if (Object[i] == aNewObject) return aNewObject;
		}
		// Pushes onto list if not on list.
		Object.push_back(aNewObject);
		return aNewObject;
	}

	core::object::system_window* engine::create(core::object::system_window* aNewWindow) {
		// Checks for redundant elements.
		for (size_t i = 0; i < SystemWindow.size(); i++) {
			if (SystemWindow[i] == aNewWindow) return aNewWindow;
		}
		// Pushes onto list if not on list.
		SystemWindow.push_back(aNewWindow);

		// Checks for redundant elements.
		for (size_t i = 0; i < Object.size(); i++) {
			if (Object[i] == aNewWindow) return aNewWindow;
		}
		// Pushes onto list if not on list.
		Object.push_back(aNewWindow);
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

	double engine::get_time() {
		return glfwGetTime();
	}

	void engine::tupdate() {

	}

	void engine::trender() {

	}

	void engine::taudio() {

	}




}
