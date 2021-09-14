#pragma once
#ifndef GEODESUKA_CORE_GCL_DEVICE_CONTEXT_H
#define GEODESUKA_CORE_GCL_DEVICE_CONTEXT_H

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

				// Parse error into string.
				static const char* get_er_str(VkResult Res);

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

#endif // !GEODESUKA_CORE_GCL_DEVICE_CONTEXT_H
