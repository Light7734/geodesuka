#include <geodesuka/builtin/object/triangle.h>

#include <geodesuka/engine.h>

using namespace geodesuka::core;
using namespace object;
using namespace hid;
using namespace math;
using namespace gcl;
using namespace util;

namespace geodesuka::builtin::object {

	/*
	triangle::triangle(engine* aEngine, core::gcl::context* aContext, stage_t* aStage) : object_t(aEngine, aContext, aStage) {
		return;

		// Hard coded vertices
		math::real Vertices[] = {
			-1.0, 0.0, 1.0, 0.0, 0.0, 
			 0.0, 1.0, 0.0, 1.0, 0.0, 
			 1.0, 0.0, 0.0, 0.0, 1.0 
		};


		util::variable Variable(util::type::id::STRUCT, "Vertex");
		Variable.Type.push(util::type::id::FLOAT2, "Position");
		Variable.Type.push(util::type::id::FLOAT3, "Color");
		//Variable.Type.push(util::type::id::REAL3, "Color");

		buffer* VertexBuffer = new buffer(
			aContext,
			device::memory::DEVICE_LOCAL,
			buffer::usage::VERTEX | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST,
			3,
			Variable,
			Vertices
		);

		// Shader Sources hard coded into triangle. 
		const char* VertexShaderSource =
			"#version 450\n\
			#extension GL_ARB_separate_shader_objects : require \n\
			#extension GL_KHR_vulkan_glsl : enable \n\
			\n\
			layout (location = 0) in vec2 VertexPosition; \n\
			layout (location = 1) in vec3 VertexColor; \n\
			\n\
			layout (location = 0) out vec3 InterpColor;\n\
			\n\
			void main() {\n\
			    gl_Position = vec4(VertexPosition, 0.0, 1.0);\n\
			    InterpColor = VertexColor;\n\
			}";

		const char* FragmentShaderSource =
			"#version 450\n\
			#extension GL_ARB_separate_shader_objects : require \n\
			#extension GL_KHR_vulkan_glsl : enable \n\
			\n\
			layout(location = 0) in vec3 InterpColor;\n\
			\n\
			layout(location = 0) out vec4 PixelColor;\n\
			\n\
			void main() {\n\
			    PixelColor = vec4(InterpColor, 1.0);\n\
			}";

		// Does everything above but in two lines.
		shader VertexShader(aContext, shader::VERTEX, VertexShaderSource);
		shader FragmentShader(aContext, shader::FRAGMENT, FragmentShaderSource);

		// Do not run until finished working on this. Need pipeline abstraction first.
		VkResult Result = VkResult::VK_SUCCESS;
		VkAttachmentDescription AttachmentDescription[2] = { {}, {} };

		//// Subpass Description.
		//this->Subpass[0].flags						= 0;
		//this->Subpass[0].pipelineBindPoint			;
		//this->Subpass[0].inputAttachmentCount		;
		//this->Subpass[0].pInputAttachments			;
		//this->Subpass[0].colorAttachmentCount		;
		//this->Subpass[0].pColorAttachments			;
		//this->Subpass[0].pResolveAttachments		;
		//this->Subpass[0].pDepthStencilAttachment	;
		//this->Subpass[0].preserveAttachmentCount	;
		//this->Subpass[0].pPreserveAttachments		;

		//AttachmentDescription[0].flags				= 0;
		//AttachmentDescription[0].format				= VkFormat::VK_FORMAT_R8G8B8A8_SRGB;
		//AttachmentDescription[0].samples			= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		//AttachmentDescription[0].loadOp				= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		//AttachmentDescription[0].storeOp			= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//AttachmentDescription[0].stencilLoadOp		= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		//AttachmentDescription[0].stencilStoreOp		= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//AttachmentDescription[0].initialLayout		= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		//AttachmentDescription[0].finalLayout		= VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		//AttachmentDescription[1].flags				= 0;
		//AttachmentDescription[1].format				= VkFormat::VK_FORMAT_D32_SFLOAT;
		//AttachmentDescription[1].samples			= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		//AttachmentDescription[1].loadOp				= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		//AttachmentDescription[1].storeOp			= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//AttachmentDescription[1].stencilLoadOp		= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		//AttachmentDescription[1].stencilStoreOp		= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
		//AttachmentDescription[1].initialLayout		= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
		//AttachmentDescription[1].finalLayout		= VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		//VkAttachmentReference ColorAttachment{};
		//ColorAttachment.attachment		= 0;
		//ColorAttachment.layout			= VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		//VkAttachmentReference DepthAttachment{};
		//DepthAttachment.attachment		= 1;
		//DepthAttachment.layout			= VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


		//VkSubpassDescription Subpass{};
		//Subpass.flags						= 0;
		//Subpass.pipelineBindPoint			= VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
		//Subpass.inputAttachmentCount		= 0;
		//Subpass.pInputAttachments			= NULL;
		//Subpass.colorAttachmentCount		= 1;
		//Subpass.pColorAttachments			= &ColorAttachment;
		//Subpass.pResolveAttachments			= NULL;
		//Subpass.pDepthStencilAttachment		= &DepthAttachment;
		//Subpass.preserveAttachmentCount		= 0;
		//Subpass.pPreserveAttachments		= NULL;


		//VkRenderPassCreateInfo RPCreateInfo{};
		//RPCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		//RPCreateInfo.pNext				= NULL;
		//RPCreateInfo.flags				= 0;
		//RPCreateInfo.attachmentCount	= 2;
		//RPCreateInfo.pAttachments		= AttachmentDescription;
		//RPCreateInfo.subpassCount		= 1;
		//RPCreateInfo.pSubpasses			= &Subpass;
		//RPCreateInfo.dependencyCount	= 0;
		//RPCreateInfo.pDependencies		= NULL;

		////Result = vkCreateRenderPass(Context->handle(), );

		////VkRenderPass RenderPass = VK_NULL_HANDLE;
		//Result = vkCreateRenderPass(aContext->handle(), &RPCreateInfo, NULL, &this->RenderPass);

		//VkPipelineShaderStageCreateInfo ShaderStage[2];
		//VkVertexInputAttributeDescription Attribute[2];
		//VkVertexInputBindingDescription BindingLocation;

		//Attribute[0].location		= 0;
		//Attribute[0].binding		= 0;
		//Attribute[0].format			= VkFormat::VK_FORMAT_R32G32_SFLOAT;
		//Attribute[0].offset			= 0;

		//Attribute[1].location		= 1;
		//Attribute[1].binding		= 0;
		//Attribute[1].format			= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
		//Attribute[1].offset			= 8;

		//BindingLocation.binding		= 0;
		//BindingLocation.stride		= 20;
		//BindingLocation.inputRate	= VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

		//VkPipelineVertexInputStateCreateInfo VertexInput{};
		//VertexInput.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		//VertexInput.pNext								= NULL;
		//VertexInput.flags								= 0;
		//VertexInput.vertexBindingDescriptionCount		= 1;
		//VertexInput.pVertexBindingDescriptions			= &BindingLocation;
		//VertexInput.vertexAttributeDescriptionCount		= 2;
		//VertexInput.pVertexAttributeDescriptions		= Attribute;

		//VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
		//InputAssembly.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		//InputAssembly.pNext						= NULL;
		//InputAssembly.flags						= 0;
		//InputAssembly.topology					= VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		//InputAssembly.primitiveRestartEnable	= VK_FALSE;
		//
		//VkViewport ScreenSize;
		//ScreenSize.x = 0;
		//ScreenSize.y = 0;
		//ScreenSize.width = 640;
		//ScreenSize.height = 480;
		//ScreenSize.minDepth = 0.0;
		//ScreenSize.maxDepth = 1.0;

		//VkRect2D ScissorStuff = { { 0, 0 }  , { 640, 480 } };
		//

		//VkPipelineViewportStateCreateInfo Viewport{};
		//Viewport.sType				= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		//Viewport.pNext				= NULL;
		//Viewport.flags				= 0;
		//Viewport.viewportCount		= 1;
		//Viewport.pViewports			= &ScreenSize;
		//Viewport.scissorCount		= 1;
		//Viewport.pScissors			= &ScissorStuff;

		//VkPipelineRasterizationStateCreateInfo Rasterizer{};
		//Rasterizer.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		//Rasterizer.pNext						= NULL;
		//Rasterizer.flags						= 0;
		//Rasterizer.depthClampEnable				= VK_TRUE;
		//Rasterizer.rasterizerDiscardEnable		= VK_TRUE;
		//Rasterizer.polygonMode					= VkPolygonMode::VK_POLYGON_MODE_FILL;
		//Rasterizer.cullMode						= VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
		//Rasterizer.frontFace					= VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;
		//Rasterizer.depthBiasEnable				= VK_FALSE;
		//Rasterizer.depthBiasConstantFactor		= 1.0;
		//Rasterizer.depthBiasClamp				= 0.0;
		//Rasterizer.depthBiasSlopeFactor			= 0.0;
		//Rasterizer.lineWidth					= 1.0;

		////VkSampleMask SampleMask

		//VkPipelineMultisampleStateCreateInfo Multisample{};
		//Multisample.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		//Multisample.pNext					= NULL;
		//Multisample.flags					= 0;
		//Multisample.rasterizationSamples	= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
		//Multisample.sampleShadingEnable		= VK_FALSE;
		//Multisample.minSampleShading		= 1.0;
		//Multisample.pSampleMask				= NULL;
		//Multisample.alphaToCoverageEnable	= VK_TRUE;
		//Multisample.alphaToOneEnable		= VK_FALSE;

		//VkPipelineDepthStencilStateCreateInfo DepthStencil{};
		//DepthStencil.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		//DepthStencil.pNext						= NULL;
		//DepthStencil.flags						= 0;
		//DepthStencil.depthTestEnable			= VK_TRUE;
		//DepthStencil.depthWriteEnable			= VK_TRUE;
		//DepthStencil.depthCompareOp				= VkCompareOp::VK_COMPARE_OP_LESS;
		//DepthStencil.depthBoundsTestEnable		= VK_FALSE;
		//DepthStencil.stencilTestEnable			= VK_FALSE;
		//DepthStencil.front						= {};
		//DepthStencil.back						= {};
		//DepthStencil.minDepthBounds				= 0.0;
		//DepthStencil.maxDepthBounds				= 1.0;

		//VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
		//ColorBlendAttachment.blendEnable			= VK_TRUE;
		//ColorBlendAttachment.srcColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
		//ColorBlendAttachment.dstColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
		//ColorBlendAttachment.colorBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
		//ColorBlendAttachment.srcAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE;
		//ColorBlendAttachment.dstAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ZERO;
		//ColorBlendAttachment.alphaBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
		//ColorBlendAttachment.colorWriteMask			= VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT;


		//VkPipelineColorBlendStateCreateInfo Blending{};
		//Blending.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		//Blending.pNext					= NULL;
		//Blending.flags					= 0;
		//Blending.logicOpEnable			= VK_FALSE;
		//Blending.logicOp				;
		//Blending.attachmentCount		= 1;
		//Blending.pAttachments			= &ColorBlendAttachment;
		//Blending.blendConstants[0]		= 0.0;
		//Blending.blendConstants[1]		= 0.0;
		//Blending.blendConstants[2]		= 0.0;
		//Blending.blendConstants[3]		= 0.0;


		//// Sets up shaders in graphics pipeline.
		//ShaderStage[0].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		//ShaderStage[0].pNext = NULL;
		//ShaderStage[0].flags = 0;
		//ShaderStage[0].stage = VertexShader.get_stage();
		//ShaderStage[0].module = VertexShader.get_handle();
		//ShaderStage[0].pName = "main";
		//ShaderStage[0].pSpecializationInfo = NULL;

		//ShaderStage[1].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		//ShaderStage[1].pNext = NULL;
		//ShaderStage[1].flags = 0;
		//ShaderStage[1].stage = FragmentShader.get_stage();
		//ShaderStage[1].module = FragmentShader.get_handle();
		//ShaderStage[1].pName = "main";
		//ShaderStage[1].pSpecializationInfo = NULL;

		//VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo{};
		//VkPipelineLayout PipelineLayout;
		//PipelineLayoutCreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		//PipelineLayoutCreateInfo.pNext						= NULL;
		//PipelineLayoutCreateInfo.flags						= 0;
		//PipelineLayoutCreateInfo.setLayoutCount				= 0;
		//PipelineLayoutCreateInfo.pSetLayouts				= NULL;
		//PipelineLayoutCreateInfo.pushConstantRangeCount		= 0;
		//PipelineLayoutCreateInfo.pPushConstantRanges		= NULL;
		//Result = vkCreatePipelineLayout(aContext->handle(), &PipelineLayoutCreateInfo, NULL, &PipelineLayout);

		//VkGraphicsPipelineCreateInfo CreateInfo{};	
		//CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		//CreateInfo.pNext					= NULL;
		//CreateInfo.flags					= 0;
		//CreateInfo.stageCount				= 2;
		//CreateInfo.pStages					= ShaderStage;
		//CreateInfo.pVertexInputState		= &VertexInput;
		//CreateInfo.pInputAssemblyState		= &InputAssembly;
		//CreateInfo.pTessellationState		= NULL;
		//CreateInfo.pViewportState			= &Viewport;
		//CreateInfo.pRasterizationState		= &Rasterizer;
		//CreateInfo.pMultisampleState		= &Multisample;
		//CreateInfo.pDepthStencilState		= &DepthStencil;
		//CreateInfo.pColorBlendState			= &Blending;
		//CreateInfo.pDynamicState			= NULL;
		//CreateInfo.layout					= PipelineLayout;
		//CreateInfo.renderPass				= RenderPass;
		//CreateInfo.subpass					= 0;
		//CreateInfo.basePipelineHandle		= VK_NULL_HANDLE;
		//CreateInfo.basePipelineIndex		= 0;

	}

	triangle::~triangle() {

	}
	*/

}
