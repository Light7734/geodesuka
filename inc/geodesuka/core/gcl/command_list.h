#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_LIST_H
#define GEODESUKA_CORE_GCL_COMMAND_LIST_H

#include <vulkan/vulkan.h>

namespace geodesuka::core::gcl {

	//class command_pool;

	class command_list {
	public:

		command_list();
		command_list(VkCommandBuffer aCommandBuffer);
		command_list(uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList);
		command_list(const command_list& aCommandList);
		command_list(command_list&& aCommandList) noexcept;
		~command_list();

		//command_list& operator=(VkCommandBuffer aRhs);
		command_list& operator=(const command_list& aRhs);
		command_list& operator=(command_list&& aRhs) noexcept;

		//VkCommandBuffer operator[](uint32_t aIndex);
		VkCommandBuffer& operator[](uint32_t aIndex);

		command_list& operator+=(VkCommandBuffer aRhs);
		command_list& operator+=(const command_list& aRhs);

	private:

		//command_pool* CommandPool;
		uint32_t n;
		VkCommandBuffer* ptr;

	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_LIST_H
