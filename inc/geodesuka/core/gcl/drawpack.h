#pragma once
#ifndef GEODESUKA_CORE_GCL_DRAWPACK_H
#define GEODESUKA_CORE_GCL_DRAWPACK_H

#include <vulkan/vulkan.h>

#include "context.h"
//#include "renderpass.h"
//#include "framebuffer.h"

// Forward Declaration.
namespace geodesuka::core::object {
	class rendertarget;
}

namespace geodesuka::core::gcl {

	class drawpack {
	public:

		context* Context;
		object::rendertarget* RenderTarget;

		VkRenderPass RenderPass;
		VkFramebuffer* FrameBuffer;
		VkCommandBuffer* CommandBuffer;


		VkPipeline *Pipeline;
		VkPipelineBindPoint BindPoint;

		drawpack(context *aContext, object::rendertarget* aRenderTarget, uint32_t aSubpassDescriptionCount, VkSubpassDescription* aSubpassDescriptionList, uint32_t aSubpassDependencyCount, VkSubpassDependency* aSubpassDependencyList);
		~drawpack();

		VkCommandBuffer operator[](int aIndex);

	};

}

#endif // !GEODESUKA_CORE_GCL_DRAWPACK_H
