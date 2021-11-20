#include <geodesuka/core/gcl/buffer.h>

// Used to interact with texture class
#include <geodesuka/core/gcl/texture.h>

namespace geodesuka::core::gcl {

	buffer::buffer() {
		this->Context = nullptr;
		this->Handle = VK_NULL_HANDLE;
		this->MemoryHandle = VK_NULL_HANDLE;
		this->MemoryProperty = 0;
		this->Count = 0;
	}

	buffer::buffer(context* aContext, int aMemType, int aUsage, int aCount, util::variable aMemoryLayout, void* aBufferData) {
		if (aContext == nullptr) return;
		VkResult Result = VK_SUCCESS;
		this->Context = aContext;

		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0; // Ignore.
		this->CreateInfo.size						= aCount * aMemoryLayout.Type.Size;
		this->CreateInfo.usage						= (VkBufferUsageFlags)(aUsage | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST); // Enable Transfer
		this->CreateInfo.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		this->CreateInfo.queueFamilyIndexCount		= 0;
		this->CreateInfo.pQueueFamilyIndices		= NULL;

		this->Handle								= VK_NULL_HANDLE;
		this->MemoryHandle							= VK_NULL_HANDLE;

		this->Count									= aCount;
		this->MemoryLayout							= aMemoryLayout;

		// Create Device Buffer Object.
		Result = vkCreateBuffer(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);

		// Allocates Memory Handle
		if (Result == VkResult::VK_SUCCESS) {
			// Gathers memory requirements of the created buffer.
			VkMemoryRequirements MemReq;
			vkGetBufferMemoryRequirements(aContext->handle(), this->Handle, &MemReq);

			// Gathers memory properties of the device.
			VkPhysicalDeviceMemoryProperties MemProp;
			vkGetPhysicalDeviceMemoryProperties(aContext->parent()->handle(), &MemProp);

			this->AllocateInfo.sType			= VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			this->AllocateInfo.pNext			= NULL;
			this->AllocateInfo.allocationSize	= MemReq.size;
			// Currently index selection chooses indice based on proposed aMemType,
			// and can possibly include extra features rather than exactly demanded.
			// Maybe change to exactly only chosen features later on.
			for (uint32_t i = 0; i < MemProp.memoryTypeCount; i++) {
				// Searches for exact memory properties.
				//if (((MemReq.memoryTypeBits & (1 << i)) >> i) && (MemProp.memoryTypes[i].propertyFlags == aMemType))
				// Searches for approximate memory properties, with additional props.
				if (((MemReq.memoryTypeBits & (1 << i)) >> i) && ((MemProp.memoryTypes[i].propertyFlags & aMemType) == aMemType)) {
					this->MemoryProperty = MemProp.memoryTypes[i].propertyFlags;
					this->AllocateInfo.memoryTypeIndex = i;
					break;
				}
			}
			
			// Allocate Device Memory.
			Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
		}

		// Bind memory to buffer
		if (Result == VkResult::VK_SUCCESS) {
			Result = vkBindBufferMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
		}

		if ((Result == VkResult::VK_SUCCESS) && (aBufferData != NULL) && ((this->MemoryProperty & (device::memory::HOST_VISIBLE)) == device::memory::HOST_VISIBLE)) {
			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, this->CreateInfo.size, 0, &nptr);
			if ((nptr != NULL) && (Result == VK_SUCCESS)) {
				memcpy(nptr, aBufferData, this->CreateInfo.size);
				vkUnmapMemory(this->Context->handle(), this->MemoryHandle);
			}
		}
		
	}

	buffer::buffer(context* aContext, int aMemoryType, int aUsage, size_t aMemorySize, void* aBufferData) {
		if (aContext == nullptr) return;
		VkResult Result = VK_SUCCESS;
		this->Context = aContext;

		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0; // Ignore.
		this->CreateInfo.size						= aMemorySize;
		this->CreateInfo.usage						= (VkBufferUsageFlags)(aUsage | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST); // Enable Transfer
		this->CreateInfo.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		this->CreateInfo.queueFamilyIndexCount		= 0;
		this->CreateInfo.pQueueFamilyIndices		= NULL;

		// Create Device Buffer Object.
		Result = vkCreateBuffer(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);

		// Allocates Memory Handle
		if (Result == VkResult::VK_SUCCESS) {
			// Gathers memory requirements of the created buffer.
			VkMemoryRequirements MemReq;
			vkGetBufferMemoryRequirements(aContext->handle(), this->Handle, &MemReq);

			// Gathers memory properties of the device.
			VkPhysicalDeviceMemoryProperties MemProp;
			vkGetPhysicalDeviceMemoryProperties(aContext->parent()->handle(), &MemProp);

			this->AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			this->AllocateInfo.pNext = NULL;
			this->AllocateInfo.allocationSize = MemReq.size;
			// Currently index selection chooses indice based on proposed aMemType,
			// and can possibly include extra features rather than exactly demanded.
			// Maybe change to exactly only chosen features later on.
			for (uint32_t i = 0; i < MemProp.memoryTypeCount; i++) {
				// Searches for exact memory properties.
				//if (((MemReq.memoryTypeBits & (1 << i)) >> i) && (MemProp.memoryTypes[i].propertyFlags == aMemType))
				// Searches for approximate memory properties, with additional props.
				if (((MemReq.memoryTypeBits & (1 << i)) >> i) && ((MemProp.memoryTypes[i].propertyFlags & aMemoryType) == aMemoryType)) {
					this->MemoryProperty = MemProp.memoryTypes[i].propertyFlags;
					this->AllocateInfo.memoryTypeIndex = i;
					break;
				}
			}

			// Allocate Device Memory.
			Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
		}

		// Bind memory to buffer
		if (Result == VkResult::VK_SUCCESS) {
			Result = vkBindBufferMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
		}

		if ((Result == VkResult::VK_SUCCESS) && (aBufferData != NULL) && ((this->MemoryProperty & (device::memory::HOST_VISIBLE)) == device::memory::HOST_VISIBLE)) {
			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, this->CreateInfo.size, 0, &nptr);
			if ((nptr != NULL) && (Result == VK_SUCCESS)) {
				memcpy(nptr, aBufferData, this->CreateInfo.size);
				vkUnmapMemory(this->Context->handle(), this->MemoryHandle);
			}
		}

	}

	buffer::~buffer() {
		if (this->Context != nullptr) {
			vkDestroyBuffer(this->Context->handle(), this->Handle, NULL);
			this->Handle = VK_NULL_HANDLE;
			vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
			this->MemoryHandle = VK_NULL_HANDLE;
		}
		this->Context = nullptr;
	}

	buffer::buffer(const buffer& aInp) {
		this->Context = aInp.Context;
		this->CreateInfo = aInp.CreateInfo;
		this->AllocateInfo = aInp.AllocateInfo;
		this->MemoryProperty = aInp.MemoryProperty;
		this->Count = aInp.Count;
		this->MemoryLayout = aInp.MemoryLayout;
		VkResult Result = VkResult::VK_SUCCESS;
		if (this->Context != nullptr) {
			Result = vkCreateBuffer(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);
			if (Result == VkResult::VK_SUCCESS) {
				Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
			}
			if (Result == VkResult::VK_SUCCESS) {
				Result = vkBindBufferMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
			}
			if (Result == VkResult::VK_SUCCESS) {
				VkSubmitInfo Submission{};
				VkCommandBufferBeginInfo BeginInfo{};
				VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
				VkBufferCopy Region{};
				VkFenceCreateInfo FenceCreateInfo{};
				VkFence Fence;

				Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
				Submission.pNext					= NULL;
				Submission.waitSemaphoreCount		= 0;
				Submission.pWaitSemaphores			= NULL;
				Submission.pWaitDstStageMask		= 0;
				Submission.commandBufferCount		= 1;
				Submission.pCommandBuffers			= &CommandBuffer;
				Submission.signalSemaphoreCount		= 0;
				Submission.pSignalSemaphores		= NULL;

				BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				BeginInfo.pNext						= NULL;
				BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				BeginInfo.pInheritanceInfo			= NULL;

				Region.srcOffset					= 0;
				Region.dstOffset					= 0;
				Region.size							= this->CreateInfo.size; // this->Count* this->MemoryLayout.Type.Size;

				FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				//this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
				CommandBuffer = this->Context->create(device::qfs::TRANSFER);
				if (CommandBuffer != VK_NULL_HANDLE) {
					Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);
					Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
					vkCmdCopyBuffer(CommandBuffer, aInp.Handle, this->Handle, 1, &Region);
					Result = vkEndCommandBuffer(CommandBuffer);
					this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
					Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
					vkDestroyFence(this->Context->handle(), Fence, NULL);
				}
				//this->Context->destroy(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
				this->Context->destroy(device::qfs::TRANSFER, CommandBuffer);
			}
		}
	}

	buffer::buffer(buffer&& aInp) {
		this->Context			= aInp.Context;
		this->CreateInfo		= aInp.CreateInfo;
		this->Handle			= aInp.Handle;
		this->AllocateInfo		= aInp.AllocateInfo;
		this->MemoryHandle		= aInp.MemoryHandle;
		this->MemoryProperty	= aInp.MemoryProperty;
		this->Count				= aInp.Count;
		this->MemoryLayout		= aInp.MemoryLayout;

		aInp.Context			= nullptr;
		aInp.CreateInfo			= {};
		aInp.Handle				= VK_NULL_HANDLE;
		aInp.AllocateInfo		= {};
		aInp.MemoryHandle		= VK_NULL_HANDLE;
		aInp.MemoryProperty		= 0;
		aInp.Count				= 0;
		aInp.MemoryLayout		= util::variable();
	}

	buffer& buffer::operator=(const buffer& aRhs) {
		if (this == &aRhs) return *this;
		if ((this->Context != nullptr) && (this->CreateInfo.size != aRhs.CreateInfo.size)) {
			vkDestroyBuffer(this->Context->handle(), this->Handle, NULL);
			this->Handle = VK_NULL_HANDLE;
			vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
			this->MemoryHandle = VK_NULL_HANDLE;
		}

		this->Context			= aRhs.Context;
		this->CreateInfo		= aRhs.CreateInfo;
		//this->Handle			= aRhs.Handle;
		this->AllocateInfo		= aRhs.AllocateInfo;
		//this->MemoryHandle		= aRhs.MemoryHandle;
		this->MemoryProperty	= aRhs.MemoryProperty;
		this->Count				= aRhs.Count;
		this->MemoryLayout		= aRhs.MemoryLayout;

		VkResult Result = VkResult::VK_SUCCESS;
		if (this->Context != nullptr) {
			Result = vkCreateBuffer(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);
			if (Result == VkResult::VK_SUCCESS) {
				Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
			}
			if (Result == VkResult::VK_SUCCESS) {
				Result = vkBindBufferMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
			}
			if (Result == VkResult::VK_SUCCESS) {
				VkSubmitInfo Submission{};
				VkCommandBufferBeginInfo BeginInfo{};
				VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
				VkBufferCopy Region{};
				VkFenceCreateInfo FenceCreateInfo{};
				VkFence Fence;

				Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
				Submission.pNext					= NULL;
				Submission.waitSemaphoreCount		= 0;
				Submission.pWaitSemaphores			= NULL;
				Submission.pWaitDstStageMask		= 0;
				Submission.commandBufferCount		= 1;
				Submission.pCommandBuffers			= &CommandBuffer;
				Submission.signalSemaphoreCount		= 0;
				Submission.pSignalSemaphores		= NULL;

				BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				BeginInfo.pNext						= NULL;
				BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				BeginInfo.pInheritanceInfo			= NULL;

				Region.srcOffset					= 0;
				Region.dstOffset					= 0;
				Region.size							= this->CreateInfo.size; // this->Count* this->MemoryLayout.Type.Size;

				FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				//this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
				CommandBuffer = this->Context->create(device::qfs::TRANSFER);
				if (CommandBuffer != VK_NULL_HANDLE) {
					Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);
					Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
					vkCmdCopyBuffer(CommandBuffer, aRhs.Handle, this->Handle, 1, &Region);
					Result = vkEndCommandBuffer(CommandBuffer);
					this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
					Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
					vkDestroyFence(this->Context->handle(), Fence, NULL);
				}
				//this->Context->destroy(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
				this->Context->destroy(device::qfs::TRANSFER, CommandBuffer);
			}
		}

		return *this;
	}

	buffer& buffer::operator=(buffer&& aRhs) {
		if (this->Context != nullptr) {
			vkDestroyBuffer(this->Context->handle(), this->Handle, NULL);
			this->Handle = VK_NULL_HANDLE;
			vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
			this->MemoryHandle = VK_NULL_HANDLE;
		}

		this->Context			= aRhs.Context;
		this->CreateInfo		= aRhs.CreateInfo;
		this->Handle			= aRhs.Handle;
		this->AllocateInfo		= aRhs.AllocateInfo;
		this->MemoryHandle		= aRhs.MemoryHandle;
		this->MemoryProperty	= aRhs.MemoryProperty;
		this->Count				= aRhs.Count;
		this->MemoryLayout		= aRhs.MemoryLayout;

		aRhs.Context			= nullptr;
		aRhs.CreateInfo			= {};
		aRhs.Handle				= VK_NULL_HANDLE;
		aRhs.AllocateInfo		= {};
		aRhs.MemoryHandle		= VK_NULL_HANDLE;
		aRhs.MemoryProperty		= 0;
		aRhs.Count				= 0;
		aRhs.MemoryLayout		= util::variable();

		return *this;
	}

	VkCommandBuffer buffer::operator<<(buffer& aRhs) {
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
		// Both operands must share the same parent context, and have same memory size.
		if ((this->Context != aRhs.Context) || ((size_t)this->CreateInfo.size != aRhs.CreateInfo.size)) return CommandBuffer;
		// Left operand must have TRANSFER_DST flag enabled, and Right operand must have TRANSFER_SRC flag enabled.
		if (
			((this->CreateInfo.usage & buffer::usage::TRANSFER_DST) != buffer::usage::TRANSFER_DST)
			||
			((aRhs.CreateInfo.usage & buffer::usage::TRANSFER_SRC) != buffer::usage::TRANSFER_SRC)
		) return CommandBuffer;

		VkResult Result = VkResult::VK_SUCCESS;
		VkCommandBufferBeginInfo BeginInfo{};
		VkBufferCopy Region{};

		BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext						= NULL;
		BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo			= NULL;

		Region.srcOffset					= 0;
		Region.dstOffset					= 0;
		Region.size							= this->CreateInfo.size;

		//Result = this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
		CommandBuffer = this->Context->create(device::qfs::TRANSFER);
		if (CommandBuffer != VK_NULL_HANDLE) {
			Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
			vkCmdCopyBuffer(CommandBuffer, aRhs.Handle, this->Handle, 1, &Region);
			Result = vkEndCommandBuffer(CommandBuffer);
		}
		return CommandBuffer;
	}

	VkCommandBuffer buffer::operator>>(buffer& aRhs) {
		return (aRhs << *this);
	}

	VkCommandBuffer buffer::operator<<(texture& aRhs) {
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
		// Must share the same parent context and have the same size.
		if ((this->Context != aRhs.Context) || ((size_t)this->CreateInfo.size != aRhs.MemorySize)) return CommandBuffer;
		// buffer must have enabled, DST flag. texture must have SRC flag.
		if (
			((this->CreateInfo.usage & buffer::usage::TRANSFER_DST) != buffer::usage::TRANSFER_DST) 
			|| 
			((aRhs.CreateInfo.usage & texture::usage::TRANSFER_SRC) != texture::usage::TRANSFER_SRC)
		) return CommandBuffer;

		VkResult Result = VkResult::VK_SUCCESS;
		VkCommandBufferBeginInfo BeginInfo{};
		std::vector<VkImageMemoryBarrier> Barrier(aRhs.CreateInfo.arrayLayers);
		VkBufferImageCopy Region{};

		BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext						= NULL;
		BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo			= NULL;

		for (uint32_t i = 0; i < aRhs.CreateInfo.arrayLayers; i++) {
			Barrier[i].sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier[i].pNext								= NULL;
			Barrier[i].srcAccessMask						= VkAccessFlagBits::VK_ACCESS_MEMORY_WRITE_BIT;
			Barrier[i].dstAccessMask						= VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT;
			Barrier[i].oldLayout							= aRhs.Layout[0][i];
			Barrier[i].newLayout							= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			Barrier[i].srcQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
			Barrier[i].dstQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
			Barrier[i].image								= aRhs.Handle;
			Barrier[i].subresourceRange.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier[i].subresourceRange.baseMipLevel		= 0;
			Barrier[i].subresourceRange.levelCount			= 1;
			Barrier[i].subresourceRange.baseArrayLayer		= i;
			Barrier[i].subresourceRange.layerCount			= 1;
		}

		//Result = this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
		CommandBuffer = this->Context->create(device::qfs::TRANSFER);
		Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

		// Use barrier for transition if layout doesn't match.
		vkCmdPipelineBarrier(CommandBuffer,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			0,
			0, NULL,
			0, NULL,
			Barrier.size(), Barrier.data()
		);

		vkCmdCopyImageToBuffer(CommandBuffer,
			aRhs.Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			this->Handle,
			1, &Region
		);

		Result = vkEndCommandBuffer(CommandBuffer);

		return CommandBuffer;
	}

	VkCommandBuffer buffer::operator>>(texture& aRhs) {
		return (aRhs >> *this);
		return VK_NULL_HANDLE;
	}

	void buffer::write(size_t aMemOffset, size_t aMemSize, void* aData) {
		VkBufferCopy Region;
		Region.srcOffset = 0;
		Region.dstOffset = aMemOffset;
		Region.size = aMemSize;
		this->write(1, &Region, aData);
	}

	void buffer::write(uint32_t aRegionCount, VkBufferCopy* aRegion, void* aData) {
		if ((this->Context == nullptr) || (aRegionCount == 0) || (aRegion == NULL) || (aData == NULL)) return;
		if ((this->MemoryProperty & device::memory::HOST_VISIBLE) != device::memory::HOST_VISIBLE) return;

		VkResult Result = VkResult::VK_SUCCESS;
		void* nptr = NULL;
		Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
		if ((nptr == NULL) || (Result != VK_SUCCESS)) return;
		for (uint32_t i = 0; i < aRegionCount; i++) {
			memcpy((void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)aData + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
		}
		vkUnmapMemory(this->Context->handle(), this->MemoryHandle);

		/*
		if ((this->MemoryProperty & device::memory::HOST_VISIBLE) == device::memory::HOST_VISIBLE) {
			// If memory buffer is host visible, use direct write operation.

			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
			if (nptr != NULL) {
				for (uint32_t i = 0; i < aRegionCount; i++) {
					memcpy((void *)((uintptr_t)nptr + (uintptr_t)aRegion[i].dstOffset), (void *)((uintptr_t)aData + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
				}
				vkUnmapMemory(this->Context->handle(), this->MemoryHandle);
			}

		}
		else {

			// Load into staging buffer.
			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->StagingBuffer->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
			if (nptr != NULL) {
				for (uint32_t i = 0; i < aRegionCount; i++) {
					memcpy((void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)aData + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
				}
				vkUnmapMemory(this->Context->handle(), this->StagingBuffer->MemoryHandle);
			}

			// Execute transfer commands
			VkCommandBuffer Transfer = NULL;
			this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &Transfer);

			VkCommandBufferBeginInfo BeginInfo;
			BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			BeginInfo.pNext						= NULL;
			BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			BeginInfo.pInheritanceInfo			= NULL;

			// Fill out command buffer.
			Result = vkBeginCommandBuffer(Transfer, &BeginInfo);
			vkCmdCopyBuffer(Transfer, this->StagingBuffer->Handle, this->Handle, aRegionCount, aRegion);
			Result = vkEndCommandBuffer(Transfer);

			// Create fence
			VkFence Fence;
			VkFenceCreateInfo FenceCreateInfo;
			FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			FenceCreateInfo.pNext				= NULL;
			FenceCreateInfo.flags				= 0;
			Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);

			VkSubmitInfo Submission;
			Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
			Submission.pNext					= NULL;
			Submission.waitSemaphoreCount		= 0;
			Submission.pWaitSemaphores			= NULL;
			Submission.pWaitDstStageMask		= 0;
			Submission.commandBufferCount		= 1;
			Submission.pCommandBuffers			= &Transfer;
			Submission.signalSemaphoreCount		= 0;
			Submission.pSignalSemaphores		= NULL;

			this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
			Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
			vkDestroyFence(this->Context->handle(), Fence, NULL);
			this->Context->destroy(context::cmdtype::TRANSFER_OTS, 1, &Transfer);

		}
		*/

	}

	void buffer::read(size_t aMemOffset, size_t aMemSize, void* aData) {
		VkBufferCopy Region;
		Region.srcOffset = aMemOffset;
		Region.dstOffset = 0;
		Region.size = aMemSize;
		this->read(1, &Region, aData);
	}

	void buffer::read(uint32_t aRegionCount, VkBufferCopy* aRegion, void* aData) {
		if ((this->Context == nullptr) || (aRegionCount == 0) || (aRegion == NULL) || (aData == NULL)) return;
		if ((this->MemoryProperty & device::memory::HOST_VISIBLE) != device::memory::HOST_VISIBLE) return;

		void* nptr = NULL;
		VkResult Result = VkResult::VK_SUCCESS;
		Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
		if ((nptr == NULL) || (Result != VK_SUCCESS)) return;
		for (uint32_t i = 0; i < aRegionCount; i++) {
			memcpy((void*)((uintptr_t)aData + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
		}
		vkUnmapMemory(this->Context->handle(), this->MemoryHandle);

		/*
		if ((Property.memoryTypes[this->AllocateInfo.memoryTypeIndex].propertyFlags & device::memory::HOST_VISIBLE) == device::memory::HOST_VISIBLE) {
			// If memory buffer is host visible, use direct write operation.

			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
			if (nptr != NULL) {
				for (uint32_t i = 0; i < aRegionCount; i++) {
					memcpy((void *)((uintptr_t)aData + (uintptr_t)aRegion[i].dstOffset), (void *)((uintptr_t)nptr + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
				}
				vkUnmapMemory(this->Context->handle(), this->MemoryHandle);
			}

		}
		else {

			// Execute transfer commands
			VkCommandBuffer Transfer = NULL;
			this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &Transfer);

			VkCommandBufferBeginInfo BeginInfo;
			BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			BeginInfo.pNext						= NULL;
			BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
			BeginInfo.pInheritanceInfo			= NULL;

			// Fill out command buffer.
			Result = vkBeginCommandBuffer(Transfer, &BeginInfo);
			vkCmdCopyBuffer(Transfer, this->StagingBuffer->Handle, this->Handle, aRegionCount, aRegion);
			Result = vkEndCommandBuffer(Transfer);

			// Create fence
			VkFence Fence;
			VkFenceCreateInfo FenceCreateInfo;
			FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			FenceCreateInfo.pNext				= NULL;
			FenceCreateInfo.flags				= 0;
			Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);

			VkSubmitInfo Submission;
			Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
			Submission.pNext					= NULL;
			Submission.waitSemaphoreCount		= 0;
			Submission.pWaitSemaphores			= NULL;
			Submission.pWaitDstStageMask		= 0;
			Submission.commandBufferCount		= 1;
			Submission.pCommandBuffers			= &Transfer;
			Submission.signalSemaphoreCount		= 0;
			Submission.pSignalSemaphores		= NULL;

			this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
			Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
			vkDestroyFence(this->Context->handle(), Fence, NULL);
			this->Context->destroy(context::cmdtype::TRANSFER_OTS, 1, &Transfer);

			// Load into staging buffer.
			void* nptr = NULL;
			Result = vkMapMemory(this->Context->handle(), this->StagingBuffer->MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
			if (nptr != NULL) {
				for (uint32_t i = 0; i < aRegionCount; i++) {
					memcpy((void*)((uintptr_t)aData + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
				}
				vkUnmapMemory(this->Context->handle(), this->StagingBuffer->MemoryHandle);
			}

		}
		*/

	}

	VkBuffer buffer::handle() {
		return this->Handle;
	}

}

//buffer::buffer() {
//	/* DEFAULT CONSTRUCTOR */
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = 0;
//	this->Child = nullptr;
//
//	this->MemorySize = 0;
//	this->MemoryOffset = 0;
//	this->TypeQualifierID = NULL;
//	this->NameStr = NULL;
//	this->ArrayDimCount = 0;
//	this->ArrayDimSize = NULL;
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer::~buffer() {
//	/* DESTRUCTOR */
//	if (this->hptr != NULL) {
//		if (this->Root == nullptr) {
//			free(this->hptr);
//		}
//		this->hptr = NULL;
//	}
//	this->Count = 0;
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = 0;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	this->TypeQualifierID = NULL;
//	this->MemoryOffset = 0;
//	this->MemorySize = 0;
//
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//	this->ChildCount = 0;
//	//this->Parent = nullptr;
//	//this->Root = nullptr;
//}
//
//buffer::buffer(const buffer & inp) {
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = inp.ChildCount;
//	this->Child = nullptr;
//	if (this->ChildCount > 0) {
//		this->Child = new buffer[this->ChildCount];
//		if (this->Child == nullptr) this->ChildCount = 0;
//	}
//	for (integer i = 0; i < this->ChildCount; i++) {
//		this->Child[i].Root = this;
//		this->Child[i].Parent = this;
//		this->Child[i] = inp[i];
//	}
//
//	this->MemorySize = inp.MemorySize;
//	this->MemoryOffset = inp.MemoryOffset;
//	this->TypeQualifierID = inp.TypeQualifierID;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	size_t StrLen = 0;
//	if (inp.NameStr != NULL) {
//		StrLen = strlen(inp.NameStr);
//		if (StrLen > 0) {
//			this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//		}
//		if (this->NameStr != NULL) {
//			memcpy(this->NameStr, inp.NameStr, StrLen * sizeof(char));
//			this->NameStr[StrLen] = '\0';
//		}
//	}
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = inp.ArrayDimCount;
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer*)malloc(this->ArrayDimCount * sizeof(integer));
//	}
//	if ((this->ArrayDimSize != NULL) && (inp.ArrayDimSize != NULL)) {
//		memcpy(this->ArrayDimSize, inp.ArrayDimSize, this->ArrayDimCount * sizeof(integer));
//	}
//
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer::buffer(buffer && inp) {
//	// MOVE CONSTRUCTOR
//	Root = inp.Root;
//	Parent = inp.Parent;
//	ChildCount = inp.ChildCount;
//	Child = inp.Child;
//	MemorySize = inp.MemorySize;
//	MemoryOffset = inp.MemoryOffset;
//	TypeQualifierID = inp.TypeQualifierID;
//	NameStr = inp.NameStr;
//	ArrayDimCount = inp.ArrayDimCount;
//	ArrayDimSize = inp.ArrayDimSize;
//	inp.Root = nullptr;
//	inp.Parent = nullptr;
//	inp.ChildCount = 0;
//	inp.Child = nullptr;
//	inp.MemorySize = 0;
//	inp.MemoryOffset = 0;
//	inp.TypeQualifierID = NULL;
//	inp.NameStr = NULL;
//	inp.ArrayDimCount = 0;
//	inp.ArrayDimSize = NULL;
//}
//
//buffer::buffer(int TypeSpecifier, const char* IdentifierString) {
//
//}
//
//buffer::buffer(int TypeSpecifier, const char* IdentifierString, int SubscriptCount, int* SubscriptSize) {
//	this->Root = nullptr;
//	this->Parent = nullptr;
//	this->ChildCount = 0;
//	this->Child = nullptr;
//
//	if ((this->get_type_name_of(TypeSpecifier) != NULL) /*&& (IdentifierString != NULL)*/) {
//		this->MemorySize = this->get_size_of(TypeSpecifier);
//		this->MemoryOffset = 0;
//		this->TypeQualifierID = TypeSpecifier;
//		if (IdentifierString != NULL) {
//			size_t StrLen = strlen(IdentifierString);
//			if (StrLen > 0) {
//				this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//				if (this->NameStr != NULL) {
//					memcpy(this->NameStr, IdentifierString, StrLen * sizeof(char));
//					this->NameStr[StrLen] = '\0';
//				}
//			}
//		}
//		if (SubscriptCount > 0) {
//			if (SubscriptSize != NULL) {
//				this->ArrayDimCount = SubscriptCount;
//			}
//			else {
//				this->ArrayDimCount = 1;
//			}
//		}
//		else {
//			this->ArrayDimCount = 0;
//		}
//
//		if (this->ArrayDimCount > 0) {
//			this->ArrayDimSize = (int *)malloc(this->ArrayDimCount * sizeof(int));
//		}
//
//		if (this->ArrayDimSize != NULL) {
//			if (SubscriptSize != NULL) {
//				memcpy(this->ArrayDimSize, SubscriptSize, this->ArrayDimCount * sizeof(int));
//			}
//			else {
//				//memcpy(this->ArrayDimSize, &SubscriptCount, this->ArrayDimCount * sizeof(integer));
//				this->ArrayDimSize[0] = SubscriptCount;
//			}
//		}
//
//		if (this->ArrayDimSize != NULL) {
//			int TotalDimensionalSize = 1;
//			for (int i = 0; i < this->ArrayDimCount; i++) {
//				TotalDimensionalSize = this->ArrayDimSize[i];
//			}
//		}
//	}
//	else {
//		this->MemorySize = 0;
//		this->MemoryOffset = 0;
//		this->TypeQualifierID = NULL;
//		this->NameStr = NULL;
//		this->ArrayDimCount = 0;
//		this->ArrayDimSize = NULL;
//	}
//	this->Count = 0;
//	this->hptr = NULL;
//}
//
//buffer& buffer::operator=(const buffer& rhs) {
//	/* COPY ASSIGNMENT */
//	if (this == &rhs) return *this;
//
//	boolean NodeDamage = false;
//
//	this->MemorySize = rhs.MemorySize;
//	//this->MemoryOffset = 0;
//	this->TypeQualifierID = rhs.TypeQualifierID;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	size_t StrLen = 0;
//	if (rhs.NameStr != NULL) {
//		StrLen = strlen(rhs.NameStr);
//		if (StrLen > 0) {
//			this->NameStr = (char*)malloc((StrLen + 1) * sizeof(char));
//			if (this->NameStr == NULL) NodeDamage = true;
//		}
//		if (this->NameStr != NULL) {
//			memcpy(this->NameStr, rhs.NameStr, StrLen * sizeof(char));
//			this->NameStr[StrLen] = '\0';
//		}
//	}
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = rhs.ArrayDimCount;
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer *)malloc(this->ArrayDimCount * sizeof(integer));
//		if (this->ArrayDimSize == NULL) NodeDamage = true;
//	}
//	if ((this->ArrayDimSize != NULL) && (rhs.ArrayDimSize != NULL)) {
//		memcpy(this->ArrayDimSize, rhs.ArrayDimSize, this->ArrayDimCount * sizeof(integer));
//	}
//
//	// -------------------- Node Map -------------------- //
//
//	//this->Root = rhs.Root;
//	//this->Parent = rhs.Parent;
//	this->ChildCount = rhs.ChildCount;
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//
//	if ((this->TypeQualifierID == buffer::STRUCT) && (this->ChildCount > 0)) {
//		// Composite Structure
//		size_t TotalSize = 0;
//		this->Child = new buffer[this->ChildCount];
//		if (this->Child == nullptr) NodeDamage = true;
//		if ((this->Child != nullptr) && (rhs.Child != nullptr)) {
//			for (integer i = 0; i < this->ChildCount; i++) {
//
//				if (this->Root == nullptr) {
//					this->Child[i].Root = this;
//				}
//				else {
//					this->Child[i].Root = this->Root;
//				}
//				this->Child[i].Parent = this;
//
//				this->Child[i] = rhs[i];
//
//				this->Child[i].MemoryOffset = this->MemoryOffset + TotalSize;
//
//				TotalSize += this->Child[i].MemorySize;
//			}
//
//			if (TotalSize != this->MemorySize) {
//
//			}
//		}
//		else {
//			// Memory Allocation Failure
//			this->ChildCount = 0;
//
//			this->MemorySize = 0;
//			this->MemoryOffset = 0;
//		}
//	}
//
//	return *this;
//}
//
//buffer & buffer::operator=(buffer && rhs) {
//	this->Root = rhs.Root;
//	this->Parent = rhs.Parent;
//	this->ChildCount = rhs.ChildCount;
//	this->Child = rhs.Child;
//	this->MemorySize = rhs.MemorySize;
//	this->MemoryOffset = rhs.MemoryOffset;
//	this->TypeQualifierID = rhs.TypeQualifierID;
//	this->NameStr = rhs.NameStr;
//	this->ArrayDimCount = rhs.ArrayDimCount;
//	this->ArrayDimSize = rhs.ArrayDimSize;
//	rhs.Root = nullptr;
//	rhs.Parent = nullptr;
//	rhs.ChildCount = 0;
//	rhs.Child = nullptr;
//	rhs.MemorySize = 0;
//	rhs.MemoryOffset = 0;
//	rhs.TypeQualifierID = NULL;
//	rhs.NameStr = NULL;
//	rhs.ArrayDimCount = 0;
//	rhs.ArrayDimSize = NULL;
//	return *this;
//}
//
//buffer& buffer::operator[](int Index) {
//	//tex:
//	// $\text{Consider an } n \text{-dimensional array} $
//	// $\text{Declaration:} \quad A[m_{0}][m_{1}]...[m_{n-1}] \rightarrow \text{Access:} \quad A[k_{0}][k_{1}]...[k_{n-1}]$
//	// $ Access = \displaystyle\sum_{i = 0}^{n - 2} k_{i} \displaystyle\prod_{j = i + 1}^{n-1}m_{j} + k_{n-1} $
//	return this->Child[Index];
//}
//
//const buffer& buffer::operator[](int Index) const {
//	return this->Child[Index];
//}
//
//int buffer::create(int TypeSpecifier, const char* IdentifierString) {
//	return this->create(TypeSpecifier, IdentifierString, 0, NULL);
//}
//
//int buffer::create(int TypeSpecifier, const char* IdentifierString, int SubscriptSize) {
//	return this->create(TypeSpecifier, IdentifierString, SubscriptSize, NULL);
//}
//
//int buffer::create(int TypeSpecifier, /*const char *TypeSpecifierString,*/ const char *IdentifierString, int SubscriptCount, int *SubscriptSize) {
//	if (this->get_type_name_of(TypeSpecifier) == NULL) return -1;
//
//	if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//		for (int i = 0; i < SubscriptCount; i++) {
//			if (SubscriptSize[i] <= 0) return -1;
//		}
//	}
//
//	this->annihilate();
//
//	this->TypeQualifierID = TypeSpecifier;
//	this->NameStr = NULL;
//	if (IdentifierString != NULL) {
//		size_t CharCount = strlen(IdentifierString);
//		if (CharCount > 0) {
//			this->NameStr = (char *)malloc((CharCount + 1) * sizeof(char));
//			if (this->NameStr != NULL) {
//				memcpy(this->NameStr, IdentifierString, CharCount * sizeof(char));
//				this->NameStr[CharCount] = '\0';
//			}
//		}
//	}
//
//	if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//		this->ArrayDimCount = SubscriptCount;
//	}
//	else if (SubscriptCount > 0) {
//		this->ArrayDimCount = 1;
//	}
//	else {
//		this->ArrayDimCount = 0;
//	}
//
//	if (this->ArrayDimCount > 0) {
//		this->ArrayDimSize = (integer*)malloc(this->ArrayDimCount * sizeof(integer));
//		if (this->ArrayDimSize == NULL) this->ArrayDimCount = 0;
//	}
//
//	if (this->ArrayDimSize != NULL) {
//		if ((SubscriptCount > 0) && (SubscriptSize != NULL)) {
//			memcpy(this->ArrayDimSize, SubscriptSize, this->ArrayDimCount*sizeof(integer));
//		}
//		else if (SubscriptCount > 0) {
//			memcpy(this->ArrayDimSize, &SubscriptCount, this->ArrayDimCount * sizeof(integer));
//		}
//	}
//
//	if (this->TypeQualifierID == buffer::STRUCT) {
//		this->MemorySize = 0;
//	}
//	else {
//		this->MemorySize = this->get_size_of(this->TypeQualifierID);
//		for (int i = 0; i < this->ArrayDimCount; i++) {
//			this->MemorySize *= this->ArrayDimSize[i];
//		}
//	}
//
//	return 0;
//}
//
//int buffer::annihilate() {
//	if (this->hptr != NULL) {
//		if (this->Root == nullptr) {
//			free(this->hptr);
//		}
//		this->hptr = NULL;
//	}
//	this->Count = 0;
//	if (this->ArrayDimSize != NULL) {
//		free(this->ArrayDimSize); this->ArrayDimSize = NULL;
//	}
//	this->ArrayDimCount = 0;
//	if (this->NameStr != NULL) {
//		free(this->NameStr); this->NameStr = NULL;
//	}
//	this->TypeQualifierID = NULL;
//	this->MemoryOffset = 0;
//	this->MemorySize = 0;
//
//	if (this->Child != nullptr) {
//		delete[] this->Child; this->Child = nullptr;
//	}
//	this->ChildCount = 0;
//	//this->Parent = nullptr;
//	//this->Root = nullptr;
//	return 0;
//}
//
//int buffer::push(int VariableCount, int* TypeSpecifier, const char** IdentifierString, int* SubscriptCount, int** SubscriptSize) {
//	// Check if proper struct first.
//	if (this->TypeQualifierID != buffer::STRUCT) return -1;
//	// First validate arguments
//	if ((VariableCount <= 0) || (TypeSpecifier == NULL) || (IdentifierString == NULL)/*|| (SubscriptCount == NULL) || (SubscriptSize == NULL)*/) return -1;
//	// Second, check if args are
//	for (int i = 0; i < VariableCount; i++) {
//		if ((this->get_type_name_of(TypeSpecifier[i]) == NULL) || (IdentifierString[i] == NULL)) return -1;
//	}
//
//	integer NewTotalCount = this->ChildCount + VariableCount;
//	buffer* NewTotalChild = new buffer[NewTotalCount];
//	if (NewTotalChild != nullptr) {
//		integer j = 0;
//		for (integer i = 0; i < NewTotalCount; i++) {
//			if ((i >= 0) && (i < this->ChildCount)) {
//				// Swap Data from old.
//			}
//			else {
//				j = i - this->ChildCount;
//				if ((SubscriptCount != NULL) && (SubscriptSize != NULL)) {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], SubscriptCount[j], SubscriptSize[j]);
//				}
//				else if (SubscriptCount != NULL) {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], SubscriptCount[j], NULL);
//				}
//				else {
//					NewTotalChild[i].create(TypeSpecifier[j], IdentifierString[j], 0, NULL);
//				}
//			}
//		}
//	}
//
//	return 0;
//}
//
//buffer buffer::get_hard_copy() {
//	buffer temp;
//
//	if (!this->isHollowNode) {
//		temp = *this;
//	}
//	else {
//		temp.isHollowNode = false;
//
//	}
//
//	temp.Root = this;
//
//	return temp;
//}
//
//buffer buffer::get_hollow_copy() {
//	buffer temp;
//
//	temp.isHollowNode = true;
//	temp.Root = this->Root;
//	if (!this->isHollowNode) {
//		temp.Parent = this;
//	}
//	else {
//		temp.Parent = this->Parent;
//	}
//	temp.ChildCount = this->ChildCount;
//	temp.Child = this->Child;
//
//	temp.MemorySize = this->MemorySize;
//	temp.MemoryOffset = this->MemoryOffset;
//	temp.TypeQualifierID = this->TypeQualifierID;
//	temp.NameStr = this->NameStr;
//	temp.ArrayDimCount = this->ArrayDimCount;
//	temp.ArrayDimSize = this->ArrayDimSize;
//
//	temp.Count = this->Count;
//	temp.hptr = this->hptr;
//
//	//temp.NameStr = NULL;
//	//if (this->NameStr != NULL) {
//	//	size_t CharCount = strlen(this->NameStr);
//	//	if (CharCount > 0) {
//	//		temp.NameStr = (char *)malloc((CharCount + 1) * sizeof(char));
//	//		if (temp.NameStr != NULL) {
//	//			memcpy(temp.NameStr, this->NameStr, CharCount * sizeof(char));
//	//			temp.NameStr[CharCount] = '\0';
//	//		}
//	//	}
//	//}
//
//	return temp;
//}
//
//int buffer::reserve_memory(int VertexCount) {
//	/* If this is the root node, memory operations are allowed */
//	if (this != Root) { return -1; }
//
//	
//
//
//	return 0;
//}
//
//int buffer::resize_memory(int VertexCount) {
//
//
//
//
//	return 0;
//}
//
//int buffer::release_memory() {
//	
//
//	if (hptr == NULL) { return 0; }
//	free(hptr); hptr = NULL;
//	return 0;
//}
//
//int buffer::set(int VertexIndex, const void * Arg, size_t ArgMemSize) {
//	/* Actually it's your fault if you go out of bounds dipshit. */
//	uintptr_t BaseAddress = (uintptr_t)Root->hptr;
//	uintptr_t MemoryShift = ((uintptr_t)VertexIndex)*((uintptr_t)Root->MemorySize) + ((uintptr_t)this->MemoryOffset);
//	uintptr_t TargetAddress = BaseAddress + MemoryShift;
//	memcpy((void *)TargetAddress, Arg, ArgMemSize);
//	return 0;
//}
