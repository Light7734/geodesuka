#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_LIST_H
#define GEODESUKA_CORE_GCL_COMMAND_LIST_H

#include <vulkan/vulkan.h>

#include "config.h"

namespace geodesuka::core::gcl {

	//class command_pool;

	class command_list {
	public:

		friend class command_pool;

		command_list();
		command_list(vk_command_buffer aCommandBuffer);
		command_list(uint32_t aCommandBufferCount, vk_command_buffer* aCommandBufferList);
		command_list(const command_list& aCommandList);
		command_list(command_list&& aCommandList) noexcept;
		~command_list();

		//command_list& operator=(vk_command_buffer aRhs);
		command_list& operator=(const command_list& aRhs);
		command_list& operator=(command_list&& aRhs) noexcept;

		//vk_command_buffer operator[](uint32_t aIndex);
		vk_command_buffer& operator[](uint32_t aIndex);

		command_list& operator+=(vk_command_buffer aRhs);
		command_list& operator+=(const command_list& aRhs);

	private:

		uint32_t n;
		vk_command_buffer* ptr;

	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_LIST_H
