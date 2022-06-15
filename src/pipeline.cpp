#include <geodesuka/core/gcl/pipeline.h>

#include <cassert>

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

		this->DynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		this->DynamicState.pNext = NULL;
		this->DynamicState.flags = 0;

		bool TesselationShaderExists = false;
		bool GeometryShaderExists = false;

		StageCount = aShaderCount;
		StageList = (vk_pipeline_shader_stage_create_info*)malloc(StageCount * sizeof(vk_pipeline_shader_stage_create_info));
		if (StageList != NULL) {
			for (uint32_t i = 0; i < aShaderCount; i++) {
				StageList[i] = aShaderList[i]->stageci();
			}
		}


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

	pipeline::pipeline(context* aContext, rasterizer& aRasterizer) {
		VkResult Result = VkResult::VK_SUCCESS;

		AttachmentReferenceCount = 0;
		AttachmentReferenceList = NULL;
		RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassCreateInfo.pNext = NULL;

		Context = aContext;
		Rasterizer = aRasterizer;

		BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		VkDescriptorSetLayoutCreateInfo DSLCreateInfo{};

		VkDescriptorSetAllocateInfo AllocateInfo{};
		VkPipelineLayoutCreateInfo LayoutCreateInfo{};
		LayoutCreateInfo.sType					= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		LayoutCreateInfo.pNext					= NULL;
		LayoutCreateInfo.flags					= 0;
		LayoutCreateInfo.setLayoutCount			;
		LayoutCreateInfo.pSetLayouts			;
		LayoutCreateInfo.pushConstantRangeCount	= 0;
		LayoutCreateInfo.pPushConstantRanges	= NULL;

		Result = vkCreatePipelineLayout(Context->handle(), &LayoutCreateInfo, NULL, &Layout);

		Rasterizer.CreateInfo.layout			= Layout;

		if (Rasterizer.CreateInfo.renderPass == VK_NULL_HANDLE) {
			AttachmentReferenceCount = Rasterizer.OutputCount;
			AttachmentReferenceList = (vk_attachment_reference*)malloc(AttachmentReferenceCount * sizeof(vk_attachment_reference));
			assert(AttachmentReferenceList != NULL);

			for (uint32_t i = 0; i < AttachmentReferenceCount; i++) {
				AttachmentReferenceList[i].attachment	= i;
				AttachmentReferenceList[i].layout		= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			}

			SubpassDescription.flags					= 0;
			SubpassDescription.pipelineBindPoint		= BindPoint;
			SubpassDescription.inputAttachmentCount		= 0;				// This is inter subpass resource reusing.
			SubpassDescription.pInputAttachments		= NULL;				// This is inter subpass resource reusing.
			SubpassDescription.colorAttachmentCount		= AttachmentReferenceCount;
			SubpassDescription.pColorAttachments		= AttachmentReferenceList;
			SubpassDescription.pResolveAttachments		= NULL;
			SubpassDescription.pDepthStencilAttachment	= NULL;
			SubpassDescription.preserveAttachmentCount	= 0;
			SubpassDescription.pPreserveAttachments		= NULL;

			SubpassDependency.srcSubpass				= VK_SUBPASS_EXTERNAL;
			SubpassDependency.dstSubpass				= 0;
			SubpassDependency.srcStageMask				= VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
			SubpassDependency.dstStageMask				= VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			SubpassDependency.srcAccessMask				= VK_ACCESS_MEMORY_WRITE_BIT;
			SubpassDependency.dstAccessMask				= VK_ACCESS_SHADER_WRITE_BIT;
			SubpassDependency.dependencyFlags			= 0;

			RenderPassCreateInfo.flags					= 0;
			RenderPassCreateInfo.attachmentCount		= Rasterizer.OutputCount;
			RenderPassCreateInfo.pAttachments			= Rasterizer.OutputList;
			RenderPassCreateInfo.subpassCount			= 1;
			RenderPassCreateInfo.pSubpasses				= &SubpassDescription;
			RenderPassCreateInfo.dependencyCount		= 1;
			RenderPassCreateInfo.pDependencies			= &SubpassDependency;
			// Only Create If Render Pass has not been provided. Create Single Subpass RenderPass.
			Result = vkCreateRenderPass(Context->handle(), &RenderPassCreateInfo, NULL, &RenderPass);

			Rasterizer.CreateInfo.renderPass			= RenderPass;
			Rasterizer.CreateInfo.subpass				= 0;
		}


		Result = vkCreateGraphicsPipelines(Context->handle(), Cache, 1, &Rasterizer.CreateInfo, NULL, &Handle);

	}

	pipeline::pipeline(context* aContext, raytracer& aRaytracer) {
		VkResult Result = VkResult::VK_SUCCESS;

		BindPoint = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;
		Context = aContext;
		Raytracer = aRaytracer;

		//Result = vkCreateRayTracingPipelinesKHR(Context->handle())
	}

	pipeline::pipeline(context* aContext, compute& aCompute) {
		VkResult Result = VkResult::VK_SUCCESS;

		BindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;
		Context = aContext;
		Compute = aCompute;

		Result = vkCreateComputePipelines(Context->handle(), Cache, 1, &Compute.CreateInfo, NULL, &Handle);
	}

}
