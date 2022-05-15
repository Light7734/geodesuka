#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_POOL_H
#define GEODESUKA_CORE_GCL_COMMAND_POOL_H

#include <vector>
#include <mutex>

#include "../gcl.h"
#include "device.h"
#include "context.h"

namespace geodesuka::core::gcl {

	class command_pool {
	public:

		enum flags {
			TRANSIENT_BIT				= 0x00000001,
			RESET_COMMAND_BUFFER_BIT	= 0x00000002,
			PROTECTED_BIT				= 0x00000004,
		};

		enum level {

		};

		std::mutex Mutex;

		command_pool(context* aContext, int aFlags, uint32_t aQueueFamilyIndex);
		command_pool(context* aContext, int aFlags, device::qfs aQueueFamilySupport);
		~command_pool();

		VkCommandBuffer allocate(int aLevel);
		void allocate(int aLevel, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList);


		void release(VkCommandBuffer aCommandBuffer);
		void release(uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBufferList);

	private:

		context* Context;
		VkCommandPoolCreateInfo CreateInfo{};
		VkCommandPool Handle;

		std::vector<VkCommandBuffer> CommandList;

	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_POOL_H
