#pragma once
#ifndef GEODESUKA_CORE_GCL_CONTEXT_H
#define GEODESUKA_CORE_GCL_CONTEXT_H

#include <atomic>
#include <mutex>

#include "config.h"

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

		context(engine* aEngine, device* aDevice, uint32_t aLayerCount, const char** aLayerList, uint32_t aExtensionCount, const char** aExtensionList);
		~context();

		vk_memory_requirements get_buffer_memory_requirements(vk_buffer aBufferHandle);

		vk_memory_requirements get_image_memory_requirements(vk_image aImageHandle);

		// ----- Command Buffers From Context ----- //

		// Creates a single command buffer with selected operations.
		vk_command_buffer create(device::qfs aQFS);

		// Creates a list of command buffers with this context and selected support options.
		vk_result create(device::qfs aQFS, uint32_t aCommandBufferCount, vk_command_buffer* aCommandBuffer);

		// Destroys a single command buffer created by this context.
		void destroy(device::qfs aQFS, vk_command_buffer &aCommandBuffer);

		// Destroys all command buffers provided if they were created by this context.
		void destroy(device::qfs aQFS, uint32_t aCommandBufferCount, vk_command_buffer *aCommandBuffer);

		// -------------------- Queue Family Stuff -------------------- //

		// Grabs the Queue Family Index associated with Queue Support Bit from context.
		int qfi(device::qfs aQFS);

		// Queries if queue type exists with context.
		bool available(device::qfs aQFS);

		//
		vk_result execute(device::qfs aQFS, command_batch& aCommandBatch, vk_fence aFence);

		// Submission for TRANSFER, COMPUTE, GRAPHICS, is multithread safe. 
		vk_result submit(device::qfs aQID, uint32_t aSubmissionCount, vk_submit_info* aSubmission, vk_fence aFence);

		// Simply presents images corresponding to indices.
		vk_result present(vk_present_info_khr* aPresentation);

		vk_instance inst();
		device* parent();
		vk_device handle();

	private:

		// -------------------- Engine Data -------------------- //
		// Used for engine backend.
		std::mutex ExecutionMutex;
		VkFence ExecutionFence[3];
		command_batch BackBatch[3];
		command_batch WorkBatch[3];

		// -------------------- Engine Data -------------------- //

		std::mutex Mutex;
		std::atomic<bool> isReadyToBeProcessed;

		// Parent physical device.
		engine* Engine;
		device* Device;

		// Supported Queue options for this context
		unsigned int Support;

		// Queue Family Indices = QFI
		// Array of QFIs.
		int QFI[4];

		// Array of Unique QFIs.
		int UQFICount;
		int UQFI[4];

		float** QueueFamilyPriority;
		vk_device_queue_create_info* QueueCreateInfo;
		vk_device_create_info CreateInfo{};
		vk_device Handle;

		struct queue {
			uint32_t i, j;		
			//device::queue_family_capability Capability;
			std::mutex Mutex;			// Use mutex wait if no other queues are available.
			vk_queue Handle;				// vkQueueSubmit() must be done by one thread at a time.
			queue();
		};

		// Linearized Queue Array.
		size_t QueueCount;
		queue *Queue;

		// Builtin command pools.
		vk_command_pool_create_info PoolCreateInfo[3];
		vk_command_pool Pool[3];
		uint32_t CommandBufferCount[3];
		vk_command_buffer *CommandBuffer[3];

	};

}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
