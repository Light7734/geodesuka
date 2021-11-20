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

	buffer::buffer(context* aContext, int aMemoryType, int aUsage, int aCount, util::variable aMemoryLayout, void* aBufferData) {
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
			VkMemoryRequirements MemoryRequirement;
			vkGetBufferMemoryRequirements(aContext->handle(), this->Handle, &MemoryRequirement);

			// Will search for exact then approximate type.
			int MemoryTypeIndex = aContext->parent()->get_memory_type_index(MemoryRequirement, aMemoryType);
			if (MemoryTypeIndex >= 0) {
				this->AllocateInfo.sType			= VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				this->AllocateInfo.pNext			= NULL;
				this->AllocateInfo.allocationSize	= MemoryRequirement.size;
				this->AllocateInfo.memoryTypeIndex	= MemoryTypeIndex;
				this->MemoryProperty				= aContext->parent()->get_memory_type(MemoryTypeIndex);

				// Allocate Device Memory.
				Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
			}
			else {
				Result = VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED;
			}
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
			VkMemoryRequirements MemoryRequirement;
			vkGetBufferMemoryRequirements(aContext->handle(), this->Handle, &MemoryRequirement);

			// Will search for exact then approximate type.
			int MemoryTypeIndex = aContext->parent()->get_memory_type_index(MemoryRequirement, aMemoryType);
			if (MemoryTypeIndex >= 0) {
				this->AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				this->AllocateInfo.pNext = NULL;
				this->AllocateInfo.allocationSize = MemoryRequirement.size;
				this->AllocateInfo.memoryTypeIndex = MemoryTypeIndex;
				this->MemoryProperty = aContext->parent()->get_memory_type(MemoryTypeIndex);

				// Allocate Device Memory.
				Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
			}
			else {
				Result = VkResult::VK_ERROR_FORMAT_NOT_SUPPORTED;
			}
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
		this->pmclearall();
	}

	buffer::buffer(buffer& aInp) {
		this->Context			= aInp.Context;

		this->CreateInfo		= aInp.CreateInfo;
		this->AllocateInfo		= aInp.AllocateInfo;
		this->MemoryProperty	= aInp.MemoryProperty;
		this->Count				= aInp.Count;
		this->MemoryLayout		= aInp.MemoryLayout;

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
				VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
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

				FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				CommandBuffer = (*this << aInp);
				Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);
				Result = this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
				Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);

				this->Context->destroy(device::qfs::TRANSFER, CommandBuffer);
				vkDestroyFence(this->Context->handle(), Fence, NULL);

			}
		}
	}

	buffer::buffer(buffer&& aInp) noexcept {
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

	buffer& buffer::operator=(buffer& aRhs) {
		if (this == &aRhs) return *this;
		this->pmclearall();

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
				VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
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

				FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				CommandBuffer = (*this << aRhs);
				Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);
				Result = this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
				Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);

				this->Context->destroy(device::qfs::TRANSFER, CommandBuffer);
				vkDestroyFence(this->Context->handle(), Fence, NULL);
			}
		}

		return *this;
	}

	buffer& buffer::operator=(buffer&& aRhs) noexcept {
		this->pmclearall();

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
			aRhs.Layout[0][i]								= Barrier[i].newLayout;
		}

		Region.bufferOffset						= 0;
		Region.bufferRowLength					= 0;
		Region.bufferImageHeight				= 0;
		Region.imageSubresource.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
		Region.imageSubresource.mipLevel		= 0;
		Region.imageSubresource.baseArrayLayer	= 0;
		Region.imageSubresource.layerCount		= aRhs.CreateInfo.arrayLayers;
		Region.imageOffset						= { 0, 0, 0 };
		Region.imageExtent						= aRhs.CreateInfo.extent;

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

	}

	VkBuffer buffer::handle() {
		return this->Handle;
	}

	void buffer::pmclearall() {
		if (this->Context != nullptr) {
			if (this->Handle != VK_NULL_HANDLE) {
				vkDestroyBuffer(this->Context->handle(), this->Handle, NULL);
				this->Handle = VK_NULL_HANDLE;
			}
			if (this->MemoryHandle != VK_NULL_HANDLE) {
				vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
				this->MemoryHandle = VK_NULL_HANDLE;
			}
		}

		this->Context = nullptr;
		this->CreateInfo = {};
		this->AllocateInfo = {};
		this->MemoryProperty = 0;

		this->Count = 0;
		this->MemoryLayout = util::variable();

	}

}
