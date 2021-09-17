#pragma once
#ifndef GEODESUKA_CORE_GCL_CONTEXT_H
#define GEODESUKA_CORE_GCL_CONTEXT_H

#include "device.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class context {
			public:

				struct queue_family {
					VkDeviceQueueCreateInfo CreateInfo;
					float Priority;
				};


				context(device* aDevice, uint32_t aExtensionCount, const char **aExtensionList);
				~context();

				// ----- Query ----- //

				bool ext_supported(const char* aExtension);
				VkQueue get_queue(uint32_t FamilyIndex, uint32_t Index);

				// ----- Handles ----- //

				VkInstance inst();
				device* parent();
				VkDevice handle();

				// Parse error into string.
				static const char* get_er_str(VkResult Res);

			private:

				device* ParentDevice;
				VkDevice Handle;

				// Stores queues and stuff.
				VkDeviceCreateInfo CreationInfo{};

				uint32_t QueueCreateInfoCount;
				VkDeviceQueueCreateInfo* QueueCreateInfo;
				//float* QueueFamilyPriority;
				const float Priority = 1.0f;


			};

		}
	}
}

#endif // !GEODESUKA_CORE_GCL_CONTEXT_H
