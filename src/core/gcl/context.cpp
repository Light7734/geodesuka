#include <geodesuka/core/gcl/context.h>

#include <cstdlib>

namespace geodesuka {
	namespace core {
		namespace gcl {

			context::context(device* aDevice, uint32_t aExtensionCount, const char** aExtensionList) {
				// List of operations.
				// Check for support of required extensions requested i
				// 1: Check for extensions.
				// 2: Queue Create Info.
				// 3: Create Logical Device.

				VkResult Result = VK_SUCCESS;
				if (aDevice->check_extension_list(aExtensionCount, aExtensionList)) {
					this->ParentDevice = aDevice;
					this->Handle = VK_NULL_HANDLE;

					uint32_t QueueFamilyCount = 0;
					const VkQueueFamilyProperties* QueueFamily = aDevice->get_queue_families(&QueueFamilyCount);

					bool Allocated = false;
					this->QueueCreateInfoCount = QueueFamilyCount;
					this->QueueCreateInfo = (VkDeviceQueueCreateInfo*)malloc(QueueFamilyCount * sizeof(VkDeviceQueueCreateInfo));
					this->QueueFamilyPriority = (float**)malloc(QueueFamilyCount * sizeof(float*));
					Allocated = (this->QueueCreateInfo != NULL) && (this->QueueFamilyPriority != NULL);
					if (this->QueueCreateInfo != NULL) {
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
				vkDestroyDevice(this->Handle, NULL);
				this->Handle = VK_NULL_HANDLE;
				this->ParentDevice = nullptr;
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

			const char* context::get_er_str(VkResult Res) {
				const char* temp;
				switch (Res) {
				default:
					temp = "Error: Unknown";
					break;
				case VK_SUCCESS:
					temp = "Success";
					break;
				case VK_NOT_READY:
					temp = "Not Ready.";
					break;
				case VK_TIMEOUT:
					temp = "Timeout.";
					break;
				case VK_EVENT_SET:
					temp = "Event Set.";
					break;
				case VK_EVENT_RESET:
					temp = "Event Reset.";
					break;
				case VK_INCOMPLETE:
					temp = "Incomplete.";
					break;
				case VK_ERROR_OUT_OF_HOST_MEMORY:
					temp = "Error: Out of Host Memory.";
					break;
				case VK_ERROR_OUT_OF_DEVICE_MEMORY:
					temp = "Error: Out of Device Memory.";
					break;
				case VK_ERROR_INITIALIZATION_FAILED:
					temp = "Error: Initialization failed.";
					break;
				case VK_ERROR_DEVICE_LOST:
					temp = "Error: Device Lost";
					break;
				case VK_ERROR_MEMORY_MAP_FAILED:
					temp = "Error: Memory Map Failed.";
					break;
				case VK_ERROR_LAYER_NOT_PRESENT:
					temp = "Error: Layer Not Present.";
					break;
				case VK_ERROR_EXTENSION_NOT_PRESENT:
					temp = "Error: Extension not present.";
					break;
				case VK_ERROR_FEATURE_NOT_PRESENT:
					temp = "Error: Feature Not Present.";
					break;
				case VK_ERROR_INCOMPATIBLE_DRIVER:
					temp = "Error: Incompatible Driver.";
					break;
				case VK_ERROR_TOO_MANY_OBJECTS:
					temp = "Error: Too many objects.";
					break;
				case VK_ERROR_FORMAT_NOT_SUPPORTED:
					temp = "Error: Format not supported.";
					break;
				case VK_ERROR_FRAGMENTED_POOL:
					temp = "Error: Fragmented pool.";
					break;
				case VK_ERROR_UNKNOWN:
					temp = "Error: Unknown.";
					break;
				case VK_ERROR_OUT_OF_POOL_MEMORY:
					temp = "Error: Out of pool memory.";
					break;
				case VK_ERROR_INVALID_EXTERNAL_HANDLE:
					temp = "Error: Invalid external handle.";
					break;
				case VK_ERROR_FRAGMENTATION:
					temp = "Error: Fragmentation.";
					break;
				case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
					temp = "Error: Invalid opaque capture address.";
					break;
				case VK_ERROR_SURFACE_LOST_KHR:
					temp = "Error: Surface lost (KHR)";
					break;
				case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
					temp = "Error: Native window in use (KHR)";
					break;
				case VK_SUBOPTIMAL_KHR:
					temp = "Suboptimal (khr)";
					break;
				case VK_ERROR_OUT_OF_DATE_KHR:
					temp = "Error: Out of date (khr)";
					break;
				case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
					temp = "Error: Incompatible display.";
					break;
				case VK_ERROR_VALIDATION_FAILED_EXT:
					temp = "Error: Validation failed (ext).";
					break;
				case VK_ERROR_INVALID_SHADER_NV:
					temp = "Error: Invalid shader (nv)";
					break;
				case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
					temp = "Error: Invalid DRM format modifier plane layout (ext)";
					break;
				case VK_ERROR_NOT_PERMITTED_EXT:
					temp = "Error: Not permitted extension";
					break;
				case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
					temp = "Error: Fullscreen exclusive mode lost.";
					break;
				case VK_THREAD_IDLE_KHR:
					temp = "Thread Idle (khr)";
					break;
				case VK_THREAD_DONE_KHR:
					temp = "Thread Done (khr)";
					break;
				case VK_OPERATION_DEFERRED_KHR:
					temp = "Operation Deferred (khr)";
					break;
				case VK_OPERATION_NOT_DEFERRED_KHR:
					temp = "Operation not deferred (khr)";
					break;
				case VK_PIPELINE_COMPILE_REQUIRED_EXT:
					temp = "Pipeline compile required. (ext)";
					break;
				}
				return temp;
				/*
				VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR = VK_ERROR_INVALID_EXTERNAL_HANDLE,
				VK_ERROR_FRAGMENTATION_EXT = VK_ERROR_FRAGMENTATION,
				VK_ERROR_INVALID_DEVICE_ADDRESS_EXT = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
				VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR = VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,
				VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT = VK_PIPELINE_COMPILE_REQUIRED_EXT,
				VK_RESULT_MAX_ENUM = 0x7FFFFFFF
				*/
			}

		}
	}
}
