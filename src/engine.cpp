#include <geodesuka/engine.h>

/* --------------- Standard C Libraries --------------- */

/* --------------- Standard C++ Libraries --------------- */
#include <iostream>
std::mutex IOMutex;

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
		this->isGLSLANGReady = false;
		this->isGLFWReady = false;
		this->isVulkanReady = false;
		this->isSystemDisplayAvailable = false;
		this->isGCDeviceAvailable = false;

		this->isReady = false;
		this->Shutdown.store(false);

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

			for (uint32_t i = 0; i < OSExtensionCount; i++) {
				this->RequiredExtension.push_back(OSExtensionList[i]);
			}
			//this->RequiredExtension.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);

			for (size_t i = 0; i < this->RequiredExtension.size(); i++) {
				std::cout << this->RequiredExtension[i] << std::endl;
			}

			this->AppProp.sType							= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
			this->AppProp.pNext							= NULL;
			this->AppProp.pApplicationName				= "No Name";
			this->AppProp.applicationVersion			= VK_MAKE_VERSION(0, 0, 1);
			this->AppProp.pEngineName					= "Geodesuka Engine";
			this->AppProp.engineVersion					= VK_MAKE_VERSION(this->Version.Major, this->Version.Minor, this->Version.Patch);
			this->AppProp.apiVersion					= VK_MAKE_VERSION(1, 2, 0);

			this->InstProp.sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			this->InstProp.pNext						= NULL;
			this->InstProp.flags						= 0;
			this->InstProp.pApplicationInfo				= &AppProp;
			this->InstProp.enabledLayerCount			= 0;
			this->InstProp.ppEnabledLayerNames			= NULL;
			this->InstProp.enabledExtensionCount		= this->RequiredExtension.size();
			this->InstProp.ppEnabledExtensionNames		= this->RequiredExtension.data();

			VkResult Result = vkCreateInstance(&InstProp, NULL, &this->Instance);
			if (Result == VK_SUCCESS) {
				this->isVulkanReady = true;
			}
			else {
				this->isVulkanReady = false;
			}

		}

		// First initialized object is the system terminal.
		this->Object.push_back(&SystemTerminal);

		if (this->isGLSLANGReady && this->isGLFWReady && this->isVulkanReady) {

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
				this->isSystemDisplayAvailable = true;
			}

			// Query for gcl devices
			uint32_t PhysicalDeviceCount = 0;
			vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, NULL);
			if (PhysicalDeviceCount > 0) {
				std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
				vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
				for (size_t i = 0; i < PhysicalDeviceList.size(); i++) {
					this->DeviceList.push_back(new core::gcl::device(this->Instance, PhysicalDeviceList[i]));
				}
				this->isGCDeviceAvailable = true;
			}

		}

		this->isReady = this->isGLSLANGReady && this->isGLFWReady && this->isVulkanReady && this->isSystemDisplayAvailable && this->isGCDeviceAvailable;

		// Engine is ready, initialize loops.
		if (this->isReady) {

			// Initialize update thread for all objects.
			this->UpdateThread = std::thread(&engine::tupdate, this);
			this->RenderThread = std::thread(&engine::trender, this);

		}

		// ------------------------- Debug Print Info ------------------------- //

		//// Will print out display info.
		//for (size_t i = 0; i < Display.size(); i++) {
		//	std::cout << "Display Name:\t\t" << Display[i]->Name.str() << std::endl;
		//	std::cout << "Display Size:\t\t" << Display[i]->Size.x << ", " << Display[i]->Size.y << "\t[m]" << std::endl;
		//	std::cout << "Display Resolution:\t" << Display[i]->Resolution.x << ", " << Display[i]->Resolution.y << "\t[pixels]" << std::endl;
		//	std::cout << "Display Refresh Rate:\t" << Display[i]->Property.RefreshRate << "\t\t[1/s]" << std::endl;
		//	std::cout << std::endl;
		//}
		//
		//// Just simply prints out device info.
		//for (size_t i = 0; i < this->DeviceList.size(); i++) {
		//	std::cout << "Device ID:\t" << this->DeviceList[i]->Properties.deviceID << std::endl;
		//	std::cout << "Device Name:\t" << this->DeviceList[i]->Properties.deviceName << std::endl;
		//	std::cout << "Device Type:\t";
		//	switch (this->DeviceList[i]->Properties.deviceType) {
		//	case VK_PHYSICAL_DEVICE_TYPE_OTHER:
		//		std::cout << "Unknown" << std::endl;
		//		break;
		//	case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		//		std::cout << "Integrated GPU" << std::endl;
		//		break;
		//	case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		//		std::cout << "Discrete GPU" << std::endl;
		//		break;
		//	case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		//		std::cout << "Virtual GPU" << std::endl;
		//		break;
		//	case VK_PHYSICAL_DEVICE_TYPE_CPU:
		//		std::cout << "CPU" << std::endl;
		//		break;
		//	}
		//	std::cout << std::endl;
		//	for (size_t j = 0; j < this->DeviceList[i]->QueueFamilyProperties.size(); j++) {
		//		std::cout << "Family Index:\t" << j << std::endl;
		//		std::cout << "Queue Count:\t" << this->DeviceList[i]->QueueFamilyProperties[j].queueCount << std::endl;
		//		std::cout << "Graphics:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) >> 0) << std::endl;
		//		std::cout << "Compute:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) >> 1) << std::endl;
		//		std::cout << "Transfer:\t" << ((this->DeviceList[i]->QueueFamilyProperties[j].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) >> 2) << std::endl;
		//		// No idea what sparse binding is..
		//		//std::cout << "Sparse Binding:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT) >> 3) << std::endl << std::endl;
		//		std::cout << std::endl;
		//	}
		//	std::cout << std::endl;
		//}

		this->State = state::ENGINE_ACTIVE_STATE;
	}

	/*
	* Since the engine manages all created objects, it is the responsibility of the engine.
	* Also must shut down backend API. 
	*/
	engine::~engine() {

		this->State = state::ENGINE_DESTRUCTION_STATE;
		this->Shutdown.store(true);
		if (this->isReady) {
			this->UpdateThread.join();
			this->RenderThread.join();
		}

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

		vkDestroyInstance(this->Instance, NULL);

		glfwTerminate();

		glslang::FinalizeProcess();
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
		this->ThreadTrap.set(true);
		this->ThreadTrap.wait_until(2);
		this->Context.push_back(aContext);
		this->ThreadTrap.set(false);
	}

	void engine::remove(core::gcl::context* aContext) {
		// Should be fine?
		if (this->State != ENGINE_ACTIVE_STATE) return;

		this->ThreadTrap.set(true);
		this->ThreadTrap.wait_until(2);
		for (size_t i = 0; i < this->Context.size(); i++) {
			if (this->Context[i] == aContext) {
				this->Context.erase(this->Context.begin() + i);
			}
		}
		this->ThreadTrap.set(false);
	}

	void engine::submit(core::object_t* aObject) {
		this->ObjMtx.lock();
		this->Object.push_back(aObject);
		this->ObjMtx.unlock();
	}
	// TODO: Fix these two methods.
	void engine::remove(core::object_t* aObject) {
		this->ObjMtx.lock();
		for (size_t i = 0; i < this->Object.size(); i++) {
			if (this->Object[i] == aObject) {
				this->Object.erase(this->Object.begin() + i);
			}
		}
		this->ObjMtx.unlock();
	}

	VkInstance engine::handle() {
		return this->Instance;
	}

	bool engine::is_ready() {
		return this->isReady;
	}

	engine::version engine::get_version() {
		return this->Version;
	}

	double engine::get_time() {
		this->Mutex.lock();
		double temp = glfwGetTime();
		this->Mutex.unlock();
		return temp;
	}

	// TODO: Maybe move to another section of core?
	void engine::tsleep(double aSeconds) {
		double Microseconds = 1000.0 * aSeconds;
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

	// --------------- Render Thread --------------- //
	// Updates all objects that have been created asynchronously.
	// --------------- Render Thread --------------- //
	void engine::tupdate() {
		double t1, t2;
		double wt, ht;
		double t, dt;
		double ts = 1.0 / 2.0;
		dt = 0.0;
		

		std::vector<std::vector<VkSubmitInfo>> TransferSubmission;
		std::vector<std::vector<VkSubmitInfo>> ComputeSubmission;

		//uint32_t TransferSubmissionCount = 0;
		//VkSubmitInfo *TransferSubmission = NULL;

		while (!this->Shutdown.load()) {
			this->ThreadTrap.door();

			t1 = this->get_time();

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

			// Execute all host to device transfer operations.
			this->CtxMtx.lock();
			for (size_t i = 0; i < this->Context.size(); i++) {
				//vkQueueSubmit(this->Context[i]->Transfer, TransferSubmission[i].size(), TransferSubmission[i].data(), VK_NULL_HANDLE);
				//this->Context[i]->submit(core::gcl::context::qid::TRANSFER, TransferSubmission[i].size(), TransferSubmission[i].data(), VK_NULL_HANDLE);
				this->Context[i]->submit(core::gcl::context::qid::TRANSFER, 0, NULL, VK_NULL_HANDLE);
			}

			// Execute all device compute operations.
			for (size_t i = 0; i < this->Context.size(); i++) {
				//this->Context[i]->submit(core::gcl::context::qid::COMPUTE, ComputeSubmission[i].size(), ComputeSubmission[i].data(), VK_NULL_HANDLE);
				this->Context[i]->submit(core::gcl::context::qid::COMPUTE, 0, NULL, VK_NULL_HANDLE);
			}
			this->CtxMtx.unlock();

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
		}
		//std::cout << "Update Thread has exited." << std::endl;
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
			this->ThreadTrap.door();

			t1 = this->get_time();

			// Generates Submissions per stage.
			for (size_t i = 0; i < this->Stage.size(); i++) {
				//this->Stage[i]->render();
			}

			// Alter submission size to match number of contexts.
			Submission.resize(this->Context.size());


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
			
			// Execute all draw commands per context.
			for (size_t i = 0; i < this->Context.size(); i++) {
				//this->Context[i]->submit(core::gcl::context::qid::GRAPHICS, Submission[i].size(), Submission[i].data(), VK_NULL_HANDLE);
				this->Context[i]->submit(core::gcl::context::qid::GRAPHICS, 0, NULL, VK_NULL_HANDLE);
			}

			// Wait for render operations to complete for system_window presentation.

			// Present aggregated image indices.
			for (size_t i = 0; i < this->Context.size(); i++) {
				this->Context[i]->present(/*&Presentation[i]*/NULL);

				// After presentation has been called for system_windows, update
				// image indices ready to be acquired.
				//vkAcquireNextImageKHR()
			}

			t2 = this->get_time();
			dt = t2 - t1;
			this->tsleep(0.6);
		}
	}

	void engine::taudio() {

	}




}
