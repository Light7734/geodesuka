#include <geodesuka/core/gcl/device_context.h>

#include <iostream>

namespace geodesuka {
	namespace core {
		namespace gcl {



			device_context::device_context(device* aDevice) {
				ActiveExtension.resize(DesiredExtension.size());
				// Queuries physical device extensions.
				uint32_t PhysicalDeviceExtensionCount;
				vkEnumerateDeviceExtensionProperties(aDevice->get_handle(), NULL, &PhysicalDeviceExtensionCount, NULL);
				std::vector<VkExtensionProperties> PhysicalDeviceExtension(PhysicalDeviceExtensionCount);
				vkEnumerateDeviceExtensionProperties(aDevice->get_handle(), NULL, &PhysicalDeviceExtensionCount, PhysicalDeviceExtension.data());
				// Now that list of extensions is exposed from device, search for desired extensions.

				// Default is disabled
				for (size_t i = 0; i < ActiveExtension.size(); i++) {
					ActiveExtension[i] = false;
				}

				// Searches for desired extensions.
				for (size_t i = 0; i < PhysicalDeviceExtension.size(); i++) {
					size_t StrLen1 = strlen(PhysicalDeviceExtension[i].extensionName);
					for (size_t j = 0; j < DesiredExtension.size(); j++) {
						//std::cout << PhysicalDeviceExtension[i].extensionName << " = " << this->DesiredExtension[j] << std::endl;
						size_t StrLen2 = strlen(this->DesiredExtension[j]);
						if (StrLen1 == StrLen2) {
							if (strcmp(PhysicalDeviceExtension[i].extensionName, this->DesiredExtension[j]) == 0) {
								this->ActiveExtension[j] = true;
								this->FoundExtension.push_back(PhysicalDeviceExtension[i].extensionName);
							}
						}
					}
				}

				// Begin Device creation here.
				this->ParentDevice = aDevice;
				// Create Info for all available queues?
				this->QueueCreateInfo.resize(aDevice->QueueFamilyProperties.size());
				for (size_t i = 0; i < aDevice->QueueFamilyProperties.size(); i++) {
					VkDeviceQueueCreateInfo temp;
					temp.sType				= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
					temp.pNext				= NULL;
					temp.flags				= 0;
					temp.queueFamilyIndex	= (uint32_t)i;
					temp.queueCount			= aDevice->QueueFamilyProperties[i].queueCount;
					temp.pQueuePriorities	= &this->Priority; // Seems fucking retarded. Why a reference?
					this->QueueCreateInfo.push_back(temp);
				}

				this->CreationInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
				this->CreationInfo.pNext					= NULL; // No idea what this is for.
				this->CreationInfo.flags					= 0;	// Reserved for Future use. (Ignored)
				this->CreationInfo.queueCreateInfoCount		= (uint32_t)this->QueueCreateInfo.size();
				this->CreationInfo.pQueueCreateInfos		= this->QueueCreateInfo.data(); 
				this->CreationInfo.enabledLayerCount		= 0;
				this->CreationInfo.ppEnabledLayerNames		= NULL;
				this->CreationInfo.enabledExtensionCount	= (uint32_t)this->FoundExtension.size();
				this->CreationInfo.ppEnabledExtensionNames	= this->FoundExtension.data();
				this->CreationInfo.pEnabledFeatures			= &aDevice->Features; // Important

				this->ErrorCode = vkCreateDevice(aDevice->Handle, &this->CreationInfo, NULL, &this->Handle);

				// This is how to access the queues for the logical device.
				//vkGetDeviceQueue(this->Handle, QueueFamilyIndex, QueueIndex, &Queue);
				
				
				
				// Figure out how to allow user to interact with device queues.
				//for (size_t i = 0; i < aDevice->QueueFamilyProperties.size(); i++) {
				//	VkQueue temp;
				//	// Help?
				//	vkGetDeviceQueue(this->Handle, i, 0, &temp);
				//	this->Queue.push_back(temp);
				//}
			}

			device_context::~device_context() {
				vkDestroyDevice(this->Handle, NULL);
			}

			VkInstance* device_context::get_inst() {
				return this->ParentDevice->get_inst();
			}

			device* device_context::get_pdevice() {
				return this->ParentDevice;
			}

			VkDevice device_context::get_handle() {
				return this->Handle;
			}

			bool device_context::ext_supported(const char* aExtension) {
				// Make hash map.
				for (size_t i = 0; i < ActiveExtension.size(); i++) {
					if (strcmp(this->DesiredExtension[i], aExtension) == 0) {
						return this->ActiveExtension[i];
					}
					else {
						return false;
					}
				}
				return false;
			}

			const char* device_context::get_er_str(VkResult Res) {
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
