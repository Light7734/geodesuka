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

	int engine::input() {
		// This will conduct system wide input polling and deliver input polls to respective objects in focus.
		glfwPollEvents();

		for (size_t i = 0; i < SystemWindow.size(); i++) {

			// Check if window wants to close.
	

			// Check if system_window has entered new display region.

		}

		return 0;
	}

	int engine::update(core::math::real adt) {
		// This will conduct the time step interval and evaluate input poll from last section.

		for (size_t i = 0; i < Display.size(); i++) {
			Display[i]->update(dt);
		}

		

		for (size_t i = 0; i < Object.size(); i++) {
			Object[i]->update(dt);
		}

		return 0;
	}

	int engine::render() {
		// This will conduct all final draw calls required by the engine internally.

		// Should first submit all obj

		//for (core::math::integer i = 0; i < Object.size(); i++) {
		//	PrimaryDisplay->draw(Object[i]);
		//}

		
		// Will draw to (means update) system_displays.
		//for (int i = 0; i < this->SystemWindow.size(); i++) {
		//	core::object::system_display* ParentDisplay = this->SystemWindow[i]->get_parent_display();
		//	ParentDisplay->draw(this->SystemWindow[i]);
		//}

		return 0;
	}

	core::object::system_display* engine::get_primary_display() {
		return this->PrimaryDisplay;
	}

	std::vector<core::object::system_display*> engine::get_display_list() {
		return this->Display;
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

	const char* engine::get_er_str(VkResult Res) {
		const char* temp;
		switch (Res) {
		default:
			temp = "Error: Unknown";
			break;
		case VK_SUCCESS:
			temp = "Success";
			break;
		case VK_NOT_READY:
			temp = "Not Ready.";
			break;
		case VK_TIMEOUT:
			temp = "Timeout.";
			break;
		case VK_EVENT_SET:
			temp = "Event Set.";
			break;
		case VK_EVENT_RESET:
			temp = "Event Reset.";
			break;
		case VK_INCOMPLETE:
			temp = "Incomplete.";
			break;
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			temp = "Error: Out of Host Memory.";
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			temp = "Error: Out of Device Memory.";
			break;
		case VK_ERROR_INITIALIZATION_FAILED:
			temp = "Error: Initialization failed.";
			break;
		case VK_ERROR_DEVICE_LOST:
			temp = "Error: Device Lost";
			break;
		case VK_ERROR_MEMORY_MAP_FAILED:
			temp = "Error: Memory Map Failed.";
			break;
		case VK_ERROR_LAYER_NOT_PRESENT:
			temp = "Error: Layer Not Present.";
			break;
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			temp = "Error: Extension not present.";
			break;
		case VK_ERROR_FEATURE_NOT_PRESENT:
			temp = "Error: Feature Not Present.";
			break;
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			temp = "Error: Incompatible Driver.";
			break;
		case VK_ERROR_TOO_MANY_OBJECTS:
			temp = "Error: Too many objects.";
			break;
		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			temp = "Error: Format not supported.";
			break;
		case VK_ERROR_FRAGMENTED_POOL:
			temp = "Error: Fragmented pool.";
			break;
		case VK_ERROR_UNKNOWN:
			temp = "Error: Unknown.";
			break;
		case VK_ERROR_OUT_OF_POOL_MEMORY:
			temp = "Error: Out of pool memory.";
			break;
		case VK_ERROR_INVALID_EXTERNAL_HANDLE:
			temp = "Error: Invalid external handle.";
			break;
		case VK_ERROR_FRAGMENTATION:
			temp = "Error: Fragmentation.";
			break;
		case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
			temp = "Error: Invalid opaque capture address.";
			break;
		case VK_ERROR_SURFACE_LOST_KHR:
			temp = "Error: Surface lost (KHR)";
			break;
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			temp = "Error: Native window in use (KHR)";
			break;
		case VK_SUBOPTIMAL_KHR:
			temp = "Suboptimal (khr)";
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
			temp = "Error: Out of date (khr)";
			break;
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			temp = "Error: Incompatible display.";
			break;
		case VK_ERROR_VALIDATION_FAILED_EXT:
			temp = "Error: Validation failed (ext).";
			break;
		case VK_ERROR_INVALID_SHADER_NV:
			temp = "Error: Invalid shader (nv)";
			break;
		case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
			temp = "Error: Invalid DRM format modifier plane layout (ext)";
			break;
		case VK_ERROR_NOT_PERMITTED_EXT:
			temp = "Error: Not permitted extension";
			break;
		case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
			temp = "Error: Fullscreen exclusive mode lost.";
			break;
		case VK_THREAD_IDLE_KHR:
			temp = "Thread Idle (khr)";
			break;
		case VK_THREAD_DONE_KHR:
			temp = "Thread Done (khr)";
			break;
		case VK_OPERATION_DEFERRED_KHR:
			temp = "Operation Deferred (khr)";
			break;
		case VK_OPERATION_NOT_DEFERRED_KHR:
			temp = "Operation not deferred (khr)";
			break;
		case VK_PIPELINE_COMPILE_REQUIRED_EXT:
			temp = "Pipeline compile required. (ext)";
			break;
		}
		return temp;
		/*
		VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE,
		VK_ERROR_FRAGMENTATION_EXT = VK_ERROR_FRAGMENTATION,
		VK_ERROR_INVALID_DEVICE_ADDRESS_EXT = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
		VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
		VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT = VK_PIPELINE_COMPILE_REQUIRED_EXT,
		VK_RESULT_MAX_ENUM = 0x7FFFFFFF
		*/
	}




}
