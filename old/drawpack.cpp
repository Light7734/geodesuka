#include <geodesuka/core/gcl/drawpack.h>

#include <geodesuka/core/object/rendertarget.h>

#include <assert.h>

namespace geodesuka::core::gcl {

	drawpack::drawpack(context* aContext, object::rendertarget* aRenderTarget, uint32_t aSubpassDescriptionCount, VkSubpassDescription* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, VkSubpassDependency* aSubpassDependencyList) {

		Context = aContext;
		RenderTarget = aRenderTarget;

		CreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		CreateInfo.pNext				= NULL;
		CreateInfo.flags				= 0;
		CreateInfo.attachmentCount		= RenderTarget->FrameAttachmentCount;
		CreateInfo.pAttachments			= RenderTarget->FrameAttachmentDescription;
		CreateInfo.subpassCount			= aSubpassDescriptionCount;
		CreateInfo.pSubpasses			= aSubpassDescriptionList;
		CreateInfo.dependencyCount		= aSubpassDependencyCount;
		CreateInfo.pDependencies		= aSubpassDependencyList;

		Result = vkCreateRenderPass(Context->handle(), &CreateInfo, NULL, &RenderPass);

		Frame = (VkFramebuffer*)malloc(RenderTarget->FrameCount * sizeof(VkFramebuffer));
		Command = (VkCommandBuffer*)malloc(RenderTarget->FrameCount * sizeof(VkCommandBuffer));

		assert(!((Frame == NULL) || (Command == NULL)));

		for (uint32_t i = 0; i < RenderTarget->FrameCount; i++) {
			VkFramebufferCreateInfo FramebufferCreateInfo{};
			FramebufferCreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			FramebufferCreateInfo.pNext					= NULL;
			FramebufferCreateInfo.flags					= 0;
			FramebufferCreateInfo.renderPass			= RenderPass;
			FramebufferCreateInfo.attachmentCount		= RenderTarget->FrameAttachmentCount;
			FramebufferCreateInfo.pAttachments			= RenderTarget->FrameAttachment[i];
			FramebufferCreateInfo.width					= RenderTarget->Resolution.x;
			FramebufferCreateInfo.height				= RenderTarget->Resolution.y;
			FramebufferCreateInfo.layers				= RenderTarget->Resolution.z;
			Result = vkCreateFramebuffer(Context->handle(), &FramebufferCreateInfo, NULL, &Frame[i]);
		}

		RenderTarget->DrawCommandPool.allocate(command_pool::level::PRIMARY, RenderTarget->FrameCount, Command);
	}

	drawpack::~drawpack() {
		RenderTarget->DrawCommandPool.release(RenderTarget->FrameCount, Command);
		free(Command);
		for (uint32_t i = 0; i < RenderTarget->FrameCount; i++) {
			vkDestroyFramebuffer(Context->handle(), Frame[i], NULL);
		}
		free(Frame);
		vkDestroyRenderPass(Context->handle(), RenderPass, NULL);
		Command = NULL;
		Frame = NULL;
		RenderPass = VK_NULL_HANDLE;
		RenderTarget = nullptr;
		Context = nullptr;
	}

}
