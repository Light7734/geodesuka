#include <geodesuka/core/gcl/context.h>

#include <cstdlib>

#include <geodesuka/core/gcl/buffer.h>
#include <geodesuka/core/gcl/shader.h>
#include <geodesuka/core/gcl/texture.h>
#include <geodesuka/core/gcl/framebuffer.h>

namespace geodesuka::core::gcl {

	context::context(device* aDevice, uint32_t aExtensionCount, const char** aExtensionList) {
		// List of operations.
		// Check for support of required extensions requested i
		// 1: Check for extensions.
		// 2: Queue Create Info.
		// 3: Create Logical Device.

		this->QueueCreateInfoCount = 0;
		this->QueueCreateInfo = NULL;
		this->QueueFamilyPriority = NULL;

		this->ParentDevice = nullptr;
		this->Handle = VK_NULL_HANDLE;

		VkResult Result = VK_SUCCESS;
		if (aDevice->is_extension_list_supported(aExtensionCount, aExtensionList)) {
			this->ParentDevice = aDevice;
			this->Handle = VK_NULL_HANDLE;

			uint32_t QueueFamilyCount = 0;
			const VkQueueFamilyProperties* QueueFamily = aDevice->get_queue_families(&QueueFamilyCount);

			bool Allocated = false;
			this->QueueCreateInfoCount = QueueFamilyCount;
			this->QueueCreateInfo = (VkDeviceQueueCreateInfo*)malloc(QueueFamilyCount * sizeof(VkDeviceQueueCreateInfo));
			this->QueueFamilyPriority = (float**)malloc(QueueFamilyCount * sizeof(float*));
			Allocated = (this->QueueCreateInfo != NULL) && (this->QueueFamilyPriority != NULL);
			if (Allocated) {
				for (uint32_t i = 0; i < QueueFamilyCount; i++) {
					this->QueueFamilyPriority[i] = (float*)malloc(QueueFamily[i].queueCount * sizeof(float));
					Allocated &= (this->QueueFamilyPriority[i] != NULL);
				}
			}

			// Memory Allocated, fill out rest.
			if (Allocated) {

				// Set priority values. (Adjust later)
				for (uint32_t i = 0; i < QueueFamilyCount; i++) {
					for (uint32_t j = 0; j < QueueFamily[i].queueCount; j++) {
						this->QueueFamilyPriority[i][j] = 1.0f;
					}
				}

				for (uint32_t i = 0; i < QueueFamilyCount; i++) {
					QueueCreateInfo[i].sType					= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					QueueCreateInfo[i].pNext					= NULL;
					QueueCreateInfo[i].flags					= 0;
					QueueCreateInfo[i].queueFamilyIndex			= i;
					QueueCreateInfo[i].queueCount				= QueueFamily[i].queueCount;
					QueueCreateInfo[i].pQueuePriorities			= QueueFamilyPriority[i];
				}

				this->EnabledFeatures = aDevice->get_features();

				this->CreationInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				this->CreationInfo.pNext						= NULL;
				this->CreationInfo.flags						= 0;
				this->CreationInfo.queueCreateInfoCount			= this->QueueCreateInfoCount;
				this->CreationInfo.pQueueCreateInfos			= this->QueueCreateInfo;
				this->CreationInfo.enabledLayerCount			= 0;
				this->CreationInfo.ppEnabledLayerNames			= NULL;
				this->CreationInfo.enabledExtensionCount		= aExtensionCount;
				this->CreationInfo.ppEnabledExtensionNames		= aExtensionList;
				this->CreationInfo.pEnabledFeatures				= &this->EnabledFeatures;

				Result = vkCreateDevice(aDevice->handle(), &this->CreationInfo, NULL, &this->Handle);
			}
			else {
				if (this->QueueCreateInfo != NULL) {
					free(this->QueueCreateInfo);
					this->QueueCreateInfo = NULL;
				}
				if (this->QueueFamilyPriority != NULL) {
					for (uint32_t i = 0; i < this->QueueCreateInfoCount; i++) {
						if (this->QueueFamilyPriority[i] != NULL) {
							free(this->QueueFamilyPriority[i]);
							this->QueueFamilyPriority[i] = NULL;
						}
					}
					free(this->QueueFamilyPriority);
					this->QueueFamilyPriority = NULL;
				}
				this->QueueCreateInfoCount = 0;

				this->ParentDevice = nullptr;
				this->Handle = VK_NULL_HANDLE;
			}

		}
	}

	context::~context() {
		vkDestroyDevice(this->Handle, NULL); this->Handle = VK_NULL_HANDLE;

		this->ParentDevice = nullptr;

		free(this->QueueCreateInfo); this->QueueCreateInfo = NULL;

		if (this->QueueFamilyPriority != NULL) {
			for (uint32_t i = 0; i < this->QueueCreateInfoCount; i++) {
				free(this->QueueFamilyPriority[i]); this->QueueFamilyPriority[i] = NULL;
			}
		}

		free(this->QueueFamilyPriority); this->QueueFamilyPriority = NULL;

		this->QueueCreateInfoCount = 0;
	}

	//bool context::ext_supported(const char* aExtension) {
	//	// Make hash map.
	//	for (size_t i = 0; i < ActiveExtension.size(); i++) {
	//		if (strcmp(this->DesiredExtension[i], aExtension) == 0) {
	//			return this->ActiveExtension[i];
	//		}
	//		else {
	//			return false;
	//		}
	//	}
	//	return false;
	//}

	VkInstance context::inst() {
		return this->ParentDevice->inst();
	}

	device* context::parent() {
		return this->ParentDevice;
	}

	VkDevice context::handle() {
		return this->Handle;
	}

}
