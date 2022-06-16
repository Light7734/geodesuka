#pragma once
#ifndef GEODESUKA_CORE_GCL_RENDERPASS_H
#define GEODESUKA_CORE_GCL_RENDERPASS_H

#include "config.h"

#include "device.h"
#include "context.h"
#include "image.h"

// Forward Declaration.
namespace geodesuka::core::object {
	class rendertarget;
}

namespace geodesuka::core::gcl {

	class renderpass {
	public:

		vk_render_pass Handle;
		uint32_t FramebufferCount;
		vk_framebuffer* Framebuffer;

		renderpass(context *aContext, object::rendertarget* aRenderTarget, uint32_t aSubpassDescriptionCount, vk_subpass_description* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, vk_subpass_dependency* aSubpassDependencyList);
		//renderpass(context* aContext, uint32_t aAttachmentCount, vk_image_view* aAttachmentList, uint32_t aSubpassDescriptionCount, vk_subpass_description* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, vk_subpass_dependency* aSubpassDependencyList);
		~renderpass();

	private:

		context* Context;
		object::rendertarget* RenderTarget;

	};

}

#endif // !GEODESUKA_CORE_GCL_RENDERPASS_H
