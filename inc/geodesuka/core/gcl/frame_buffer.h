#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "../gcl/gcl.h"
#include "../math.h"

#include "device.h"
#include "device_context.h"
#include "context.h"
// Holds no data, only references.

namespace geodesuka {
	namespace core {
		namespace gcl {

			class frame_buffer {
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

				device_context* Context;
				struct prop Property;

				frame_buffer();
				frame_buffer(device_context* aDeviceContext);
				~frame_buffer();

				//int set_output(const variable& Target, const texture& Variable);

			private:

				VkFramebufferCreateInfo CreateInfo;
				VkFramebuffer Handle;

			};

		}
	}
}

#endif // !FRAME_BUFFER_H