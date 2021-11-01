#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_POOL_H
#define GEODESUKA_CORE_GCL_COMMAND_POOL_H

#include <vector>

#include <vulkan/vulkan.h>

#include "context.h"

namespace geodesuka::core::gcl {

	// TODO: Change this in future versions, this feels like a shitty wrapper class.
	class command_pool {
	public:

		enum flag {
			// Implies that command buffers created will be reset/freed often.
			TRANSIENT				= 0x00000001,
			// Allows individual command buffers to be reset.
			RESET_COMMAND_BUFFER	= 0x00000002,
			// Are protected command buffers. (No idea what this does)
			PROTECTED				= 0x00000004,
		};

		// Create from context, flags, and qid options.
		// command_pool *CommandPool = new command_pool(Context, command_pool::flag::TRANSIENT, context::qid::GRAPHICS);
		command_pool(context* aContext, int aFlags, int aQID);
		~command_pool();

		// Will create a series of command buffer handles, and fill the respective arguments.
		VkResult create(int aLevel, size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);

		// Will search and clear allocated command buffers from instance.
		void destroy(size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);

	protected:

	private:

		// Parent Context.
		context* Context;

		VkCommandPoolCreateInfo CreateInfo{};
		VkCommandPool Handle;

		// Too lazy to do it myself.
		std::vector<VkCommandBufferAllocateInfo> AllocateInfo;
		std::vector<VkCommandBuffer> CommandBuffer;

	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_POOL_H
