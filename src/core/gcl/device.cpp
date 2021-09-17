#include <geodesuka/core/gcl/device.h>

#include <cstdlib>
#include <cstring>

namespace geodesuka {
	namespace core {
		namespace gcl {

			device::device(VkInstance aInstance, VkPhysicalDevice aPhysicalDevice) {
				this->ParentInstance = aInstance;
				this->Handle = aPhysicalDevice;

				VkResult Result = VK_SUCCESS;

				// Gather all extensions.
				Result = vkEnumerateDeviceExtensionProperties(this->Handle, NULL, &this->ExtensionCount, NULL);
				if (this->ExtensionCount > 0) {
					this->Extension = (VkExtensionProperties*)malloc(this->ExtensionCount * sizeof(VkExtensionProperties));
					if (this->Extension != NULL) {
						Result = vkEnumerateDeviceExtensionProperties(this->Handle, NULL, &this->ExtensionCount, this->Extension);
					}
					else {
						this->ExtensionCount = 0;
					}
				}
				else {
					this->Extension = NULL;
				}

				// Gather all possible queues
				vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &this->QueueFamilyCount, NULL);
				if (this->QueueFamilyCount > 0) {
					this->QueueFamily = (VkQueueFamilyProperties*)malloc(this->QueueFamilyCount * sizeof(VkQueueFamilyProperties));
					if (this->QueueFamily != NULL) {
						vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &this->QueueFamilyCount, this->QueueFamily);
					}
					else {
						this->QueueFamilyCount = 0;
					}
				}
				else {
					this->QueueFamily = NULL;
				}
			}

			device::~device() {
				free(this->Extension);
				this->Extension = NULL;
				free(this->QueueFamily);
				this->QueueFamily = NULL;
			}

			bool device::check_extension_list(uint32_t aExtensionCount, const char** aExtensionList) const {
				// Checks if args are valid extensions.
				bool isSupported = false;
				for (uint32_t i = 0; i < aExtensionCount; i++) {
					size_t L1 = strlen(aExtensionList[i]);
					for (uint32_t j = 0; j < this->ExtensionCount; j++) {
						size_t L2 = strlen(this->Extension[j].extensionName);
						if (L1 == L2) {
							// Compare
						}
					}
				}

				return isSupported;
			}

			VkPhysicalDeviceProperties device::get_properties() const {
				VkPhysicalDeviceProperties temp{};
				if (this->Handle != VK_NULL_HANDLE) {
					vkGetPhysicalDeviceProperties(this->Handle, &temp);
				}
				return temp;
			}

			VkPhysicalDeviceFeatures device::get_features() const {
				VkPhysicalDeviceFeatures temp{};
				if (this->Handle != VK_NULL_HANDLE) {
					vkGetPhysicalDeviceFeatures(this->Handle, &temp);
				}
				return temp;
			}

			const VkExtensionProperties* device::get_extensions(uint32_t* aExtensionCount) const {
				*aExtensionCount = this->ExtensionCount;
				return this->Extension;
			}

			const VkQueueFamilyProperties* device::get_queue_families(uint32_t* aQueueFamilyCount) const {
				*aQueueFamilyCount = this->QueueFamilyCount;
				return this->QueueFamily;
			}

			VkInstance device::inst() {
				return this->ParentInstance;
			}

			VkPhysicalDevice device::handle() {
				return this->Handle;
			}

		}
	}
}