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

		friend class buffer;
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
			int ArrayLayerCount;
			int SampleCounts;
			int Tiling;
			int Usage;

			prop();
		};

		// Will yield the number of bits per pixel.
		static size_t bytesperpixel(VkFormat aFormat);
		static size_t bitsperpixel(VkFormat aFormat);

		texture();
		texture(context *aContext, int aMemoryType, prop aProperty, int aFormat, int aWidth, int aHeight, int aDepth, void *aTextureData);
		~texture();
		
		// Copy Constructor.
		texture(texture& aInput);
		// Move Constructor.
		texture(texture&& aInput) noexcept;
		// Copy Assignment.
		texture& operator=(texture& aRhs);
		// Move Assignment.
		texture& operator=(texture&& aRhs) noexcept;

		// Each of these operators produces OTS Command Buffers.

		// Copies the contents and mip levels of the right, to the left.
		VkCommandBuffer operator<<(texture& aRhs);
		// Copies the contents and mip levels of the left, to the right.
		VkCommandBuffer operator>>(texture& aRhs);
		// Copies the contents of the first buffer to the first mip level of the texture.
		VkCommandBuffer operator<<(buffer& aRhs);
		// Copies the contents of the first mip level to the buffer on the right.
		VkCommandBuffer operator>>(buffer& aRhs);
		// Produces OTS Graphics command to generate mip maps from base level.
		VkCommandBuffer generate_mipmaps(VkFilter aFilter);

		// Generates image views from texture instance.
		VkImageView view(VkImageViewType aType, VkImageSubresourceRange aRange);
		VkImageView view(VkImageViewType aType, VkComponentMapping aComponentMapping, VkImageSubresourceRange aRange);
		void destroy_view(VkImageView aImageView);

	private:

		context* Context;
		VkImageCreateInfo CreateInfo{};
		VkImage Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;
		int MemoryType;
		size_t BytesPerPixel;
		size_t MemorySize; // Size of the image

		VkImageLayout** Layout; // Keeps track of mip level and element image layouts.
		VkExtent3D* MipExtent; // TODO: Fill out MipExtent for easier blitting.

		uint32_t miplevelcalc(VkImageType aImageType, VkExtent3D aExtent);
		void pmclearall();

	};

}

#endif // !GEODESUKA_CORE_GCL_TEXTURE_H