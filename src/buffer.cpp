#include <geodesuka/core/gcl/buffer.h>

#include <cstdlib>
#include <cstring>

#include <vector>

// Used to interact with texture class
#include <geodesuka/core/gcl/image.h>

namespace geodesuka::core::gcl {

	buffer::buffer() {
		Context = nullptr;
		Handle = VK_NULL_HANDLE;
		MemoryHandle = VK_NULL_HANDLE;
		Count = 0;
	}

	buffer::buffer(context* aContext, vk_memory_property_flags aMemoryPropertyFlags, vk_buffer_usage_flags aBufferUsageFlags, int aVertexCount, variable aVertexLayout, void* aVertexData) {
		if (aContext == nullptr) return;

		vk_result Result = VK_SUCCESS;
		device* Device = aContext->parent();
		int MemoryTypeIndex = -1;

		Context = aContext;

		// struct type and extender info.
		CreateInfo.sType		= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		CreateInfo.pNext		= NULL;
		AllocateInfo.sType		= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.pNext		= NULL;

		CreateInfo.flags					= 0; // Ignore.
		CreateInfo.size						= aVertexCount * aVertexLayout.Type.Size;
		CreateInfo.usage					= aBufferUsageFlags | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST;
		CreateInfo.sharingMode				= VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount	= 0;
		CreateInfo.pQueueFamilyIndices		= NULL;

		Handle								= VK_NULL_HANDLE;
		MemoryHandle						= VK_NULL_HANDLE;

		Count								= aVertexCount;
		MemoryLayout						= aVertexLayout;

		// Creates buffer object handle.
		Result = vkCreateBuffer(Context->handle(), &CreateInfo, NULL, &Handle);

		// On success, will execute the creation of its memory handle.
		if (Result == VK_SUCCESS) {

			// Gathers memory requirements of the created buffer.
			vk_memory_requirements MemoryRequirement = Context->get_buffer_memory_requirements(Handle);

			// Queries buffer memory requirements and chosen memory property support from parent device.
			MemoryTypeIndex = Device->get_memory_property_flags_index(MemoryRequirement, aMemoryPropertyFlags);

			// Check if MemoryTypeIndex is greater than zero.
			if (MemoryTypeIndex >= 0) {
				// If memory type index exists, allocate memory from device.
				AllocateInfo.allocationSize		= MemoryRequirement.size;
				AllocateInfo.memoryTypeIndex	= MemoryTypeIndex;

				// Allocate Device Memory.
				Result = vkAllocateMemory(Context->handle(), &AllocateInfo, NULL, &MemoryHandle);
			}
			else {
				Result = VK_ERROR_FORMAT_NOT_SUPPORTED;
			}

		}
		else {
			this->pmclearall();
			return;
		}

		// Bind memory to buffer
		if (Result == VK_SUCCESS) {
			Result = vkBindBufferMemory(Context->handle(), Handle, MemoryHandle, 0);
		}
		else {
			this->pmclearall();
			return;
		}

		// Fill memory buffer if HOST_VISIBLE is enabled.
		if ((Result == VK_SUCCESS) && (MemoryTypeIndex > 0) && (aVertexData != NULL)) {
			// Fills device buffer if aVertexData has been provided.
			vk_memory_property_flags MemoryType = Device->get_memory_property_flags(MemoryTypeIndex);
			if ((MemoryType & device::memory::HOST_VISIBLE) == device::memory::HOST_VISIBLE) {
				void* nptr = NULL;
				Result = vkMapMemory(Context->handle(), MemoryHandle, 0, CreateInfo.size, 0, &nptr);
				if ((nptr != NULL) && (Result == VK_SUCCESS)) {
					memcpy(nptr, aVertexData, CreateInfo.size);
					vkUnmapMemory(Context->handle(), MemoryHandle);
				}
			}
		}
		else {
			this->pmclearall();
			return;
		}

	}

	buffer::buffer(context* aContext, vk_memory_property_flags aMemoryPropertyFlags, vk_buffer_usage_flags aBufferUsageFlags, size_t aBufferSize, void* aBufferData) {
		if (aContext == nullptr) return;

		vk_result Result = VK_SUCCESS;
		device* Device = aContext->parent();
		int MemoryTypeIndex = -1;

		Context = aContext;

		// struct type and extender info.
		CreateInfo.sType		= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		CreateInfo.pNext		= NULL;
		AllocateInfo.sType		= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.pNext		= NULL;

		CreateInfo.flags					= 0; // Ignore.
		CreateInfo.size						= aBufferSize;
		CreateInfo.usage					= aBufferUsageFlags | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST;
		CreateInfo.sharingMode				= VK_SHARING_MODE_EXCLUSIVE;
		CreateInfo.queueFamilyIndexCount	= 0;
		CreateInfo.pQueueFamilyIndices		= NULL;

		Handle								= VK_NULL_HANDLE;
		MemoryHandle						= VK_NULL_HANDLE;

		Count								= 0;
		MemoryLayout						= variable();

		// Creates buffer object handle.
		Result = vkCreateBuffer(Context->handle(), &CreateInfo, NULL, &Handle);

		// On success, will execute the creation of its memory handle.
		if (Result == VK_SUCCESS) {

			// Gathers memory requirements of the created buffer.
			vk_memory_requirements MemoryRequirement = Context->get_buffer_memory_requirements(Handle);

			// Queries buffer memory requirements and chosen memory property support from parent device.
			MemoryTypeIndex = Device->get_memory_property_flags_index(MemoryRequirement, aMemoryPropertyFlags);

			// Check if MemoryTypeIndex is greater than zero.
			if (MemoryTypeIndex >= 0) {
				// If memory type index exists, allocate memory from device.
				AllocateInfo.allocationSize		= MemoryRequirement.size;
				AllocateInfo.memoryTypeIndex	= MemoryTypeIndex;

				// Allocate Device Memory.
				Result = vkAllocateMemory(Context->handle(), &AllocateInfo, NULL, &MemoryHandle);
			}
			else {
				Result = VK_ERROR_FORMAT_NOT_SUPPORTED;
			}

		}
		else {
			this->pmclearall();
			return;
		}

		// Bind memory to buffer
		if (Result == VK_SUCCESS) {
			Result = vkBindBufferMemory(Context->handle(), Handle, MemoryHandle, 0);
		}
		else {
			this->pmclearall();
			return;
		}

		// Fill memory buffer if HOST_VISIBLE is enabled.
		if ((Result == VK_SUCCESS) && (MemoryTypeIndex > 0) && (aBufferData != NULL)) {
			// Fills device buffer if aVertexData has been provided.
			vk_memory_property_flags MemoryType = Device->get_memory_property_flags(MemoryTypeIndex);
			if ((MemoryType & device::memory::HOST_VISIBLE) == device::memory::HOST_VISIBLE) {
				void* nptr = NULL;
				Result = vkMapMemory(Context->handle(), MemoryHandle, 0, CreateInfo.size, 0, &nptr);
				if ((nptr != NULL) && (Result == VK_SUCCESS)) {
					memcpy(nptr, aBufferData, CreateInfo.size);
					vkUnmapMemory(Context->handle(), MemoryHandle);
				}
			}
		}
		else {
			this->pmclearall();
			return;
		}

	}

	buffer::~buffer() {
		this->pmclearall();
	}

	buffer::buffer(buffer& aInp) {
		Context			= aInp.Context;

		CreateInfo		= aInp.CreateInfo;
		AllocateInfo	= aInp.AllocateInfo;
		Count			= aInp.Count;
		MemoryLayout	= aInp.MemoryLayout;

		vk_result Result = VK_SUCCESS;
		if (Context != nullptr) {
			Result = vkCreateBuffer(Context->handle(), &CreateInfo, NULL, &Handle);
			if (Result == VK_SUCCESS) {
				Result = vkAllocateMemory(Context->handle(), &AllocateInfo, NULL, &MemoryHandle);
			}
			if (Result == VK_SUCCESS) {
				Result = vkBindBufferMemory(Context->handle(), Handle, MemoryHandle, 0);
			}
			if (Result == VK_SUCCESS) {
				vk_submit_info Submission{};
				vk_command_buffer CommandBuffer = VK_NULL_HANDLE;
				vk_fence_create_info FenceCreateInfo{};
				vk_fence Fence;

				Submission.sType					= VK_STRUCTURE_TYPE_SUBMIT_INFO;
				Submission.pNext					= NULL;
				Submission.waitSemaphoreCount		= 0;
				Submission.pWaitSemaphores			= NULL;
				Submission.pWaitDstStageMask		= 0;
				Submission.commandBufferCount		= 1;
				Submission.pCommandBuffers			= &CommandBuffer;
				Submission.signalSemaphoreCount		= 0;
				Submission.pSignalSemaphores		= NULL;

				FenceCreateInfo.sType				= VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				CommandBuffer = (*this << aInp);
				Result = vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
				Result = Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
				Result = vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);

				Context->destroy(device::qfs::TRANSFER, CommandBuffer);
				vkDestroyFence(Context->handle(), Fence, NULL);

			}
		}
	}

	buffer::buffer(buffer&& aInp) noexcept {
		Context			= aInp.Context;
		CreateInfo		= aInp.CreateInfo;
		Handle			= aInp.Handle;
		AllocateInfo	= aInp.AllocateInfo;
		MemoryHandle	= aInp.MemoryHandle;
		Count			= aInp.Count;
		MemoryLayout	= aInp.MemoryLayout;

		aInp.Context			= nullptr;
		aInp.CreateInfo			= {};
		aInp.Handle				= VK_NULL_HANDLE;
		aInp.AllocateInfo		= {};
		aInp.MemoryHandle		= VK_NULL_HANDLE;
		aInp.Count				= 0;
		aInp.MemoryLayout		= variable();
	}

	buffer& buffer::operator=(buffer& aRhs) {
		if (this == &aRhs) return *this;
		this->pmclearall();

		Context			= aRhs.Context;
		CreateInfo		= aRhs.CreateInfo;
		AllocateInfo	= aRhs.AllocateInfo;
		Count			= aRhs.Count;
		MemoryLayout	= aRhs.MemoryLayout;

		vk_result Result = vk_result::VK_SUCCESS;
		if (Context != nullptr) {
			Result = vkCreateBuffer(Context->handle(), &CreateInfo, NULL, &Handle);
			if (Result == vk_result::VK_SUCCESS) {
				Result = vkAllocateMemory(Context->handle(), &AllocateInfo, NULL, &MemoryHandle);
			}
			if (Result == vk_result::VK_SUCCESS) {
				Result = vkBindBufferMemory(Context->handle(), Handle, MemoryHandle, 0);
			}
			if (Result == vk_result::VK_SUCCESS) {
				vk_submit_info Submission{};
				vk_command_buffer CommandBuffer = VK_NULL_HANDLE;
				vk_fence_create_info FenceCreateInfo{};
				vk_fence Fence;

				Submission.sType					= vk_structure_type::VK_STRUCTURE_TYPE_SUBMIT_INFO;
				Submission.pNext					= NULL;
				Submission.waitSemaphoreCount		= 0;
				Submission.pWaitSemaphores			= NULL;
				Submission.pWaitDstStageMask		= 0;
				Submission.commandBufferCount		= 1;
				Submission.pCommandBuffers			= &CommandBuffer;
				Submission.signalSemaphoreCount		= 0;
				Submission.pSignalSemaphores		= NULL;

				FenceCreateInfo.sType				= vk_structure_type::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
				FenceCreateInfo.pNext				= NULL;
				FenceCreateInfo.flags				= 0;

				CommandBuffer = (*this << aRhs);
				Result = vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
				Result = Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
				Result = vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);

				Context->destroy(device::qfs::TRANSFER, CommandBuffer);
				vkDestroyFence(Context->handle(), Fence, NULL);
			}
		}

		return *this;
	}

	buffer& buffer::operator=(buffer&& aRhs) noexcept {
		pmclearall();

		Context			= aRhs.Context;
		CreateInfo		= aRhs.CreateInfo;
		Handle			= aRhs.Handle;
		AllocateInfo		= aRhs.AllocateInfo;
		MemoryHandle		= aRhs.MemoryHandle;
		Count				= aRhs.Count;
		MemoryLayout		= aRhs.MemoryLayout;

		aRhs.Context			= nullptr;
		aRhs.CreateInfo			= {};
		aRhs.Handle				= VK_NULL_HANDLE;
		aRhs.AllocateInfo		= {};
		aRhs.MemoryHandle		= VK_NULL_HANDLE;
		aRhs.Count				= 0;
		aRhs.MemoryLayout		= variable();

		return *this;
	}

	vk_command_buffer buffer::operator<<(buffer& aRhs) {
		vk_command_buffer CommandBuffer = VK_NULL_HANDLE;
		// Both operands must share the same parent context, and have same memory size.
		if ((Context != aRhs.Context) || ((size_t)CreateInfo.size != aRhs.CreateInfo.size)) return CommandBuffer;
		// Left operand must have TRANSFER_DST flag enabled, and Right operand must have TRANSFER_SRC flag enabled.
		if (
			((CreateInfo.usage & buffer::usage::TRANSFER_DST) != buffer::usage::TRANSFER_DST)
			||
			((aRhs.CreateInfo.usage & buffer::usage::TRANSFER_SRC) != buffer::usage::TRANSFER_SRC)
		) return CommandBuffer;

		vk_result Result = vk_result::VK_SUCCESS;
		vk_command_buffer_begin_info BeginInfo{};
		vk_buffer_copy Region{};

		BeginInfo.sType						= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext						= NULL;
		BeginInfo.flags						= 0;
		BeginInfo.pInheritanceInfo			= NULL;

		Region.srcOffset					= 0;
		Region.dstOffset					= 0;
		Region.size							= CreateInfo.size;

		CommandBuffer = Context->create(device::qfs::TRANSFER);
		if (CommandBuffer != VK_NULL_HANDLE) {
			Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
			vkCmdCopyBuffer(CommandBuffer, aRhs.Handle, Handle, 1, &Region);
			Result = vkEndCommandBuffer(CommandBuffer);
		}
		return CommandBuffer;
	}

	vk_command_buffer buffer::operator>>(buffer& aRhs) {
		return (aRhs << *this);
	}

	vk_command_buffer buffer::operator<<(image& aRhs) {
		vk_command_buffer CommandBuffer = VK_NULL_HANDLE;
		// Must share the same parent context and have the same size.
		if ((Context != aRhs.Context) || ((size_t)CreateInfo.size != aRhs.MemorySize)) return CommandBuffer;
		// buffer must have enabled, DST flag. texture must have SRC flag.
		if (
			((CreateInfo.usage & buffer::usage::TRANSFER_DST) != buffer::usage::TRANSFER_DST) 
			|| 
			((aRhs.CreateInfo.usage & image::usage::TRANSFER_SRC) != image::usage::TRANSFER_SRC)
		) return CommandBuffer;

		vk_result Result = vk_result::VK_SUCCESS;
		vk_command_buffer_begin_info BeginInfo{};
		std::vector<vk_image_memory_barrier> Barrier(aRhs.CreateInfo.arrayLayers);
		vk_buffer_image_copy Region{};

		BeginInfo.sType						= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext						= NULL;
		BeginInfo.flags						= 0;
		BeginInfo.pInheritanceInfo			= NULL;

		for (uint32_t i = 0; i < aRhs.CreateInfo.arrayLayers; i++) {
			Barrier[i].sType								= VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier[i].pNext								= NULL;
			Barrier[i].srcAccessMask						= VK_ACCESS_MEMORY_WRITE_BIT;
			Barrier[i].dstAccessMask						= VK_ACCESS_TRANSFER_READ_BIT;
			Barrier[i].oldLayout							= aRhs.Layout[0][i];
			Barrier[i].newLayout							= VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			Barrier[i].srcQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
			Barrier[i].dstQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
			Barrier[i].image								= aRhs.Handle;
			Barrier[i].subresourceRange.aspectMask			= VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier[i].subresourceRange.baseMipLevel		= 0;
			Barrier[i].subresourceRange.levelCount			= 1;
			Barrier[i].subresourceRange.baseArrayLayer		= i;
			Barrier[i].subresourceRange.layerCount			= 1;
			aRhs.Layout[0][i]								= Barrier[i].newLayout;
		}

		Region.bufferOffset						= 0;
		Region.bufferRowLength					= 0;
		Region.bufferImageHeight				= 0;
		Region.imageSubresource.aspectMask		= VK_IMAGE_ASPECT_COLOR_BIT;
		Region.imageSubresource.mipLevel		= 0;
		Region.imageSubresource.baseArrayLayer	= 0;
		Region.imageSubresource.layerCount		= aRhs.CreateInfo.arrayLayers;
		Region.imageOffset						= { 0, 0, 0 };
		Region.imageExtent						= aRhs.CreateInfo.extent;

		//Result = Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
		CommandBuffer = Context->create(device::qfs::TRANSFER);
		Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

		// Use barrier for transition if layout doesn't match.
		vkCmdPipelineBarrier(CommandBuffer,
			VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			VK_PIPELINE_STAGE_TRANSFER_BIT,
			0,
			0, NULL,
			0, NULL,
			Barrier.size(), Barrier.data()
		);

		vkCmdCopyImageToBuffer(CommandBuffer,
			aRhs.Handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			Handle,
			1, &Region
		);

		Result = vkEndCommandBuffer(CommandBuffer);

		return CommandBuffer;
	}

	vk_command_buffer buffer::operator>>(image& aRhs) {
		return (aRhs >> *this);
		return VK_NULL_HANDLE;
	}

	void buffer::write(size_t aMemOffset, size_t aMemSize, void* aData) {
		vk_buffer_copy Region;
		Region.srcOffset = 0;
		Region.dstOffset = aMemOffset;
		Region.size = aMemSize;
		write(1, &Region, aData);
	}

	void buffer::write(uint32_t aRegionCount, vk_buffer_copy* aRegion, void* aData) {
		if ((Context == nullptr) || (aRegionCount == 0) || (aRegion == NULL) || (aData == NULL)) return;
		if (((Context->parent()->get_memory_property_flags(AllocateInfo.memoryTypeIndex)) & device::memory::HOST_VISIBLE) != device::memory::HOST_VISIBLE) return;

		vk_result Result = vk_result::VK_SUCCESS;
		void* nptr = NULL;
		Result = vkMapMemory(Context->handle(), MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
		if ((nptr == NULL) || (Result != VK_SUCCESS)) return;
		for (uint32_t i = 0; i < aRegionCount; i++) {
			memcpy((void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)aData + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
		}
		vkUnmapMemory(Context->handle(), MemoryHandle);

	}

	void buffer::read(size_t aMemOffset, size_t aMemSize, void* aData) {
		vk_buffer_copy Region;
		Region.srcOffset = aMemOffset;
		Region.dstOffset = 0;
		Region.size = aMemSize;
		read(1, &Region, aData);
	}

	void buffer::read(uint32_t aRegionCount, vk_buffer_copy* aRegion, void* aData) {
		if ((Context == nullptr) || (aRegionCount == 0) || (aRegion == NULL) || (aData == NULL)) return;

		device* Device = Context->parent();
		vk_memory_property_flags MemoryType = Device->get_memory_property_flags(AllocateInfo.memoryTypeIndex);

		if ((MemoryType & device::memory::HOST_VISIBLE) != device::memory::HOST_VISIBLE) return;

		void* nptr = NULL;
		vk_result Result = VK_SUCCESS;
		Result = vkMapMemory(Context->handle(), MemoryHandle, 0, VK_WHOLE_SIZE, 0, &nptr);
		if ((nptr == NULL) || (Result != VK_SUCCESS)) return;
		for (uint32_t i = 0; i < aRegionCount; i++) {
			memcpy((void*)((uintptr_t)aData + (uintptr_t)aRegion[i].dstOffset), (void*)((uintptr_t)nptr + (uintptr_t)aRegion[i].srcOffset), aRegion[i].size);
		}
		vkUnmapMemory(Context->handle(), MemoryHandle);

	}

	vk_buffer& buffer::handle() {
		return Handle;
	}

	void buffer::pmclearall() {
		if (Context != nullptr) {
			if (Handle != VK_NULL_HANDLE) {
				vkDestroyBuffer(Context->handle(), Handle, NULL);
				Handle = VK_NULL_HANDLE;
			}
			if (MemoryHandle != VK_NULL_HANDLE) {
				vkFreeMemory(Context->handle(), MemoryHandle, NULL);
				MemoryHandle = VK_NULL_HANDLE;
			}
		}

		Context = nullptr;
		CreateInfo = {};
		AllocateInfo = {};

		Count = 0;
		MemoryLayout = variable();

	}

}
