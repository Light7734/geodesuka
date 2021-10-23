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
		
		VkQueue Transfer;
		VkQueue Compute;
		VkQueue Graphics;

		// Will be VK_NULL_HANDLE if VK_KHR_surface is not enabled.
		VkQueue Present;

		//TODO: Include dependency of engine instance.
		context(/*engine *aEngine,*/device* aDevice, uint32_t aExtensionCount, const char** aExtensionList);
		~context();



		// ----- Query ----- //

		//VkQueue get_queue(uint32_t FamilyIndex, uint32_t Index);

		// ----- Handles ----- //

		VkInstance inst();
		// TODO: Change to device()?
		device* parent();
		VkDevice handle();

	private:

		// Parent physical device.
		device* Device;

		float** QueueFamilyPriority;

		uint32_t QueueCreateInfoCount;
		VkDeviceQueueCreateInfo* QueueCreateInfo;
		VkPhysicalDeviceFeatures EnabledFeatures{};

		// Stores queues and stuff.
		VkDeviceCreateInfo CreateInfo{};
		VkDevice Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
