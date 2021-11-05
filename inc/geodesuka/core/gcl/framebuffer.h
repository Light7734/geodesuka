#ifndef GEODESUKA_CORE_GCL_FRAMEBUFFER_H
#define GEODESUKA_CORE_GCL_FRAMEBUFFER_H

#include <vulkan/vulkan.h>

#include <GLFW/glfw3.h>

#include "../math.h"

#include "device.h"
#include "context.h"
// Holds no data, only references.

namespace geodesuka::core::gcl {

	class framebuffer {
	public:

		// Enums go here

		struct prop {
			int ColorBits[4];
			int DepthBits;
			int StencilBits;
			int AccumColorBits[4];
			int AuxBuffers;
			int Stereo;
			int DoubleBuffer;
			int Transparent;
			int Samples;
			int sRGBCapable;

			uint32_t Count;
			VkFormat Format;
			VkColorSpaceKHR ColorSpace;
			VkExtent2D Extent2D;
			VkImageUsageFlags Usage;
			//uint32_t Layers; // Per Image

			// Default Contstructor
			prop();
		};

		math::natural2 Resolution;

		context* Context;
		struct prop Property;

		framebuffer();
		framebuffer(context* aDeviceContext);

		~framebuffer();

		//int set_output(const variable& Target, const texture& Variable);

	private:

		VkFramebufferCreateInfo CreateInfo;
		VkFramebuffer Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_FRAMEBUFFER_H
