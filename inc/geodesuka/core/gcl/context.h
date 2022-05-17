#pragma once
#ifndef GEODESUKA_CORE_GCL_CONTEXT_H
#define GEODESUKA_CORE_GCL_CONTEXT_H

#include <atomic>
#include <mutex>

#include "../gcl.h"
#include "command_batch.h"
#include "device.h"

namespace geodesuka::core::gcl {

	class command_batch;

	class context {
	public:

		friend class engine;

		//\\ ------------------------------ Queues ------------------------------ //\\
		// Available queues for specific operations. Names are self explanatory.
		// These members will be VK_NULL_HANDLE if not available. Sometimes they
		// may be the same queue, but treat them differently even if they are
		// the same opaque handle.

		// TODO: Include dependency of engine instance.
		context(engine* aEngine, device* aDevice, uint32_t aLayerCount, const char** aLayerList, uint32_t aExtensionCount, const char** aExtensionList);
		~context();

		// Grabs the Queue Family Index associated with Queue Support Bit from context.
		int qfi(device::qfs aQFS);

		// Queries if queue type exists with context.
		bool available(device::qfs aQFS);

		// Creates a single command buffer with selected operations.
		//VkCommandBuffer create(device::qfs aQFS);

		// Creates a list of command buffers with this context and selected support options.
		//VkResult create(device::qfs aQFS, uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);

		// Destroys a single command buffer created by this context.
		//void destroy(device::qfs aQFS, VkCommandBuffer &aCommandBuffer);

		// Destroys all command buffers provided if they were created by this context.
		//void destroy(device::qfs aQFS, uint32_t aCommandBufferCount, VkCommandBuffer *aCommandBuffer);
	
		// TODO: Make create/destroy thread safe.
		// Creates a series of command buffer handles, and fill the respective arguments.
		//VkResult create(cmdtype aCommandType, size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);

		//void destroy(VkCommandBuffer aCommandBuffer);
		// Searches and clear allocated command buffers from instance.
		//void destroy(cmdtype aCommandType, size_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);

		// Submission for TRANSFER, COMPUTE, GRAPHICS, is multithread safe. 
		VkResult submit(device::qfs aQID, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence);

		// Simply presents images corresponding to indices.
		VkResult present(VkPresentInfoKHR* aPresentation);

		VkInstance inst();
		device* parent();
		VkDevice handle();

	private:

		// Engine Specific Data.
		std::mutex ExecutionMutex;
		VkFence ExecutionFence[3];
		std::atomic<bool> UpdateInFlight;
		std::atomic<bool> RenderInFlight;
		command_batch BackBatch[3];
		command_batch WorkBatch[3];

		// Synchronization
		std::mutex Mutex;
		std::atomic<bool> isReady;
		VkFence Fence;

		// Parent physical device.
		engine* Engine;
		device* Device;

		// Supported Queue Options.
		unsigned int Support;

		// Queue Family Indices.
		int QFI[4];

		// Unique QFI.
		int UQFICount; // Always <= 4.
		int UQFI[4];

		float** QueueFamilyPriority;
		VkDeviceQueueCreateInfo* QueueCreateInfo;
		VkDeviceCreateInfo CreateInfo{};
		VkDevice Handle;

		struct queue {
			uint32_t i, j;		
			//device::queue_family_capability Capability;
			std::mutex Mutex;			// Use mutex wait if no other queues are available.
			VkQueue Handle;				// vkQueueSubmit() must be done by one thread at a time.
			queue();
		};

		// Linearized Queue Array.
		size_t QueueCount;
		queue *Queue;

		// Builtin command pools.
		VkCommandPoolCreateInfo PoolCreateInfo[3];
		VkCommandPool Pool[3];
		uint32_t CommandBufferCount[3];
		VkCommandBuffer *CommandBuffer[3];

	};

}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
