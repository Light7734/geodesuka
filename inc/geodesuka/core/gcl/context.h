#pragma once
#ifndef GEODESUKA_CORE_GCL_CONTEXT_H
#define GEODESUKA_CORE_GCL_CONTEXT_H

#include <mutex>

#include <vulkan/vulkan.h>

#include "device.h"

namespace geodesuka {
	class engine;
}

namespace geodesuka::core::gcl {

	class context {
	public:

		std::mutex Mutex;

		//\\ ------------------------------ Queues ------------------------------ //\\
		// Available queues for specific operations. Names are self explanatory.
		// These members will be VK_NULL_HANDLE if not available. Sometimes they
		// may be the same queue, but treat them differently even if they are
		// the same opaque handle.
		
		enum qid {
			TRANSFER	= 0x00000001,
			COMPUTE		= 0x00000002,
			GRAPHICS	= 0x00000004,
			PRESENT		= 0x00000008
		};

		//TODO: Include dependency of engine instance.
		context(engine *aEngine, device* aDevice, uint32_t aExtensionCount, const char** aExtensionList);
		~context();

		// Queries if queue exists with context.
		bool available(qid aQID);

		// Submission for TRANSFER, COMPUTE, GRAPHICS, is multithread safe. 
		void submit(qid aQID, uint32_t aSubmissionCount, VkSubmitInfo* aSubmission, VkFence aFence);

		// Simply presents images corresponding to indices.
		void present(VkPresentInfoKHR* aPresentation);

		// Will yield the queue family index with the least 
		//int get_index(int aQID);

		VkInstance inst();
		device* parent();
		VkDevice handle();

	private:

		// Parent physical device.
		engine* Engine;
		device* Device;

		float** QueueFamilyPriority;

		uint32_t QueueCreateInfoCount;
		VkDeviceQueueCreateInfo* QueueCreateInfo;
		VkPhysicalDeviceFeatures EnabledFeatures{};

		// Stores queues and stuff.
		VkDeviceCreateInfo CreateInfo{};
		VkDevice Handle;

		struct qindex {
			uint32_t FamilyIndex;
			uint32_t Index;
		};

		struct queue {
			qindex QIndex;				// Family Index & Sub Index
			//bool inUse;					// In use by another thread.
			// Supported Operations
			VkQueueFlags Flags;
			bool isTransferSupported;
			bool isComputeSupported;
			bool isGraphicsSupported;
			bool isPresentSupported;

			std::mutex Mutex;			// Use mutex wait if no other queues are available.
			VkQueue Handle;				// vkQueueSubmit() must be done by one thread at a time.

			queue();
		};

		// Linearized Queue Array.
		size_t QueueCount;
		queue *Queue;

	};

}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
