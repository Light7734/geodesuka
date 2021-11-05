#include <geodesuka/core/gcl/device.h>

#include <cstdlib>
#include <cstring>

#include <GLFW/glfw3.h>

namespace geodesuka::core::gcl {

	device::device(VkInstance aInstance, VkPhysicalDevice aPhysicalDevice) {

		this->ParentInstance = aInstance;
		this->Handle = aPhysicalDevice;

		this->ExtensionCount = 0;
		this->Extension = NULL;

		this->QueueFamilyCount = 0;
		this->QueueFamilyProperty = NULL;
		this->QueueFamilyCapability = NULL;
		this->QueueFamilySupportCount = NULL;

		VkResult Result = VK_SUCCESS;

		// Gather all extensions.
		Result = vkEnumerateDeviceExtensionProperties(this->Handle, NULL, &this->ExtensionCount, NULL);

		// Gather all possible queues
		vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &this->QueueFamilyCount, NULL);

		// Failure condition, device cannot be used.
		if (this->QueueFamilyCount == 0) return;

		// Allocate memory is extensions exist.
		if (this->ExtensionCount > 0) {
			this->Extension = (VkExtensionProperties*)malloc(this->ExtensionCount * sizeof(VkExtensionProperties));
			if (this->Extension == NULL) return;
		}
		else {
			this->Extension = NULL;
		}

		// Allocate memory for queues.
		if (this->QueueFamilyCount > 0) {
			this->QueueFamilyProperty = (VkQueueFamilyProperties*)malloc(this->QueueFamilyCount * sizeof(VkQueueFamilyProperties));
			this->QueueFamilyCapability = (queue_family_capability*)malloc(this->QueueFamilyCount * sizeof(queue_family_capability));
			this->QueueFamilySupportCount = (uint32_t*)malloc(this->QueueFamilyCount * sizeof(uint32_t));
		}
		else {
			this->QueueFamilyProperty = NULL;
			this->QueueFamilyCapability = NULL;
			this->QueueFamilySupportCount = NULL;
		}

		// Create Temp Window
		// This section is neccessary to create dummy surface
		// to test for presentation support. This makes the assumption
		// that presentation support does not depend on the parameters
		// of the surface created.
		glfwWindowHint(GLFW_RESIZABLE,			GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED,			GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUSED,			GLFW_TRUE);
		glfwWindowHint(GLFW_AUTO_ICONIFY,		GLFW_TRUE);
		glfwWindowHint(GLFW_FLOATING,			GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED,			GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE,			GLFW_FALSE);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR,	GLFW_FALSE);
		glfwWindowHint(GLFW_CENTER_CURSOR,		GLFW_TRUE);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW,		GLFW_TRUE);
		glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
		glfwWindowHint(GLFW_REFRESH_RATE,		GLFW_DONT_CARE);

		// Create OS window handle.
		GLFWwindow* lDummyWindow = glfwCreateWindow(640, 480, "Dummy Window", NULL, NULL);

		// Reset hints to insure no lingering parameters.
		glfwDefaultWindowHints();

		// Since this code only relies on an instance, maybe query in device class?
		VkSurfaceKHR lDummySurface = VK_NULL_HANDLE;
		Result = glfwCreateWindowSurface(aInstance, lDummyWindow, NULL, &lDummySurface);

		// Check needed objects are properly allocated, otherwise abort.
		if ((this->QueueFamilyProperty == NULL) || (this->QueueFamilyCapability == NULL) || (this->QueueFamilySupportCount == NULL) || (lDummyWindow == NULL) || (lDummySurface == VK_NULL_HANDLE)) {
			free(this->QueueFamilyProperty);
			this->QueueFamilyProperty = NULL;
			free(this->QueueFamilyCapability);
			this->QueueFamilyCapability = NULL;
			free(this->QueueFamilySupportCount);
			this->QueueFamilySupportCount = NULL;
			vkDestroySurfaceKHR(aInstance, lDummySurface, NULL);
			lDummySurface = VK_NULL_HANDLE;
			glfwDestroyWindow(lDummyWindow);
			lDummyWindow = NULL;
			return;
		}

		// Get extensions if there are any.
		if (this->Extension != NULL) {
			Result = vkEnumerateDeviceExtensionProperties(this->Handle, NULL, &this->ExtensionCount, this->Extension);
		}

		// Get Queue Family Information.
		vkGetPhysicalDeviceQueueFamilyProperties(this->Handle, &this->QueueFamilyCount, this->QueueFamilyProperty);

		for (uint32_t i = 0; i < this->QueueFamilyCount; i++) {
			this->QueueFamilySupportCount[i] = 0;

			this->QueueFamilyCapability[i].Support = 0;
			this->QueueFamilyCapability[i].Flags = this->QueueFamilyProperty[i].queueFlags;
			if ((this->QueueFamilyProperty[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) == VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) {
				this->QueueFamilyCapability[i].Support |= qfs::TRANSFER;
				this->QueueFamilyCapability[i].isTransferSupported = true;
				this->QueueFamilySupportCount[i] += 1;
			}
			if ((this->QueueFamilyProperty[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) == VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) {
				this->QueueFamilyCapability[i].Support |= qfs::COMPUTE;
				this->QueueFamilyCapability[i].isComputeSupported = true;
				this->QueueFamilySupportCount[i] += 1;
			}
			if ((this->QueueFamilyProperty[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) == VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) {
				this->QueueFamilyCapability[i].Support |= qfs::GRAPHICS;
				this->QueueFamilyCapability[i].isGraphicsSupported = true;
				this->QueueFamilySupportCount[i] += 1;
			}

			// TODO: Make sure "VK_KHR_surface" is a loaded extension in Instance.
			VkBool32 PresentSupport;
			Result = vkGetPhysicalDeviceSurfaceSupportKHR(aPhysicalDevice, i, lDummySurface, &PresentSupport);
			if (PresentSupport == VK_TRUE) {
				this->QueueFamilyCapability[i].Support |= qfs::PRESENT;
				this->QueueFamilyCapability[i].isPresentSupported = true;
				this->QueueFamilySupportCount[i] += 1;
			}
			else {
				this->QueueFamilyCapability[i].isPresentSupported = false;
			}

		}

		vkGetPhysicalDeviceProperties(this->Handle, &this->Properties);
		vkGetPhysicalDeviceFeatures(this->Handle, &this->Features);

		// Clear up Dummy stuff.
		vkDestroySurfaceKHR(aInstance, lDummySurface, NULL);
		lDummySurface = VK_NULL_HANDLE;
		glfwDestroyWindow(lDummyWindow);
		lDummyWindow = NULL;
	}

	device::~device() {
		free(this->QueueFamilyProperty);
		this->QueueFamilyProperty = NULL;
		free(this->QueueFamilyCapability);
		this->QueueFamilyCapability = NULL;
		free(this->QueueFamilySupportCount);
		this->QueueFamilySupportCount = NULL;
		free(this->Extension);
		this->Extension = NULL;
	}

	bool device::is_extension_list_supported(uint32_t aExtensionCount, const char** aExtensionList) const {
		// Checks if ExtensionList is a subset of existing extensions.
		bool isSupported = true;
		for (uint32_t i = 0; i < aExtensionCount; i++) {
			size_t L1 = strlen(aExtensionList[i]);
			bool isExtSupported = false;
			// Iterate through suppported extensions.
			for (uint32_t j = 0; j < this->ExtensionCount; j++) {
				size_t L2 = strlen(this->Extension[j].extensionName);
				if (L1 == L2) {
					// If support is found, the set isExtSupported.
					if (memcmp(aExtensionList[i], this->Extension[j].extensionName, L1 * sizeof(char)) == 0) {
						isExtSupported = true;
					}
				}
			}
			// Is equivalent to.
			// isSupported = (isExt1Supported) && (isExt2Supported) && ... (isExtNSupported);
			isSupported &= isExtSupported;
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

	VkPhysicalDeviceMemoryProperties device::get_memory_properties() const {
		VkPhysicalDeviceMemoryProperties temp;
		vkGetPhysicalDeviceMemoryProperties(this->Handle, &temp);
		return temp;
	}

	const VkExtensionProperties* device::get_extensions(uint32_t* aExtensionCount) const {
		*aExtensionCount = this->ExtensionCount;
		return this->Extension;
	}

	const VkQueueFamilyProperties* device::get_queue_families(uint32_t* aQueueFamilyCount) const {
		*aQueueFamilyCount = this->QueueFamilyCount;
		return this->QueueFamilyProperty;
	}

	const device::queue_family_capability* device::get_capability(uint32_t* aQueueFamilyCount) const {
		*aQueueFamilyCount = this->QueueFamilyCount;
		return this->QueueFamilyCapability;
	}

	bool device::available(unsigned int aQSB) const {
		for (uint32_t i = 0; i < this->QueueFamilyCount; i++) {
			if ((this->QueueFamilyCapability[i].Support & aQSB) == aQSB) {
				return true;
			}
		}
		return false;
	}

	int device::qfi(unsigned int aQSB) const {
		int temp = -1;
		uint32_t MinimumSupportCount = 10;
		for (uint32_t i = 0; i < this->QueueFamilyCount; i++) {
			if ((MinimumSupportCount > this->QueueFamilySupportCount[i]) && ((this->QueueFamilyCapability[i].Support & aQSB) == aQSB)) {
				MinimumSupportCount = this->QueueFamilySupportCount[i];
				temp = (int)i;
			}
		}
		return temp;
	}

	VkInstance device::inst() {
		return this->ParentInstance;
	}

	VkPhysicalDevice device::handle() {
		return this->Handle;
	}

}