#pragma once
#ifndef GEODESUKA_CORE_GCL_IMAGE_H
#define GEODESUKA_CORE_GCL_IMAGE_H

#include "../util/variable.h"

#include "device.h"
#include "context.h"

#include "buffer.h"

namespace geodesuka::core::object {
	class system_window;
}

namespace geodesuka::core::gcl {

	class image {
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

		enum class layout {
			UNDEFINED									= 0,
			GENERAL										= 1,
			COLOR_ATTACHMENT							= 2,
			DEPTH_STENCIL_ATTACHMENT					= 3,
			DEPTH_STENCIL_READ_ONLY						= 4,
			SHADER_READ_ONLY							= 5,
			TRANSFER_SRC								= 6,
			TRANSFER_DST								= 7,
			PREINITIALIZED								= 8,
			DEPTH_READ_ONLY_STENCIL_ATTACHMENT			= 1000117000,
			DEPTH_ATTACHMENT_STENCIL_READ_ONLY			= 1000117001,
			DEPTH_ATTACHMENT							= 1000241000,
			DEPTH_READ_ONLY								= 1000241001,
			STENCIL_ATTACHMENT							= 1000241002,
			STENCIL_READ_ONLY							= 1000241003,
			PRESENT_SRC									= 1000001002,
			SHARED_PRESENT								= 1000111000,
			FRAGMENT_DENSITY_MAP						= 1000218000,
			FRAGMENT_SHADING_RATE_ATTACHMENT			= 1000164003,
			READ_ONLY									= 1000314000,
			ATTACHMENT									= 1000314001,
		};

		enum class loadop {
			LOAD		= 0,
			CLEAR		= 1,
			DONT_CARE	= 2
		};

		enum class storeop {
			STORE		= 0,
			DONT_CARE	= 1
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

		image();
		image(context *aContext, int aMemoryType, prop aProperty, int aFormat, int aWidth, int aHeight, int aDepth, void *aTextureData);
		~image();
		
		// Copy Constructor.
		image(image& aInput);
		// Move Constructor.
		image(image&& aInput) noexcept;
		// Copy Assignment.
		image& operator=(image& aRhs);
		// Move Assignment.
		image& operator=(image&& aRhs) noexcept;

		// Each of these operators produces OTS Command Buffers.

		// Copies the contents and mip levels of the right, to the left.
		VkCommandBuffer operator<<(image& aRhs);
		// Copies the contents and mip levels of the left, to the right.
		VkCommandBuffer operator>>(image& aRhs);
		// Copies the contents of the first buffer to the first mip level of the texture.
		VkCommandBuffer operator<<(buffer& aRhs);
		// Copies the contents of the first mip level to the buffer on the right.
		VkCommandBuffer operator>>(buffer& aRhs);
		// Produces OTS Graphics command to generate mip maps from base level.
		VkCommandBuffer generate_mipmaps(VkFilter aFilter);
		// Transitions layout of all mip levels and array layers to proposed layout.
		VkCommandBuffer transition(VkImageLayout aNewLayout);
		// Transitions layout of selected MipIndex, and ArrayIndex to proposed layout.
		VkCommandBuffer transition(uint32_t MipIndex, uint32_t ArrayIndex, VkImageLayout aNewLayout);

		// MipIndex, ArrayLayer

		// Generates image views from texture instance. (YOU ARE RESPONSIBLE FOR DESTROYING VIEWS)
		VkImageView view();
		//VkImageView view(VkImageViewType aType, VkImageSubresourceRange aRange);
		//VkImageView view(VkImageViewType aType, VkComponentMapping aComponentMapping, VkImageSubresourceRange aRange);

		// Insure that all MipLevels and ArrayLayers have the same image layout before using a description.
		VkAttachmentDescription description(loadop aLoadOp, storeop aStoreOp, loadop aStencilLoadOp, storeop aStencilStoreOp, layout aInitialLayout, layout aFinalLayout);

		//VkSampler sampler();

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

#endif // !GEODESUKA_CORE_GCL_IMAGE_H