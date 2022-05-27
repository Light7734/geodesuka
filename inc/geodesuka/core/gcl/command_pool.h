#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_POOL_H
#define GEODESUKA_CORE_GCL_COMMAND_POOL_H

#include <vector>
#include <mutex>

#include "../gcl.h"
#include "device.h"
#include "context.h"
#include "command_list.h"

namespace geodesuka::core::gcl {

	class command_pool {
	public:

		enum flags {
			TRANSIENT_BIT				= 0x00000001,
			RESET_COMMAND_BUFFER_BIT	= 0x00000002,
			PROTECTED_BIT				= 0x00000004,
		};

		enum level {
			PRIMARY,
			SECONDARY
		};

		// Use for command buffer writing.
		std::mutex Mutex;

		command_pool(context* aContext, int aFlags, uint32_t aQueueFamilyIndex);
		command_pool(context* aContext, int aFlags, device::qfs aQueueFamilySupport);
		~command_pool();

		VkCommandBuffer allocate(int aLevel);
		void allocate(int aLevel, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList);
		command_list allocate(int aLevel, uint32_t aCommandBufferCount);

		void release(VkCommandBuffer aCommandBuffer);
		void release(uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList);
		void release(command_list& aCommandList);

	private:

		context* Context;
		VkCommandPoolCreateInfo CreateInfo{};
		VkCommandPool Handle;

		command_list CommandList;

	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_POOL_H
