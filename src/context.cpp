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

		this->Engine = aEngine;
		this->Device = aDevice;
		if ((this->Engine == nullptr) || (this->Device == nullptr)) return;

		VkResult Result = VkResult::VK_SUCCESS;

		// If -1, then the option is not supported by the device.
		this->QFI[0] = this->Device->qfi(device::qfs::TRANSFER);
		this->QFI[1] = this->Device->qfi(device::qfs::COMPUTE);
		this->QFI[2] = this->Device->qfi(device::qfs::GRAPHICS);
		this->QFI[3] = this->Device->qfi(device::qfs::PRESENT);

		// Register this with context.h
		this->Support = 0;
		if (this->QFI[0] >= 0) {
			this->Support |= device::qfs::TRANSFER;
		}
		if (this->QFI[1] >= 0) {
			this->Support |= device::qfs::COMPUTE;
		}
		if (this->QFI[2] >= 0) {
			this->Support |= device::qfs::GRAPHICS;
		}
		if (this->QFI[3] >= 0) {
			this->Support |= device::qfs::PRESENT;
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
			delete[] this->Queue; this->Queue = nullptr;
			free(this->QueueCreateInfo); this->QueueCreateInfo = NULL;
			if (this->QueueFamilyPriority != NULL) {
				for (int i = 0; i < this->UQFICount; i++) {
					free(this->QueueFamilyPriority[i]); this->QueueFamilyPriority = NULL;
				}
			}
			free(this->QueueFamilyPriority); this->QueueFamilyPriority = NULL;
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

		// Load VkDevice Create Info.
		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0;
		this->CreateInfo.queueCreateInfoCount		= this->UQFICount;
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

		// Now get queues from device.
		size_t QueueArrayOffset = 0;
		for (int i = 0; i < this->UQFICount; i++) {
			for (uint32_t j = 0; j < QueueFamilyProperty[this->UQFI[i]].queueCount; j++) {
				size_t Index = j + QueueArrayOffset;
				this->Queue[Index].i = this->UQFI[i];
				this->Queue[Index].j = j;
				vkGetDeviceQueue(this->Handle, this->UQFI[i], j, &this->Queue[Index].Handle);
			}
			QueueArrayOffset += QueueFamilyProperty[this->UQFI[i]].queueCount;
		}

		for (int i = 0; i < 4; i++) {
			this->PoolCreateInfo[1].sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			this->PoolCreateInfo[1].pNext = NULL;
		}

		// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT
		// Will be used for one time submits and short lived command buffers.
		// This will be useful in object construction and uploading.

		// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
		// Allows individual command buffers to be reset.
		
		// One time submit pool
		this->PoolCreateInfo[0].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

		// Persistent Transfer operations.
		this->PoolCreateInfo[1].flags				= 0;

		// Compute operations.
		this->PoolCreateInfo[2].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		// Graphics operations.
		this->PoolCreateInfo[3].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		for (int i = 0; i < 4; i++) {
			if (this->QFI[i] != -1) {
				this->PoolCreateInfo[i].queueFamilyIndex = this->QFI[i];
				Result = vkCreateCommandPool(this->Handle, &this->PoolCreateInfo[i], NULL, &this->Pool[i]);
			}
		}

		this->Engine->submit(this);

	}

	context::~context() {
		// lock so context can be safely removed from engine instance.
		this->Mutex.lock();

		this->Engine->remove(this);

		// Clear all command buffers and pools.
		for (int i = 0; i < 4; i++) {
			vkFreeCommandBuffers(this->Handle, this->Pool[i], this->CommandBufferCount[i], this->CommandBuffer[i]);
			free(this->CommandBuffer[i]); this->CommandBuffer[i] = NULL;
			this->CommandBufferCount[i] = 0;
			vkDestroyCommandPool(this->Handle, this->Pool[i], NULL);
			this->Pool[i] = VK_NULL_HANDLE;
		}

		delete[] this->Queue; this->Queue = nullptr;
		this->QueueCount = 0;

		vkDestroyDevice(this->Handle, NULL); this->Handle = VK_NULL_HANDLE;

		free(this->QueueCreateInfo); this->QueueCreateInfo = NULL;

		if (this->QueueFamilyPriority != NULL) {
			for (int i = 0; i < this->UQFICount; i++) {
				free(this->QueueFamilyPriority[i]); this->QueueFamilyPriority[i] = NULL;
			}
		}

		free(this->QueueFamilyPriority); this->QueueFamilyPriority = NULL;

		for (int i = 0; i < 4; i++) {
			this->QFI[i] = -1;
			this->UQFI[i] = -1;
		}
		this->UQFICount = 0;

		this->Support = 0;

		this->Engine = nullptr;
		this->Device = nullptr;

		this->Mutex.unlock();
	}

	int context::qfi(device::qfs aQSB) {
		switch (aQSB) {			
		default						: return -1;
		case device::qfs::TRANSFER	: return this->QFI[0];
		case device::qfs::COMPUTE	: return this->QFI[1];
		case device::qfs::GRAPHICS	: return this->QFI[2];
		case device::qfs::PRESENT	: return this->QFI[3];
		}
		return 0;
	}

	bool context::available(device::qfs aQID) {
		return (this->available(aQID) != -1);
	}

	void context::submit(device::qfs aQID, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence) {
		if ((aSubmissionCount < 1) || (aSubmission == NULL) || (this->qfi(aQID) == -1)) return;
		// When placing an execution submission, thread must find
		// and available queue to submit to.
		VkQueueFlags lFlag = 0;
		switch (aQID) {
		default:
			return;
		case device::qfs::TRANSFER:
			lFlag |= VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT;
			break;
		case device::qfs::COMPUTE:
			lFlag |= VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT;
			break;
		case device::qfs::GRAPHICS:
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
		//this->Capability.Flags = 0;
		//this->Capability.isTransferSupported = false;
		//this->Capability.isComputeSupported = false;
		//this->Capability.isGraphicsSupported = false;
		//this->Capability.isPresentSupported = false;
		//this->Capability.Support = 0;
		this->Handle = VK_NULL_HANDLE;
	}

}
