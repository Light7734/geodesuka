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

		//// layout (location = 0) in vec3 VertexPosition;
		//// layout (location = 1) in vec3 VertexColor;
		//float VertexData[] = {
		//	-0.5, 0.0, 0.0, 1.0, 0.0, 0.0,
		//	 0.5, 0.0, 0.0, 0.0, 1.0, 0.0,
		//	 0.0, -0.5, 0.0, 0.0, 0.0, 1.0
		//};

		//// Shader Sources hard coded into triangle.
		//const char* VertexShaderSource =
		//	"#version 450\n\
		//	#extension GL_ARB_separate_shader_objects : require \n\
		//	#extension GL_KHR_vulkan_glsl : enable \n\
		//	\n\
		//	layout (location = 0) in vec3 VertexPosition; \n\
		//	layout (location = 1) in vec3 VertexColor; \n\
		//	\n\
		//	layout (location = 0) out vec3 InterpColor;\n\
		//	\n\
		//	void main() {\n\
		//		gl_Position = vec4(VertexPosition, 1.0);\n\
		//		InterpColor = VertexColor;\n\
		//	}";

		//const char* PixelShaderSource =
		//	"#version 450\n\
		//	#extension GL_ARB_separate_shader_objects : require \n\
		//	#extension GL_KHR_vulkan_glsl : enable \n\
		//	\n\
		//	layout(location = 0) in vec3 InterpColor;\n\
		//	\n\
		//	layout(location = 0) out vec4 PixelColor;\n\
		//	\n\
		//	void main() {\n\
		//		PixelColor = vec4(InterpColor, 1.0);\n\
		//	}";

		const char* VertexShaderSource =
			"#version 450														\n\
																				\n\
			vec2 VertexPosition[3] = vec2[](									\n\
			    vec2(0.0, -0.5),												\n\
			    vec2(0.5, 0.5),													\n\
			    vec2(-0.5, 0.5)													\n\
			);																	\n\
																				\n\
			vec3 VertexColor[3] = vec3[](										\n\
				vec3(1.0, 0.0, 0.0),											\n\
				vec3(0.0, 1.0, 0.0),											\n\
				vec3(0.0, 0.0, 1.0)												\n\
			);																	\n\
																				\n\
			layout (location = 0) out vec3 InterpColor;							\n\
																				\n\
			void main() {														\n\
			    gl_Position = vec4(VertexPosition[gl_VertexIndex], 0.0, 1.0);	\n\
				InterpColor = VertexColor[gl_VertexIndex];						\n\
			}";

		const char* PixelShaderSource =
			"#version 450										\n\
																\n\
			layout (location = 0) in vec3 InterpColor;			\n\
																\n\
			layout(location = 0) out vec4 PixelColor;			\n\
																\n\
			void main() {										\n\
				PixelColor = vec4(InterpColor, 1.0);			\n\
			}";

		// Could glslang be a point of error for why a triangle is not rendering?
		VertexShader = new shader(Context, shader::stage::VERTEX, VertexShaderSource);
		PixelShader = new shader(Context, shader::stage::FRAGMENT, PixelShaderSource);

		// ----- Render Pass Construction ----- //

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		VkRenderPassCreateInfo RenderPassCreateInfo{};
		RenderPassCreateInfo.sType				= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassCreateInfo.pNext				= NULL;
		RenderPassCreateInfo.flags				;
		RenderPassCreateInfo.attachmentCount	= Stage->RenderTarget[0]->FrameAttachmentCount;
		RenderPassCreateInfo.pAttachments		= Stage->RenderTarget[0]->FrameAttachmentDescription;
		RenderPassCreateInfo.subpassCount		= 1;
		RenderPassCreateInfo.pSubpasses			= &subpass;
		RenderPassCreateInfo.dependencyCount	= 1;
		RenderPassCreateInfo.pDependencies		= &dependency;

		if (vkCreateRenderPass(Context->handle(), &RenderPassCreateInfo, nullptr, &RenderPass) != VK_SUCCESS) {
			throw std::runtime_error("failed to create render pass!");
		}

		FrameBuffer.resize(Stage->RenderTarget[0]->FrameCount);
		for (uint32_t i = 0; i < Stage->RenderTarget[0]->FrameCount; i++) {
			VkFramebufferCreateInfo FrameBufferCreateInfo{};
			FrameBufferCreateInfo.sType				= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			FrameBufferCreateInfo.pNext				= NULL;
			FrameBufferCreateInfo.flags				= 0;
			FrameBufferCreateInfo.renderPass		= RenderPass;
			FrameBufferCreateInfo.attachmentCount	= Stage->RenderTarget[0]->FrameAttachmentCount;
			FrameBufferCreateInfo.pAttachments		= Stage->RenderTarget[0]->FrameAttachment[i];
			FrameBufferCreateInfo.width				= Stage->RenderTarget[0]->Resolution.x;
			FrameBufferCreateInfo.height			= Stage->RenderTarget[0]->Resolution.y;
			FrameBufferCreateInfo.layers			= 1;

			vkCreateFramebuffer(Context->handle(), &FrameBufferCreateInfo, NULL, &FrameBuffer[i]);
		}

		// ----- Command Buffer Construction ----- //
		CommandBuffer.resize(Stage->RenderTarget[0]->FrameCount);
		Stage->RenderTarget[0]->DrawCommandPool.allocate(VK_COMMAND_BUFFER_LEVEL_PRIMARY, CommandBuffer.size(), CommandBuffer.data());

		// ----- Graphics Pipeline Constrcution ----- //

		VkPipelineShaderStageCreateInfo vertShaderStageInfo = VertexShader->stageci();
		//vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		//vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		//vertShaderStageInfo.module = vertShaderModule;
		//vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo = PixelShader->stageci();
		//fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		//fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		//fragShaderStageInfo.module = fragShaderModule;
		//fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.vertexAttributeDescriptionCount = 0;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width		= (float)Stage->RenderTarget[0]->Resolution.x;
		viewport.height		= (float)Stage->RenderTarget[0]->Resolution.x;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = { Stage->RenderTarget[0]->Resolution.x, Stage->RenderTarget[0]->Resolution.y };

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(Context->handle(), &pipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = PipelineLayout;
		pipelineInfo.renderPass = RenderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(Context->handle(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &Pipeline) != VK_SUCCESS) {
			throw std::runtime_error("failed to create graphics pipeline!");
		}

		// ----- Record Draw Commands ----- //

		for (uint32_t i = 0; i < Stage->RenderTarget[0]->FrameCount; i++) {
			VkCommandBufferBeginInfo CommandBufferBeginInfo{};
			VkRenderPassBeginInfo RenderPassBeginInfo{};
			VkClearValue ClearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };

			CommandBufferBeginInfo.sType				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			CommandBufferBeginInfo.pNext				= NULL;
			CommandBufferBeginInfo.flags				= 0;
			CommandBufferBeginInfo.pInheritanceInfo		= NULL;

			RenderPassBeginInfo.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			RenderPassBeginInfo.renderPass				= RenderPass;
			RenderPassBeginInfo.framebuffer				= FrameBuffer[i];
			RenderPassBeginInfo.renderArea.offset		= { 0, 0 };
			RenderPassBeginInfo.renderArea.extent		= { Stage->RenderTarget[0]->Resolution.x, Stage->RenderTarget[0]->Resolution.y };
			RenderPassBeginInfo.clearValueCount			= 1;
			RenderPassBeginInfo.pClearValues			= &ClearColor;

			if (vkBeginCommandBuffer(CommandBuffer[i], &CommandBufferBeginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffer!");
			}

			vkCmdBeginRenderPass(CommandBuffer[i], &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

			vkCmdBindPipeline(CommandBuffer[i], VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline);

			vkCmdDraw(CommandBuffer[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(CommandBuffer[i]);

			if (vkEndCommandBuffer(CommandBuffer[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to record command buffer!");
			}
		}


		//type VertexLayoutType(type::id::STRUCT, "");
		//VertexLayoutType.push(type::id::FLOAT3, "Position");
		//VertexLayoutType.push(type::id::FLOAT3, "Color");
		//variable VertexLayout(VertexLayoutType, "Vertex");

		//VertexBuffer = new buffer(Context, device::memory::DEVICE_LOCAL, buffer::usage::VERTEX, 3, VertexLayout, VertexData);

		//{
		//	gcl::buffer StagingBuffer(Context, device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT, buffer::usage::VERTEX, 3, VertexLayout, VertexData);
		//	VkFenceCreateInfo FenceCreateInfo{};
		//	VkFence Fence = VK_NULL_HANDLE;
		//	VkSubmitInfo SubmitInfo;
		//	VkCommandBuffer Transfer;


		//	FenceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		//	FenceCreateInfo.pNext = NULL;
		//	FenceCreateInfo.flags = 0;

		//	SubmitInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		//	SubmitInfo.pNext					= NULL;
		//	SubmitInfo.waitSemaphoreCount		= 0;
		//	SubmitInfo.pWaitSemaphores			= NULL;
		//	SubmitInfo.pWaitDstStageMask		= NULL;
		//	SubmitInfo.commandBufferCount		= 1;
		//	SubmitInfo.pCommandBuffers			= &Transfer;
		//	SubmitInfo.signalSemaphoreCount		= 0;
		//	SubmitInfo.pSignalSemaphores		= NULL;

		//	Transfer = *VertexBuffer << StagingBuffer;
		//	vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
		//	Context->submit(device::qfs::TRANSFER, 1, &SubmitInfo, Fence);
		//	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);
		//	vkDestroyFence(Context->handle(), Fence, NULL);
		//	Context->destroy(device::qfs::TRANSFER, Transfer);

		//	gcl::buffer ReturnBuffer(Context, device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT, buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST | buffer::usage::VERTEX, 3, VertexLayout, NULL);

		//	Transfer = ReturnBuffer << *VertexBuffer;
		//	vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
		//	Context->submit(device::qfs::TRANSFER, 1, &SubmitInfo, Fence);
		//	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);
		//	vkDestroyFence(Context->handle(), Fence, NULL);
		//	Context->destroy(device::qfs::TRANSFER, Transfer);

		//	float temp[18];
		//	ReturnBuffer.read(0, 3 * 24, temp);
		//	int Success = memcmp(VertexData, temp, 18 * sizeof(float)) ;
		//}


		/*
		for (size_t i = 0; i < Stage->RenderTarget.size(); i++) {
			switch (Stage->RenderTarget[i]->rtid()) {
			default:
				break;
			//case system_display::RTID:
			//	break;
			case system_window::RTID:
			{
				// Describe how object will draw to system_window.

				// Render Pass Info
				VkAttachmentReference Reference{};
				VkSubpassDescription SubpassDescription[1];
				VkSubpassDependency SubpassDependency[1];
				// Pipeline Info
				VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo{};

				VkPipelineShaderStageCreateInfo			ShaderStage[2] {};
				VkPipelineVertexInputStateCreateInfo	VertexInput{};
				VkPipelineInputAssemblyStateCreateInfo	InputAssembly{};
				VkPipelineTessellationStateCreateInfo	Tesselation{};
				VkPipelineViewportStateCreateInfo		Viewport{};
				VkPipelineRasterizationStateCreateInfo	Rasterizer{};
				VkPipelineMultisampleStateCreateInfo	Multisample{};
				VkPipelineDepthStencilStateCreateInfo	DepthStencil{};
				VkPipelineColorBlendStateCreateInfo		ColorBlend{};
				VkPipelineDynamicStateCreateInfo		DynamicState{};
				VkGraphicsPipelineCreateInfo			GraphicsPipelineCreateInfo{};
				VkPipelineLayout						PipelineLayout;

				Reference.attachment = 0;
				Reference.layout = VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

				SubpassDescription[0].flags						= 0;
				SubpassDescription[0].pipelineBindPoint			= VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
				SubpassDescription[0].inputAttachmentCount		= 0;
				SubpassDescription[0].pInputAttachments			= NULL;
				SubpassDescription[0].colorAttachmentCount		= 1;
				SubpassDescription[0].pColorAttachments			= &Reference;
				SubpassDescription[0].pResolveAttachments		= NULL;
				SubpassDescription[0].pDepthStencilAttachment	= NULL;
				SubpassDescription[0].preserveAttachmentCount	= 0;
				SubpassDescription[0].pPreserveAttachments		= NULL;

				SubpassDependency[0].srcSubpass					= VK_SUBPASS_EXTERNAL;
				SubpassDependency[0].dstSubpass					= 0;
				SubpassDependency[0].srcStageMask				= VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
				SubpassDependency[0].dstStageMask				= VkPipelineStageFlagBits::VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
				SubpassDependency[0].srcAccessMask				= VkAccessFlagBits::VK_ACCESS_MEMORY_WRITE_BIT;
				SubpassDependency[0].dstAccessMask				= VkAccessFlagBits::VK_ACCESS_SHADER_READ_BIT;
				SubpassDependency[0].dependencyFlags			= 0;

				DrawPack.try_emplace(Stage->RenderTarget[i], new drawpack(Context, Stage->RenderTarget[i], 1, SubpassDescription, 1, SubpassDependency));

				ShaderStage[0] = VertexShader->stageci();
				ShaderStage[1] = PixelShader->stageci();

				//// Only One Buffer
				//VkVertexInputBindingDescription BindingDescription[1];
				//// Two Attributes in the buffer.
				//VkVertexInputAttributeDescription AttributeDescription[2];

				//BindingDescription[0].binding		= 0;
				//BindingDescription[0].stride		= VertexLayout.Size;
				//BindingDescription[0].inputRate		= VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

				//// VertexPosition
				//AttributeDescription[0].location	= 0;
				//AttributeDescription[0].binding		= 0;
				//AttributeDescription[0].format		= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
				//AttributeDescription[0].offset		= VertexLayout[0].Offset;

				//// VertexColor
				//AttributeDescription[1].location	= 1;
				//AttributeDescription[1].binding		= 0;
				//AttributeDescription[1].format		= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
				//AttributeDescription[1].offset		= VertexLayout[1].Offset;

				VertexInput.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				VertexInput.pNext								= NULL;
				VertexInput.flags								= 0;
				VertexInput.vertexBindingDescriptionCount		= 0;
				VertexInput.pVertexBindingDescriptions			= NULL;
				VertexInput.vertexAttributeDescriptionCount		= 0;
				VertexInput.pVertexAttributeDescriptions		= NULL;
				//VertexInput.vertexBindingDescriptionCount		= 1;
				//VertexInput.pVertexBindingDescriptions			= BindingDescription;
				//VertexInput.vertexAttributeDescriptionCount		= 2;
				//VertexInput.pVertexAttributeDescriptions		= AttributeDescription;

				InputAssembly.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				InputAssembly.pNext								= NULL;
				InputAssembly.flags								= 0;
				InputAssembly.topology							= VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				InputAssembly.primitiveRestartEnable			= VK_FALSE;

				VkViewport Vp{};
				VkRect2D Rc{};

				Vp.x			= 0;
				Vp.y			= 0;
				Vp.width		= Stage->RenderTarget[i]->Resolution.x;
				Vp.height		= Stage->RenderTarget[i]->Resolution.y;
				Vp.minDepth		= 0.0f;
				Vp.maxDepth		= 1.0f;

				Rc.offset = { 0, 0 };
				Rc.extent = { Stage->RenderTarget[i]->Resolution.x, Stage->RenderTarget[i]->Resolution.y };

				Viewport.sType				= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport.pNext				= NULL;
				Viewport.flags				= 0;
				Viewport.viewportCount		= 1;
				Viewport.pViewports			= &Vp;
				Viewport.scissorCount		= 1;
				Viewport.pScissors			= &Rc;

				Rasterizer.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterizer.pNext						= NULL;
				Rasterizer.flags						= 0;
				Rasterizer.depthClampEnable				= VK_FALSE;
				Rasterizer.rasterizerDiscardEnable		= VK_FALSE;
				Rasterizer.polygonMode					= VkPolygonMode::VK_POLYGON_MODE_FILL;
				Rasterizer.cullMode						= VkCullModeFlagBits::VK_CULL_MODE_NONE;
				Rasterizer.frontFace					= VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;
				Rasterizer.depthBiasEnable				= VK_FALSE;
				Rasterizer.depthBiasConstantFactor		= 0.0f;
				Rasterizer.depthBiasClamp				= 0.0f;
				Rasterizer.depthBiasSlopeFactor			= 0.0;
				Rasterizer.lineWidth					= 1.0f;

				Multisample.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample.sampleShadingEnable		= VK_FALSE;
				Multisample.rasterizationSamples	= VK_SAMPLE_COUNT_1_BIT;
				Multisample.minSampleShading		= 1.0f; // Optional
				Multisample.pSampleMask				= NULL; // Optional
				Multisample.alphaToCoverageEnable	= VK_FALSE; // Optional
				Multisample.alphaToOneEnable		= VK_FALSE; // Optional

				VkPipelineColorBlendAttachmentState colorBlendAttachment{};
				colorBlendAttachment.colorWriteMask			= VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
				colorBlendAttachment.blendEnable			= VK_FALSE;
				colorBlendAttachment.srcColorBlendFactor	= VK_BLEND_FACTOR_ONE; // Optional
				colorBlendAttachment.dstColorBlendFactor	= VK_BLEND_FACTOR_ZERO; // Optional
				colorBlendAttachment.colorBlendOp			= VK_BLEND_OP_ADD; // Optional
				colorBlendAttachment.srcAlphaBlendFactor	= VK_BLEND_FACTOR_ONE; // Optional
				colorBlendAttachment.dstAlphaBlendFactor	= VK_BLEND_FACTOR_ZERO; // Optional
				colorBlendAttachment.alphaBlendOp			= VK_BLEND_OP_ADD; // Optional

				ColorBlend.sType				= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				ColorBlend.pNext				= NULL;
				ColorBlend.flags				= 0;
				ColorBlend.logicOpEnable		= VK_FALSE;
				ColorBlend.logicOp				= VK_LOGIC_OP_COPY;
				ColorBlend.attachmentCount		= 1;
				ColorBlend.pAttachments			= &colorBlendAttachment;
				ColorBlend.blendConstants[0]	= 0.0f;
				ColorBlend.blendConstants[1]	= 0.0f;
				ColorBlend.blendConstants[2]	= 0.0f;
				ColorBlend.blendConstants[3]	= 0.0f;

				VkDynamicState DynamicStateInfo[2] = {
					VK_DYNAMIC_STATE_VIEWPORT,
					VK_DYNAMIC_STATE_LINE_WIDTH
				};

				DynamicState.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				DynamicState.pNext					= NULL;
				DynamicState.flags					= 0;
				DynamicState.dynamicStateCount		= 0;
				DynamicState.pDynamicStates			= NULL;

				PipelineLayoutCreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				PipelineLayoutCreateInfo.pNext						= NULL;
				PipelineLayoutCreateInfo.flags						= 0;
				PipelineLayoutCreateInfo.setLayoutCount				= 0;
				PipelineLayoutCreateInfo.pSetLayouts				= NULL;
				PipelineLayoutCreateInfo.pushConstantRangeCount		= 0;
				PipelineLayoutCreateInfo.pPushConstantRanges		= NULL;

				vkCreatePipelineLayout(Context->handle(), &PipelineLayoutCreateInfo, NULL, &PipelineLayout);

				GraphicsPipelineCreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				GraphicsPipelineCreateInfo.pNext					= NULL;
				GraphicsPipelineCreateInfo.flags					= 0;
				GraphicsPipelineCreateInfo.stageCount				= 2;
				GraphicsPipelineCreateInfo.pStages					= ShaderStage;
				GraphicsPipelineCreateInfo.pVertexInputState		= &VertexInput;
				GraphicsPipelineCreateInfo.pInputAssemblyState		= &InputAssembly;
				GraphicsPipelineCreateInfo.pTessellationState		= NULL;
				GraphicsPipelineCreateInfo.pViewportState			= &Viewport;
				GraphicsPipelineCreateInfo.pRasterizationState		= &Rasterizer;
				GraphicsPipelineCreateInfo.pMultisampleState		= &Multisample;
				GraphicsPipelineCreateInfo.pDepthStencilState		= NULL;
				GraphicsPipelineCreateInfo.pColorBlendState			= &ColorBlend;
				GraphicsPipelineCreateInfo.pDynamicState			= NULL;
				GraphicsPipelineCreateInfo.layout					= PipelineLayout;
				GraphicsPipelineCreateInfo.renderPass				= DrawPack[Stage->RenderTarget[i]]->RenderPass;
				GraphicsPipelineCreateInfo.subpass					= 0;
				GraphicsPipelineCreateInfo.basePipelineHandle		= VK_NULL_HANDLE;
				GraphicsPipelineCreateInfo.basePipelineIndex		= 0;

				vkCreateGraphicsPipelines(Context->handle(), VK_NULL_HANDLE, 1, &GraphicsPipelineCreateInfo, NULL, &Pipeline);

				VkCommandBufferBeginInfo BeginInfo{};
				BeginInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				BeginInfo.pNext					= NULL;
				BeginInfo.flags					= 0;
				BeginInfo.pInheritanceInfo		= NULL;

				// Needed to write command buffers.
				Stage->RenderTarget[i]->DrawCommandPool.Mutex.lock();
				for (uint32_t j = 0; j < Stage->RenderTarget[i]->FrameCount; j++) {
					VkRenderPassBeginInfo RenderPassBeginInfo{};
					VkRect2D RenderArea{};
					VkClearValue ClearValue = { 0.0, 0.0, 0.0, 0.0 };
					ClearValue.color			= { 0.5f, 0.0f, 0.0f, 0.0f };
					ClearValue.depthStencil		= { 0.0f, 0u };
					RenderArea.offset = { 0, 0 };
					RenderArea.extent = { Stage->RenderTarget[i]->Resolution.x, Stage->RenderTarget[i]->Resolution.y };
					RenderPassBeginInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
					RenderPassBeginInfo.pNext				= NULL;
					RenderPassBeginInfo.renderPass			= DrawPack[Stage->RenderTarget[i]]->RenderPass;
					RenderPassBeginInfo.framebuffer			= DrawPack[Stage->RenderTarget[i]]->Frame[j];
					RenderPassBeginInfo.renderArea			= RenderArea;
					RenderPassBeginInfo.clearValueCount		= 1;
					RenderPassBeginInfo.pClearValues		= &ClearValue;
					VkDeviceSize BufferOffset = 0;

					vkBeginCommandBuffer(DrawPack[Stage->RenderTarget[i]]->Command[j], &BeginInfo);
					vkCmdBeginRenderPass(DrawPack[Stage->RenderTarget[i]]->Command[j], &RenderPassBeginInfo, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
					vkCmdBindPipeline(DrawPack[Stage->RenderTarget[i]]->Command[j], VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline);
					//vkCmdBindVertexBuffers(DrawPack[Stage->RenderTarget[i]]->Command[j], 0, 1, &VertexBuffer->handle(), &BufferOffset);
					//vkCmdDraw(DrawPack[Stage->RenderTarget[i]]->Command[j], 3, 1, 0, 0);
					vkCmdEndRenderPass(DrawPack[Stage->RenderTarget[i]]->Command[j]);
					vkEndCommandBuffer(DrawPack[Stage->RenderTarget[i]]->Command[j]);
				}
				Stage->RenderTarget[i]->DrawCommandPool.Mutex.unlock();
			}
				break;
			case virtual_window::RTID:
				break;
			//case camera2d::RTID:
			//	break;
			//case camera3d::RTID:
			//	break;
			}
		}
		//*/

		isReadyToBeProcessed.store(true);
	}

	triangle::~triangle() {
		isReadyToBeProcessed.store(false);
		// Delete Drawpack
		delete PixelShader;
		delete VertexShader;
		delete VertexBuffer;
	}

	VkCommandBuffer triangle::draw(core::object::rendertarget* aRenderTarget) {
		return CommandBuffer[aRenderTarget->FrameDrawIndex];
	}

}
