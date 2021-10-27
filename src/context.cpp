#include <geodesuka/engine.h>

#include <geodesuka/core/gcl/context.h>

#include <cstdlib>
#include <climits>

#include <GLFW/glfw3.h>

namespace geodesuka::core::gcl {

	context::context(engine* aEngine, device* aDevice, uint32_t aExtensionCount, const char** aExtensionList) {
		// List of operations.
		// Check for support of required extensions requested i
		// 1: Check for extensions.
		// 2: Queue Create Info.
		// 3: Create Logical Device.


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
		*/

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

			// Now create dummy window surface.
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
					if (PresentSupport) {
						this->Queue[lIndex].isPresentSupported = true;
					}

					this->Queue[lIndex].Handle = VK_NULL_HANDLE;
					vkGetDeviceQueue(this->Handle, i, j, &this->Queue[lIndex].Handle);
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
		// Check for existence of queue.
		this->Mutex.unlock();
		return DoesQueueExist;
	}

	void context::submit(qid aQID, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence) {
		if ((aSubmissionCount == 0) || (aSubmission == NULL)) return;
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

		//size_t StackQueueSize;
		queue* lQueue = nullptr;
		size_t lQIndex = 0;

		size_t lFamilyOffset = 0;
		size_t lFamilyCount = 0;
		size_t lFamilyIndex = UINT_MAX;

		// Select Queue Family based on least multiple support.
		this->Mutex.lock();
		uint32_t lQueueFamilyCount = 0;
		const VkQueueFamilyProperties* lQueueFamily = this->Device->get_queue_families(&lQueueFamilyCount);
		std::vector<uint32_t> lFamilySupportCount(lQueueFamilyCount);
		lQueue = this->Queue;
		this->Mutex.unlock();

		// Query for support count.
		for (uint32_t i = 0; i < lQueueFamilyCount; i++) {
			lQIndex = lFamilyOffset;
			if (lQueue[lQIndex].isTransferSupported)
				lFamilySupportCount[i] += 1;
			if (lQueue[lQIndex].isComputeSupported)
				lFamilySupportCount[i] += 1;
			if (lQueue[lQIndex].isGraphicsSupported)
				lFamilySupportCount[i] += 1;
			if (lQueue[lQIndex].isPresentSupported)
				lFamilySupportCount[i] += 1;
			lFamilyOffset += lQueueFamily[i].queueCount;
		}

		uint32_t lMinSupport = 10;
		
		// Find Min Support Index
		for (size_t i = 0; i < lFamilySupportCount.size(); i++) {
			if ((lMinSupport > lFamilySupportCount[i]) && ((lQueueFamily[i].queueFlags & lFlag) == lFlag)) {
				lMinSupport = lFamilySupportCount[i];
				lFamilyIndex = i;
			}
		}

		// Calculate offset
		lFamilyOffset = 0;
		for (uint32_t i = 0; i < lFamilyIndex; i++) {
			lFamilyOffset += lQueueFamily[i].queueCount;
		}
		
		// C++11
		// Different elements in the same container can be modified concurrently by
		// different threads, except for the elements of std::vector< bool> (for example,
		// a vector of std::future objects can be receiving values from multiple threads).
		
		// Find an empty queue within the family to execute payload.
		lFamilyIndex = 0;
		while (true) {
			lQIndex = lFamilyIndex + lFamilyOffset;
			if (lQueue[lQIndex].Mutex.try_lock()) {
				//vkQueueSubmit(lQueue[lQIndex].Handle, aSubmissionCount, aSubmission, aFence);
				lQueue[lQIndex].Mutex.unlock();
				break;
			}

			// Cycle until available queue is found.
			lFamilyIndex += 1;
			if (lFamilyIndex == lFamilyCount) {
				lFamilyIndex = 0;
			}
		}


	}

	void context::present(VkPresentInfoKHR* aPresentation) {
		this->Mutex.lock();

		this->Mutex.unlock();
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
		this->QIndex = { 0, 0 };

		this->Flags = 0;
		this->isTransferSupported = false;
		this->isComputeSupported = false;
		this->isGraphicsSupported = false;
		this->isPresentSupported = false;

		this->Handle = VK_NULL_HANDLE;
	}

}
