#pragma once
#ifndef DEVICE_CONTEXT_H
#define DEVICE_CONTEXT_H

#include "gcl.h"
#include "device.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class device_context {
			public:

				struct queue_family {
					std::vector<VkQueue> Queue;
				};

				VkResult ErrorCode;
				std::vector<queue_family> QueueFamily;

				device_context(device* aDevice);
				~device_context();

				VkInstance* get_inst();
				device* get_pdevice();
				VkDevice get_handle();
				bool ext_supported(const char* aExtension);


			private:

				bool SwapChainSupport;

				// Stores queues and stuff.
				const float Priority = 1.0f;
				std::vector<VkDeviceQueueCreateInfo> QueueCreateInfo;
				VkDeviceCreateInfo CreationInfo{};

				// Replace with ParentDevice;
				device* ParentDevice;
				//VkInstance* ParentInstance;
				VkDevice Handle;

				// Extensions desired for context creation.
				const std::vector<const char*> DesiredExtension = { "VK_KHR_swapchain" };
				// Currently Active Desired Extensions.
				std::vector<bool> ActiveExtension;
				// Found Extensions from Desired Extensions.
				std::vector<const char*> FoundExtension;
			};

		}
	}
}

#endif // !DEVICE_CONTEXT_H
