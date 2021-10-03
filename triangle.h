#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <geodesuka/engine.h>

class triangle : public geodesuka::core::object_t {
public:

	//triangle(geodesuka::engine* aEngine);
	triangle(geodesuka::engine& aEngine, geodesuka::core::gcl::context* aContext);

private:


	// Describes the bound vertex buffers in draw call.
	std::vector<VkVertexInputBindingDescription> InputBindingDescription;
	// Describes the per vertex memory layout of bound buffers.
	std::vector<VkVertexInputAttributeDescription> InputAttributeDescription;
	// Shader stages of the graphics pipeline.
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStage;

	// Shader Stages for triangle.
	VkPipelineVertexInputStateCreateInfo VertexInput;
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	//VkPipelineTessellationStateCreateInfo Tessellation;
	VkPipelineViewportStateCreateInfo Viewport;
	VkPipelineRasterizationStateCreateInfo Rasterizer;
	VkPipelineMultisampleStateCreateInfo Multisample;
	VkPipelineDepthStencilStateCreateInfo DepthStencil;
	VkPipelineColorBlendStateCreateInfo ColorBlend;
	VkPipelineDynamicStateCreateInfo DynamicState;

	VkGraphicsPipelineCreateInfo CreateInfo;
	VkPipeline GraphicsPipeline;

};

#endif // !TRIANGLE_H
