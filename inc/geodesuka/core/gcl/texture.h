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

		enum sample {
			COUNT_1		= 0x00000001,
			COUNT_2		= 0x00000002,
			COUNT_4		= 0x00000004,
			COUNT_8		= 0x00000008,
			COUNT_16	= 0x00000010,
			COUNT_32	= 0x00000020,
			COUNT_64	= 0x00000040
		};

		enum tiling {
			OPTIMAL		= 0,
			LINEAR		= 1,
		};

		enum usage {
			TRANSFER_SRC				= 0x00000001,
			TRANSFER_DST				= 0x00000002,
			SAMPLED 					= 0x00000004,
			STORAGE						= 0x00000008,
			COLOR_ATTACHMENT			= 0x00000010,
			DEPTH_STENCIL_ATTACHMENT	= 0x00000020,
			TRANSIENT_ATTACHMENT		= 0x00000040,
			INPUT_ATTACHMENT			= 0x00000080
		};

		struct prop {
			//int MipLevelCount;
			int ArrayLayerCount;
			int SampleCounts;
			int Tiling;
			int Usage;
			//int InitialLayout;

			prop();
		};

		// Will yield the number of bits per pixel.
		static size_t bpp(VkFormat aFormat);
		static size_t bitsperpixel(VkFormat aFormat);

		texture();
		texture(context *aContext, int aMemoryType, prop aProperty, int aFormat, int aWidth, int aHeight, int aDepth, void *aTextureData);
		~texture();
		
		// Copy Constructor.
		texture(texture& aInput);
		// Move Constructor.
		texture(texture&& aInput);
		// Copy Assignment.
		texture& operator=(texture& aRhs);
		// Move Assignment.
		texture& operator=(texture&& aRhs);

		// 

	private:

		context* Context;
		VkImageCreateInfo CreateInfo{};
		VkImage Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;

		VkImageLayout CurrentImageLayout;
		int MemoryType;
		int BytesPerPixel;

		// Will have dimensions of MipLevel - 1.
		VkExtent3D* MipExtent;


		uint32_t miplevelcalc(VkImageType aImageType, VkExtent3D aExtent);

	};

}

#endif // !GEODESUKA_CORE_GCL_TEXTURE_H