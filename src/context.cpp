#include <geodesuka/core/gcl/context.h>

#include <cstdlib>

#include <GLFW/glfw3.h>

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

		// These public queues will be loaded.
		this->Transfer	= VK_NULL_HANDLE;
		this->Compute	= VK_NULL_HANDLE;
		this->Graphics	= VK_NULL_HANDLE;
		this->Present	= VK_NULL_HANDLE;

		this->QueueCreateInfoCount = 0;
		this->QueueCreateInfo = NULL;
		this->QueueFamilyPriority = NULL;

		this->Device = aDevice;
		this->Handle = VK_NULL_HANDLE;

		// -------------------- Context Creation -------------------- //

		// Used for early termination conditions.
		VkResult Result = VkResult::VK_SUCCESS;

		// TODO: For future reference with cross platform compatibility, insure
		// that a check is done here with extension "VK_KHR_surface".

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
		GLFWwindow* DummyWindow = glfwCreateWindow(640, 480, "Dummy Window", NULL, NULL);

		// Reset hints to insure no lingering parameters.
		glfwDefaultWindowHints();

		// Now create dummy window surface.
		VkSurfaceKHR DummySurface = VK_NULL_HANDLE;
		Result = glfwCreateWindowSurface(this->Device->inst(), DummyWindow, NULL, &DummySurface);

		// Get the queue families associated with creation physical device.
		uint32_t QueueFamilyCount = 0;
		const VkQueueFamilyProperties* QueueFamily = aDevice->get_queue_families(&QueueFamilyCount);

		// Ideally, I would like to seperate each of the queues for their own specific
		// purposes, but if push comes to shove, they can all referece the exact same queue
		// handle.

		// Number of Queue Families with support.
		// {T, C, G, P}
		bool SupportExists[4] = { false, false, false, false };
		uint32_t SupportCount[4] = { 0, 0, 0, 0 };

		// Iterate through queue family and check support.
		for (uint32_t i = 0; i < QueueFamilyCount; i++) {
			// Checks for Transfer, Compute, and Graphics.
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) == VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) {
				SupportCount[0] += 1;
				SupportExists[0] = true;
			}
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) == VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) {
				SupportCount[1] += 1;
				SupportExists[1] = true;
			}
			if ((QueueFamily[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) == VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) {
				SupportCount[2] += 1;
				SupportExists[2] = true;
			}

			// TODO: Make sure "VK_KHR_surface" is a loaded extension in Instance.
			VkBool32 PresentSupport;
			Result = vkGetPhysicalDeviceSurfaceSupportKHR(this->Device->handle(), i, DummySurface, &PresentSupport);
			if (PresentSupport) {
				SupportCount[3] += 1;
				SupportExists[3] = true;
			}
		}

		// Queue create info selection metrics based on device...

		

		// TODO: Change this to reference device features from actual class.
		this->EnabledFeatures = this->Device->get_features();

		// Fill out logical device create info.
		this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		this->CreateInfo.pNext						= NULL;
		this->CreateInfo.flags						= 0;
		this->CreateInfo.queueCreateInfoCount		= this->QueueCreateInfoCount;
		this->CreateInfo.pQueueCreateInfos			= this->QueueCreateInfo;
		this->CreateInfo.enabledLayerCount			= 0;
		this->CreateInfo.ppEnabledLayerNames		= NULL;
		if (this->Device->is_extension_list_supported(aExtensionCount, aExtensionList)) {
			// If extensions are supported, loaded into context creation.
			this->CreateInfo.enabledExtensionCount		= aExtensionCount;
			this->CreateInfo.ppEnabledExtensionNames	= aExtensionList;
		}
		else {
			// TODO: Maybe change this to load only supported subset?
			this->CreateInfo.enabledExtensionCount		= 0;
			this->CreateInfo.ppEnabledExtensionNames	= NULL;
		}
		this->CreateInfo.pEnabledFeatures			= &this->EnabledFeatures;

		// Create Device and check errors.
		Result = vkCreateDevice(this->Device->handle(), &this->CreateInfo, NULL, &this->Handle);

		//vkGetDeviceQueue(this->Handle, 0, 0, &Q);
		

		// -------------------- Context Creation -------------------- //

		// Old code, no longer in use. New metrics are used to created queues.
		// Old method created all available queues for respective queue families.

		/*
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
		*/
	}

	context::~context() {
		vkDestroyDevice(this->Handle, NULL); this->Handle = VK_NULL_HANDLE;

		this->Device = nullptr;

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
		return this->Device->inst();
	}

	device* context::parent() {
		return this->Device;
	}

	VkDevice context::handle() {
		return this->Handle;
	}

}
