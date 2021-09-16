#include <geodesuka/core/gcl/device.h>


namespace geodesuka {
	namespace core {
		namespace gcl {

			device::device(VkInstance* aParentInstance, VkPhysicalDevice aPhysicalDevice) {
				this->ParentInstance = aParentInstance;
				this->Handle = aPhysicalDevice;
				vkGetPhysicalDeviceProperties(this->Handle, &this->Properties);
				vkGetPhysicalDeviceFeatures(this->Handle, &this->Features);
				uint32_t QueueFamilyPropertiesCount;
				vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &QueueFamilyPropertiesCount, NULL);
				if (QueueFamilyPropertiesCount > 0) {
					this->QueueFamilyProperties.resize(QueueFamilyPropertiesCount);
					vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &QueueFamilyPropertiesCount, this->QueueFamilyProperties.data());
				}
			}

			device::~device() {
			
			}

			VkInstance* device::inst() {
				return this->ParentInstance;
			}

			VkPhysicalDevice device::handle() {
				return this->Handle;
			}

		}
	}
}