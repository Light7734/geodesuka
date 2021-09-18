#pragma once
#ifndef GEODESUKA_CORE_GCL_TEXTURE_H
#define GEODESUKA_CORE_GCL_TEXTURE_H

#include "../io/file.h"
#include "../io/image.h"

#include "../util/variable.h"

#include "device.h"
#include "context.h"

namespace geodesuka {
	namespace core {

		namespace object {
			class system_window;
		}

		namespace gcl {

			class texture {
			public:
				
				// How do I make a texture useful in a graphics pipeline.

				friend class object::system_window;

				// Holds most recent error code.
				VkResult ErrorCode;

				// Load raw data into texture.
				//texture(device_context* aDeviceContext, )

				texture(context* aDeviceContext, io::file* aImage);
				//texture(device_context* aDeviceContext, VkFormat aFormat, math::natural aGridSize);
				//texture(device_context* aDeviceContext, VkFormat aFormat, math::natural2 aGridSize);
				texture(context *aDeviceContext, VkFormat aFormat, math::natural3 aGridSize);
				~texture();

			private:

				// Data Handles
				object::system_window *ParentSW;
				context* ParentDC;
				VkImage Handle;

				// Parameters of texture.
				VkImageCreateInfo CreateInfo{};

				// Used for window swap chain. (Should not be public API).
				texture(object::system_window* aSystemWindow, context* aDeviceContext, VkImage aImageHandle, VkImageCreateInfo aCreateInfo);

				VkExtent3D convert_to_extent(math::natural aX, math::natural aY, math::natural aZ);

			};

		}
	}
}

#endif // !GEODESUKA_CORE_GCL_TEXTURE_H