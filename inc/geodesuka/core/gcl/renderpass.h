#pragma once
#ifndef GEODESUKA_CORE_GCL_RENDERPASS_H
#define GEODESUKA_CORE_GCL_RENDERPASS_H

#include "config.h"

#include "device.h"
#include "context.h"
#include "image.h"

namespace geodesuka::core::gcl {

	class renderpass {
	public:

		context* Context;
		//object::rendertarget* RenderTarget;

		VkRenderPass RenderPass;
		VkFramebuffer* FrameBuffer;
		VkCommandBuffer* CommandBuffer;

		//renderpass(context* aContext, object::rendertarget* aRenderTarget, uint32_t aSubpassDescriptionCount, VkSubpassDescription* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, VkSubpassDependency* aSubpassDependencyList);
		renderpass(context* aContext, uint32_t aAttachmentCount, VkImageView* aAttachmentList, uint32_t aSubpassDescriptionCount, VkSubpassDescription* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, VkSubpassDependency* aSubpassDependencyList);
		~renderpass();

	private:

	};

}

#endif // !GEODESUKA_CORE_GCL_RENDERPASS_H
