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

	int context::qfi(device::qfs aQFS) {
		switch (aQFS) {			
		default						: return -1;
		case device::qfs::TRANSFER	: return this->QFI[0];
		case device::qfs::COMPUTE	: return this->QFI[1];
		case device::qfs::GRAPHICS	: return this->QFI[2];
		case device::qfs::PRESENT	: return this->QFI[3];
		}
		return 0;
	}

	bool context::available(device::qfs aQFS) {
		return (this->available(aQFS) != -1);
	}

	VkResult context::create(device::qfs aQueueFamilySupport, size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {

		return VkResult();
	}

	void context::destroy(size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {

	}

	void context::submit(device::qfs aQFS, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence) {
		if ((aSubmissionCount < 1) || (aSubmission == NULL) || (this->qfi(aQFS) == -1)) return;
		// When placing an execution submission, thread must find
		// and available queue to submit to.

		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties* QueueFamilyProperty = this->Device->get_queue_families(&QueueFamilyCount);
		int lQFI = this->qfi(aQFS);

		int Offset = 0;
		int lQueueCount = 0;
		for (int i = 0; i < this->UQFICount; i++) {
			if (this->UQFI[i] == lQFI) {
				lQueueCount = QueueFamilyProperty[this->UQFI[i]].queueCount;
				break;
			}
			Offset += QueueFamilyProperty[this->UQFI[i]].queueCount;
		}

		int i = 0;
		while (true) {
			int Index = i + Offset;
			if (this->Queue[Index].Mutex.try_lock()) {
				vkQueueSubmit(this->Queue[Index].Handle, aSubmissionCount, aSubmission, aFence);
				this->Queue[Index].Mutex.unlock();
			}
			i += 1;
			if (i == lQueueCount) {
				i = 0;
			}
		}

	}

	void context::present(VkPresentInfoKHR* aPresentation) {
		if ((aPresentation == NULL) || (this->qfi(device::qfs::PRESENT) == -1)) return;

		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties* QueueFamilyProperty = this->Device->get_queue_families(&QueueFamilyCount);
		int lQFI = this->qfi(device::qfs::PRESENT);

		int Offset = 0;
		int lQueueCount = 0;
		for (int i = 0; i < this->UQFICount; i++) {
			if (this->UQFI[i] == lQFI) {
				lQueueCount = QueueFamilyProperty[this->UQFI[i]].queueCount;
				break;
			}
			Offset += QueueFamilyProperty[this->UQFI[i]].queueCount;
		}

		int i = 0;
		while (true) {
			int Index = i + Offset;
			if (this->Queue[Index].Mutex.try_lock()) {
				vkQueuePresentKHR(this->Queue[Index].Handle, aPresentation);
				this->Queue[Index].Mutex.unlock();
			}
			i += 1;
			if (i == lQueueCount) {
				i = 0;
			}
		}

	}

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
