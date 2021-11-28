#pragma once
#ifndef GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
#define GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H

#include <geodesuka/engine.h>

namespace geodesuka::builtin::object {

	class triangle : public core::object_t {
	public:

		triangle(engine* aEngine, core::gcl::context* aContext);
		~triangle();

		virtual VkCommandBuffer draw(core::object::system_window* aTargetSystemWindow)		override;

	private:

		// Create with first interaction with window.
		VkRenderPassCreateInfo RenderPassCreateInfo{};
		VkRenderPass RenderPass;

		VkFramebufferCreateInfo FramebufferCreateInfo{};
		VkFramebuffer Framebuffer;

		//core::gcl::pipeline Pipeline;
		VkSubpassDescription Subpass[1];
		VkSubpassDependency Dependency[1];



	};

}

#endif // !GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
