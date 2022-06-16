#include <geodesuka/builtin/object/triangle.h>

#include <geodesuka/engine.h>

#include <assert.h>

using namespace geodesuka::core;
using namespace object;
using namespace hid;
using namespace math;
using namespace gcl;
using namespace util;

namespace geodesuka::builtin::object {

	triangle::triangle(engine* aEngine, core::gcl::context* aContext, core::stage_t* aStage) : object_t(aEngine, aContext, aStage) {

		////// layout (location = 0) in vec3 VertexPosition;
		////// layout (location = 1) in vec3 VertexColor;
		////float VertexData[] = {
		////	-0.5, 0.0, 0.0, 1.0, 0.0, 0.0,
		////	 0.5, 0.0, 0.0, 0.0, 1.0, 0.0,
		////	 0.0, -0.5, 0.0, 0.0, 0.0, 1.0
		////};

		////// Shader Sources hard coded into triangle.
		////const char* VertexShaderSource =
		////	"#version 450\n\
		////	#extension GL_ARB_separate_shader_objects : require \n\
		////	#extension GL_KHR_vulkan_glsl : enable \n\
		////	\n\
		////	layout (location = 0) in vec3 VertexPosition; \n\
		////	layout (location = 1) in vec3 VertexColor; \n\
		////	\n\
		////	layout (location = 0) out vec3 InterpColor;\n\
		////	\n\
		////	void main() {\n\
		////		gl_Position = vec4(VertexPosition, 1.0);\n\
		////		InterpColor = VertexColor;\n\
		////	}";

		////const char* PixelShaderSource =
		////	"#version 450\n\
		////	#extension GL_ARB_separate_shader_objects : require \n\
		////	#extension GL_KHR_vulkan_glsl : enable \n\
		////	\n\
		////	layout(location = 0) in vec3 InterpColor;\n\
		////	\n\
		////	layout(location = 0) out vec4 PixelColor;\n\
		////	\n\
		////	void main() {\n\
		////		PixelColor = vec4(InterpColor, 1.0);\n\
		////	}";

		//const char* VertexShaderSource =
		//	"#version 450														\n\
		//																		\n\
		//	vec2 VertexPosition[3] = vec2[](									\n\
		//	    vec2(0.0, -0.5),												\n\
		//	    vec2(0.5, 0.5),													\n\
		//	    vec2(-0.5, 0.5)													\n\
		//	);																	\n\
		//																		\n\
		//	vec3 VertexColor[3] = vec3[](										\n\
		//		vec3(1.0, 0.0, 0.0),											\n\
		//		vec3(0.0, 1.0, 0.0),											\n\
		//		vec3(0.0, 0.0, 1.0)												\n\
		//	);																	\n\
		//																		\n\
		//	layout (location = 0) out vec3 InterpColor;							\n\
		//																		\n\
		//	void main() {														\n\
		//	    gl_Position = vec4(VertexPosition[gl_VertexIndex], 0.0, 1.0);	\n\
		//		InterpColor = VertexColor[gl_VertexIndex];						\n\
		//	}";

		//const char* PixelShaderSource =
		//	"#version 450										\n\
		//														\n\
		//	layout (location = 0) in vec3 InterpColor;			\n\
		//														\n\
		//	layout(location = 0) out vec4 PixelColor;			\n\
		//														\n\
		//	void main() {										\n\
		//		PixelColor = vec4(InterpColor, 1.0);			\n\
		//	}";

		//// Could glslang be a point of error for why a triangle is not rendering?
		//VertexShader = new shader(Context, shader::stage::VERTEX, VertexShaderSource);
		//PixelShader = new shader(Context, shader::stage::FRAGMENT, PixelShaderSource);

		//// ----- Render Pass Construction ----- //

		//VkAttachmentReference colorAttachmentRef{};
		//colorAttachmentRef.attachment = 0;
		//colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		//VkSubpassDescription subpass{};
		//subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		//subpass.colorAttachmentCount = 1;
		//subpass.pColorAttachments = &colorAttachmentRef;

		//VkSubpassDependency dependency{};
		//dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		//dependency.dstSubpass = 0;
		//dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		//dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		//dependency.srcAccessMask = 0;
		//dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		//VkRenderPassCreateInfo RenderPassCreateInfo{};
		//RenderPassCreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		//RenderPassCreateInfo.pNext				= NULL;
		//RenderPassCreateInfo.flags				;
		//RenderPassCreateInfo.attachmentCount	= Stage->RenderTarget[0]->FrameAttachmentCount;
		//RenderPassCreateInfo.pAttachments		= Stage->RenderTarget[0]->FrameAttachmentDescription;
		//RenderPassCreateInfo.subpassCount		= 1;
		//RenderPassCreateInfo.pSubpasses			= &subpass;
		//RenderPassCreateInfo.dependencyCount	= 1;
		//RenderPassCreateInfo.pDependencies		= &dependency;

		//if (vkCreateRenderPass(Context->handle(), &RenderPassCreateInfo, nullptr, &RenderPass) != VK_SUCCESS) {
		//	throw std::runtime_error("failed to create render pass!");
		//}

		//FrameBuffer.resize(Stage->RenderTarget[0]->FrameCount);
		//for (uint32_t i = 0; i < Stage->RenderTarget[0]->FrameCount; i++) {
		//	VkFramebufferCreateInfo FrameBufferCreateInfo{};
		//	FrameBufferCreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		//	FrameBufferCreateInfo.pNext				= NULL;
		//	FrameBufferCreateInfo.flags				= 0;
		//	FrameBufferCreateInfo.renderPass		= RenderPass;
		//	FrameBufferCreateInfo.attachmentCount	= Stage->RenderTarget[0]->FrameAttachmentCount;
		//	FrameBufferCreateInfo.pAttachments		= Stage->RenderTarget[0]->FrameAttachment[i];
		//	FrameBufferCreateInfo.width				= Stage->RenderTarget[0]->Resolution.x;
		//	FrameBufferCreateInfo.height			= Stage->RenderTarget[0]->Resolution.y;
		//	FrameBufferCreateInfo.layers			= 1;

		//	vkCreateFramebuffer(Context->handle(), &FrameBufferCreateInfo, NULL, &FrameBuffer[i]);
		//}

		//// ----- Command Buffer Construction ----- //
		//CommandBuffer.resize(Stage->RenderTarget[0]->FrameCount);
		//Stage->RenderTarget[0]->DrawCommandPool.allocate(VK_COMMAND_BUFFER_LEVEL_PRIMARY, CommandBuffer.size(), CommandBuffer.data());

		//// ----- Graphics Pipeline Constrcution ----- //

		//VkPipelineShaderStageCreateInfo vertShaderStageInfo = VertexShader->stageci();
		////vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		////vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		////vertShaderStageInfo.module = vertShaderModule;
		////vertShaderStageInfo.pName = "main";

		//VkPipelineShaderStageCreateInfo fragShaderStageInfo = PixelShader->stageci();
		////fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		////fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		////fragShaderStageInfo.module = fragShaderModule;
		////fragShaderStageInfo.pName = "main";

		//VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		//VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		//vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		//vertexInputInfo.vertexBindingDescriptionCount = 0;
		//vertexInputInfo.vertexAttributeDescriptionCount = 0;

		//VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		//inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		//inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		//inputAssembly.primitiveRestartEnable = VK_FALSE;

		//VkViewport viewport{};
		//viewport.x = 0.0f;
		//viewport.y = 0.0f;
		//viewport.width		= (float)Stage->RenderTarget[0]->Resolution.x;
		//viewport.height		= (float)Stage->RenderTarget[0]->Resolution.x;
		//viewport.minDepth = 0.0f;
		//viewport.maxDepth = 1.0f;

		//VkRect2D scissor{};
		//scissor.offset = { 0, 0 };
		//scissor.extent = { Stage->RenderTarget[0]->Resolution.x, Stage->RenderTarget[0]->Resolution.y };

		//VkPipelineViewportStateCreateInfo viewportState{};
		//viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		//viewportState.viewportCount = 1;
		//viewportState.pViewports = &viewport;
		//viewportState.scissorCount = 1;
		//viewportState.pScissors = &scissor;

		//VkPipelineRasterizationStateCreateInfo rasterizer{};
		//rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		//rasterizer.depthClampEnable = VK_FALSE;
		//rasterizer.rasterizerDiscardEnable = VK_FALSE;
		//rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		//rasterizer.lineWidth = 1.0f;
		//rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		//rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		//rasterizer.depthBiasEnable = VK_FALSE;

		//VkPipelineMultisampleStateCreateInfo multisampling{};
		//multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		//multisampling.sampleShadingEnable = VK_FALSE;
		//multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		//VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		//colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		//colorBlendAttachment.blendEnable = VK_FALSE;

		//VkPipelineColorBlendStateCreateInfo colorBlending{};
		//colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		//colorBlending.logicOpEnable = VK_FALSE;
		//colorBlending.logicOp = VK_LOGIC_OP_COPY;
		//colorBlending.attachmentCount = 1;
		//colorBlending.pAttachments = &colorBlendAttachment;
		//colorBlending.blendConstants[0] = 0.0f;
		//colorBlending.blendConstants[1] = 0.0f;
		//colorBlending.blendConstants[2] = 0.0f;
		//colorBlending.blendConstants[3] = 0.0f;

		//VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		//pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		//pipelineLayoutInfo.setLayoutCount = 0;
		//pipelineLayoutInfo.pushConstantRangeCount = 0;

		//if (vkCreatePipelineLayout(Context->handle(), &pipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS) {
		//	throw std::runtime_error("failed to create pipeline layout!");
		//}

		//VkGraphicsPipelineCreateInfo pipelineInfo{};
		//pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		//pipelineInfo.stageCount = 2;
		//pipelineInfo.pStages = shaderStages;
		//pipelineInfo.pVertexInputState = &vertexInputInfo;
		//pipelineInfo.pInputAssemblyState = &inputAssembly;
		//pipelineInfo.pViewportState = &viewportState;
		//pipelineInfo.pRasterizationState = &rasterizer;
		//pipelineInfo.pMultisampleState = &multisampling;
		//pipelineInfo.pColorBlendState = &colorBlending;
		//pipelineInfo.layout = PipelineLayout;
		//pipelineInfo.renderPass = RenderPass;
		//pipelineInfo.subpass = 0;
		//pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		//if (vkCreateGraphicsPipelines(Context->handle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &Pipeline) != VK_SUCCESS) {
		//	throw std::runtime_error("failed to create graphics pipeline!");
		//}

		//// ----- Record Draw Commands ----- //

		//for (uint32_t i = 0; i < Stage->RenderTarget[0]->FrameCount; i++) {
		//	VkCommandBufferBeginInfo CommandBufferBeginInfo{};
		//	VkRenderPassBeginInfo RenderPassBeginInfo{};
		//	VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };

		//	CommandBufferBeginInfo.sType				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		//	CommandBufferBeginInfo.pNext				= NULL;
		//	CommandBufferBeginInfo.flags				= 0;
		//	CommandBufferBeginInfo.pInheritanceInfo		= NULL;

		//	RenderPassBeginInfo.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		//	RenderPassBeginInfo.renderPass				= RenderPass;
		//	RenderPassBeginInfo.framebuffer				= FrameBuffer[i];
		//	RenderPassBeginInfo.renderArea.offset		= { 0, 0 };
		//	RenderPassBeginInfo.renderArea.extent		= { Stage->RenderTarget[0]->Resolution.x, Stage->RenderTarget[0]->Resolution.y };
		//	RenderPassBeginInfo.clearValueCount			= 1;
		//	RenderPassBeginInfo.pClearValues			= &ClearColor;

		//	if (vkBeginCommandBuffer(CommandBuffer[i], &CommandBufferBeginInfo) != VK_SUCCESS) {
		//		throw std::runtime_error("failed to begin recording command buffer!");
		//	}

		//	vkCmdBeginRenderPass(CommandBuffer[i], &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		//	vkCmdBindPipeline(CommandBuffer[i], VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline);

		//	vkCmdDraw(CommandBuffer[i], 3, 1, 0, 0);

		//	vkCmdEndRenderPass(CommandBuffer[i]);

		//	if (vkEndCommandBuffer(CommandBuffer[i]) != VK_SUCCESS) {
		//		throw std::runtime_error("failed to record command buffer!");
		//	}
		//}

		isReadyToBeProcessed.store(true);
	}

	triangle::~triangle() {
		isReadyToBeProcessed.store(false);
		// Delete Drawpack
		delete PixelShader;
		delete VertexShader;
		delete VertexBuffer;
	}

	VkCommandBuffer triangle::draw(core::object::render_target* aRenderTarget) {
		return CommandBuffer[aRenderTarget->FrameDrawIndex];
	}

}
