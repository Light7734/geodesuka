#pragma once
#ifndef GEODESUKA_CORE_GCL_SWAPCHAIN_H
#define GEODESUKA_CORE_GCL_SWAPCHAIN_H

#include <vector>

#include "texture.h"

#include "context.h"

namespace geodesuka::core::gcl {

	class swapchain {
	public:

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
			VkExtent2D Resolution;
			//int Layers;
			int Usage;
			int CompositeAlpha;
			int PresentMode;
			bool Clipped;
		};

		swapchain(context* aContext, VkSurfaceKHR aSurface, prop aProperty, swapchain* aOldSwapchain);
		~swapchain();

	private:

		std::vector<gcl::texture*> Texture;

		VkSwapchainCreateInfoKHR CreateInfo{};
		VkSwapchainKHR Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_SWAPCHAIN_H
