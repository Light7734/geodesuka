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

		enum colorspace {
			SRGB_NONLINEAR			= 0,
			DISPLAY_P3_NONLINEAR	= 1000104001,
			EXTENDED_SRGB_LINEAR	= 1000104002,
			DISPLAY_P3_LINEAR		= 1000104003,
			DCI_P3_NONLINEAR		= 1000104004,
			BT709_LINEAR			= 1000104005,
			BT709_NONLINEAR			= 1000104006,
			BT2020_LINEAR			= 1000104007,
			HDR10_ST2084			= 1000104008,
			DOLBYVISION				= 1000104009,
			HDR10_HLG				= 1000104010,
			ADOBERGB_LINEAR			= 1000104011,
			ADOBERGB_NONLINEAR		= 1000104012,
			PASS_THROUGH			= 1000104013,
			EXTENDED_SRGB_NONLINEAR = 1000104014,
			DISPLAY_NATIVE_AMD		= 1000213000,
		};

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
