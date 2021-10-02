#pragma once
#ifndef GEODESUKA_CORE_GCL_TEXTURE_H
#define GEODESUKA_CORE_GCL_TEXTURE_H

#include "../io/file.h"
#include "../io/image.h"

#include "../util/variable.h"

#include "device.h"
#include "context.h"

#include "buffer.h"

namespace geodesuka::core::object {
	class system_window;
}

namespace geodesuka::core::gcl {

	class texture {
	public:

		friend class object::system_window;

		enum tiling {
			OPTIMAL = 0,
			LINEAR = 1,
		};

		enum usage {
			TRANSFER_SRC_BIT				= 0x00000001,
			TRANSFER_DST_BIT				= 0x00000002,
			SAMPLED_BIT						= 0x00000004,
			STORAGE_BIT						= 0x00000008,
			COLOR_ATTACHMENT_BIT			= 0x00000010,
			DEPTH_STENCIL_ATTACHMENT_BIT	= 0x00000020,
			TRANSIENT_ATTACHMENT_BIT		= 0x00000040,
			INPUT_ATTACHMENT_BIT			= 0x00000080
		};



		//texture(gcl::context* aContext, VkFormat aFormat, uint32_t aWidth, uint32_t aHeight, uint32_t aDepth);
		~texture();

		VkImageView get_view();

	private:

		gcl::context* Context;


		VkImageCreateInfo CreateInfo{};
		VkImage Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;


	};

}

#endif // !GEODESUKA_CORE_GCL_TEXTURE_H