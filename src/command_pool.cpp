#include <geodesuka/core/gcl/command_pool.h>

#include <assert.h>

namespace geodesuka::core::gcl {

	command_pool::command_pool(context* aContext, int aFlags, uint32_t aQueueFamilyIndex) {
		this->Context = aContext;
		if (this->Context == nullptr) return;
		this->CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		this->CreateInfo.pNext = NULL;
		this->CreateInfo.flags = aFlags;
		this->CreateInfo.queueFamilyIndex = aQueueFamilyIndex;
		vkCreateCommandPool(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
	}

	command_pool::command_pool(context* aContext, int aFlags, device::qfs aQueueFamilySupport) {
		this->Context = aContext;
		if (this->Context == nullptr) return;
		this->CreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		this->CreateInfo.pNext = NULL;
		this->CreateInfo.flags = aFlags;
		this->CreateInfo.queueFamilyIndex = aContext->parent()->qfi(aQueueFamilySupport);
		vkCreateCommandPool(aContext->handle(), &this->CreateInfo, NULL, &this->Handle);
	}

	command_pool::~command_pool() {
		if (Context != nullptr) {
			if ((CommandList.n > 0) && (CommandList.ptr != NULL)) {
				vkFreeCommandBuffers(Context->handle(), Handle, CommandList.n, CommandList.ptr);
			}
			free(CommandList.ptr);
			CommandList.n = 0;
			CommandList.ptr = NULL;
			if (Handle != VK_NULL_HANDLE) {
				vkDestroyCommandPool(Context->handle(), Handle, NULL);
			}
		}
		Context = nullptr;
	}

	VkCommandBuffer command_pool::allocate(int aLevel) {
		VkCommandBufferAllocateInfo AllocateInfo{};
		AllocateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.pNext					= NULL;
		AllocateInfo.commandPool			= Handle;
		AllocateInfo.level					= (VkCommandBufferLevel)aLevel;
		AllocateInfo.commandBufferCount		= 1;
		VkCommandBuffer CommandBuffer		= VK_NULL_HANDLE;
		VkResult Result = vkAllocateCommandBuffers(this->Context->handle(), &AllocateInfo, &CommandBuffer);
		return CommandBuffer;
	}

	void command_pool::allocate(int aLevel, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList) {
		VkCommandBufferAllocateInfo AllocateInfo{};
		AllocateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.pNext					= NULL;
		AllocateInfo.commandPool			= this->Handle;
		AllocateInfo.level					= (VkCommandBufferLevel)aLevel;
		AllocateInfo.commandBufferCount		= aCommandBufferCount;
		VkResult Result = vkAllocateCommandBuffers(this->Context->handle(), &AllocateInfo, aCommandBufferList);
	}

	command_list command_pool::allocate(int aLevel, uint32_t aCommandBufferCount) {
		command_list ReturnList;
		VkCommandBufferAllocateInfo AllocateInfo{};
		AllocateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.pNext					= NULL;
		AllocateInfo.commandPool			= Handle;
		AllocateInfo.level					= (VkCommandBufferLevel)aLevel;
		AllocateInfo.commandBufferCount		= aCommandBufferCount;
		ReturnList.n						= aCommandBufferCount;
		ReturnList.ptr						= (VkCommandBuffer*)malloc(aCommandBufferCount * sizeof(VkCommandBuffer));
		if (ReturnList.ptr != NULL) {
			VkResult Result = vkAllocateCommandBuffers(Context->handle(), &AllocateInfo, ReturnList.ptr);
		}
		return ReturnList;
	}

	void command_pool::release(VkCommandBuffer aCommandBuffer) {
		this->release(1, &aCommandBuffer);
	}

	void command_pool::release(uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList) {

		uint32_t RemoveCount = 0;
		VkCommandBuffer* RemoveList = NULL;	
		uint32_t NewCount = 0;
		VkCommandBuffer* NewList = NULL;

		for (uint32_t i = 0; i < aCommandBufferCount; i++) {
			for (uint32_t j = 0; j < CommandList.n; j++) {
				if (aCommandBufferList[i] == CommandList.ptr[j]) {
					RemoveCount += 1;
				}
			}
		}

		NewCount = CommandList.n - RemoveCount;
		RemoveList = (VkCommandBuffer*)malloc(RemoveCount * sizeof(VkCommandBuffer));
		NewList = (VkCommandBuffer*)malloc(NewCount * sizeof(VkCommandBuffer));

		assert(!((RemoveList == NULL) || (NewList == NULL)));

		uint32_t m = 0;
		for (uint32_t i = 0; i < CommandList.n; i++) {
			for (uint32_t j = 0; j < aCommandBufferCount; j++) {
				if (CommandList[i] == aCommandBufferList[j]) {
					RemoveList[m] = aCommandBufferList[j];
					CommandList[i] = VK_NULL_HANDLE;
					aCommandBufferList[j] = VK_NULL_HANDLE;
					m += 1;
				}
			}
		}

		uint32_t n = 0;
		for (uint32_t i = 0; i < CommandList.n; i++) {
			if (CommandList[i] != VK_NULL_HANDLE) {
				NewList[n] = CommandList[i];
				n += 1;
			}
		}

		vkFreeCommandBuffers(Context->handle(), Handle, RemoveCount, RemoveList);
		free(RemoveList);
		free(CommandList.ptr);
		CommandList.n = NewCount;
		CommandList.ptr = NewList;
	}

	void command_pool::release(command_list& aCommandList) {
		this->release(aCommandList.n, aCommandList.ptr);
	}

}
