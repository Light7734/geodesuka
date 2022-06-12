#include <geodesuka/core/gcl/pipeline.h>

namespace geodesuka::core::gcl {

	pipeline::rasterizer::rasterizer() {

	}

	// Needs shaders to determine descriptor sets/pipeline layout.
	pipeline::rasterizer::rasterizer(uint32_t aShaderCount, shader** aShaderList) {
		this->VertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		this->VertexInput.pNext = NULL;
		this->VertexInput.flags = 0;

		this->InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		this->InputAssembly.pNext = NULL;
		this->InputAssembly.flags = 0;

		// Depends
		this->Tesselation.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		this->Tesselation.pNext = NULL;
		this->Tesselation.flags = 0;

		this->Viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		this->Viewport.pNext = NULL;
		this->Viewport.flags = 0;

		this->Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		this->Rasterizer.pNext = NULL;
		this->Rasterizer.flags = 0;

		this->Multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		this->Multisample.pNext = NULL;
		this->Multisample.flags = 0;

		this->DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		this->DepthStencil.pNext = NULL;
		this->DepthStencil.flags = 0;

		this->ColorBlend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		this->ColorBlend.pNext = NULL;
		this->ColorBlend.flags = 0;

		this->DynamicState.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		this->DynamicState.pNext = NULL;
		this->DynamicState.flags = 0;

		bool TesselationShaderExists = false;
		bool GeometryShaderExists = false;

		CreateInfo.sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		CreateInfo.pNext					= NULL;
		CreateInfo.flags					= 0;
		CreateInfo.stageCount				= StageCount;
		CreateInfo.pStages					= StageList;
		CreateInfo.pVertexInputState		= &VertexInput;
		CreateInfo.pInputAssemblyState		= &InputAssembly;
		if (TesselationShaderExists) {
			CreateInfo.pTessellationState = &Tesselation;
		}
		else {
			CreateInfo.pTessellationState = NULL;
		}
		CreateInfo.pViewportState			= &Viewport;
		CreateInfo.pRasterizationState		= &Rasterizer;
		CreateInfo.pMultisampleState		= &Multisample;
		CreateInfo.pDepthStencilState		= &DepthStencil;
		CreateInfo.pColorBlendState			= &ColorBlend;
		CreateInfo.pDynamicState			= &DynamicState;
		CreateInfo.layout					= VK_NULL_HANDLE;
		CreateInfo.renderPass				= VK_NULL_HANDLE;
		CreateInfo.subpass					= 0;
		CreateInfo.basePipelineHandle		= VK_NULL_HANDLE;
		CreateInfo.basePipelineIndex		= 0;

	}

	pipeline::raytracer::raytracer() {

	}

	pipeline::compute::compute() {

	}

	pipeline::pipeline(context* aContext, rasterizer& aRasterizer, VkRenderPass aRenderPass, uint32_t aSubpassIndex) {
		VkResult Result = VkResult::VK_SUCCESS;

		Type = VK_PIPELINE_BIND_POINT_GRAPHICS;
		Context = aContext;
		Rasterizer = aRasterizer;

		// Create Descriptor Set Layouts
		for (uint32_t i = 0; i < Rasterizer.UniformSetCount; i++) {
			VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo{};
			DescriptorSetLayoutCreateInfo.sType				= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			DescriptorSetLayoutCreateInfo.pNext				= NULL;
			DescriptorSetLayoutCreateInfo.flags				= 0;
			DescriptorSetLayoutCreateInfo.bindingCount		= Rasterizer.UniformSetBindingCount[i];
			DescriptorSetLayoutCreateInfo.pBindings			= Rasterizer.UniformSetBindingList[i];
			Result = vkCreateDescriptorSetLayout(Context->handle(), &DescriptorSetLayoutCreateInfo, NULL, &DescriptorSetLayoutList[i]);
		}

		VkDescriptorSetLayoutBinding;

		// Number of Pool Types.

		VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
		DescriptorPoolCreateInfo.sType			= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		DescriptorPoolCreateInfo.pNext			= NULL;
		DescriptorPoolCreateInfo.flags			= 0;
		DescriptorPoolCreateInfo.maxSets		;
		DescriptorPoolCreateInfo.poolSizeCount	;
		DescriptorPoolCreateInfo.pPoolSizes		;

		Result = vkCreateDescriptorPool(Context->handle(), &DescriptorPoolCreateInfo, NULL, &DescriptorPool);

		VkPipelineLayoutCreateInfo LayoutCreateInfo{};
		LayoutCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		LayoutCreateInfo.pNext					= NULL;
		LayoutCreateInfo.flags					= 0;
		LayoutCreateInfo.setLayoutCount			;
		LayoutCreateInfo.pSetLayouts			;
		LayoutCreateInfo.pushConstantRangeCount	= 0;
		LayoutCreateInfo.pPushConstantRanges	= NULL;

		// Load rasterizer
		Rasterizer.CreateInfo.layout			= Layout;
		Rasterizer.CreateInfo.renderPass		= aRenderPass;
		Rasterizer.CreateInfo.subpass			= aSubpassIndex;

		Result = vkCreatePipelineLayout(Context->handle(), &LayoutCreateInfo, NULL, &Layout);

		Result = vkCreateGraphicsPipelines(Context->handle(), VK_NULL_HANDLE, 1, &Rasterizer.CreateInfo, NULL, &Handle);
	}

	pipeline::pipeline(context* aContext, raytracer& aRaytracer) {
		VkResult Result = VkResult::VK_SUCCESS;

		Type = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
		Context = aContext;
		Raytracer = aRaytracer;

		//Result = vkCreateRayTracingPipelinesKHR(Context->handle())
	}

	pipeline::pipeline(context* aContext, compute& aCompute) {
		VkResult Result = VkResult::VK_SUCCESS;

		Type = VK_PIPELINE_BIND_POINT_COMPUTE;
		Context = aContext;
		Compute = aCompute;

		Result = vkCreateComputePipelines(Context->handle(), Cache, 1, &Compute.CreateInfo, NULL, &Handle);
	}

	void pipeline::subpass(VkCommandBuffer aCommandBuffer) {
		vkCmdBindPipeline(aCommandBuffer, Type, Handle);
		switch (Type) {
		default:
			break;
		case VK_PIPELINE_BIND_POINT_GRAPHICS:

			break;
		case VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR:
			break;
		case VK_PIPELINE_BIND_POINT_COMPUTE:
			break;
		}
	}

}
