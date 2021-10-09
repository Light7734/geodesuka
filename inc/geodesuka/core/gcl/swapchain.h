#pragma once
#ifndef GEODESUKA_CORE_GCL_SWAPCHAIN_H
#define GEODESUKA_CORE_GCL_SWAPCHAIN_H

#include <vector>

#include "texture.h"

#include "context.h"

namespace geodesuka::core::gcl {

	class swapchain {
	public:

		enum composite {
			ALPHA_OPAQUE			= 0x00000001,
			ALPHA_PRE_MULTIPLIED	= 0x00000002,
			ALPHA_POST_MULTIPLIED	= 0x00000004,
			ALPHA_INHERIT			= 0x00000008,
		};

		enum mode {
			IMMEDIATE		= 0,
			MAILBOX			= 1,
			FIFO			= 2,
			FIFO_RELAXED	= 3
		};

		struct prop {
			int Count;
			int Format;
			int ColorSpace;
			//VkExtent2D Resolution;
			//int Layers;
			int Usage;
			int CompositeAlpha;
			int PresentMode;
			bool Clipped;

			prop();
		};

		swapchain(context* aContext, VkSurfaceKHR aSurface, prop aProperty, uint32_t aWidth, uint32_t aHeight, swapchain* aOldSwapchain);
		~swapchain();

	private:

		context* Context;

		std::vector<gcl::texture*> Texture;

		VkSwapchainCreateInfoKHR CreateInfo{};
		VkSwapchainKHR Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_SWAPCHAIN_H
