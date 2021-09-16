#include "triangle.h"

#include <geodesuka/engine.h>

using namespace geodesuka::core;
using namespace object;
using namespace hid;
using namespace math;
using namespace gcl;

triangle::triangle(geodesuka::engine &aEngine, gcl::device_context* aDeviceContext) {

	// Hard coded vertices
	float Vertices[] = {
		-1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0, 0.0, 1.0
	};

	// Shader Sources hard coded into triangle. 
	const char* VertexShaderSource =
		"#version 450\n\
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
		\n\
		layout(location = 0) in vec3 InterpColor;\n\
		\n\
		layout(location = 0) out vec4 PixelColor;\n\
		\n\
		void main() {\n\
		    PixelColor = vec4(InterpColor, 1.0);\n\
		}";

	// Does everything above but in two lines.
	shader VertexShader(aDeviceContext, shader::VERTEX, VertexShaderSource);
	shader FragmentShader(aDeviceContext, shader::FRAGMENT, FragmentShaderSource);

	//std::cout << "Vertex Shader Compile Status: " << aEngine.get_er_str(VertexShader.ErrorCode) << std::endl;
	//std::cout << "Fragment Shader Compile Status: " << aEngine.get_er_str(FragmentShader.ErrorCode) << std::endl;

	// Sets up shaders in graphics pipeline
	this->ShaderStage.resize(2);
	this->ShaderStage[0].sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	this->ShaderStage[0].pNext					= NULL;
	this->ShaderStage[0].flags					= 0;
	this->ShaderStage[0].stage					= VertexShader.get_stage();
	this->ShaderStage[0].module					= VertexShader.get_handle();
	this->ShaderStage[0].pName					= "Vertex Shader";
	this->ShaderStage[0].pSpecializationInfo	= NULL;

	this->ShaderStage[1].sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	this->ShaderStage[1].pNext					= NULL;
	this->ShaderStage[1].flags					= 0;
	this->ShaderStage[1].stage					= FragmentShader.get_stage();
	this->ShaderStage[1].module					= FragmentShader.get_handle();
	this->ShaderStage[1].pName					= "Fragment Shader";
	this->ShaderStage[1].pSpecializationInfo	= NULL;

	// Set up vertex map.

	// Defines the per vertex stride of each vertex buffer bound in draw call.
	this->InputBindingDescription.resize(1);
	this->InputBindingDescription[0].binding		= 0;	// Vertex Binding index in vkCmdBindVertexBuffers(...)
	this->InputBindingDescription[0].stride			= 5 * sizeof(float);
	this->InputBindingDescription[0].inputRate		= VK_VERTEX_INPUT_RATE_VERTEX;

	this->InputAttributeDescription.resize(2);
	// Describes "layout (location = 0) in vec2 VertexPosition;"
	this->InputAttributeDescription[0].location		= 0; // Specifies the location within the appropriate shader.
	this->InputAttributeDescription[0].binding		= 0;
	this->InputAttributeDescription[0].format		= VkFormat::VK_FORMAT_R32G32_SFLOAT;
	this->InputAttributeDescription[0].offset		= 0;

	// Describes "layout (location = 1) in vec3 VertexColor;"
	this->InputAttributeDescription[1].location		= 1; // Specifies the location within the appropriate shader.
	this->InputAttributeDescription[1].binding		= 0;
	this->InputAttributeDescription[1].format		= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
	this->InputAttributeDescription[1].offset		= 2 * sizeof(float);

	// Wrap binding and attribute descriptions in VertexInput state create info.
	this->VertexInput.sType								= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	this->VertexInput.pNext								= NULL;
	this->VertexInput.flags								= 0;
	this->VertexInput.vertexBindingDescriptionCount		= this->InputBindingDescription.size(); // Only one intended binding, using interleaved format.
	this->VertexInput.pVertexBindingDescriptions		= this->InputBindingDescription.data();
	this->VertexInput.vertexAttributeDescriptionCount	= this->InputAttributeDescription.size();
	this->VertexInput.pVertexAttributeDescriptions		= this->InputAttributeDescription.data();

	// Interpret Vertices as triangle.
	this->InputAssembly.sType					= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	this->InputAssembly.pNext					= NULL;
	this->InputAssembly.flags					= 0;
	this->InputAssembly.topology				= VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	this->InputAssembly.primitiveRestartEnable	= VK_FALSE;

	// Viewport Options.

	// sub windows maybe?
	VkViewport Viewport{};
	Viewport.x = 0;
	Viewport.y = 0;
	Viewport.width = 640;
	Viewport.height = 480;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	// Kind of cool, might fuck with later
	VkRect2D Scissor{};
	Scissor.offset = { 0, 0 };
	//Scissor.extent = Window->FrameBuffer.Property.Extent2D;


	this->Viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	this->Viewport.pNext = NULL;
	//this->Viewport

	// Full pipeline create info
	this->CreateInfo.sType					= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	this->CreateInfo.pNext					= NULL;
	this->CreateInfo.flags					= 0;
	this->CreateInfo.stageCount				= (uint32_t)this->ShaderStage.size();
	this->CreateInfo.pStages				= this->ShaderStage.data();
	this->CreateInfo.pVertexInputState		= &this->VertexInput;
	this->CreateInfo.pInputAssemblyState	= &this->InputAssembly;
	this->CreateInfo.pTessellationState		= NULL;
	this->CreateInfo.pViewportState			= &this->Viewport;
	this->CreateInfo.pRasterizationState	= &this->Rasterizer;
	this->CreateInfo.pMultisampleState		= &this->Multisample;
	this->CreateInfo.pDepthStencilState		= NULL;// &DepthStencil;
	this->CreateInfo.pColorBlendState		= &this->ColorBlend;
	this->CreateInfo.pDynamicState			= NULL;// &DynamicState;
	//this->CreateInfo.layout  = 

	vkCreateGraphicsPipelines(aDeviceContext->handle(), VK_NULL_HANDLE, 1, &this->CreateInfo, NULL, &this->GraphicsPipeline);

	VkAttachmentDescription;

	//VkRenderPassCreateInfo RenderPassCI{};
	//VkRenderPass RenderPass;

	//VkFramebufferCreateInfo FramebufferCI{};
	//VkFramebuffer Framebuffer;


	//FramebufferCI.sType = VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	//FramebufferCI.pNext = NULL;
	//FramebufferCI.flags = 0;
	////FramebufferCI.renderPass		= Describes the images and attachment layouts?;
	////FramebufferCI.attachmentCount	= 1;
	////FramebufferCI.pAttachments		= Image Views go here.;
	//FramebufferCI.width = Window->FrameBuffer.Property.Extent2D.width;
	//FramebufferCI.height = Window->FrameBuffer.Property.Extent2D.height;
	//FramebufferCI.layers = 1;

	//vkCreateFramebuffer(aDeviceContext->get_handle(), &FramebufferCI, NULL, &Framebuffer);

	//// ---------------------------------------- Graphics Pipeline ---------------------------------------- //
	///*
	//* This is a lot of information to describe a pipeline, but I do prefer this over the state machine model.
	//* At least it is easy to know exactly what is going on. Rather than a global state machine, this is rather
	//* contained.
	//*/

	//VkPipelineCache Cache;
	//VkPipeline GraphicsPipeline;

	//VkPipelineCacheCreateInfo CacheCI;
	//VkGraphicsPipelineCreateInfo GraphicsPipelineCI;

	//// Loads compiled shaders into graphics pipeline
	//std::vector<VkPipelineShaderStageCreateInfo> ShaderStage(2);

	//// Vertex Shader
	//ShaderStage[0].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	//ShaderStage[0].pNext = NULL;
	//ShaderStage[0].flags = 0;
	//ShaderStage[0].stage = VertexShader.get_stage();
	//ShaderStage[0].module = VertexShader.get_handle();
	//ShaderStage[0].pName = "Vertex Shader";
	//ShaderStage[0].pSpecializationInfo = NULL;

	//// Fragment Shader
	//ShaderStage[1].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	//ShaderStage[1].pNext = NULL;
	//ShaderStage[1].flags = 0;
	//ShaderStage[1].stage = FragmentShader.get_stage();
	//ShaderStage[1].module = FragmentShader.get_handle();
	//ShaderStage[1].pName = "Fragment Shader";
	//ShaderStage[1].pSpecializationInfo = NULL;

	//// Describes map for buffers to graphics pipeline.
	//VkPipelineVertexInputStateCreateInfo VertexInputStateCI;
	//VertexInputStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	//VertexInputStateCI.pNext = NULL;
	//VertexInputStateCI.flags = 0; // Reserved for Future use. (Ignore)
	//VertexInputStateCI.vertexBindingDescriptionCount = 0;
	//VertexInputStateCI.pVertexBindingDescriptions = NULL;
	//VertexInputStateCI.vertexAttributeDescriptionCount = 0;
	//VertexInputStateCI.pVertexAttributeDescriptions = NULL;

	//// Input assembly topology for how the rasterizer will interpret vertex data.
	//VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCI;
	//InputAssemblyStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	//InputAssemblyStateCI.pNext = NULL;
	//InputAssemblyStateCI.flags = 0; // Reserved for future use. (Ignore)
	//InputAssemblyStateCI.topology = VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	//InputAssemblyStateCI.primitiveRestartEnable = VK_FALSE; // Most likely never going to use this.

	//// sub windows maybe?
	//VkViewport Viewport{};
	//Viewport.x = 0;
	//Viewport.y = 0;
	//Viewport.width = Window->Resolution.x;
	//Viewport.height = Window->Resolution.y;
	//Viewport.minDepth = 0.0f;
	//Viewport.maxDepth = 1.0f;

	//// Kind of cool, might fuck with later
	//VkRect2D Scissor{};
	//Scissor.offset = { 0, 0 };
	//Scissor.extent = Window->FrameBuffer.Property.Extent2D;

	//// Creates Viewport, (How can there be multiple scissors and viewports? What does this mean?)
	//VkPipelineViewportStateCreateInfo ViewportStateCI{};
	//ViewportStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	//ViewportStateCI.pNext = NULL;
	//ViewportStateCI.flags = 0; // Reserved for future use (Ignored)
	//ViewportStateCI.viewportCount = 1;
	//ViewportStateCI.pViewports = &Viewport;
	//ViewportStateCI.scissorCount = 1;
	//ViewportStateCI.pScissors = &Scissor;

	//VkPipelineRasterizationStateCreateInfo RasterizationStateCI;
	//RasterizationStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	//RasterizationStateCI.pNext = NULL;
	//RasterizationStateCI.flags = 0; // Cool, reserved for future use.
	//RasterizationStateCI.depthClampEnable = VK_FALSE;
	//RasterizationStateCI.rasterizerDiscardEnable = VK_FALSE; // Fuck no
	//RasterizationStateCI.polygonMode = VkPolygonMode::VK_POLYGON_MODE_FILL;
	//RasterizationStateCI.cullMode = VkCullModeFlagBits::VK_CULL_MODE_NONE;
	//RasterizationStateCI.frontFace = VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE; // Defines CCW as front face.
	//RasterizationStateCI.depthBiasEnable = VK_FALSE;
	//RasterizationStateCI.depthBiasConstantFactor = 0.0f;
	//RasterizationStateCI.depthBiasClamp = 0.0f;
	//RasterizationStateCI.depthBiasSlopeFactor = 0.0f;
	//RasterizationStateCI.lineWidth = 1.0f;

	//VkPipelineMultisampleStateCreateInfo MultisampleStateCI;
	//MultisampleStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	//MultisampleStateCI.pNext = NULL;
	//MultisampleStateCI.flags = 0; // Fuck yeah
	//MultisampleStateCI.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	//MultisampleStateCI.sampleShadingEnable = VK_FALSE;
	//MultisampleStateCI.minSampleShading = 1.0f;
	//MultisampleStateCI.pSampleMask = NULL;
	//MultisampleStateCI.alphaToCoverageEnable = VK_FALSE;
	//MultisampleStateCI.alphaToOneEnable = VK_FALSE;

	///*
	//VkPipelineDepthStencilStateCreateInfo DepthStencilStateCI;
	//DepthStencilStateCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	//DepthStencilStateCI.pNext						= NULL;
	//DepthStencilStateCI.flags						= 0; // NICE
	//DepthStencilStateCI.depthTestEnable				;
	//DepthStencilStateCI.depthWriteEnable			;
	//DepthStencilStateCI.depthCompareOp				;
	//DepthStencilStateCI.depthBoundsTestEnable		;
	//DepthStencilStateCI.stencilTestEnable			;
	//DepthStencilStateCI.front						;
	//DepthStencilStateCI.back						;
	//DepthStencilStateCI.minDepthBounds				;
	//DepthStencilStateCI.maxDepthBounds				;
	//*/

	//// wtf? the fisrt vulkan struct that doesn't begin with sType and pNext?
	//// Alpha channel is being used in this pipeline.
	//VkPipelineColorBlendAttachmentState Attachment{};
	//Attachment.blendEnable = VK_TRUE;
	//Attachment.srcColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
	//Attachment.dstColorBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	//Attachment.colorBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
	//Attachment.srcAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ONE;
	//Attachment.dstAlphaBlendFactor = VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	//Attachment.alphaBlendOp = VkBlendOp::VK_BLEND_OP_ADD;
	////Attachment.colorWriteMask		= 0;

	//VkPipelineColorBlendStateCreateInfo ColorBlendStateCI{};
	//ColorBlendStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	//ColorBlendStateCI.pNext = NULL;
	//ColorBlendStateCI.flags = 0;
	//ColorBlendStateCI.logicOpEnable = VK_FALSE;
	//ColorBlendStateCI.logicOp = VK_LOGIC_OP_COPY;
	//ColorBlendStateCI.attachmentCount = 1;
	//ColorBlendStateCI.pAttachments = &Attachment;
	//ColorBlendStateCI.blendConstants[0] = 0.0f;
	//ColorBlendStateCI.blendConstants[1] = 0.0f;
	//ColorBlendStateCI.blendConstants[2] = 0.0f;
	//ColorBlendStateCI.blendConstants[3] = 0.0f;

	//VkDynamicState DynamicState[] = {
	//		VK_DYNAMIC_STATE_VIEWPORT,
	//		VK_DYNAMIC_STATE_LINE_WIDTH
	//};

	//// Heads up warning for what changes quickly
	//VkPipelineDynamicStateCreateInfo DynamicStateCI{};
	//DynamicStateCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	//DynamicStateCI.pNext = NULL;
	//DynamicStateCI.flags = 0;
	//DynamicStateCI.dynamicStateCount = 2;
	//DynamicStateCI.pDynamicStates = DynamicState;

	//// This will apparently be the interface for uniforms in shaders.
	//VkPipelineLayout Layout;
	//VkPipelineLayoutCreateInfo LayoutCI;
	//LayoutCI.sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	//LayoutCI.pNext = NULL;
	//LayoutCI.flags = 0; // Sweet.
	//LayoutCI.setLayoutCount = 0;
	//LayoutCI.pSetLayouts = NULL;
	//LayoutCI.pushConstantRangeCount = 0;
	//LayoutCI.pPushConstantRanges = NULL;
	//aEngine->ErrorCode = vkCreatePipelineLayout(DeviceContext->get_handle(), &LayoutCI, NULL, &Layout);
	//std::cout << "PipelineLayout Creation Status: " << aEngine->get_er_str(aEngine->ErrorCode) << std::endl;

	//// Finalizes previous steps into graphics pipeline creation info.
	//GraphicsPipelineCI.sType = VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	//GraphicsPipelineCI.pNext = NULL;
	//GraphicsPipelineCI.flags = 0;
	//GraphicsPipelineCI.stageCount = 2;
	//GraphicsPipelineCI.pStages = ShaderStage.data();
	//GraphicsPipelineCI.pVertexInputState = &VertexInputStateCI;
	//GraphicsPipelineCI.pInputAssemblyState = &InputAssemblyStateCI;
	//GraphicsPipelineCI.pTessellationState = NULL; // Not using this right now
	//GraphicsPipelineCI.pViewportState = &ViewportStateCI;
	//GraphicsPipelineCI.pRasterizationState = &RasterizationStateCI;
	//GraphicsPipelineCI.pMultisampleState = &MultisampleStateCI;
	//GraphicsPipelineCI.pDepthStencilState = NULL; // Ignore for now
	//GraphicsPipelineCI.pColorBlendState = &ColorBlendStateCI;
	//GraphicsPipelineCI.pDynamicState = &DynamicStateCI;
	//GraphicsPipelineCI.layout = Layout;
	//GraphicsPipelineCI.renderPass;
	///*
	//GraphicsPipelineCI.subpass						;
	//GraphicsPipelineCI.basePipelineHandle			;
	//GraphicsPipelineCI.basePipelineIndex			;
	//*/

	//vkCreatePipelineCache(DeviceContext->get_handle(), &CacheCI, NULL, &Cache);
	//vkCreateGraphicsPipelines(DeviceContext->get_handle(), Cache, 1, &GraphicsPipelineCI, NULL, &GraphicsPipeline);

	//for (size_t i = 0; i < 7; i++) {
	//	std::cout << io::file::BuiltInTypes[i].Type << " ";
	//	for (size_t j = 0; j < io::file::BuiltInTypes[i].Extension.size(); j++) {
	//		std::cout << io::file::BuiltInTypes[i].Extension[j].str() << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//std::cout << io::file::str2type("fsh") << std::endl;

	//io::file File("assets/shaders/BasicVertex.fsh");

	//std::cout << File.get_path().str() << std::endl;
	//std::cout << File.get_dir().str() << std::endl;
	//std::cout << File.get_name().str() << std::endl;
	//std::cout << File.get_ext().str() << std::endl;

	////VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo;


}

integer triangle::input(const keyboard& aKeyboard) {
	return 0;
}

integer triangle::input(const mouse& aMouse) {
	return 0;
}

integer triangle::update(real aDeltaTime) {
	return 0;
}

integer triangle::draw(system_display* aTargetSystemDisplay) {
	return 0;
}

integer triangle::draw(system_window* aTargetSystemWindow) {
	return 0;
}

integer triangle::draw(virtual_window* aTargetVirtualWindow) {
	return 0;
}

integer triangle::draw(camera2d* aTargetCamera2D) {
	return 0;
}

integer triangle::draw(camera3d* aTargetCamera3D) {
	return 0;
}

