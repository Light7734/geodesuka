#include <geodesuka/engine.h>

#include <geodesuka/core/gcl/context.h>

#include <cstdlib>
#include <climits>

#include <GLFW/glfw3.h>

namespace geodesuka::core::gcl {

	context::context(engine* aEngine, device* aDevice, uint32_t aLayerCount, const char** aLayerList, uint32_t aExtensionCount, const char** aExtensionList) {

		// Is this necessary?
		//this->Mutex.lock();
		// Insures that object isn't accessed during construction.
		this->isReady.store(false);
		// Adds context to engine state. Cannot be accessed while not ready.
		this->Engine->State.Mutex.lock();
		this->Engine->State.Context.push_back(this);
		this->Engine->State.Mutex.unlock();

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
		//this->QFI[2] = this->Device->qfi(device::qfs::GRAPHICS);
		this->QFI[2] = this->Device->qfi(device::qfs::GRAPHICS_AND_COMPUTE);
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

		// Searches and sorts out Unique Queue Indices.
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

		// With UQFI found, generate queues for selected indices.
		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties *QueueFamilyProperty = this->Device->get_queue_families(&QueueFamilyCount);

		this->QueueCount = 0;
		for (int i = 0; i < this->UQFICount; i++) {
			this->QueueCount += QueueFamilyProperty[this->UQFI[i]].queueCount;
		}

		this->QueueFamilyPriority = (float**)malloc(this->UQFICount * sizeof(float*));
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
		this->CreateInfo.enabledLayerCount			= aLayerCount;
		this->CreateInfo.ppEnabledLayerNames		= aLayerList;
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

		for (int i = 0; i < 3; i++) {
			this->PoolCreateInfo[i].sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			this->PoolCreateInfo[i].pNext = NULL;
		}

		// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT
		// Will be used for one time submits and short lived command buffers.
		// This will be useful in object construction and uploading.

		// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
		// Allows individual command buffers to be reset.
		
		// One time submit pool
		// Transfer operations.
		this->PoolCreateInfo[0].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		this->PoolCreateInfo[0].queueFamilyIndex	= this->qfi(device::qfs::TRANSFER);

		// Compute operations.
		this->PoolCreateInfo[1].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		this->PoolCreateInfo[1].queueFamilyIndex	= this->qfi(device::qfs::COMPUTE);

		// Graphics operations.
		this->PoolCreateInfo[2].flags				= VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VkCommandPoolCreateFlagBits::VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		this->PoolCreateInfo[2].queueFamilyIndex	= this->qfi(device::qfs::GRAPHICS);

		for (int i = 0; i < 3; i++) {
			if (this->QFI[i] != -1) {
				Result = vkCreateCommandPool(this->Handle, &this->PoolCreateInfo[i], NULL, &this->Pool[i]);
			}
			else {
				this->Pool[i] = VK_NULL_HANDLE;
			}
			this->CommandBufferCount[i] = 0;
			this->CommandBuffer[i] = NULL;
		}

		this->isReady.store(true);
		this->Mutex.unlock();
	}

	context::~context() {
		// lock so context can be safely removed from engine instance.
		this->Mutex.lock();
		this->Engine->State->Mutex.lock();


		// Clear all command buffers and pools.
		for (int i = 0; i < 3; i++) {
			if (this->CommandBufferCount[i] > 0) {
				vkFreeCommandBuffers(this->Handle, this->Pool[i], this->CommandBufferCount[i], this->CommandBuffer[i]);
			}
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
		default									: return -1;
		case device::qfs::TRANSFER				: return this->QFI[0];
		case device::qfs::COMPUTE				: return this->QFI[1];
		case device::qfs::GRAPHICS				: return this->QFI[2];
		//case device::qfs::GRAPHICS_AND_COMPUTE	: return this->QFI[3];
		case device::qfs::PRESENT				: return this->QFI[3];
		}
		return 0;
	}

	bool context::available(device::qfs aQFS) {
		return (this->qfi(aQFS) != -1);
	}

	VkCommandBuffer context::create(device::qfs aQFS) {
		VkCommandBuffer temp = VK_NULL_HANDLE;
		this->create(aQFS, 1, &temp);
		return temp;
	}

	VkResult context::create(device::qfs aQFS, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {
		VkResult Result = VkResult::VK_INCOMPLETE;
		if ((this->qfi(aQFS) < 0) || (aCommandBufferCount == 0) || (aCommandBuffer == NULL)) return Result;

		int i;
		switch (aQFS) {
		default: return Result;
		case device::qfs::TRANSFER:	 i = 0; break;
		case device::qfs::COMPUTE:	 i = 1; break;
		case device::qfs::GRAPHICS:	 i = 2; break;
		}

		// Pool is invalid.
		if (this->Pool[i] == VK_NULL_HANDLE) return Result;

		VkCommandBufferAllocateInfo AllocateInfo{};

		AllocateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.pNext					= NULL;
		AllocateInfo.commandPool			= this->Pool[i];
		AllocateInfo.level					= VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		AllocateInfo.commandBufferCount		= aCommandBufferCount;

		this->Mutex.lock();
		// Check if allocation is succesful.
		Result = vkAllocateCommandBuffers(this->Handle, &AllocateInfo, aCommandBuffer);
		if (Result != VkResult::VK_SUCCESS) {
			this->Mutex.unlock();
			return Result;
		}

		// alloc/realloc command buffer memory pool.
		void* nptr = NULL;
		if (this->CommandBuffer[i] == NULL) {
			nptr = malloc(aCommandBufferCount * sizeof(VkCommandBuffer));
		}
		else {
			nptr = realloc(this->CommandBuffer[i], (aCommandBufferCount + this->CommandBufferCount[i]) * sizeof(VkCommandBuffer));
		}

		// Out of host memory.
		if (nptr == NULL) {
			Result = VkResult::VK_ERROR_OUT_OF_HOST_MEMORY;
			vkFreeCommandBuffers(this->Handle, this->Pool[i], aCommandBufferCount, aCommandBuffer);
			for (size_t j = 0; j < aCommandBufferCount; j++) {
				aCommandBuffer[j] = VK_NULL_HANDLE;
			}
			this->Mutex.unlock();
			return Result;
		}

		// Copy new pointer over.
		this->CommandBuffer[i] = (VkCommandBuffer*)nptr;

		// Store new command buffers.
		std::memcpy(&(this->CommandBuffer[i][this->CommandBufferCount[i]]), aCommandBuffer, aCommandBufferCount * sizeof(VkCommandBuffer));
		//for (int j = this->CommandBufferCount[i]; j < aCommandBufferCount + this->CommandBufferCount[i]; j++) {
		//	this->CommandBuffer[i][j] = aCommandBuffer[j - this->CommandBufferCount[i]];
		//}

		// Account for new buffer count.
		this->CommandBufferCount[i] += aCommandBufferCount;
		this->Mutex.unlock();
		return Result;
	}

	void context::destroy(device::qfs aQFS, VkCommandBuffer& aCommandBuffer) {
		this->destroy(aQFS, 1, &aCommandBuffer);
	}

	void context::destroy(device::qfs aQFS, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {
		if ((this->qfi(aQFS) < 0) || (aCommandBufferCount == 0) || (aCommandBuffer == NULL)) return;
		// Takes a list of aggregated command buffers and cross references them
		// with already created command buffers.


		int Index;
		switch (aQFS) {
		default: return;
		case device::qfs::TRANSFER:	 Index = 0; break;
		case device::qfs::COMPUTE:	 Index = 1; break;
		case device::qfs::GRAPHICS:	 Index = 2; break;
		}

		if (this->Pool[Index] == VK_NULL_HANDLE) return;

		// Match
		int MatchCount = 0;
		VkCommandBuffer* MatchBuffer = NULL;
		VkCommandBuffer* NewBuffer = NULL;

		this->Mutex.lock();
		// Count number of matches.
		for (uint32_t i = 0; i < this->CommandBufferCount[Index]; i++) {
			for (uint32_t j = 0; j < aCommandBufferCount; j++) {
				if (this->CommandBuffer[Index][i] == aCommandBuffer[j]) {
					MatchCount += 1;
				}
			}
		}

		// No command buffers matched.
		if (MatchCount == 0) {
			this->Mutex.unlock();
			return;
		}

		// Clears all command buffer with family in question.
		if (MatchCount == this->CommandBufferCount[Index]) {
			for (uint32_t i = 0; i < this->CommandBufferCount[Index]; i++) {
				for (uint32_t j = 0; j < aCommandBufferCount; j++) {
					if (this->CommandBuffer[Index][i] == aCommandBuffer[j]) {
						aCommandBuffer[j] = VK_NULL_HANDLE;
					}
				}
			}
			vkFreeCommandBuffers(this->Handle, this->Pool[Index], aCommandBufferCount, aCommandBuffer);
			free(this->CommandBuffer[Index]);
			this->CommandBuffer[Index] = NULL;
			this->CommandBufferCount[Index] = 0;
			this->Mutex.unlock();
			return;
		}

		MatchBuffer = (VkCommandBuffer*)malloc(MatchCount * sizeof(VkCommandBuffer));
		NewBuffer = (VkCommandBuffer*)malloc((this->CommandBufferCount[Index] - MatchCount) * sizeof(VkCommandBuffer));

		// Memory allocation failure.
		if ((MatchBuffer == NULL) || (NewBuffer == NULL)) {
			free(MatchBuffer);
			MatchBuffer = NULL;
			free(NewBuffer);
			NewBuffer = NULL;
			this->Mutex.unlock();
			return;
		}

		int m = 0;
		int n = 0;
		// Iterate through pre existing buffers and compare.
		for (uint32_t i = 0; i < this->CommandBufferCount[Index]; i++) {
			bool isFound = false;
			int FoundIndex = -1;
			// Compare to proposed buffers.
			for (uint32_t j = 0; j < aCommandBufferCount; j++) {
				if (this->CommandBuffer[Index][i] == aCommandBuffer[j]) {
					isFound = true;
					FoundIndex = j;
					break;
				}
			}

			if (isFound) {
				// If match, move to MatchBuffer;
				MatchBuffer[m] = aCommandBuffer[FoundIndex];
				aCommandBuffer[FoundIndex] = VK_NULL_HANDLE;
				m += 1;
			}
			else {
				NewBuffer[n] = this->CommandBuffer[Index][i];
				n += 1;
			}

		}

		vkFreeCommandBuffers(this->Handle, this->Pool[Index], MatchCount, MatchBuffer);
		free(MatchBuffer);
		MatchBuffer = NULL;
		free(this->CommandBuffer[Index]);
		this->CommandBuffer[Index] = NewBuffer;
		this->CommandBufferCount[Index] = this->CommandBufferCount[Index] - MatchCount;
		this->Mutex.unlock();
		return;
	}

	VkResult context::submit(device::qfs aQFS, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence) {
		VkResult Result = VkResult::VK_INCOMPLETE;
		if ((aSubmissionCount < 1) || (aSubmission == NULL) || (this->qfi(aQFS) == -1)) return Result;
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
				Result = vkQueueSubmit(this->Queue[Index].Handle, aSubmissionCount, aSubmission, aFence);
				this->Queue[Index].Mutex.unlock();
				break;
			}
			i += 1;
			if (i == lQueueCount) {
				i = 0;
			}
		}
		return Result;
	}

	VkResult context::present(VkPresentInfoKHR* aPresentation) {
		VkResult Result = VkResult::VK_INCOMPLETE;
		if ((aPresentation == NULL) || (this->qfi(device::qfs::PRESENT) == -1)) return Result;

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
				Result = vkQueuePresentKHR(this->Queue[Index].Handle, aPresentation);
				this->Queue[Index].Mutex.unlock();
				break;
			}
			i += 1;
			if (i == lQueueCount) {
				i = 0;
			}
		}
		return Result;
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
		this->Handle = VK_NULL_HANDLE;
	}

}
