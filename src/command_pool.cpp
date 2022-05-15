#include <geodesuka/core/gcl/command_pool.h>

namespace geodesuka::core::gcl {

	command_pool::command_pool(context* aContext, int aFlags, uint32_t aQueueFamilyIndex) {
		this->Context = aContext;
		this->CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		this->CreateInfo.pNext = NULL;
		this->CreateInfo.flags = aFlags;
		this->CreateInfo.queueFamilyIndex = aQueueFamilyIndex;
		vkCreateCommandPool(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
	}

	command_pool::command_pool(context* aContext, int aFlags, device::qfs aQueueFamilySupport) {
		this->Context = aContext;
		this->CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		this->CreateInfo.pNext = NULL;
		this->CreateInfo.flags = aFlags;
		this->CreateInfo.queueFamilyIndex = aContext->parent()->qfi(aQueueFamilySupport);
		vkCreateCommandPool(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
	}

	command_pool::~command_pool() {
		//vkFreeCommandBuffers(this->Context->handle(), this->Handle, this->CommandList.size(), this->CommandList.ptr());
	}

	VkCommandBuffer command_pool::allocate(int aLevel) {
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;

		return CommandBuffer;
	}

	void command_pool::allocate(int aLevel, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList) {
		VkCommandBufferAllocateInfo AllocationInfo{};
		AllocationInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocationInfo.pNext = NULL;
		AllocationInfo.commandPool = this->Handle;
		AllocationInfo.level = (VkCommandBufferLevel)aLevel;
		AllocationInfo.commandBufferCount = aCommandBufferCount;
		VkResult Result = vkAllocateCommandBuffers(this->Context->handle(), &AllocationInfo, aCommandBufferList);
	}

}
