#pragma once
#ifndef GEODESUKA_CORE_GCL_PIPELINE_H
#define GEODESUKA_CORE_GCL_PIPELINE_H

#include <vulkan/vulkan.h>

#include "device.h"
#include "context.h"
#include "shader.h"
#include "renderpass.h"

namespace geodesuka::core::gcl {

	class pipeline {
	public:

		// Compute Pipeline
		
		pipeline();
		// Graphics Pipeline
		pipeline(
			context* aContext,
			uint32_t aShaderCount, shader* aShader,
			uint32_t aDSLCount, VkDescriptorSetLayout* aDSL,
			renderpass& aRenderPass, uint32_t aSubpassIndex
		);

		~pipeline();

	protected:

		context* Context;

		uint32_t ShaderCount;
		shader* Shader;

		VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
		VkDescriptorPool DescriptorPool;

		// Graphics Options.
		VkGraphicsPipelineCreateInfo			GraphicsCreateInfo{};

		VkPipelineShaderStageCreateInfo*		ShaderStage;
		VkPipelineVertexInputStateCreateInfo	VertexInput{};
		VkPipelineInputAssemblyStateCreateInfo	InputAssembly{};
		VkPipelineTessellationStateCreateInfo	Tesselation{};
		VkPipelineViewportStateCreateInfo		Viewport{};
		VkPipelineRasterizationStateCreateInfo	Rasterizer{};
		VkPipelineMultisampleStateCreateInfo	Multisample{};
		VkPipelineDepthStencilStateCreateInfo	DepthStencil{};
		VkPipelineColorBlendStateCreateInfo		ColorBlend{};
		VkPipelineDynamicStateCreateInfo		DynamicState{};

		// Compute Options.
		//VkComputePipelineCreateInfo				ComputeCreateInfo{};

		VkPipelineLayoutCreateInfo				LayoutCreateInfo{};
		VkPipelineLayout						Layout;

		VkPipeline Handle;

		void gdefault();

	};

}

#endif // !GEODESUKA_CORE_GCL_PIPELINE_H
