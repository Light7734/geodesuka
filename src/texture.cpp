#include <geodesuka/core/gcl/texture.h>

// Standard C Libs
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

#include <geodesuka/core/math.h>

#include <geodesuka/core/util/variable.h>

//#include <geodesuka/core/object.h>
//#include <geodesuka/core/object/system_window.h>

namespace geodesuka::core::gcl {

	texture::prop::prop() {
		//this->MipLevelCount			= 1;
		this->ArrayLayerCount	= 1;
		this->SampleCounts		= sample::COUNT_1;
		this->Tiling			= tiling::OPTIMAL;
		this->Usage				= 0;
	}

	texture::texture() {
		this->Context		= nullptr;
		this->Handle		= VK_NULL_HANDLE;
		this->MemoryHandle	= VK_NULL_HANDLE;
	}

	texture::texture(context* aContext, int aMemoryType, prop aProperty, int aFormat, int aWidth, int aHeight, int aDepth, void* aTextureData) {
		if (aContext == nullptr) return;
		this->Context = aContext;

		VkResult Result = VkResult::VK_SUCCESS;
		this->CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		this->CreateInfo.pNext					= NULL;
		this->CreateInfo.flags					= 0;
		if ((aWidth > 1) && (aHeight > 1) && (aDepth > 1)) {
			this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_3D;
		}
		else if ((aWidth > 1) && (aHeight > 1)) {
			this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_2D;
		}
		else if (aWidth > 1) {
			this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_1D;
		}
		else {
			return;
		}
		this->CreateInfo.format					= (VkFormat)aFormat;
		switch (this->CreateInfo.imageType) {
		default:
			return;
		case VK_IMAGE_TYPE_1D:
			this->CreateInfo.extent = { (uint32_t)aWidth, 1u, 1u };
			break;
		case VK_IMAGE_TYPE_2D:
			this->CreateInfo.extent = { (uint32_t)aWidth, (uint32_t)aHeight, 1u };
			break;
		case VK_IMAGE_TYPE_3D:
			this->CreateInfo.extent = { (uint32_t)aWidth, (uint32_t)aHeight, (uint32_t)aDepth };
			break;
		}
		this->CreateInfo.mipLevels				= this->miplevelcalc(this->CreateInfo.imageType, this->CreateInfo.extent);
		this->CreateInfo.arrayLayers			= aProperty.ArrayLayerCount;
		this->CreateInfo.samples				= (VkSampleCountFlagBits)aProperty.SampleCounts;
		this->CreateInfo.tiling					= (VkImageTiling)aProperty.Tiling;
		this->CreateInfo.usage					= aProperty.Usage | texture::usage::TRANSFER_SRC | texture::usage::TRANSFER_DST; // Enable Transfer
		this->CreateInfo.sharingMode			= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
		this->CreateInfo.queueFamilyIndexCount	= 0;
		this->CreateInfo.pQueueFamilyIndices	= NULL;
		this->CreateInfo.initialLayout			= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;

		this->BytesPerPixel = this->bytesperpixel(this->CreateInfo.format);
		// So apparently mip levels can have their own image layouts.
		// and possibly elements of a texture array.


		Result = vkCreateImage(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);

		// Allocate device memory for image handle
		if (Result == VkResult::VK_SUCCESS) {
			VkMemoryRequirements MemoryRequirements;
			vkGetImageMemoryRequirements(this->Context->handle(), this->Handle, &MemoryRequirements);

			VkPhysicalDeviceMemoryProperties MemoryProperties = this->Context->parent()->get_memory_properties();

			VkMemoryAllocateInfo;

			this->AllocateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			this->AllocateInfo.pNext = NULL;
			this->AllocateInfo.allocationSize = MemoryRequirements.size;

			// First search for exact memory type.
			this->MemoryType = -1;
			for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++) {
				if (((MemoryRequirements.memoryTypeBits & (1 << i)) >> i) && (MemoryProperties.memoryTypes[i].propertyFlags == aMemoryType)) {
					this->AllocateInfo.memoryTypeIndex = i;
					this->MemoryType = aMemoryType;
					break;
				}
			}

			// If exact memory type doesn't exist, search for approximate type.
			if (this->MemoryType == -1) {
				for (uint32_t i = 0; i < MemoryProperties.memoryTypeCount; i++) {
					if (((MemoryRequirements.memoryTypeBits & (1 << i)) >> i) && ((MemoryProperties.memoryTypes[i].propertyFlags & aMemoryType) == aMemoryType)) {
						this->AllocateInfo.memoryTypeIndex = i;
						this->MemoryType = aMemoryType;
						break;
					}
				}
			}

			if (this->MemoryType == -1) {
				vkDestroyImage(this->Context->handle(), this->Handle, NULL);
				this->Handle = VK_NULL_HANDLE;
				return;
			}

			Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
		}

		// Bind image handle to memory.
		if (Result == VkResult::VK_SUCCESS) {
			Result = vkBindImageMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
		}

		// TODO: Fix later for failed allocations.
		// All initialized layouts is above.
		// i = mip level, and j = array level;
		this->Layout = (VkImageLayout**)malloc(this->CreateInfo.mipLevels * sizeof(VkImageLayout*));
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
			this->Layout[i] = (VkImageLayout*)malloc(this->CreateInfo.arrayLayers * sizeof(VkImageLayout));
			for (uint32_t j = 0; j < this->CreateInfo.arrayLayers; j++) {
				this->Layout[i][j] = this->CreateInfo.initialLayout;
			}
		}

		// Mip Level resolutions.
		this->MipExtent = (VkExtent3D*)malloc(this->CreateInfo.mipLevels * sizeof(VkExtent3D));
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
			switch (this->CreateInfo.imageType) {
			default:
				return;
			case VK_IMAGE_TYPE_1D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), 1u, 1u };
				break;
			case VK_IMAGE_TYPE_2D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), (this->CreateInfo.extent.height >> i), 1u };
				break;
			case VK_IMAGE_TYPE_3D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), (this->CreateInfo.extent.height >> i), (this->CreateInfo.extent.depth >> i) };
				break;
			}
		}

	
		// Create staging buffer and prepare for transfer.
		buffer StagingBuffer(
			Context,
			device::HOST_VISIBLE | device::HOST_COHERENT,
			buffer::TRANSFER_SRC | buffer::TRANSFER_DST,
			this->CreateInfo.arrayLayers * this->CreateInfo.extent.width * this->CreateInfo.extent.height * this->CreateInfo.extent.depth * this->BytesPerPixel,
			aTextureData
		);

		// Disgusting code, tmi.
		VkSubmitInfo Submission[2] = { {}, {} };
		VkCommandBufferBeginInfo BeginInfo[2] = { {}, {} };
		VkCommandBuffer CommandBuffer[2] = { VK_NULL_HANDLE, VK_NULL_HANDLE };
		VkSemaphoreCreateInfo SemaphoreCreateInfo{};
		VkSemaphore Semaphore = VK_NULL_HANDLE;
		VkPipelineStageFlags StageFlags = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT;
		VkFenceCreateInfo FenceCreateInfo{};
		VkFence Fence[2];
		VkImageMemoryBarrier Barrier{};
		VkBufferImageCopy BufferImageRegion{};

		// Transfer Submission.
		Submission[0].sType							= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		Submission[0].pNext							= NULL;
		Submission[0].waitSemaphoreCount			= 0;
		Submission[0].pWaitSemaphores				= NULL;
		Submission[0].pWaitDstStageMask				= 0;
		Submission[0].commandBufferCount			= 1;
		Submission[0].pCommandBuffers				= &CommandBuffer[0];
		Submission[0].signalSemaphoreCount			= 1;
		Submission[0].pSignalSemaphores				= &Semaphore;

		// Graphics Submission
		Submission[1].sType							= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		Submission[1].pNext							= NULL;
		Submission[1].waitSemaphoreCount			= 1;
		Submission[1].pWaitSemaphores				= &Semaphore;
		Submission[1].pWaitDstStageMask				= &StageFlags;
		Submission[1].commandBufferCount			= 1;
		Submission[1].pCommandBuffers				= &CommandBuffer[1];
		Submission[1].signalSemaphoreCount			= 0;
		Submission[1].pSignalSemaphores				= NULL;

		BeginInfo[0].sType							= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo[0].pNext							= NULL;
		BeginInfo[0].flags							= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo[0].pInheritanceInfo				= NULL;

		BeginInfo[1].sType							= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo[1].pNext							= NULL;
		BeginInfo[1].flags							= 0;// VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo[1].pInheritanceInfo				= NULL;

		SemaphoreCreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		SemaphoreCreateInfo.pNext					= NULL;
		SemaphoreCreateInfo.flags					= 0;

		FenceCreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		FenceCreateInfo.pNext						= NULL;
		FenceCreateInfo.flags						= 0;

		Barrier.sType								= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		Barrier.pNext								= NULL;
		Barrier.srcAccessMask						= 0;
		Barrier.dstAccessMask						= VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
		Barrier.oldLayout							= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		Barrier.newLayout							= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		Barrier.srcQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
		Barrier.dstQueueFamilyIndex					= VK_QUEUE_FAMILY_IGNORED;
		Barrier.image								= this->Handle;
		Barrier.subresourceRange.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
		Barrier.subresourceRange.baseMipLevel		= 0;
		Barrier.subresourceRange.levelCount			= 1;
		Barrier.subresourceRange.baseArrayLayer		= 0;
		Barrier.subresourceRange.layerCount			= this->CreateInfo.arrayLayers;
		// Track update to all elements.
		for (uint32_t i = 0; i < this->CreateInfo.arrayLayers; i++) {
			this->Layout[0][i] = Barrier.newLayout;
		}

		BufferImageRegion.bufferOffset						= 0;
		BufferImageRegion.bufferRowLength					= 0;
		BufferImageRegion.bufferImageHeight					= 0;
		BufferImageRegion.imageSubresource.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
		BufferImageRegion.imageSubresource.mipLevel			= 0;
		BufferImageRegion.imageSubresource.baseArrayLayer	= 0;
		BufferImageRegion.imageSubresource.layerCount		= this->CreateInfo.arrayLayers;
		BufferImageRegion.imageOffset						= { 0, 0, 0 };
		BufferImageRegion.imageExtent						= this->CreateInfo.extent;

		Result = vkCreateSemaphore(this->Context->handle(), &SemaphoreCreateInfo, NULL, &Semaphore);
		Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence[0]);
		Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence[1]);
		this->Context->create(context::TRANSFER_OTS, 1, &CommandBuffer[0]);
		this->Context->create(context::GRAPHICS, 1, &CommandBuffer[1]);
		// Check allocation results before commencing.
		
		// Staging Buffer transfer operations.
		Result = vkBeginCommandBuffer(CommandBuffer[0], &BeginInfo[0]);

		// Waits for nothing, to transfer to mip 0 image.
		vkCmdPipelineBarrier(
			CommandBuffer[0], 
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, 
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT, 
			0, 
			0, NULL,
			0, NULL, 
			1, &Barrier);
		vkCmdCopyBufferToImage(CommandBuffer[0], StagingBuffer.handle(), this->Handle, this->Layout[0][0], 1, &BufferImageRegion);

		Result = vkEndCommandBuffer(CommandBuffer[0]);

		// filling out this command buffer generates mip maps.
		Result = vkBeginCommandBuffer(CommandBuffer[1], &BeginInfo[1]);

		/*
		Generating Mipmaps.
		0 -> 1 -> 2 -> 3 -> 4 ... N
		D -> U -> U -> U -> U ... U
		S -> D -> U -> U -> U ... U
		S -> S -> D -> U -> U ... U
		*/

		// Generate Mip Level params to blit image.
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels - 1; i++) {


			VkImageMemoryBarrier BlitBarrier[2] = { {}, {} };
			VkImageBlit MipGen{};

			// Changes previous mip level from dst to src, for blitting.
			BlitBarrier[0].sType							= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			BlitBarrier[0].pNext							= NULL;
			BlitBarrier[0].srcAccessMask					= VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
			BlitBarrier[0].dstAccessMask					= VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT;
			BlitBarrier[0].oldLayout						= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			BlitBarrier[0].newLayout						= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			BlitBarrier[0].srcQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			BlitBarrier[0].dstQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			BlitBarrier[0].image							= this->Handle;
			BlitBarrier[0].subresourceRange.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			BlitBarrier[0].subresourceRange.baseMipLevel	= i;
			BlitBarrier[0].subresourceRange.levelCount		= 1;
			BlitBarrier[0].subresourceRange.baseArrayLayer	= 0;
			BlitBarrier[0].subresourceRange.layerCount		= this->CreateInfo.arrayLayers;
			for (uint32_t j = 0; j < this->CreateInfo.arrayLayers; j++) {
				this->Layout[i][j] = BlitBarrier[0].newLayout;
			}

			// Prepares next mip for writing
			BlitBarrier[1].sType							= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			BlitBarrier[1].pNext							= NULL;
			BlitBarrier[1].srcAccessMask					= 0;
			BlitBarrier[1].dstAccessMask					= VkAccessFlagBits::VK_ACCESS_TRANSFER_WRITE_BIT;
			BlitBarrier[1].oldLayout						= this->CreateInfo.initialLayout;
			BlitBarrier[1].newLayout						= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			BlitBarrier[1].srcQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			BlitBarrier[1].dstQueueFamilyIndex				= VK_QUEUE_FAMILY_IGNORED;
			BlitBarrier[1].image							= this->Handle;
			BlitBarrier[1].subresourceRange.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			BlitBarrier[1].subresourceRange.baseMipLevel	= i + 1;
			BlitBarrier[1].subresourceRange.levelCount		= 1;
			BlitBarrier[1].subresourceRange.baseArrayLayer	= 0;
			BlitBarrier[1].subresourceRange.layerCount		= this->CreateInfo.arrayLayers;
			for (uint32_t j = 0; j < this->CreateInfo.arrayLayers; j++) {
				this->Layout[i + 1][j] = BlitBarrier[1].newLayout;
			}

			// Uses bit shifts to generate mip maps.
			// Source Description.
			MipGen.srcSubresource.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			MipGen.srcSubresource.mipLevel			= i;
			MipGen.srcSubresource.baseArrayLayer	= 0;
			MipGen.srcSubresource.layerCount		= this->CreateInfo.arrayLayers;
			MipGen.srcOffsets[0] = { 0, 0, 0 };
			switch (this->CreateInfo.imageType) {
			default:
				return;
			case VK_IMAGE_TYPE_1D:
				MipGen.srcOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> i), 1, 1 };
				break;
			case VK_IMAGE_TYPE_2D:
				MipGen.srcOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> i), (int32_t)(this->CreateInfo.extent.height >> i), 1 };
				break;
			case VK_IMAGE_TYPE_3D:
				MipGen.srcOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> i), (int32_t)(this->CreateInfo.extent.height >> i), (int32_t)(this->CreateInfo.extent.depth >> i) };
				break;
			}

			// Destination Description.
			MipGen.dstSubresource.aspectMask		= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			MipGen.dstSubresource.mipLevel			= i + 1;
			MipGen.dstSubresource.baseArrayLayer	= 0;
			MipGen.dstSubresource.layerCount		= this->CreateInfo.arrayLayers;
			MipGen.dstOffsets[0] = { 0, 0, 0 };
			switch (this->CreateInfo.imageType) {
			default:
				return;
			case VK_IMAGE_TYPE_1D:
				MipGen.dstOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> (i + 1)), 1, 1 };
				break;
			case VK_IMAGE_TYPE_2D:
				MipGen.dstOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> (i + 1)), (int32_t)(this->CreateInfo.extent.height >> (i + 1)), 1 };
				break;
			case VK_IMAGE_TYPE_3D:
				MipGen.dstOffsets[1] = { (int32_t)(this->CreateInfo.extent.width >> (i + 1)), (int32_t)(this->CreateInfo.extent.height >> (i + 1)), (int32_t)(this->CreateInfo.extent.depth >> (i + 1)) };
				break;
			}

			vkCmdPipelineBarrier(
				CommandBuffer[1],
				VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
				VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
				0,
				0, NULL,
				0, NULL,
				2, BlitBarrier
			);

			vkCmdBlitImage(
				CommandBuffer[1],
				this->Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				this->Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1,
				&MipGen,
				VkFilter::VK_FILTER_NEAREST
			);

		}

		Result = vkEndCommandBuffer(CommandBuffer[1]);

		Result = this->Context->submit(device::qfs::TRANSFER, 1, &Submission[0], Fence[0]);
		Result = this->Context->submit(device::qfs::GRAPHICS, 1, &Submission[1], Fence[1]);
		//this->Context->submit(device::qfs::GRAPHICS, 1, &Submission, Fence);
		Result = vkWaitForFences(this->Context->handle(), 1, &Fence[1], VK_TRUE, UINT64_MAX);
		vkDestroyFence(this->Context->handle(), Fence[0], NULL);
		vkDestroyFence(this->Context->handle(), Fence[1], NULL);
		vkDestroySemaphore(this->Context->handle(), Semaphore, NULL);
		this->Context->destroy(context::TRANSFER_OTS, 1, &CommandBuffer[0]);
		this->Context->destroy(context::GRAPHICS, 1, &CommandBuffer[1]);

	}

	texture::~texture() {
		if (this->Layout != NULL) {
			for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
				free(this->Layout[i]); this->Layout[i] = NULL;
			}
		}
		free(this->Layout); this->Layout = NULL;
		free(this->MipExtent); this->MipExtent = NULL;
		if (this->Context != nullptr) {
			vkDestroyImage(this->Context->handle(), this->Handle, NULL);
			this->Handle = VK_NULL_HANDLE;
			vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
			this->MemoryHandle = VK_NULL_HANDLE;
		}
		this->Context = nullptr;
	}

	texture::texture(texture& aInput) {
		this->Context			= aInput.Context;
		this->CreateInfo		= aInput.CreateInfo;
		this->Handle			= VK_NULL_HANDLE;
		this->AllocateInfo		= aInput.AllocateInfo;
		this->MemoryHandle		= VK_NULL_HANDLE;

		this->BytesPerPixel		= aInput.BytesPerPixel;
		this->MemorySize		= aInput.MemorySize;
		this->MemoryType		= aInput.MemoryType;

		VkResult Result = VkResult::VK_SUCCESS;
		this->Layout = (VkImageLayout**)malloc(this->CreateInfo.mipLevels * sizeof(VkImageLayout*));
		this->MipExtent = (VkExtent3D*)malloc(this->CreateInfo.mipLevels * sizeof(VkExtent3D));
		Result = vkCreateImage(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);
		if (Result == VkResult::VK_SUCCESS) {
			Result = vkAllocateMemory(this->Context->handle(), &this->AllocateInfo, NULL, &this->MemoryHandle);
		}
		if (Result == VkResult::VK_SUCCESS) {
			Result = vkBindImageMemory(this->Context->handle(), this->Handle, this->MemoryHandle, 0);
		}

		// Check if allocation succeeded.
		if ((Result != VkResult::VK_SUCCESS) || (this->Layout == NULL) || (this->MipExtent == NULL)) return;

		// All initialized layouts is above.
		// i = mip level, and j = array level;
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
			this->Layout[i] = (VkImageLayout*)malloc(this->CreateInfo.arrayLayers * sizeof(VkImageLayout));
			for (uint32_t j = 0; j < this->CreateInfo.arrayLayers; j++) {
				this->Layout[i][j] = this->CreateInfo.initialLayout;
			}
		}

		// Mip Level resolutions.
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
			switch (this->CreateInfo.imageType) {
			default:
				return;
			case VK_IMAGE_TYPE_1D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), 1u, 1u };
				break;
			case VK_IMAGE_TYPE_2D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), (this->CreateInfo.extent.height >> i), 1u };
				break;
			case VK_IMAGE_TYPE_3D:
				this->MipExtent[i] = { (this->CreateInfo.extent.width >> i), (this->CreateInfo.extent.height >> i), (this->CreateInfo.extent.depth >> i) };
				break;
			}
		}

		VkSubmitInfo Submission{};
		VkCommandBufferBeginInfo BeginInfo{};
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;

		VkImageMemoryBarrier Barrier{};
		VkImageCopy Region{};

		VkFenceCreateInfo FenceCreateInfo{};
		VkFence Fence;

		Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		Submission.pNext					= NULL;
		Submission.waitSemaphoreCount		= 0;
		Submission.pWaitSemaphores			= NULL;
		Submission.pWaitDstStageMask		= NULL;
		Submission.commandBufferCount		= 1;
		Submission.pCommandBuffers			= &CommandBuffer;
		Submission.signalSemaphoreCount		= 0;
		Submission.pSignalSemaphores		= NULL;

		BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext						= NULL;
		BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo			= NULL;

		Barrier.sType						;
		Barrier.pNext						;
		Barrier.srcAccessMask				;
		Barrier.dstAccessMask				;
		Barrier.oldLayout					;
		Barrier.newLayout					;
		Barrier.srcQueueFamilyIndex			;
		Barrier.dstQueueFamilyIndex			;
		Barrier.image						;
		Barrier.subresourceRange			;


		this->Context->create(context::TRANSFER_OTS, 1, &CommandBuffer);
		Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);


		Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
		// Actual transfer operations.
		vkCmdPipelineBarrier(CommandBuffer,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			0,
			0, NULL,
			0, NULL,
			1, &Barrier
		);

		vkCmdCopyImage(CommandBuffer,
			aInput.Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			this->Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1, &Region
		);
		Result = vkEndCommandBuffer(CommandBuffer);

		this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
		Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);
		vkDestroyFence(this->Context->handle(), Fence, NULL);



	}

	texture::texture(texture&& aInput) {

	}

	texture& texture::operator=(texture& aRhs) {
		if (this == &aRhs) return *this;

		//VkResult Result = VkResult::VK_SUCCESS;
		//VkSubmitInfo Submission;
		//VkCommandBufferBeginInfo BeginInfo{};
		//VkCommandBuffer CommandBuffer;
		//VkFenceCreateInfo FenceCreateInfo{};
		//VkFence Fence;
		//VkImageCopy Region{};

		//Submission.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		//Submission.pNext					= NULL;
		//Submission.waitSemaphoreCount		= 0;
		//Submission.pWaitSemaphores			= NULL;
		//Submission.pWaitDstStageMask		= 0;
		//Submission.commandBufferCount		= 1;
		//Submission.pCommandBuffers			= &CommandBuffer;
		//Submission.signalSemaphoreCount		= 0;
		//Submission.pSignalSemaphores		= NULL;

		//BeginInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		//BeginInfo.pNext						= NULL;
		//BeginInfo.flags						= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		//BeginInfo.pInheritanceInfo			= NULL;

		//FenceCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		//FenceCreateInfo.pNext				= NULL;
		//FenceCreateInfo.flags				= 0;

		//Region.srcSubresource.aspectMask;
		//Region.srcSubresource.mipLevel;
		//Region.srcSubresource.baseArrayLayer;
		//Region.srcSubresource.layerCount;
		//Region.srcOffset = { 0, 0, 0 };
		//Region.dstSubresource.aspectMask;
		//Region.dstSubresource.mipLevel;
		//Region.dstSubresource.baseArrayLayer;
		//Region.dstSubresource.layerCount;
		//Region.dstOffset = { 0, 0, 0 };
		//Region.extent = { aRhs.CreateInfo.extent.width, aRhs.CreateInfo.extent.height, aRhs.CreateInfo.extent.depth };

		//this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
		//if (CommandBuffer != VK_NULL_HANDLE) {
		//	Result = vkCreateFence(this->Context->handle(), &FenceCreateInfo, NULL, &Fence);
		//	Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);
		//	//vkCmdCopyImage(CommandBuffer, aRhs.Handle, NULL, this->Handle, NULL, 1, &Region);
		//	Result = vkEndCommandBuffer(CommandBuffer);
		//	this->Context->submit(device::qfs::TRANSFER, 1, &Submission, Fence);
		//	Result = vkWaitForFences(this->Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
		//	vkDestroyFence(this->Context->handle(), Fence, NULL);
		//}
		//this->Context->destroy(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);

		return *this;
	}

	texture& texture::operator=(texture&& aRhs) {
		return *this;
	}

	VkCommandBuffer texture::operator<<(texture& aRhs) {
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
		// Cannot do transfer operations if they do not share the
		// same context.
		if (this->Context != aRhs.Context) return CommandBuffer;
		// Check if dimensions are equal.
		if ((this->CreateInfo.extent.width != aRhs.CreateInfo.extent.width) ||
			(this->CreateInfo.extent.height != aRhs.CreateInfo.extent.height) ||
			(this->CreateInfo.extent.depth != aRhs.CreateInfo.extent.depth) ||
			(this->CreateInfo.arrayLayers != aRhs.CreateInfo.arrayLayers) ||
			(this->CreateInfo.mipLevels != aRhs.CreateInfo.mipLevels) ||
			(this->CreateInfo.format != aRhs.CreateInfo.format)
		) return CommandBuffer;

		// Check if proper usage flags are enabled.
		if (
			((this->CreateInfo.usage & texture::usage::TRANSFER_DST) != texture::usage::TRANSFER_DST) 
			||
			((aRhs.CreateInfo.usage & texture::usage::TRANSFER_SRC) != texture::usage::TRANSFER_SRC)
		) return CommandBuffer;

		// Ready to setup transfer operations.
		VkResult Result = VkResult::VK_SUCCESS;
		VkCommandBufferBeginInfo BeginInfo{};
		std::vector<VkImageMemoryBarrier> Barrier;
		std::vector<VkImageCopy> Region;

		BeginInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.pNext					= NULL;
		BeginInfo.flags					= VkCommandBufferUsageFlagBits::VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo		= NULL;

		// Use Barrier layout transitions for al
		for (uint32_t i = 0; i < this->CreateInfo.mipLevels; i++) {
			for (uint32_t j = 0; j < this->CreateInfo.arrayLayers; j++) {

				// Image layout transitions for source.
				if (this->Layout[i][j] != VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
					VkImageMemoryBarrier temp{};
					VkImageSubresourceRange Range{};

					Range.aspectMask				= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
					Range.baseMipLevel				= i;
					Range.levelCount				= 1;
					Range.baseArrayLayer			= j;
					Range.layerCount				= 1;

					temp.sType						= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					temp.pNext						= NULL;
					temp.srcAccessMask				= VkAccessFlagBits::VK_ACCESS_MEMORY_WRITE_BIT; // Hopefully finishes all previous writes?
					temp.dstAccessMask				= VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT;
					temp.oldLayout					= this->Layout[i][j];
					temp.newLayout					= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
					temp.srcQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
					temp.dstQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
					temp.image						= this->Handle;
					temp.subresourceRange			= Range;
					this->Layout[i][j]				= temp.newLayout;
					Barrier.push_back(temp);
				}

				// Image layout transitions for source.
				if (aRhs.Layout[i][j] != VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
					VkImageMemoryBarrier temp{};
					VkImageSubresourceRange Range{};

					Range.aspectMask				= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT; // Figure out what other options do.
					Range.baseMipLevel				= i;
					Range.levelCount				= 1;
					Range.baseArrayLayer			= j;
					Range.layerCount				= 1;

					temp.sType						= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					temp.pNext						= NULL;
					temp.srcAccessMask				= VkAccessFlagBits::VK_ACCESS_MEMORY_WRITE_BIT; // Hopefully finishes all previous writes?
					temp.dstAccessMask				= VkAccessFlagBits::VK_ACCESS_TRANSFER_READ_BIT;
					temp.oldLayout					= aRhs.Layout[i][j];
					temp.newLayout					= VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
					temp.srcQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
					temp.dstQueueFamilyIndex		= VK_QUEUE_FAMILY_IGNORED;
					temp.image						= aRhs.Handle;
					temp.subresourceRange			= Range;
					aRhs.Layout[i][j]				= temp.newLayout;
					Barrier.push_back(temp);
				}

			}

			VkImageCopy SubRegion{};
			// Specify memory regions to copy.
			SubRegion.srcSubresource.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			SubRegion.srcSubresource.mipLevel			= i;
			SubRegion.srcSubresource.baseArrayLayer		= 0;
			SubRegion.srcSubresource.layerCount			= aRhs.CreateInfo.arrayLayers;
			SubRegion.srcOffset							= { 0, 0, 0 };
			SubRegion.dstSubresource.aspectMask			= VkImageAspectFlagBits::VK_IMAGE_ASPECT_COLOR_BIT;
			SubRegion.dstSubresource.mipLevel			= i;
			SubRegion.dstSubresource.baseArrayLayer		= 0;
			SubRegion.dstSubresource.layerCount			= this->CreateInfo.arrayLayers;
			SubRegion.dstOffset							= { 0, 0, 0 };
			SubRegion.extent							= this->MipExtent[i];

			Region.push_back(SubRegion);
		}

		Result = this->Context->create(context::cmdtype::TRANSFER_OTS, 1, &CommandBuffer);
		Result = vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

		// Transition all images.
		vkCmdPipelineBarrier(CommandBuffer,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
			VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT,
			0,
			0, NULL,
			0, NULL,
			Barrier.size(), Barrier.data()
		);

		vkCmdCopyImage(CommandBuffer,
			aRhs.Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			this->Handle, VkImageLayout::VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			Region.size(), Region.data()
		);

		Result = vkEndCommandBuffer(CommandBuffer);

		return CommandBuffer;
	}

	VkCommandBuffer texture::operator>>(texture& aRhs) {
		return (aRhs << *this);
	}

	VkCommandBuffer texture::operator<<(buffer& aRhs) {
		VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
		if (this->Context != aRhs.Context) return CommandBuffer;


		return CommandBuffer;
	}

	VkCommandBuffer texture::operator>>(buffer& aRhs) {
		return (aRhs << *this);
	}

	/*
	0 = 640, 480
	1 = 320, 240
	2 = 160, 120
	3 = 80, 60
	4 = 40, 30
	5 = 20, 15

	6 mip levels.
	*/
	uint32_t texture::miplevelcalc(VkImageType aImageType, VkExtent3D aExtent) {
		uint32_t MipLevelCount = 1;
		switch (aImageType) {
		default:
			return 0;
		case VK_IMAGE_TYPE_1D:
			while (true) {
				if (aExtent.width % 2 == 0) {
					aExtent.width /= 2;
					MipLevelCount += 1;
				}
				else {
					break;
				}
			}
			break;
		case VK_IMAGE_TYPE_2D:
			while (true) {
				if ((aExtent.width % 2 == 0) && (aExtent.height % 2 == 0)) {
					aExtent.width /= 2;
					aExtent.height /= 2;
					MipLevelCount += 1;
				}
				else {
					break;
				}
			}
			break;
		case VK_IMAGE_TYPE_3D:
			while (true) {
				if ((aExtent.width % 2 == 0) && (aExtent.height % 2 == 0) && (aExtent.depth % 2 == 0)) {
					aExtent.width /= 2;
					aExtent.height /= 2;
					aExtent.depth /= 2;
					MipLevelCount += 1;
				}
				else {
					break;
				}
			}
			break;
		}
		return MipLevelCount;
	}



	size_t texture::bytesperpixel(VkFormat aFormat) {
		return (texture::bitsperpixel(aFormat) / 8);
	}

	// So gross.
	size_t texture::bitsperpixel(VkFormat aFormat) {

		/*
		* UNORM : Unsigned Normalized
		* SNORM : Signed Normalized
		* USCALED : ?
		* SSCALED : ?
		* SRGB : ?
		* 
		*/

		switch (aFormat) {
		default: return 0;
		//case VK_FORMAT_UNDEFINED                                        : return 0;
		case VK_FORMAT_R4G4_UNORM_PACK8                                 : return 8;
		case VK_FORMAT_R4G4B4A4_UNORM_PACK16                            : return 16;
		case VK_FORMAT_B4G4R4A4_UNORM_PACK16                            : return 16;
		case VK_FORMAT_R5G6B5_UNORM_PACK16                              : return 16;
		case VK_FORMAT_B5G6R5_UNORM_PACK16                              : return 16;
		case VK_FORMAT_R5G5B5A1_UNORM_PACK16                            : return 16;
		case VK_FORMAT_B5G5R5A1_UNORM_PACK16                            : return 16;
		case VK_FORMAT_A1R5G5B5_UNORM_PACK16                            : return 16;
		case VK_FORMAT_R8_UNORM                                         : return 8;
		case VK_FORMAT_R8_SNORM                                         : return 8;
		case VK_FORMAT_R8_USCALED                                       : return 8;
		case VK_FORMAT_R8_SSCALED                                       : return 8;
		case VK_FORMAT_R8_UINT                                          : return 8;
		case VK_FORMAT_R8_SINT                                          : return 8;
		case VK_FORMAT_R8_SRGB                                          : return 8;
		case VK_FORMAT_R8G8_UNORM                                       : return 16;
		case VK_FORMAT_R8G8_SNORM                                       : return 16;
		case VK_FORMAT_R8G8_USCALED                                     : return 16;
		case VK_FORMAT_R8G8_SSCALED                                     : return 16;
		case VK_FORMAT_R8G8_UINT                                        : return 16;
		case VK_FORMAT_R8G8_SINT                                        : return 16;
		case VK_FORMAT_R8G8_SRGB                                        : return 16;
		case VK_FORMAT_R8G8B8_UNORM                                     : return 24;
		case VK_FORMAT_R8G8B8_SNORM                                     : return 24;
		case VK_FORMAT_R8G8B8_USCALED                                   : return 24;
		case VK_FORMAT_R8G8B8_SSCALED                                   : return 24;
		case VK_FORMAT_R8G8B8_UINT                                      : return 24;
		case VK_FORMAT_R8G8B8_SINT                                      : return 24;
		case VK_FORMAT_R8G8B8_SRGB                                      : return 24;
		case VK_FORMAT_B8G8R8_UNORM                                     : return 24;
		case VK_FORMAT_B8G8R8_SNORM                                     : return 24;
		case VK_FORMAT_B8G8R8_USCALED                                   : return 24;
		case VK_FORMAT_B8G8R8_SSCALED                                   : return 24;
		case VK_FORMAT_B8G8R8_UINT                                      : return 24;
		case VK_FORMAT_B8G8R8_SINT                                      : return 24;
		case VK_FORMAT_B8G8R8_SRGB                                      : return 24;
		case VK_FORMAT_R8G8B8A8_UNORM                                   : return 32;
		case VK_FORMAT_R8G8B8A8_SNORM                                   : return 32;
		case VK_FORMAT_R8G8B8A8_USCALED                                 : return 32;
		case VK_FORMAT_R8G8B8A8_SSCALED                                 : return 32;
		case VK_FORMAT_R8G8B8A8_UINT                                    : return 32;
		case VK_FORMAT_R8G8B8A8_SINT                                    : return 32;
		case VK_FORMAT_R8G8B8A8_SRGB                                    : return 32;
		case VK_FORMAT_B8G8R8A8_UNORM                                   : return 32;
		case VK_FORMAT_B8G8R8A8_SNORM                                   : return 32;
		case VK_FORMAT_B8G8R8A8_USCALED                                 : return 32;
		case VK_FORMAT_B8G8R8A8_SSCALED                                 : return 32;
		case VK_FORMAT_B8G8R8A8_UINT                                    : return 32;
		case VK_FORMAT_B8G8R8A8_SINT                                    : return 32;
		case VK_FORMAT_B8G8R8A8_SRGB                                    : return 32;
		case VK_FORMAT_A8B8G8R8_UNORM_PACK32                            : return 32;
		case VK_FORMAT_A8B8G8R8_SNORM_PACK32                            : return 32;
		case VK_FORMAT_A8B8G8R8_USCALED_PACK32                          : return 32;
		case VK_FORMAT_A8B8G8R8_SSCALED_PACK32                          : return 32;
		case VK_FORMAT_A8B8G8R8_UINT_PACK32                             : return 32;
		case VK_FORMAT_A8B8G8R8_SINT_PACK32                             : return 32;
		case VK_FORMAT_A8B8G8R8_SRGB_PACK32                             : return 32;
		case VK_FORMAT_A2R10G10B10_UNORM_PACK32                         : return 32;
		case VK_FORMAT_A2R10G10B10_SNORM_PACK32                         : return 32;
		case VK_FORMAT_A2R10G10B10_USCALED_PACK32                       : return 32;
		case VK_FORMAT_A2R10G10B10_SSCALED_PACK32                       : return 32;
		case VK_FORMAT_A2R10G10B10_UINT_PACK32                          : return 32;
		case VK_FORMAT_A2R10G10B10_SINT_PACK32                          : return 32;
		case VK_FORMAT_A2B10G10R10_UNORM_PACK32                         : return 32;
		case VK_FORMAT_A2B10G10R10_SNORM_PACK32                         : return 32;
		case VK_FORMAT_A2B10G10R10_USCALED_PACK32                       : return 32;
		case VK_FORMAT_A2B10G10R10_SSCALED_PACK32                       : return 32;
		case VK_FORMAT_A2B10G10R10_UINT_PACK32                          : return 32;
		case VK_FORMAT_A2B10G10R10_SINT_PACK32                          : return 32;
		case VK_FORMAT_R16_UNORM                                        : return 16;
		case VK_FORMAT_R16_SNORM                                        : return 16;
		case VK_FORMAT_R16_USCALED                                      : return 16;
		case VK_FORMAT_R16_SSCALED                                      : return 16;
		case VK_FORMAT_R16_UINT                                         : return 16;
		case VK_FORMAT_R16_SINT                                         : return 16;
		case VK_FORMAT_R16_SFLOAT                                       : return 16;
		case VK_FORMAT_R16G16_UNORM                                     : return 16;
		case VK_FORMAT_R16G16_SNORM                                     : return 16;
		case VK_FORMAT_R16G16_USCALED                                   : return 16;
		case VK_FORMAT_R16G16_SSCALED                                   : return 16;
		case VK_FORMAT_R16G16_UINT                                      : return 16;
		case VK_FORMAT_R16G16_SINT                                      : return 16;
		case VK_FORMAT_R16G16_SFLOAT                                    : return 16;
		case VK_FORMAT_R16G16B16_UNORM                                  : return 48;
		case VK_FORMAT_R16G16B16_SNORM                                  : return 48;
		case VK_FORMAT_R16G16B16_USCALED                                : return 48;
		case VK_FORMAT_R16G16B16_SSCALED                                : return 48;
		case VK_FORMAT_R16G16B16_UINT                                   : return 48;
		case VK_FORMAT_R16G16B16_SINT                                   : return 48;
		case VK_FORMAT_R16G16B16_SFLOAT                                 : return 48;
		case VK_FORMAT_R16G16B16A16_UNORM                               : return 64;
		case VK_FORMAT_R16G16B16A16_SNORM                               : return 64;
		case VK_FORMAT_R16G16B16A16_USCALED                             : return 64;
		case VK_FORMAT_R16G16B16A16_SSCALED                             : return 64;
		case VK_FORMAT_R16G16B16A16_UINT                                : return 64;
		case VK_FORMAT_R16G16B16A16_SINT                                : return 64;
		case VK_FORMAT_R16G16B16A16_SFLOAT                              : return 64;
		case VK_FORMAT_R32_UINT                                         : return 32;
		case VK_FORMAT_R32_SINT                                         : return 32;
		case VK_FORMAT_R32_SFLOAT                                       : return 32;
		case VK_FORMAT_R32G32_UINT                                      : return 64;
		case VK_FORMAT_R32G32_SINT                                      : return 64;
		case VK_FORMAT_R32G32_SFLOAT                                    : return 64;
		case VK_FORMAT_R32G32B32_UINT                                   : return 96;
		case VK_FORMAT_R32G32B32_SINT                                   : return 96;
		case VK_FORMAT_R32G32B32_SFLOAT                                 : return 96;
		case VK_FORMAT_R32G32B32A32_UINT                                : return 128;
		case VK_FORMAT_R32G32B32A32_SINT                                : return 128;
		case VK_FORMAT_R32G32B32A32_SFLOAT                              : return 128;
		case VK_FORMAT_R64_UINT                                         : return 64;
		case VK_FORMAT_R64_SINT                                         : return 64;
		case VK_FORMAT_R64_SFLOAT                                       : return 64;
		case VK_FORMAT_R64G64_UINT                                      : return 128;
		case VK_FORMAT_R64G64_SINT                                      : return 128;
		case VK_FORMAT_R64G64_SFLOAT                                    : return 128;
		case VK_FORMAT_R64G64B64_UINT                                   : return 192;
		case VK_FORMAT_R64G64B64_SINT                                   : return 192;
		case VK_FORMAT_R64G64B64_SFLOAT                                 : return 192;
		case VK_FORMAT_R64G64B64A64_UINT                                : return 256;
		case VK_FORMAT_R64G64B64A64_SINT                                : return 256;
		case VK_FORMAT_R64G64B64A64_SFLOAT                              : return 256;
		case VK_FORMAT_B10G11R11_UFLOAT_PACK32                          : return 32;
			// I might comment this section out.
			/*
		case VK_FORMAT_E5B9G9R9_UFLOAT_PACK32                           : return 32;
		case VK_FORMAT_D16_UNORM                                        : return 16;
		case VK_FORMAT_X8_D24_UNORM_PACK32                              : return 32;
		case VK_FORMAT_D32_SFLOAT                                       : return 32;
		case VK_FORMAT_S8_UINT                                          : return 8;
		case VK_FORMAT_D16_UNORM_S8_UINT                                : return 24;
		case VK_FORMAT_D24_UNORM_S8_UINT                                : return 32;
		case VK_FORMAT_D32_SFLOAT_S8_UINT                               : return 0;
		case VK_FORMAT_BC1_RGB_UNORM_BLOCK                              : return 0;
		case VK_FORMAT_BC1_RGB_SRGB_BLOCK                               : return 0;
		case VK_FORMAT_BC1_RGBA_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_BC1_RGBA_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_BC2_UNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC2_SRGB_BLOCK                                   : return 0;
		case VK_FORMAT_BC3_UNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC3_SRGB_BLOCK                                   : return 0;
		case VK_FORMAT_BC4_UNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC4_SNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC5_UNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC5_SNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC6H_UFLOAT_BLOCK                                : return 0;
		case VK_FORMAT_BC6H_SFLOAT_BLOCK                                : return 0;
		case VK_FORMAT_BC7_UNORM_BLOCK                                  : return 0;
		case VK_FORMAT_BC7_SRGB_BLOCK                                   : return 0;
		case VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK                          : return 0;
		case VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK                           : return 0;
		case VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK                        : return 0;
		case VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK                         : return 0;
		case VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK                        : return 0;
		case VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK                         : return 0;
		case VK_FORMAT_EAC_R11_UNORM_BLOCK                              : return 0;
		case VK_FORMAT_EAC_R11_SNORM_BLOCK                              : return 0;
		case VK_FORMAT_EAC_R11G11_UNORM_BLOCK                           : return 0;
		case VK_FORMAT_EAC_R11G11_SNORM_BLOCK                           : return 0;
		case VK_FORMAT_ASTC_4x4_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_4x4_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_5x4_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_5x4_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_5x5_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_5x5_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_6x5_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_6x5_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_6x6_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_6x6_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_8x5_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_8x5_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_8x6_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_8x6_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_8x8_UNORM_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_8x8_SRGB_BLOCK                              : return 0;
		case VK_FORMAT_ASTC_10x5_UNORM_BLOCK                            : return 0;
		case VK_FORMAT_ASTC_10x5_SRGB_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_10x6_UNORM_BLOCK                            : return 0;
		case VK_FORMAT_ASTC_10x6_SRGB_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_10x8_UNORM_BLOCK                            : return 0;
		case VK_FORMAT_ASTC_10x8_SRGB_BLOCK                             : return 0;
		case VK_FORMAT_ASTC_10x10_UNORM_BLOCK                           : return 0;
		case VK_FORMAT_ASTC_10x10_SRGB_BLOCK                            : return 0;
		case VK_FORMAT_ASTC_12x10_UNORM_BLOCK                           : return 0;
		case VK_FORMAT_ASTC_12x10_SRGB_BLOCK                            : return 0;
		case VK_FORMAT_ASTC_12x12_UNORM_BLOCK                           : return 0;
		case VK_FORMAT_ASTC_12x12_SRGB_BLOCK                            : return 0;
		case VK_FORMAT_G8B8G8R8_422_UNORM                               : return 0;
		case VK_FORMAT_B8G8R8G8_422_UNORM                               : return 0;
		case VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM                        : return 0;
		case VK_FORMAT_G8_B8R8_2PLANE_420_UNORM                         : return 0;
		case VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM                        : return 0;
		case VK_FORMAT_G8_B8R8_2PLANE_422_UNORM                         : return 0;
		case VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM                        : return 0;
		case VK_FORMAT_R10X6_UNORM_PACK16                               : return 0;
		case VK_FORMAT_R10X6G10X6_UNORM_2PACK16                         : return 0;
		case VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16               : return 0;
		case VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16           : return 0;
		case VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16           : return 0;
		case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16       : return 0;
		case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16        : return 0;
		case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16       : return 0;
		case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16        : return 0;
		case VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16       : return 0;
		case VK_FORMAT_R12X4_UNORM_PACK16                               : return 0;
		case VK_FORMAT_R12X4G12X4_UNORM_2PACK16                         : return 0;
		case VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16               : return 0;
		case VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16           : return 0;
		case VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16           : return 0;
		case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16       : return 0;
		case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16        : return 0;
		case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16       : return 0;
		case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16        : return 0;
		case VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16       : return 0;
		case VK_FORMAT_G16B16G16R16_422_UNORM                           : return 0;
		case VK_FORMAT_B16G16R16G16_422_UNORM                           : return 0;
		case VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM                     : return 0;
		case VK_FORMAT_G16_B16R16_2PLANE_420_UNORM                      : return 0;
		case VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM                     : return 0;
		case VK_FORMAT_G16_B16R16_2PLANE_422_UNORM                      : return 0;
		case VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM                     : return 0;
		case VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG                      : return 0;
		case VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG                      : return 0;
		case VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG                      : return 0;
		case VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG                      : return 0;
		case VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG                       : return 0;
		case VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG                       : return 0;
		case VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG                       : return 0;
		case VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG                       : return 0;
		case VK_FORMAT_ASTC_4x4_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_5x4_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_5x5_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_6x5_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_6x6_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_8x5_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_8x6_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_8x8_SFLOAT_BLOCK_EXT                        : return 0;
		case VK_FORMAT_ASTC_10x5_SFLOAT_BLOCK_EXT                       : return 0;
		case VK_FORMAT_ASTC_10x6_SFLOAT_BLOCK_EXT                       : return 0;
		case VK_FORMAT_ASTC_10x8_SFLOAT_BLOCK_EXT                       : return 0;
		case VK_FORMAT_ASTC_10x10_SFLOAT_BLOCK_EXT                      : return 0;
		case VK_FORMAT_ASTC_12x10_SFLOAT_BLOCK_EXT                      : return 0;
		case VK_FORMAT_ASTC_12x12_SFLOAT_BLOCK_EXT                      : return 0;
		case VK_FORMAT_G8_B8R8_2PLANE_444_UNORM_EXT                     : return 0;
		case VK_FORMAT_G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT    : return 0;
		case VK_FORMAT_G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT    : return 0;
		case VK_FORMAT_G16_B16R16_2PLANE_444_UNORM_EXT                  : return 0;
		case VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT                        : return 0;
		case VK_FORMAT_A4B4G4R4_UNORM_PACK16_EXT                        : return 0;
			*/
		}
	}

}
