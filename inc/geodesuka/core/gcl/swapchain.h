#pragma once
#ifndef GEODESUKA_CORE_GCL_SWAPCHAIN_H
#define GEODESUKA_CORE_GCL_SWAPCHAIN_H

#include <vector>

#include "texture.h"

#include "context.h"

namespace geodesuka::core::gcl {

	class swapchain {
	public:

		friend class object::system_window;

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
			int ColorSpace;
			int Usage;
			int CompositeAlpha;
			int PresentMode;
			bool Clipped;

			prop();
		};

		std::vector<gcl::texture*> Texture;

		swapchain(context* aContext, VkSurfaceKHR aSurface, prop aProperty, int aPixelFormat, int aWidth, int aHeight, swapchain* aOldSwapchain);
		~swapchain();

		VkSwapchainKHR handle();

	private:

		context* Context;

		VkSwapchainCreateInfoKHR CreateInfo{};
		VkSwapchainKHR Handle;

	};

}

#endif // !GEODESUKA_CORE_GCL_SWAPCHAIN_H
