#include <geodesuka/core/gcl/pipeline.h>

namespace geodesuka::core::gcl {




	// Graphics Pipeline
	pipeline::pipeline(
		context* aContext,
		uint32_t aShaderCount, shader* aShader,
		uint32_t aDSLCount, VkDescriptorSetLayout* aDSL,
		renderpass& aRenderPass, uint32_t aSubpassIndex
	) {

		this->gdefault();

		VkResult Result = VkResult::VK_SUCCESS;

		// Load shaders.
		this->ShaderStage = (VkPipelineShaderStageCreateInfo*)malloc(this->ShaderCount * sizeof(VkPipelineShaderStageCreateInfo));
		for (uint32_t i = 0; i < this->ShaderCount; i++) {
			this->ShaderStage[i] = this->Shader[i].stageci();
		}

		VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
		DescriptorPoolCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		DescriptorPoolCreateInfo.pNext				= NULL;
		DescriptorPoolCreateInfo.flags				= 0;
		DescriptorPoolCreateInfo.maxSets			;
		DescriptorPoolCreateInfo.poolSizeCount		;
		DescriptorPoolCreateInfo.pPoolSizes			;

		// Create Pipeline Layout.
		this->LayoutCreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		this->LayoutCreateInfo.pNext					= NULL;
		this->LayoutCreateInfo.flags					= 0;
		this->LayoutCreateInfo.setLayoutCount			= aDSLCount;
		this->LayoutCreateInfo.pSetLayouts				= aDSL;
		this->LayoutCreateInfo.pushConstantRangeCount	= 0;
		this->LayoutCreateInfo.pPushConstantRanges		= NULL;
		Result = vkCreatePipelineLayout(this->Context->handle(), &this->LayoutCreateInfo, NULL, &this->Layout);



	}

	pipeline::~pipeline() {

	}

	void pipeline::gdefault() {
		this->GraphicsCreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		this->GraphicsCreateInfo.pNext					= NULL;
		this->GraphicsCreateInfo.flags					= 0;
		this->GraphicsCreateInfo.stageCount				= 0;
		this->GraphicsCreateInfo.pStages				= NULL;
		this->GraphicsCreateInfo.pVertexInputState		= &this->VertexInput;
		this->GraphicsCreateInfo.pInputAssemblyState	= &this->InputAssembly;
		this->GraphicsCreateInfo.pTessellationState		= &this->Tesselation;
		this->GraphicsCreateInfo.pViewportState			= &this->Viewport;
		this->GraphicsCreateInfo.pRasterizationState	= &this->Rasterizer;
		this->GraphicsCreateInfo.pMultisampleState		= &this->Multisample;
		this->GraphicsCreateInfo.pDepthStencilState		= &this->DepthStencil;
		this->GraphicsCreateInfo.pColorBlendState		= &this->ColorBlend;
		this->GraphicsCreateInfo.pDynamicState			= &this->DynamicState;
		this->GraphicsCreateInfo.layout					= VK_NULL_HANDLE;
		this->GraphicsCreateInfo.renderPass				= VK_NULL_HANDLE;
		this->GraphicsCreateInfo.subpass				= 0;
		this->GraphicsCreateInfo.basePipelineHandle		= VK_NULL_HANDLE;
		this->GraphicsCreateInfo.basePipelineIndex		= 0;

		this->VertexInput.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		this->VertexInput.pNext = NULL;
		this->VertexInput.flags = 0;

		this->InputAssembly.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		this->InputAssembly.pNext = NULL;
		this->InputAssembly.flags = 0;

		this->Tesselation.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		this->Tesselation.pNext = NULL;
		this->Tesselation.flags = 0;

		this->Viewport.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		this->Viewport.pNext = NULL;
		this->Viewport.flags = 0;

		this->Rasterizer.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		this->Rasterizer.pNext = NULL;
		this->Rasterizer.flags = 0;

		this->Multisample.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		this->Multisample.pNext = NULL;
		this->Multisample.flags = 0;

		this->DepthStencil.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		this->DepthStencil.pNext = NULL;
		this->DepthStencil.flags = 0;
		
		this->ColorBlend.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		this->ColorBlend.pNext = NULL;
		this->ColorBlend.flags = 0;

		this->DynamicState.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		this->DynamicState.pNext = NULL;
		this->DynamicState.flags = 0;
	}

}
