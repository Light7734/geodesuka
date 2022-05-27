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

		// layout (location = 0) in vec3 VertexPosition;
		// layout (location = 1) in vec3 VertexColor;
		float VertexData[] = {
			-1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
			 1.0, 0.0, 0.0, 0.0, 1.0, 0.0,
			 0.0, -1.0, 0.0, 0.0, 0.0, 1.0
		};

		// Shader Sources hard coded into triangle.
		const char* VertexShaderSource =
			"#version 450\n\
			#extension GL_ARB_separate_shader_objects : require \n\
			#extension GL_KHR_vulkan_glsl : enable \n\
			\n\
			layout (location = 0) in vec3 VertexPosition; \n\
			layout (location = 1) in vec3 VertexColor; \n\
			\n\
			layout (location = 0) out vec3 InterpColor;\n\
			\n\
			void main() {\n\
				gl_Position = vec4(VertexPosition, 1.0);\n\
				InterpColor = VertexColor;\n\
			}";

		const char* PixelShaderSource =
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

		type VertexLayoutType(type::id::STRUCT, "");
		VertexLayoutType.push(type::id::FLOAT3, "Position");
		VertexLayoutType.push(type::id::FLOAT3, "Color");
		variable VertexLayout(VertexLayoutType, "Vertex");

		VertexBuffer = new buffer(Context, device::memory::DEVICE_LOCAL, buffer::usage::VERTEX, 3, VertexLayout, VertexData);

		{
			gcl::buffer StagingBuffer(Context, device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT, buffer::usage::VERTEX, 3, VertexLayout, VertexData);
			VkFenceCreateInfo FenceCreateInfo{};
			VkFence Fence = VK_NULL_HANDLE;
			VkSubmitInfo SubmitInfo;
			VkCommandBuffer Transfer;


			FenceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			FenceCreateInfo.pNext = NULL;
			FenceCreateInfo.flags = 0;

			SubmitInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
			SubmitInfo.pNext					= NULL;
			SubmitInfo.waitSemaphoreCount		= 0;
			SubmitInfo.pWaitSemaphores			= NULL;
			SubmitInfo.pWaitDstStageMask		= NULL;
			SubmitInfo.commandBufferCount		= 1;
			SubmitInfo.pCommandBuffers			= &Transfer;
			SubmitInfo.signalSemaphoreCount		= 0;
			SubmitInfo.pSignalSemaphores		= NULL;

			Transfer = *VertexBuffer << StagingBuffer;
			vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
			Context->submit(device::qfs::TRANSFER, 1, &SubmitInfo, Fence);
			vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);
			vkDestroyFence(Context->handle(), Fence, NULL);
			Context->destroy(device::qfs::TRANSFER, Transfer);

			gcl::buffer ReturnBuffer(Context, device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT, buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST | buffer::usage::VERTEX, 3, VertexLayout, NULL);

			Transfer = ReturnBuffer << *VertexBuffer;
			vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
			Context->submit(device::qfs::TRANSFER, 1, &SubmitInfo, Fence);
			vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT64_MAX);
			vkDestroyFence(Context->handle(), Fence, NULL);
			Context->destroy(device::qfs::TRANSFER, Transfer);

			float temp[18];
			ReturnBuffer.read(0, 3 * 24, temp);
			int Success = memcmp(VertexData, temp, 18 * sizeof(float)) ;
		}

		VertexShader = new shader(Context, shader::stage::VERTEX, VertexShaderSource);
		PixelShader = new shader(Context, shader::stage::FRAGMENT, PixelShaderSource);

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

				// Only One Buffer
				VkVertexInputBindingDescription BindingDescription[1];
				// Two Attributes in the buffer.
				VkVertexInputAttributeDescription AttributeDescription[2];

				BindingDescription[0].binding		= 0;
				BindingDescription[0].stride		= VertexLayout.Size;
				BindingDescription[0].inputRate		= VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

				// VertexPosition
				AttributeDescription[0].location	= 0;
				AttributeDescription[0].binding		= 0;
				AttributeDescription[0].format		= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
				AttributeDescription[0].offset		= VertexLayout[0].Offset;

				// VertexColor
				AttributeDescription[1].location	= 1;
				AttributeDescription[1].binding		= 0;
				AttributeDescription[1].format		= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
				AttributeDescription[1].offset		= VertexLayout[1].Offset;

				VertexInput.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				VertexInput.pNext								= NULL;
				VertexInput.flags								= 0;
				VertexInput.vertexBindingDescriptionCount		= 1;
				VertexInput.pVertexBindingDescriptions			= BindingDescription;
				VertexInput.vertexAttributeDescriptionCount		= 2;
				VertexInput.pVertexAttributeDescriptions		= AttributeDescription;

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
					vkCmdBindVertexBuffers(DrawPack[Stage->RenderTarget[i]]->Command[j], 0, 1, &VertexBuffer->handle(), &BufferOffset);
					vkCmdDraw(DrawPack[Stage->RenderTarget[i]]->Command[j], 3, 1, 0, 0);
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
		isReadyToBeProcessed.store(true);
	}

	triangle::~triangle() {
		isReadyToBeProcessed.store(false);
		// Delete Drawpack
		delete PixelShader;
		delete VertexShader;
		delete VertexBuffer;
	}

}
