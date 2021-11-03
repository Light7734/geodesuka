#include <geodesuka/engine.h>

#include <geodesuka/core/gcl/context.h>

#include <cstdlib>
#include <climits>

#include <GLFW/glfw3.h>

//#include <iostream>
//std::mutex gsIOMutex;

namespace geodesuka::core::gcl {

	context::context(engine* aEngine, device* aDevice, uint32_t aExtensionCount, const char** aExtensionList) {
		// List of operations.
		// Check for support of required extensions requested i
		// 1: Check for extensions.
		// 2: Queue Create Info.
		// 3: Create Logical Device.

		/*
		* 
		*/

		this->Engine = aEngine;
		this->Device = aDevice;
		if ((this->Engine == nullptr) || (this->Device == nullptr)) return;

		VkResult Result = VkResult::VK_SUCCESS;

		// If -1, then the option is not supported by the device.
		this->QFI[0] = this->Device->index(device::qsb::TRANSFER);
		this->QFI[1] = this->Device->index(device::qsb::COMPUTE);
		this->QFI[2] = this->Device->index(device::qsb::GRAPHICS);
		this->QFI[3] = this->Device->index(device::qsb::PRESENT);

		// Register this with context.h
		this->Support = 0;
		if (this->QFI[0] >= 0) {
			this->Support |= device::qsb::TRANSFER;
		}
		if (this->QFI[1] >= 0) {
			this->Support |= device::qsb::COMPUTE;
		}
		if (this->QFI[2] >= 0) {
			this->Support |= device::qsb::GRAPHICS;
		}
		if (this->QFI[3] >= 0) {
			this->Support |= device::qsb::PRESENT;
		}

		// UQFI set to -1, as default. Do not use.
		this->UQFI[0] = -1;
		this->UQFI[1] = -1;
		this->UQFI[2] = -1;
		this->UQFI[3] = -1;
		for (int i = 0; i < 4; i++) {
			if (this->QFI[i] == -1) continue;
			if (this->UQFICount == 0) {
				this->UQFI[this->UQFICount] = this->QFI[i];
				this->UQFICount += 1;
			}
			bool AlreadyExists = false;
			for (size_t j = 0; j < this->UQFICount; j++) {
				if (this->QFI[i] == this->UQFI[j]) {
					AlreadyExists = true;
					break;
				}
			}
			if (!AlreadyExists) {
				this->UQFI[this->UQFICount] = this->QFI[i];
				this->UQFICount += 1;
			}
		}

		//for (int i = 0; i < 4; i++) {
		//	if (this->QFI[i] == -1) continue;
		//	if (this->UQFI.size() == 0) {
		//		this->UQFI.push_back(this->QFI[i]);
		//	}
		//	bool AlreadyExists = false;
		//	for (size_t j = 0; j < this->UQFI.size(); j++) {
		//		if (this->QFI[i] == this->UQFI[j]) {
		//			AlreadyExists = true;
		//			break;
		//		}
		//	}
		//	if (!AlreadyExists) {
		//		this->UQFI.push_back(this->QFI[i]);
		//	}
		//}

		// With UQFI found, generate queues for selected indices.
		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties *QueueFamilyProperty = this->Device->get_queue_families(&QueueFamilyCount);

		this->QueueCount = 0;
		for (int i = 0; i < this->UQFICount; i++) {
			this->QueueCount += QueueFamilyProperty[this->UQFI[i]].queueCount;
		}

		this->QueueFamilyPriority = (float**)malloc(this->UQFICount * sizeof(float));
		if (this->QueueFamilyPriority != NULL) {
			for (int i = 0; i < this->UQFICount; i++) {
				this->QueueFamilyPriority[i] = (float*)malloc(QueueFamilyProperty[this->UQFI[i]].queueCount * sizeof(float));
				if (this->QueueFamilyPriority[i] != NULL) {
					for (uint32_t j = 0; j < QueueFamilyProperty[this->UQFI[i]].queueCount; j++) {
						this->QueueFamilyPriority[i][j] = 1.0f;
					}
				}
			}
		}
		this->QueueCreateInfo = (VkDeviceQueueCreateInfo*)malloc(this->UQFICount * sizeof(VkDeviceQueueCreateInfo));
		this->Queue = new queue[this->QueueCount];

		// Check for allocation failure.
		bool Allocated = true;
		Allocated = (this->QueueFamilyPriority != NULL) && (this->QueueCreateInfo != NULL) && (this->Queue != nullptr);
		if (Allocated) {
			for (int i = 0; i < this->UQFICount; i++) {
				Allocated = Allocated && (this->QueueFamilyPriority[i] != NULL);
			}
		}

		// Fail condition
		if (!Allocated) {
			delete[] this->Queue;
			this->Queue = nullptr;
			free(this->QueueCreateInfo);
			this->QueueCreateInfo = NULL;
			if (this->QueueFamilyPriority != NULL) {
				for (int i = 0; i < this->UQFICount; i++) {
					free(this->QueueFamilyPriority[i]);
					this->QueueFamilyPriority = NULL;
				}
			}
			return;
		}

		// Loads all create info.
		for (int i = 0; i < this->UQFICount; i++) {
			this->QueueCreateInfo[i].sType				= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			this->QueueCreateInfo[i].pNext				= NULL;
			this->QueueCreateInfo[i].flags				= 0;
			this->QueueCreateInfo[i].queueFamilyIndex	= this->UQFI[i];
			this->QueueCreateInfo[i].queueCount			= QueueFamilyProperty[this->UQFI[i]].queueCount;
			this->QueueCreateInfo[i].pQueuePriorities	= this->QueueFamilyPriority[i];
		}

		// Change this later.
		this->QueueCreateInfoCount = this->UQFICount;

		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0;
		this->CreateInfo.queueCreateInfoCount		= this->QueueCreateInfoCount;
		this->CreateInfo.pQueueCreateInfos			= this->QueueCreateInfo;
		this->CreateInfo.enabledLayerCount			= 0;
		this->CreateInfo.ppEnabledLayerNames		= NULL;
		if (this->Device->is_extension_list_supported(aExtensionCount, aExtensionList)) {
			this->CreateInfo.enabledExtensionCount			= aExtensionCount;
			this->CreateInfo.ppEnabledExtensionNames		= aExtensionList;
		}
		else {
			this->CreateInfo.enabledExtensionCount			= 0;
			this->CreateInfo.ppEnabledExtensionNames		= NULL;
		}
		this->CreateInfo.pEnabledFeatures			= &this->Device->Features;


		Result = vkCreateDevice(this->Device->handle(), &this->CreateInfo, NULL, &this->Handle);


		/*
		
		this->QueueCreateInfoCount = 0;
		this->QueueCreateInfo = NULL;
		this->QueueFamilyPriority = NULL;

		this->Device = aDevice;
		this->Handle = VK_NULL_HANDLE;

		// Used for early termination conditions.
		VkResult Result = VkResult::VK_SUCCESS;

		// TODO: For future reference with cross platform compatibility, insure
		// that a check is done here with extension "VK_KHR_surface".

		// This section is neccessary to create dummy surface
		// to test for presentation support. This makes the assumption
		// that presentation support does not depend on the parameters
		// of the surface created.
		glfwWindowHint(GLFW_RESIZABLE,			GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED,			GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED,			GLFW_TRUE);
		glfwWindowHint(GLFW_AUTO_ICONIFY,		GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING,			GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED,			GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE,			GLFW_FALSE);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR,	GLFW_FALSE);
		glfwWindowHint(GLFW_CENTER_CURSOR,		GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW,		GLFW_TRUE);
		glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
		glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE);

		// Create OS window handle.
		GLFWwindow* DummyWindow = glfwCreateWindow(640, 480, "Dummy Window", NULL, NULL);

		// Reset hints to insure no lingering parameters.
		glfwDefaultWindowHints();

		// Now create dummy window surface.
		VkSurfaceKHR DummySurface = VK_NULL_HANDLE;
		Result = glfwCreateWindowSurface(this->Device->inst(), DummyWindow, NULL, &DummySurface);

		// Get the queue families associated with creation physical device.
		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties* QueueFamily = aDevice->get_queue_families(&QueueFamilyCount);

		// Ideally, I would like to seperate each of the queues for their own specific
		// purposes, but if push comes to shove, they can all referece the exact same queue
		// handle.

		// Number of Queue Families with support.
		// {T, C, G, P}
		bool SupportExists[4] = { false, false, false, false };
		uint32_t FamilySupportCount[4] = { 0, 0, 0, 0 };
		uint32_t TotalSupportCount[4] = { 0, 0, 0, 0 };

		// Iterate through queue family and check support.
		for (uint32_t i = 0; i < QueueFamilyCount; i++) {
			// Checks for Transfer, Compute, and Graphics.
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) == VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) {
				FamilySupportCount[0] += 1;
				TotalSupportCount[0] += QueueFamily[i].queueCount;
				SupportExists[0] = true;
			}
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) == VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) {
				FamilySupportCount[1] += 1;
				TotalSupportCount[1] += QueueFamily[i].queueCount;
				SupportExists[1] = true;
			}
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) == VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) {
				FamilySupportCount[2] += 1;
				TotalSupportCount[2] += QueueFamily[i].queueCount;
				SupportExists[2] = true;
			}

			// TODO: Make sure "VK_KHR_surface" is a loaded extension in Instance.
			VkBool32 PresentSupport;
			Result = vkGetPhysicalDeviceSurfaceSupportKHR(this->Device->handle(), i, DummySurface, &PresentSupport);
			if (PresentSupport) {
				FamilySupportCount[3] += 1;
				TotalSupportCount[3] += QueueFamily[i].queueCount;
				SupportExists[3] = true;
			}
		}

		// Queue create info selection metrics based on device...
		
		this->QueueCreateInfo[0].sType					= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		this->QueueCreateInfo[0].pNext					= NULL;
		this->QueueCreateInfo[0].flags					= 0;
		this->QueueCreateInfo[0].queueFamilyIndex;
		this->QueueCreateInfo[0].queueCount;
		this->QueueCreateInfo[0].pQueuePriorities		; // Set this to 1.0f

		// TODO: Change this to reference device features from actual class.
		this->EnabledFeatures = this->Device->get_features();

		// Fill out logical device create info.
		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0;
		this->CreateInfo.queueCreateInfoCount		= this->QueueCreateInfoCount;
		this->CreateInfo.pQueueCreateInfos			= this->QueueCreateInfo;
		this->CreateInfo.enabledLayerCount			= 0;
		this->CreateInfo.ppEnabledLayerNames		= NULL;
		if (this->Device->is_extension_list_supported(aExtensionCount, aExtensionList)) {
			// If extensions are supported, loaded into context creation.
			this->CreateInfo.enabledExtensionCount		= aExtensionCount;
			this->CreateInfo.ppEnabledExtensionNames	= aExtensionList;
		}
		else {
			// TODO: Maybe change this to load only supported subset?
			this->CreateInfo.enabledExtensionCount		= 0;
			this->CreateInfo.ppEnabledExtensionNames	= NULL;
		}
		this->CreateInfo.pEnabledFeatures			= &this->EnabledFeatures;

		// Create Device and check errors.
		Result = vkCreateDevice(this->Device->handle(), &this->CreateInfo, NULL, &this->Handle);

		//vkGetDeviceQueue(this->Handle, 0, 0, &Q);
		

		// -------------------- Context Creation -------------------- //		
		
		VkResult lResult = VK_SUCCESS;

		this->Engine = aEngine;
		this->Device = aDevice;
		this->Handle = VK_NULL_HANDLE;

		// Check Device validity.
		// TODO: Prevent Race conditions on access of array?
		uint32_t lQueueFamilyCount = 0;
		const VkQueueFamilyProperties* lQueueFamily = this->Device->get_queue_families(&lQueueFamilyCount);

		this->QueueCount = 0;
		for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
			this->QueueCount += lQueueFamily[i].queueCount;
		}

		bool lAllocated = false;
		this->QueueCreateInfoCount = lQueueFamilyCount;
		this->QueueCreateInfo = (VkDeviceQueueCreateInfo*)malloc(lQueueFamilyCount * sizeof(VkDeviceQueueCreateInfo));
		this->QueueFamilyPriority = (float**)malloc(lQueueFamilyCount * sizeof(float*));
		this->Queue = new queue[this->QueueCount];
		lAllocated = (this->QueueCreateInfo != NULL) && (this->QueueFamilyPriority != NULL) && (this->Queue != nullptr);
		if (lAllocated) {
			for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
				this->QueueFamilyPriority[i] = (float*)malloc(lQueueFamily[i].queueCount * sizeof(float));
				lAllocated &= (this->QueueFamilyPriority[i] != NULL);
			}
		}

		// Memory Allocated, fill out rest.
		if (lAllocated) {

			// Set priority values. (Adjust later)
			for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
				for (uint32_t j = 0; j < lQueueFamily[i].queueCount; j++) {
					this->QueueFamilyPriority[i][j] = 1.0f;
				}
			}

			for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
				QueueCreateInfo[i].sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				QueueCreateInfo[i].pNext = NULL;
				QueueCreateInfo[i].flags = 0;
				QueueCreateInfo[i].queueFamilyIndex = i;
				QueueCreateInfo[i].queueCount = lQueueFamily[i].queueCount;
				QueueCreateInfo[i].pQueuePriorities = QueueFamilyPriority[i];
			}

			this->EnabledFeatures = this->Device->get_features();

			this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			this->CreateInfo.pNext						= NULL;
			this->CreateInfo.flags						= 0;
			this->CreateInfo.queueCreateInfoCount		= this->QueueCreateInfoCount;
			this->CreateInfo.pQueueCreateInfos			= this->QueueCreateInfo;
			this->CreateInfo.enabledLayerCount			= 0;
			this->CreateInfo.ppEnabledLayerNames		= NULL;
			if (this->Device->is_extension_list_supported(aExtensionCount, aExtensionList)) {
				this->CreateInfo.enabledExtensionCount		= aExtensionCount;
				this->CreateInfo.ppEnabledExtensionNames	= aExtensionList;
			}
			else {
				this->CreateInfo.enabledExtensionCount		= 0;
				this->CreateInfo.ppEnabledExtensionNames	= NULL;
			}
			this->CreateInfo.pEnabledFeatures			= &this->EnabledFeatures;

			lResult = vkCreateDevice(this->Device->handle(), &this->CreateInfo, NULL, &this->Handle);

			// This section is neccessary to create dummy surface
			// to test for presentation support. This makes the assumption
			// that presentation support does not depend on the parameters
			// of the surface created.
			glfwWindowHint(GLFW_RESIZABLE,			GLFW_TRUE);
			glfwWindowHint(GLFW_DECORATED,			GLFW_TRUE);
			glfwWindowHint(GLFW_FOCUSED,			GLFW_TRUE);
			glfwWindowHint(GLFW_AUTO_ICONIFY,		GLFW_TRUE);
			glfwWindowHint(GLFW_FLOATING,			GLFW_FALSE);
			glfwWindowHint(GLFW_MAXIMIZED,			GLFW_FALSE);
			glfwWindowHint(GLFW_VISIBLE,			GLFW_FALSE);
			glfwWindowHint(GLFW_SCALE_TO_MONITOR,	GLFW_FALSE);
			glfwWindowHint(GLFW_CENTER_CURSOR,		GLFW_TRUE);
			glfwWindowHint(GLFW_FOCUS_ON_SHOW,		GLFW_TRUE);
			glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
			glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE);

			// Create OS window handle.
			GLFWwindow* lDummyWindow = glfwCreateWindow(640, 480, "Dummy Window", NULL, NULL);

			// Reset hints to insure no lingering parameters.
			glfwDefaultWindowHints();

			// Since this code only relies on an instance, maybe query in device class?
			VkSurfaceKHR lDummySurface = VK_NULL_HANDLE;
			lResult = glfwCreateWindowSurface(this->Device->inst(), lDummyWindow, NULL, &lDummySurface);

			// Now make linearized array of queues. This is so lazy.
			// But I have no idea to make a search for best case atm.
			// I will change this whole block later. This method
			// currently loads all queues and blocks 

			size_t Offset = 0;
			for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
				for (uint32_t j = 0; j < lQueueFamily[i].queueCount; j++) {
					size_t lIndex = j + Offset;
					this->Queue[lIndex].QIndex = { i, j };

					//this->Queue[lIndex].inUse = false;
					this->Queue[lIndex].Flags = lQueueFamily[i].queueFlags;
					if ((lQueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) == VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) {
						this->Queue[lIndex].isTransferSupported = true;
					}
					if ((lQueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) == VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) {
						this->Queue[lIndex].isComputeSupported = true;
					}
					if ((lQueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) == VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) {
						this->Queue[lIndex].isGraphicsSupported = true;
					}

					// TODO: Make sure "VK_KHR_surface" is a loaded extension in Instance.
					VkBool32 PresentSupport;
					lResult = vkGetPhysicalDeviceSurfaceSupportKHR(this->Device->handle(), i, lDummySurface, &PresentSupport);
					if (PresentSupport == VK_TRUE) {
						this->Queue[lIndex].isPresentSupported = true;
					}
					else {
						this->Queue[lIndex].isPresentSupported = false;
					}

					this->Queue[lIndex].Handle = VK_NULL_HANDLE;
					vkGetDeviceQueue(this->Handle, i, j, &this->Queue[lIndex].Handle);
					//gsIOMutex.lock();
					//std::cout << "Queue Family: " << i;
					//std::cout << " T: " << this->Queue[lIndex].isTransferSupported;
					//std::cout << " C: " << this->Queue[lIndex].isComputeSupported;
					//std::cout << " G: " << this->Queue[lIndex].isGraphicsSupported;
					//std::cout << " P: " << this->Queue[lIndex].isPresentSupported << std::endl;
					//gsIOMutex.unlock();
				}
				Offset += lQueueFamily[i].queueCount;
			}

			vkDestroySurfaceKHR(this->Device->inst(), lDummySurface, NULL);
			lDummySurface = VK_NULL_HANDLE;
			glfwDestroyWindow(lDummyWindow);
			lDummyWindow = NULL;

			this->Engine->submit(this);
		}
		else {
			if (this->QueueCreateInfo != NULL) {
				free(this->QueueCreateInfo);
				this->QueueCreateInfo = NULL;
			}
			if (this->QueueFamilyPriority != NULL) {
				for (uint32_t i = 0; i < this->QueueCreateInfoCount; i++) {
					if (this->QueueFamilyPriority[i] != NULL) {
						free(this->QueueFamilyPriority[i]);
						this->QueueFamilyPriority[i] = NULL;
					}
				}
				free(this->QueueFamilyPriority);
				this->QueueFamilyPriority = NULL;
			}
			this->QueueCreateInfoCount = 0;

			this->Device = nullptr;
			this->Handle = VK_NULL_HANDLE;
		}
		//*/
	}

	context::~context() {
		// lock so context can be safely removed from engine instance.
		this->Engine->remove(this);

		vkDestroyDevice(this->Handle, NULL); this->Handle = VK_NULL_HANDLE;

		this->Device = nullptr;

		free(this->QueueCreateInfo); this->QueueCreateInfo = NULL;

		if (this->QueueFamilyPriority != NULL) {
			for (uint32_t i = 0; i < this->QueueCreateInfoCount; i++) {
				free(this->QueueFamilyPriority[i]); this->QueueFamilyPriority[i] = NULL;
			}
		}

		free(this->QueueFamilyPriority); this->QueueFamilyPriority = NULL;

		this->QueueCreateInfoCount = 0;

		delete[] this->Queue;
		this->Queue = nullptr;
	}

	bool context::available(qid aQID) {
		bool DoesQueueExist = false;
		this->Mutex.lock();
		// Check for existence of TRANSFER, COMPUTE, GRAPHICS, PRESENT.
		this->Mutex.unlock();
		return DoesQueueExist;
	}

	void context::submit(qid aQID, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence) {
		if ((aSubmissionCount < 1) || (aSubmission == NULL)) return;
		// When placing an execution submission, thread must find
		// and available queue to submit to.
		VkQueueFlags lFlag = 0;
		switch (aQID) {
		default:
			return;
		case qid::TRANSFER:
			lFlag |= VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT;
			break;
		case qid::COMPUTE:
			lFlag |= VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT;
			break;
		case qid::GRAPHICS:
			lFlag |= VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;
			break;
		}

		////size_t StackQueueSize;
		//queue* lQueue = nullptr;
		//size_t lQIndex = 0;

		//size_t lFamilyOffset = 0;
		//size_t lFamilyCount = 0;
		//size_t lFamilyIndex = UINT_MAX;

		//// Select Queue Family based on least multiple support.
		//this->Mutex.lock();
		//uint32_t lQueueFamilyCount = 0;
		//const VkQueueFamilyProperties* lQueueFamily = this->Device->get_queue_families(&lQueueFamilyCount);
		//std::vector<uint32_t> lFamilySupportCount(lQueueFamilyCount);
		//lQueue = this->Queue;
		//this->Mutex.unlock();

		//// Query for support count.
		//for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
		//	lQIndex = lFamilyOffset;
		//	if (lQueue[lQIndex].isTransferSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isComputeSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isGraphicsSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isPresentSupported)
		//		lFamilySupportCount[i] += 1;
		//	lFamilyOffset += lQueueFamily[i].queueCount;
		//}

		//uint32_t lMinSupport = 10;
		//
		//// Find Min Support Index
		//for (size_t i = 0; i < lFamilySupportCount.size(); i++) {
		//	if ((lMinSupport > lFamilySupportCount[i]) && ((lQueueFamily[i].queueFlags & lFlag) == lFlag)) {
		//		lMinSupport = lFamilySupportCount[i];
		//		lFamilyIndex = i;
		//	}
		//}

		//// Calculate offset
		//lFamilyOffset = 0;
		//for (uint32_t i = 0; i < lFamilyIndex; i++) {
		//	lFamilyOffset += lQueueFamily[i].queueCount;
		//}
		//
		//// C++11
		//// Different elements in the same container can be modified concurrently by
		//// different threads, except for the elements of std::vector< bool> (for example,
		//// a vector of std::future objects can be receiving values from multiple threads).
		//
		//// Find an empty queue within the family to execute payload.
		//lFamilyIndex = 0;
		//while (true) {
		//	lQIndex = lFamilyIndex + lFamilyOffset;
		//	if (lQueue[lQIndex].Mutex.try_lock()) {
		//		vkQueueSubmit(lQueue[lQIndex].Handle, aSubmissionCount, aSubmission, aFence);
		//		lQueue[lQIndex].Mutex.unlock();
		//		break;
		//	}

		//	// Cycle until available queue is found.
		//	lFamilyIndex += 1;
		//	if (lFamilyIndex == lFamilyCount) {
		//		lFamilyIndex = 0;
		//	}
		//}

	}

	void context::present(VkPresentInfoKHR* aPresentation) {
		if (aPresentation == NULL) return;
		////size_t StackQueueSize;
		//queue* lQueue = nullptr;
		//size_t lQIndex = 0;

		//size_t lFamilyOffset = 0;
		//size_t lFamilyCount = 0;
		//size_t lFamilyIndex = UINT_MAX;

		//// Select Queue Family based on least multiple support.
		//this->Mutex.lock();
		//uint32_t lQueueFamilyCount = 0;
		//const VkQueueFamilyProperties* lQueueFamily = this->Device->get_queue_families(&lQueueFamilyCount);
		//std::vector<uint32_t> lFamilySupportCount(lQueueFamilyCount);
		//lQueue = this->Queue;

		////for (size_t i = 0; i < this->QueueCount; i++) {
		////	gsIOMutex.lock();
		////	std::cout << "Queue Family: " << i;
		////	std::cout << " T: " << this->Queue[i].isTransferSupported;
		////	std::cout << " C: " << this->Queue[i].isComputeSupported;
		////	std::cout << " G: " << this->Queue[i].isGraphicsSupported;
		////	std::cout << " P: " << this->Queue[i].isPresentSupported << std::endl;
		////	gsIOMutex.unlock();
		////}

		//this->Mutex.unlock();

		//// Query for support count.
		//for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
		//	lQIndex = lFamilyOffset;
		//	if (lQueue[lQIndex].isTransferSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isComputeSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isGraphicsSupported)
		//		lFamilySupportCount[i] += 1;
		//	if (lQueue[lQIndex].isPresentSupported)
		//		lFamilySupportCount[i] += 1;
		//	lFamilyOffset += lQueueFamily[i].queueCount;
		//}

		//uint32_t lMinSupport = 10;

		//// Find Min Present Support Index
		//lFamilyOffset = 0;
		//for (uint32_t i = 0; i < lFamilySupportCount.size(); i++) {
		//	lQIndex = lFamilyOffset;
		//	//gsIOMutex.lock();
		//	//std::cout << "Queue Family: " << lQIndex;
		//	//std::cout << " T: " << this->Queue[lQIndex].isTransferSupported;
		//	//std::cout << " C: " << this->Queue[lQIndex].isComputeSupported;
		//	//std::cout << " G: " << this->Queue[lQIndex].isGraphicsSupported;
		//	//std::cout << " P: " << this->Queue[lQIndex].isPresentSupported << std::endl;
		//	//gsIOMutex.unlock();
		//	if ((lMinSupport > lFamilySupportCount[i]) && (lQueue[lQIndex].isPresentSupported)) {
		//		lMinSupport = lFamilySupportCount[i];
		//		lFamilyIndex = i;
		//	}
		//	lFamilyOffset += lQueueFamily[i].queueCount;
		//}

		//// Calculate offset
		//lFamilyOffset = 0;
		//for (uint32_t i = 0; i < lFamilyIndex; i++) {
		//	lFamilyOffset += lQueueFamily[i].queueCount;
		//}

		//// C++11
		//// Different elements in the same container can be modified concurrently by
		//// different threads, except for the elements of std::vector< bool> (for example,
		//// a vector of std::future objects can be receiving values from multiple threads).

		//// Find an empty queue within the family to submit to.
		//lFamilyIndex = 0;
		//while (true) {
		//	lQIndex = lFamilyIndex + lFamilyOffset;
		//	if (lQueue[lQIndex].Mutex.try_lock()) {
		//		vkQueuePresentKHR(lQueue[lQIndex].Handle, aPresentation);
		//		lQueue[lQIndex].Mutex.unlock();
		//		break;
		//	}

		//	// Cycle until available queue is found.
		//	lFamilyIndex += 1;
		//	if (lFamilyIndex == lFamilyCount) {
		//		lFamilyIndex = 0;
		//	}
		//}
	}

	//bool context::ext_supported(const char* aExtension) {
	//	// Make hash map.
	//	for (size_t i = 0; i < ActiveExtension.size(); i++) {
	//		if (strcmp(this->DesiredExtension[i], aExtension) == 0) {
	//			return this->ActiveExtension[i];
	//		}
	//		else {
	//			return false;
	//		}
	//	}
	//	return false;
	//}

	VkInstance context::inst() {
		return this->Device->inst();
	}

	device* context::parent() {
		return this->Device;
	}

	VkDevice context::handle() {
		return this->Handle;
	}

	context::queue::queue() {
		this->i = 0;
		this->j = 0;
		this->FC.Flags = 0;
		this->FC.isTransferSupported = false;
		this->FC.isComputeSupported = false;
		this->FC.isGraphicsSupported = false;
		this->FC.isPresentSupported = false;
		this->FC.Support = 0;
		this->Handle = VK_NULL_HANDLE;
	}

}
