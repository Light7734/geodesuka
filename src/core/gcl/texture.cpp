#include <geodesuka/core/gcl/texture.h>

// Standard C Libs
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

#include <geodesuka/core/gcl/gcl.h>

#include <geodesuka/core/math.h>

#include <geodesuka/core/gcl/variable.h>

//#include <geodesuka/core/object.h>
//#include <geodesuka/core/object/system_window.h>

namespace geodesuka {
	namespace core {
		namespace gcl {

			texture::texture(device_context* aDeviceContext, VkFormat aFormat, math::natural3 aGridSize) {

				VkImageType lType = VkImageType::VK_IMAGE_TYPE_1D;

				bool isValidFormat = false;

				// Texture Options.
				this->CreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				this->CreateInfo.pNext						= NULL;
				this->CreateInfo.flags						= VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
				this->CreateInfo.imageType					= lType;
				this->CreateInfo.format						= aFormat;
				//this->CreateInfo.extent						= this->convert_to_extent(aGridSize);
				this->CreateInfo.mipLevels					= 1;
				this->CreateInfo.arrayLayers				= 1;
				this->CreateInfo.samples					= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
				this->CreateInfo.tiling						= VkImageTiling::VK_IMAGE_TILING_OPTIMAL;
				this->CreateInfo.usage						= VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
				this->CreateInfo.sharingMode				= VkSharingMode::VK_SHARING_MODE_EXCLUSIVE; //Exclusive implies exclusive access per queue.
				this->CreateInfo.queueFamilyIndexCount		= 0;
				this->CreateInfo.pQueueFamilyIndices		= NULL;
				this->CreateInfo.initialLayout				= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
				
				this->ErrorCode = vkCreateImage(ParentDC->get_handle(), &this->CreateInfo, NULL, &this->Handle);
			}

			// This call just simply stores the image handles for a system_window swap chain.
			texture::texture(object::system_window* aSystemWindow, device_context* aDeviceContext, VkImage aImageHandle, VkImageCreateInfo aCreateInfo) {
				this->ErrorCode = VkResult::VK_SUCCESS;
				this->ParentSW = aSystemWindow;
				this->ParentDC = aDeviceContext;
				this->Handle = aImageHandle;
				this->CreateInfo = aCreateInfo;
			}

			//VkExtent3D texture::convert_to_extent(math::natural aX, math::natural aY, math::natural aZ) {
			//	VkExtent3D temp;

			//	return temp;
			//}

			texture::~texture() {
				if ((this->ParentSW == nullptr) && (this->Handle != VK_NULL_HANDLE)) {
					vkDestroyImage(this->ParentDC->get_handle(), this->Handle, NULL);
					this->Handle = VK_NULL_HANDLE;
				}
				this->ErrorCode = VkResult::VK_SUCCESS;
				this->ParentSW = nullptr;
				this->ParentDC = nullptr;
			}


		}
	}
}
