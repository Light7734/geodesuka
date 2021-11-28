#pragma once
#ifndef GEODESUKA_CORE_GCL_RENDERPASS_H
#define GEODESUKA_CORE_GCL_RENDERPASS_H

#include <vulkan/vulkan.h>

#include "device.h"
#include "context.h"
#include "texture.h"

namespace geodesuka::core::gcl {

	class renderpass {
	public:

		renderpass();
		renderpass(
			context* aContext,
			int aAttachmentCount, texture* aAttachment,
			uint32_t aSubpassCount, VkSubpassDescription* aSubpass,
			uint32_t aDependencyCount, VkSubpassDependency* aDependency
		);
		renderpass(
			context* aContext,
			uint32_t aAttachmentCount, VkAttachmentDescription* aAttachment,
			uint32_t aSubpassCount, VkSubpassDescription* aSubpass,
			uint32_t aDependencyCount, VkSubpassDependency* aDependency
		);
		~renderpass();


		VkRenderPass handle();

	private:

		context* Context;
		VkRenderPassCreateInfo CreateInfo{};
		VkRenderPass Handle;

		uint32_t AttachmentDescriptionCount;
		VkAttachmentDescription* AttachmentDescription;

		VkRenderPass create(
			uint32_t aAttachmentCount, VkAttachmentDescription* aAttachment,
			uint32_t aSubpassCount, VkSubpassDescription* aSubpass,
			uint32_t aDependencyCount, VkSubpassDependency* aDependency
		);

	};

}

#endif // !GEODESUKA_CORE_GCL_RENDERPASS_H
