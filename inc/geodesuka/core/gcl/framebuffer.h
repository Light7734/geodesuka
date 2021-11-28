#ifndef GEODESUKA_CORE_GCL_FRAMEBUFFER_H
#define GEODESUKA_CORE_GCL_FRAMEBUFFER_H

#include <vulkan/vulkan.h>

#include "../math.h"

#include "device.h"
#include "context.h"
#include "texture.h"
#include "renderpass.h"

namespace geodesuka::core::gcl {

	class framebuffer {
	public:

		framebuffer();
		framebuffer(context* aContext, renderpass& aRenderPass, uint32_t aAttachmentCount, texture* aAttachment, uint32_t aWidth, uint32_t aHeight, uint32_t aLayers);

		~framebuffer();

	private:

		context* Context;
		VkFramebufferCreateInfo CreateInfo{};
		VkFramebuffer Handle;

		uint32_t AttachmentCount;
		texture* Attachment;
		VkImageView* View;

	};

}

#endif // !GEODESUKA_CORE_GCL_FRAMEBUFFER_H
