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
					for (size_t j = 0; j < DesiredExtension.size(); j++) {
						//std::cout << PhysicalDeviceExtension[i].extensionName << " = " << this->DesiredExtension[j] << std::endl;
						size_t StrLen1 = strlen(PhysicalDeviceExtension[i].extensionName);
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
			}

		}
	}
}
