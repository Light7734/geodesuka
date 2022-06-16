#include <geodesuka/core/gcl/drawpack.h>

#include <geodesuka/core/object/rendertarget.h>

#include <assert.h>

#include <vulkan/vulkan.h>

#include <geodesuka/core/gcl/context.h>

namespace geodesuka::core::gcl {

	drawpack::drawpack(context* aContext, object::render_target* aRenderTarget, uint32_t aSubpassDescriptionCount, VkSubpassDescription* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, VkSubpassDependency* aSubpassDependencyList) {
		Context = aContext;
		RenderTarget = aRenderTarget;

		VkResult Result = VK_SUCCESS;
		VkRenderPassCreateInfo RenderPassCreateInfo{};
		RenderPassCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassCreateInfo.pNext				= NULL;
		RenderPassCreateInfo.flags				= 0;
		RenderPassCreateInfo.attachmentCount	= RenderTarget->FrameAttachmentCount;
		RenderPassCreateInfo.pAttachments		= RenderTarget->FrameAttachmentDescription;
		RenderPassCreateInfo.subpassCount		= aSubpassDescriptionCount;
		RenderPassCreateInfo.pSubpasses			= aSubpassDescriptionList;
		RenderPassCreateInfo.dependencyCount	= aSubpassDependencyCount;
		RenderPassCreateInfo.pDependencies		= aSubpassDependencyList;

		Result = vkCreateRenderPass(Context->handle(), &RenderPassCreateInfo, NULL, &RenderPass);

		FrameBuffer = (VkFramebuffer*)malloc(RenderTarget->FrameCount * sizeof(VkFramebuffer));
		CommandBuffer = (VkCommandBuffer*)malloc(RenderTarget->FrameCount * sizeof(VkCommandBuffer));

		assert(!((FrameBuffer == NULL) || (CommandBuffer == NULL)));

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
			Result = vkCreateFramebuffer(Context->handle(), &FramebufferCreateInfo, NULL, &FrameBuffer[i]);
		}

		RenderTarget->DrawCommandPool.allocate(command_pool::level::PRIMARY, RenderTarget->FrameCount, CommandBuffer);
	}

	drawpack::~drawpack() {
		if (Context != nullptr) {
			// Return CommandBuffers to rendertarget.
			RenderTarget->DrawCommandPool.release(RenderTarget->FrameCount, CommandBuffer);
			// Destroy Framebuffers
			for (uint32_t i = 0; i < RenderTarget->FrameCount; i++) {
				vkDestroyFramebuffer(Context->handle(), FrameBuffer[i], NULL);
			}
			// Destroy Render Pass
			vkDestroyRenderPass(Context->handle(), RenderPass, NULL);
		}
		// Clear Allocated Memory.
		free(CommandBuffer);
		free(FrameBuffer);
		CommandBuffer = NULL;
		FrameBuffer = NULL;
		RenderPass = VK_NULL_HANDLE;
		RenderTarget = nullptr;
		Context = nullptr;
	}

	VkCommandBuffer drawpack::operator[](int aIndex) {
		return CommandBuffer[aIndex];
	}

}
