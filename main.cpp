#include <iostream>
#include <algorithm>

#include <geodesuka/engine.h>

#include <geodesuka/builtin/object/triangle.h>

/*
* This main file is just used for debugging library.
*/

using namespace geodesuka::core;
using namespace gcl;
using namespace object;

using namespace geodesuka::builtin::object;

/*
* setProcessDPIAwarenessContext()
* dpichagned
* Checks for monitor swaps.
*/

/*
* Currently I am unsure how I wish to queue render calls.
* I want a sorting algorithm to be implemented for sorting
* objects queued to be rendered. The idea is to sort based
* on distance from camera, and by whether or not the object
* has an opaque component.
*/
// Creates a window on every display

/*
TODO:
Add functions.
waitfor(Seconds);
get_time();

Complete system_terminal class.

Finish texture class.

Finish system_window class.

Finish Triangle Example.
*/

void buffer_unit_test(geodesuka::core::gcl::context* Context);
void texture_unit_test(geodesuka::core::gcl::context* Context);

// Updated buffer.h, testing 
int main(int argc, char *argv[]) {
	geodesuka::engine Engine(argc, argv);
	if (!Engine.is_ready()) return -1;

	size_t DeviceCount = 0;
	device** Device = Engine.get_device_list(&DeviceCount);
	context* Context = nullptr;
	context* Context2 = nullptr;
	for (size_t i = 0; i < DeviceCount; i++) {
		if (Device[i]->get_properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Provide required extensions to allow context to create system windows.
			//std::cout << "Transfer Index: " << Device[i]->qfi(device::qfs::PRESENT);
			Context = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
			Context2 = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
		}
	}

	//buffer_unit_test(Context);
	//texture_unit_test(Context);


	VkResult Result = VkResult::VK_SUCCESS;
	VkAttachmentDescription AttachmentDescription[2] = { {}, {} };

	AttachmentDescription[0].flags				= 0;
	AttachmentDescription[0].format				= VkFormat::VK_FORMAT_R8G8B8A8_SRGB;
	AttachmentDescription[0].samples			= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescription[0].loadOp				= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescription[0].storeOp			= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescription[0].stencilLoadOp		= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescription[0].stencilStoreOp		= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescription[0].initialLayout		= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescription[0].finalLayout		= VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	AttachmentDescription[1].flags				= 0;
	AttachmentDescription[1].format				= VkFormat::VK_FORMAT_D32_SFLOAT;
	AttachmentDescription[1].samples			= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	AttachmentDescription[1].loadOp				= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescription[1].storeOp			= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescription[1].stencilLoadOp		= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	AttachmentDescription[1].stencilStoreOp		= VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_DONT_CARE;
	AttachmentDescription[1].initialLayout		= VkImageLayout::VK_IMAGE_LAYOUT_UNDEFINED;
	AttachmentDescription[1].finalLayout		= VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference ColorAttachment{};
	ColorAttachment.attachment		= 0;
	ColorAttachment.layout			= VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference DepthAttachment{};
	DepthAttachment.attachment		= 1;
	DepthAttachment.layout			= VkImageLayout::VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


	VkSubpassDescription Subpass{};
	Subpass.flags						= 0;
	Subpass.pipelineBindPoint			= VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_GRAPHICS;
	Subpass.inputAttachmentCount		= 0;
	Subpass.pInputAttachments			= NULL;
	Subpass.colorAttachmentCount		= 1;
	Subpass.pColorAttachments			= &ColorAttachment;
	Subpass.pResolveAttachments			= NULL;
	Subpass.pDepthStencilAttachment		= &DepthAttachment;
	Subpass.preserveAttachmentCount		= 0;
	Subpass.pPreserveAttachments		= NULL;


	VkRenderPassCreateInfo RPCreateInfo{};
	RPCreateInfo.sType				= VkStructureType::VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	RPCreateInfo.pNext				= NULL;
	RPCreateInfo.flags				= 0;
	RPCreateInfo.attachmentCount	= 2;
	RPCreateInfo.pAttachments		= AttachmentDescription;
	RPCreateInfo.subpassCount		= 1;
	RPCreateInfo.pSubpasses			= &Subpass;
	RPCreateInfo.dependencyCount	= 0;
	RPCreateInfo.pDependencies		= NULL;

	//Result = vkCreateRenderPass(Context->handle(), );

	VkRenderPass RenderPass = VK_NULL_HANDLE;
	Result = vkCreateRenderPass(Context->handle(), &RPCreateInfo, NULL, &RenderPass);

	// Hard coded vertices
	math::real Vertices[] = {
		-1.0, 0.0, 1.0, 0.0, 0.0, 
		 0.0, 1.0, 0.0, 1.0, 0.0, 
		 1.0, 0.0, 0.0, 0.0, 1.0 
	};


	util::variable Variable(util::type::id::STRUCT, "Vertex");
	Variable.Type.push(util::type::id::REAL2, "Position");
	Variable.Type.push(util::type::id::REAL3, "Color");
	//Variable.Type.push(util::type::id::REAL3, "Color");

	//std::cout << MemLayout.get_str() << std::endl;

	buffer* VertexBuffer = new buffer(
		Context,
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
	shader VertexShader(Context, shader::VERTEX, VertexShaderSource);
	shader FragmentShader(Context, shader::FRAGMENT, FragmentShaderSource);

	VkPipelineShaderStageCreateInfo ShaderStage[2];


	VkVertexInputAttributeDescription Attribute[2];
	VkVertexInputBindingDescription BindingLocation;

	Attribute[0].location		= 0;
	Attribute[0].binding		= 0;
	Attribute[0].format			= VkFormat::VK_FORMAT_R32G32_SFLOAT;
	Attribute[0].offset			= 0;

	Attribute[1].location		= 1;
	Attribute[1].binding		= 0;
	Attribute[1].format			= VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
	Attribute[1].offset			= 8;

	BindingLocation.binding		= 0;
	BindingLocation.stride		= 20;
	BindingLocation.inputRate	= VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;

	VkPipelineVertexInputStateCreateInfo VertexInput{};
	VertexInput.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInput.pNext								= NULL;
	VertexInput.flags								= 0;
	VertexInput.vertexBindingDescriptionCount		= 1;
	VertexInput.pVertexBindingDescriptions			= &BindingLocation;
	VertexInput.vertexAttributeDescriptionCount		= 2;
	VertexInput.pVertexAttributeDescriptions		= Attribute;

	VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
	InputAssembly.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssembly.pNext						= NULL;
	InputAssembly.flags						= 0;
	InputAssembly.topology					= VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssembly.primitiveRestartEnable	= VK_FALSE;
	
	VkViewport ScreenSize;
	ScreenSize.x = 0;
	ScreenSize.y = 0;
	ScreenSize.width = 640;
	ScreenSize.height = 480;
	ScreenSize.minDepth = 0.0;
	ScreenSize.maxDepth = 1.0;

	VkRect2D ScissorStuff = { { 0, 0 }  , { 640, 480 } };
	

	VkPipelineViewportStateCreateInfo Viewport{};
	Viewport.sType				= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	Viewport.pNext				= NULL;
	Viewport.flags				= 0;
	Viewport.viewportCount		= 1;
	Viewport.pViewports			= &ScreenSize;
	Viewport.scissorCount		= 1;
	Viewport.pScissors			= &ScissorStuff;

	VkPipelineRasterizationStateCreateInfo Rasterizer{};
	Rasterizer.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	Rasterizer.pNext						= NULL;
	Rasterizer.flags						= 0;
	Rasterizer.depthClampEnable				= VK_TRUE;
	Rasterizer.rasterizerDiscardEnable		= VK_TRUE;
	Rasterizer.polygonMode					= VkPolygonMode::VK_POLYGON_MODE_FILL;
	Rasterizer.cullMode						= VkCullModeFlagBits::VK_CULL_MODE_BACK_BIT;
	Rasterizer.frontFace					= VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE;
	Rasterizer.depthBiasEnable				= VK_FALSE;
	Rasterizer.depthBiasConstantFactor		= 1.0;
	Rasterizer.depthBiasClamp				= 0.0;
	Rasterizer.depthBiasSlopeFactor			= 0.0;
	Rasterizer.lineWidth					= 1.0;

	//VkSampleMask SampleMask

	VkPipelineMultisampleStateCreateInfo Multisample{};
	Multisample.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	Multisample.pNext					= NULL;
	Multisample.flags					= 0;
	Multisample.rasterizationSamples	= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	Multisample.sampleShadingEnable		= VK_FALSE;
	Multisample.minSampleShading		= 1.0;
	Multisample.pSampleMask				= NULL;
	Multisample.alphaToCoverageEnable	= VK_TRUE;
	Multisample.alphaToOneEnable		= VK_FALSE;

	VkPipelineDepthStencilStateCreateInfo DepthStencil{};
	DepthStencil.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencil.pNext						= NULL;
	DepthStencil.flags						= 0;
	DepthStencil.depthTestEnable			= VK_TRUE;
	DepthStencil.depthWriteEnable			= VK_TRUE;
	DepthStencil.depthCompareOp				= VkCompareOp::VK_COMPARE_OP_LESS;
	DepthStencil.depthBoundsTestEnable		= VK_FALSE;
	DepthStencil.stencilTestEnable			= VK_FALSE;
	DepthStencil.front						= {};
	DepthStencil.back						= {};
	DepthStencil.minDepthBounds				= 0.0;
	DepthStencil.maxDepthBounds				= 1.0;

	VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
	ColorBlendAttachment.blendEnable			= VK_TRUE;
	ColorBlendAttachment.srcColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
	ColorBlendAttachment.dstColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColorBlendAttachment.colorBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
	ColorBlendAttachment.srcAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE;
	ColorBlendAttachment.dstAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	ColorBlendAttachment.alphaBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
	ColorBlendAttachment.colorWriteMask			= VkColorComponentFlagBits::VK_COLOR_COMPONENT_R_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_G_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_B_BIT | VkColorComponentFlagBits::VK_COLOR_COMPONENT_A_BIT;


	VkPipelineColorBlendStateCreateInfo Blending{};
	Blending.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	Blending.pNext					= NULL;
	Blending.flags					= 0;
	Blending.logicOpEnable			= VK_FALSE;
	Blending.logicOp				;
	Blending.attachmentCount		= 1;
	Blending.pAttachments			= &ColorBlendAttachment;
	Blending.blendConstants[0]		= 0.0;
	Blending.blendConstants[1]		= 0.0;
	Blending.blendConstants[2]		= 0.0;
	Blending.blendConstants[3]		= 0.0;


	// Sets up shaders in graphics pipeline.
	ShaderStage[0].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStage[0].pNext = NULL;
	ShaderStage[0].flags = 0;
	ShaderStage[0].stage = VertexShader.get_stage();
	ShaderStage[0].module = VertexShader.get_handle();
	ShaderStage[0].pName = "main";
	ShaderStage[0].pSpecializationInfo = NULL;

	ShaderStage[1].sType = VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStage[1].pNext = NULL;
	ShaderStage[1].flags = 0;
	ShaderStage[1].stage = FragmentShader.get_stage();
	ShaderStage[1].module = FragmentShader.get_handle();
	ShaderStage[1].pName = "main";
	ShaderStage[1].pSpecializationInfo = NULL;

	VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo{};
	VkPipelineLayout PipelineLayout;
	PipelineLayoutCreateInfo.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	PipelineLayoutCreateInfo.pNext						= NULL;
	PipelineLayoutCreateInfo.flags						= 0;
	PipelineLayoutCreateInfo.setLayoutCount				= 0;
	PipelineLayoutCreateInfo.pSetLayouts				= NULL;
	PipelineLayoutCreateInfo.pushConstantRangeCount		= 0;
	PipelineLayoutCreateInfo.pPushConstantRanges		= NULL;
	Result = vkCreatePipelineLayout(Context->handle(), &PipelineLayoutCreateInfo, NULL, &PipelineLayout);

	VkGraphicsPipelineCreateInfo CreateInfo{};	
	CreateInfo.sType					= VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	CreateInfo.pNext					= NULL;
	CreateInfo.flags					= 0;
	CreateInfo.stageCount				= 2;
	CreateInfo.pStages					= ShaderStage;
	CreateInfo.pVertexInputState		= &VertexInput;
	CreateInfo.pInputAssemblyState		= &InputAssembly;
	CreateInfo.pTessellationState		= NULL;
	CreateInfo.pViewportState			= &Viewport;
	CreateInfo.pRasterizationState		= &Rasterizer;
	CreateInfo.pMultisampleState		= &Multisample;
	CreateInfo.pDepthStencilState		= &DepthStencil;
	CreateInfo.pColorBlendState			= &Blending;
	CreateInfo.pDynamicState			= NULL;
	CreateInfo.layout					= PipelineLayout;
	CreateInfo.renderPass				= RenderPass;
	CreateInfo.subpass					= 0;
	CreateInfo.basePipelineHandle		= VK_NULL_HANDLE;
	CreateInfo.basePipelineIndex		= 0;

	double DeltaTime[10];
	VkPipeline Pipeline[10];
	for (uint32_t i = 0; i < 10; i++) {
		DeltaTime[i] = glfwGetTime();
		Result = vkCreateGraphicsPipelines(Context->handle(), VK_NULL_HANDLE, 1, &CreateInfo, NULL, &Pipeline[i]);
		DeltaTime[i] = glfwGetTime() - DeltaTime[i];
	}
	std::cout << "\n\n\n\n\n\n\n" << std::endl;
	for (uint32_t i = 0; i < 10; i++) {
		std::cout << "time: " << DeltaTime[i] * 1000.0 << std::endl;
	}


	Engine.tsleep(1);

	return 0;
}

void buffer_unit_test(geodesuka::core::gcl::context *Context) {
	// This function tests the integrity of data by passing
	// it to the selected devices memory, and then retrieving it.
	math::real Vertices[] = {
		-1.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0,
		 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0,
		 1.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0
	};

	math::real VertexReturn[] = {
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
	};

	memset(VertexReturn, 0xAA, 24 * sizeof(float));

	util::variable Variable(util::type::id::STRUCT, "Vertex");
	Variable.Type.push(util::type::id::REAL3, "Position");
	Variable.Type.push(util::type::id::REAL2, "TexCoord");
	Variable.Type.push(util::type::id::REAL3, "Color");

	buffer HostBuffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		Vertices
	);

	buffer DeviceBuffer(
		Context,
		device::memory::DEVICE_LOCAL,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	buffer ReturnBuffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	// Test methods later.
	buffer ConstructorCopy(HostBuffer);
	buffer ConstructorMove(buffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	));
	buffer AssignmentCopy;
	AssignmentCopy = HostBuffer;
	buffer AssignmentMove;
	AssignmentMove = buffer(
		Context,
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		buffer::usage::VERTEX,
		3,
		Variable,
		NULL
	);

	VkSubmitInfo Submission[2];
	VkCommandBuffer CommandBuffer[2];
	VkSemaphoreCreateInfo SemaphoreCreateInfo{};
	VkSemaphore Semaphore;
	VkFenceCreateInfo FenceCreateInfo{};
	VkFence Fence;

	FenceCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	FenceCreateInfo.pNext = NULL;
	FenceCreateInfo.flags = 0;

	SemaphoreCreateInfo.sType = VkStructureType::VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = NULL;
	SemaphoreCreateInfo.flags = 0;

	VkResult Result = VkResult::VK_SUCCESS;

	Result = vkCreateFence(Context->handle(), &FenceCreateInfo, NULL, &Fence);
	Result = vkCreateSemaphore(Context->handle(), &SemaphoreCreateInfo, NULL, &Semaphore);

	CommandBuffer[0] = (DeviceBuffer << HostBuffer);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);

	Submission[0].sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	Submission[0].pNext					= NULL;
	Submission[0].waitSemaphoreCount	= 0;
	Submission[0].pWaitSemaphores		= NULL;
	Submission[0].pWaitDstStageMask		= 0;
	Submission[0].commandBufferCount	= 1;
	Submission[0].pCommandBuffers		= &CommandBuffer[0];
	Submission[0].signalSemaphoreCount	= 1;
	Submission[0].pSignalSemaphores		= &Semaphore;

	Submission[1].sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
	Submission[1].pNext					= NULL;
	Submission[1].waitSemaphoreCount	= 1;
	Submission[1].pWaitSemaphores		= &Semaphore;
	Submission[1].pWaitDstStageMask		= 0;
	Submission[1].commandBufferCount	= 1;
	Submission[1].pCommandBuffers		= &CommandBuffer[1];
	Submission[1].signalSemaphoreCount	= 0;
	Submission[1].pSignalSemaphores		= NULL;

	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);

	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "Data matches" << std::endl;
	}
	else {
		std::cout << "Data doesn't match" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	CommandBuffer[0] = (DeviceBuffer << ConstructorCopy);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "ConstructorCopy Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "ConstructorCopy Data Integrity Test Status: Failure" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	ConstructorMove.write(0, 24 * sizeof(math::real), Vertices);
	CommandBuffer[0] = (DeviceBuffer << ConstructorMove);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "CopyMove Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "CopyMove Data Integrity Test Status: Failure" << std::endl;
	}

	memset(VertexReturn, 0xAA, 24 * sizeof(math::real));
	CommandBuffer[0] = (DeviceBuffer << AssignmentCopy);
	CommandBuffer[1] = (ReturnBuffer << DeviceBuffer);
	Context->submit(device::qfs::TRANSFER, 2, Submission, Fence);
	vkWaitForFences(Context->handle(), 1, &Fence, VK_TRUE, UINT_MAX);
	Context->destroy(context::cmdtype::TRANSFER_OTS, 2, CommandBuffer);
	vkResetFences(Context->handle(), 1, &Fence);
	ReturnBuffer.read(0, 24 * sizeof(math::real), VertexReturn);
	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "AssignmentCopy Data Integrity Test Status: Success" << std::endl;
	}
	else {
		std::cout << "AssignmentCopy Data Integrity Test Status: Failure" << std::endl;
	}
}

void texture_unit_test(geodesuka::core::gcl::context *Context) {
	// This function tests the integrity of data by passing
	// it to the selected devices memory, and then retrieving it.
	texture::prop DeviceProp = texture::prop();

	//HostProp.MipLevelCount		= 1;
	DeviceProp.ArrayLayerCount		= 1;
	DeviceProp.SampleCounts			= texture::sample::COUNT_1;
	DeviceProp.Tiling				= texture::tiling::OPTIMAL;
	DeviceProp.Usage				= texture::usage::SAMPLED;

	unsigned char PixelData[4 * 4 * 4] = {
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,
		0xAA, 0xBB, 0xCC, 0xDD, 0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD,0xAA, 0xBB, 0xCC, 0xDD
	};

	texture DeviceTexture(Context, device::memory::DEVICE_LOCAL, DeviceProp, VkFormat::VK_FORMAT_R8G8B8A8_UINT, 4, 4, 1, (void*)PixelData);


	buffer HostBuffer(Context, 
		device::memory::HOST_VISIBLE | device::memory::HOST_COHERENT,
		0, 
		4*4*4, NULL);



}
