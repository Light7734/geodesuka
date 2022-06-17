#include <geodesuka/core/gcl/renderpass.h>

#include <cassert>

#include <geodesuka/core/object/render_target.h>

namespace geodesuka::core::gcl {

	renderpass::renderpass(context* aContext, object::render_target* aRenderTarget, uint32_t aSubpassDescriptionCount, vk_subpass_description* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, vk_subpass_dependency* aSubpassDependencyList) {

		FramebufferCount = aRenderTarget->FrameCount;
		Framebuffer = (vk_framebuffer*)malloc(aRenderTarget->FrameCount * sizeof(vk_framebuffer));
		assert(Framebuffer != NULL);

		vk_result Result = VK_SUCCESS;
		vk_render_pass_create_info RenderPassCreateInfo{};
		RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassCreateInfo.pNext = NULL;

		RenderPassCreateInfo.flags					= 0;
		RenderPassCreateInfo.attachmentCount		= aRenderTarget->FrameAttachmentCount;
		RenderPassCreateInfo.pAttachments			= aRenderTarget->FrameAttachmentDescription;
		RenderPassCreateInfo.subpassCount			= aSubpassDescriptionCount;
		RenderPassCreateInfo.pSubpasses				= aSubpassDescriptionList;
		RenderPassCreateInfo.dependencyCount		= aSubpassDependencyCount;
		RenderPassCreateInfo.pDependencies			= aSubpassDependencyList;

		Result = vkCreateRenderPass(Context->handle(), &RenderPassCreateInfo, NULL, &Handle);
		assert(Result != VK_SUCCESS);

		vk_framebuffer_create_info FramebufferCreateInfo{};
		FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		FramebufferCreateInfo.pNext = NULL;

		for (uint32_t i = 0; i < FramebufferCount; i++) {
			FramebufferCreateInfo.flags				= 0;
			FramebufferCreateInfo.renderPass		= Handle;
			FramebufferCreateInfo.attachmentCount	= aRenderTarget->FrameAttachmentCount;
			FramebufferCreateInfo.pAttachments		= aRenderTarget->FrameAttachment[i];
			FramebufferCreateInfo.width				= aRenderTarget->Resolution.x;
			FramebufferCreateInfo.height			= aRenderTarget->Resolution.y;
			FramebufferCreateInfo.layers			= 1;
			Result = vkCreateFramebuffer(Context->handle(), &FramebufferCreateInfo, NULL, &Framebuffer[i]);
			assert(Result != VK_SUCCESS);
		}

	}

	//renderpass::renderpass(context* aContext, uint32_t aAttachmentCount, vk_image_view* aAttachmentList, uint32_t aSubpassDescriptionCount, vk_subpass_description* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, vk_subpass_dependency* aSubpassDependencyList) {}

	renderpass::~renderpass() {

	}

}