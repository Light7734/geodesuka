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

namespace geodesuka {
	namespace core {
		namespace gcl {




			//// (Context, Format, Width, Height, Depth, 
			//texture::texture(gcl::context *aContext, tiling aTiling, usage aUsage, VkFormat aFormat, uint32_t aWidth, uint32_t aHeight, uint32_t aDepth) {
			//	VkResult ReturnCode = VK_SUCCESS;
			//	
			//	struct createinfo {
			//		uint32_t MipLevels;
			//		uint32_t ArrayLevels;
			//		
			//	};

			//	VkImageLayout;
			//	//VkImageUsageFlagBits::
			//	this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			//	this->CreateInfo.pNext						= NULL;
			//	this->CreateInfo.flags						= 0; // Leave as zero for now, 
			//	if ((aWidth > 1) && (aHeight <= 1) && (aDepth <= 1)) {
			//		this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_1D;
			//	}
			//	else if ((aWidth > 1) && (aHeight > 1) && (aDepth <= 1)) {
			//		this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_2D;
			//	}
			//	else if ((aWidth > 1) && (aHeight > 1) && (aDepth > 1))  {
			//		this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_3D;
			//	}
			//	else {
			//		// Error, invalid state.
			//		this->CreateInfo.imageType = VkImageType::VK_IMAGE_TYPE_MAX_ENUM;
			//	}
			//	this->CreateInfo.imageType					; // Will be determined by width, height, and depth.
			//	this->CreateInfo.format						= aFormat;
			//	this->CreateInfo.extent						= { aWidth, aHeight, aDepth };
			//	this->CreateInfo.mipLevels					= 1;
			//	this->CreateInfo.arrayLayers				= 1;
			//	this->CreateInfo.samples					= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
			//	this->CreateInfo.tiling						= (VkImageTiling)aTiling;
			//	this->CreateInfo.usage						= (VkImageUsageFlags)aUsage;
			//	this->CreateInfo.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE;
			//	this->CreateInfo.queueFamilyIndexCount		= 0;
			//	this->CreateInfo.pQueueFamilyIndices		= NULL;
			//	this->CreateInfo.initialLayout				= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;

			//	vkCreateImage(this->Context->handle(), &this->CreateInfo, NULL, &this->Handle);

			//	// Use staging buffer here to transfer pixel data
			//	//buffer StagingBuffer;


			//}

			texture::~texture() {
				vkDestroyImage(this->Context->handle(), this->Handle, NULL);
				this->Handle = VK_NULL_HANDLE;
				// Clear Device Memory
				vkFreeMemory(this->Context->handle(), this->MemoryHandle, NULL);
				this->MemoryHandle = VK_NULL_HANDLE;
			}

		}
	}
}
