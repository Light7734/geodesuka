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

		VkQueue Transfer;
		VkQueue Compute;
		VkQueue Graphics;
		VkQueue Present;

		//TODO: Include dependency of engine instance.
		context(device* aDevice, uint32_t aExtensionCount, const char** aExtensionList);
		~context();



		// ----- Query ----- //

		//VkQueue get_queue(uint32_t FamilyIndex, uint32_t Index);

		// ----- Handles ----- //

		VkInstance inst();
		device* parent();
		VkDevice handle();

	private:

		uint32_t QueueCreateInfoCount;
		VkDeviceQueueCreateInfo* QueueCreateInfo;
		float** QueueFamilyPriority;
		VkPhysicalDeviceFeatures EnabledFeatures{};

		// Stores queues and stuff.
		VkDeviceCreateInfo CreationInfo{};

		device* ParentDevice;
		VkDevice Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
