#pragma once
#ifndef GEODESUKA_CORE_GCL_CONTEXT_H
#define GEODESUKA_CORE_GCL_CONTEXT_H

#include <vulkan/vulkan.h>

#include "device.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class buffer;
			class shader;
			class texture;

			class renderpass;
			class framebuffer;
			class pipeline;

			class context {
			public:


				context(device* aDevice, uint32_t aExtensionCount, const char **aExtensionList);
				~context();

				

				// ----- Query ----- //

				//VkQueue get_queue(uint32_t FamilyIndex, uint32_t Index);

				// ----- Handles ----- //

				VkInstance inst();
				device* parent();
				VkDevice handle();

				// Parse error into string.
				static const char* get_er_str(VkResult Res);

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
	}
}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
