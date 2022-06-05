#pragma once
#ifndef GEODESUKA_CORE_GCL_PIPELINE_H
#define GEODESUKA_CORE_GCL_PIPELINE_H

#include "../gcl.h"

#include "device.h"
#include "context.h"
#include "shader.h"
#include "renderpass.h"

namespace geodesuka::core::gcl {

	class pipeline {
	public:

		// Pre creation options for a rasterizer pipeline.
		struct rasterizer {

			VkPipelineBindPoint BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

			uint32_t UniformSetCount;
			uint32_t *UniformSetBindingCount;
			VkDescriptorSetLayoutBinding **UniformSetBindingList;

			uint32_t InputCount;
			VkVertexInputAttributeDescription* InputList;

			uint32_t OutputCount;
			VkAttachmentDescription* OutputList;

			uint32_t StageCount;
			VkPipelineShaderStageCreateInfo* StageList;
			VkPipelineVertexInputStateCreateInfo VertexInput{};
			VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
			VkPipelineTessellationStateCreateInfo Tesselation{};
			VkPipelineViewportStateCreateInfo Viewport{};
			VkPipelineRasterizationStateCreateInfo Rasterizer{};
			VkPipelineMultisampleStateCreateInfo Multisample{};
			VkPipelineDepthStencilStateCreateInfo DepthStencil{};
			VkPipelineColorBlendStateCreateInfo ColorBlend{};
			VkPipelineDynamicStateCreateInfo DynamicState{};

			VkGraphicsPipelineCreateInfo CreateInfo{};

			rasterizer();
			rasterizer(uint32_t aShaderCount, shader** aShaderList);

		};

		// Pre creation options for a raytracer pipeline.
		struct raytracer {

			VkPipelineBindPoint BindPoint = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;

			VkRayTracingPipelineCreateInfoKHR CreateInfo{};

			raytracer();
			//raytracer(uint32_t aShaderCount, shader** aShaderList);

		};

		// Pre creation options for a compute pipeline.
		// Requires on a single compute shader.
		struct compute {

			VkPipelineBindPoint BindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;

			VkComputePipelineCreateInfo CreateInfo{};

			compute();
			//compute(shader* aComputeShader);

		};



		// Creates rasterizer pipeline. (RenderPass is only needed for rasterizers, Thanks Khronos...)
		pipeline(context* aContext, rasterizer& aRasterizer, VkRenderPass aRenderPass, uint32_t aSubpassIndex);

		// Dynamic Rendering Rasterizer
		//pipeline(context* aContext, rasterizer& aRasterizer);

		// Creates raytracer pipeline.
		pipeline(context* aContext, raytracer& aRaytracer);

		// Creates compute pipeline.
		pipeline(context* aContext, compute& aCompute);

		VkCommandBuffer set_uniform(int aSet, int aBinding, buffer* Image);
		VkCommandBuffer set_uniform(int aSet, int aBinding, image* Image);

	private:

		rasterizer Rasterizer;
		raytracer Raytracer;
		compute Compute;

		context* Context;

		uint32_t DescriptorSetCount;
		VkDescriptorSetLayout* DescriptorSetLayoutList;
		VkDescriptorPool DescriptorPool;
		VkDescriptorSet* DescriptorSetList;

		VkPipelineLayout Layout;
		VkPipelineCache Cache;
		VkPipelineBindPoint Type;
		VkPipeline Handle;


	};

}

#endif // !GEODESUKA_CORE_GCL_PIPELINE_H
