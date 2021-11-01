#include <geodesuka/core/gcl/command_pool.h>

#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

#include <geodesuka/core/gcl/context.h>

namespace geodesuka::core::gcl {

	command_pool::command_pool(context* aContext, int aFlags, int aQID) {
		if ((aContext == nullptr) /*|| (aContext->available(aQID))*/) return;
		this->Context = aContext;

		this->CreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		this->CreateInfo.pNext				= NULL;
		this->CreateInfo.flags				= aFlags;
		this->CreateInfo.queueFamilyIndex	= aQID; // TODO: Update index selection.	
		VkResult Result = vkCreateCommandPool(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);
	}

	command_pool::~command_pool() {
		vkFreeCommandBuffers(this->Context->handle(), this->Handle, this->CommandBuffer.size(), this->CommandBuffer.data());
		vkDestroyCommandPool(this->Context->handle(), this->Handle, NULL);
	}

	VkResult command_pool::create(int aLevel, size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {
		VkCommandBufferAllocateInfo temp{};
		temp.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		temp.pNext					= NULL;
		temp.commandPool			= this->Handle;
		temp.level					= (VkCommandBufferLevel)aLevel;
		temp.commandBufferCount		= aCommandBufferCount;
		this->AllocateInfo.push_back(temp);
		size_t lOffset = this->CommandBuffer.size();
		VkCommandBuffer* lAddress = (VkCommandBuffer*)((uintptr_t)lOffset * sizeof(VkCommandBuffer) + (uintptr_t)this->CommandBuffer.data());
		return vkAllocateCommandBuffers(this->Context->handle(), &this->AllocateInfo.back(), lAddress);
	}

	void command_pool::destroy(size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer) {
		std::vector<VkCommandBuffer> FoundBuffer;
		for (size_t i = 0; i < this->CommandBuffer.size(); i++) {
			for (size_t j = 0; j < aCommandBufferCount; j++) {
				if (this->CommandBuffer[i] == aCommandBuffer[j]) {
					FoundBuffer.push_back(this->CommandBuffer[i]);
					this->CommandBuffer[i] = VK_NULL_HANDLE;
				}
			}
		}

		for (size_t i = 1; i <= this->CommandBuffer.size(); i++) {
			size_t Index = this->CommandBuffer.size() - i;
			if (this->CommandBuffer[Index] == VK_NULL_HANDLE) {
				this->CommandBuffer.erase(this->CommandBuffer.begin() + Index);
			}
		}

		vkFreeCommandBuffers(this->Context->handle(), this->Handle, FoundBuffer.size(), FoundBuffer.data());
	}

}
