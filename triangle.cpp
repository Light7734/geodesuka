#include "triangle.h"

#include <geodesuka/engine.h>

using namespace geodesuka::core;
using namespace object;
using namespace hid;
using namespace math;
using namespace gcl;
using namespace util;

triangle::triangle(geodesuka::engine *aEngine, gcl::context* aContext) : object_t(aEngine, aContext) {	

	// Hard coded vertices
	float Vertices[] = {
		-1.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0, 0.0, 1.0
	};


	type VLType(type::id::STRUCT, NULL);
	VLType.push(type::id::REAL3, "Position");
	VLType.push(type::id::REAL3, "Color");
	variable MemLayout(VLType, "Vertex");

	std::cout << MemLayout.get_str() << std::endl;

	buffer VertexBuffer(aContext, buffer::memory::DEVICE_LOCAL, buffer::usage::VERTEX | buffer::usage::TRANSFER_SRC | buffer::usage::TRANSFER_DST, 3, MemLayout, Vertices);

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
	shader VertexShader(aContext, shader::VERTEX, VertexShaderSource);
	shader FragmentShader(aContext, shader::FRAGMENT, FragmentShaderSource);

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

	vkCreateGraphicsPipelines(aContext->handle(), VK_NULL_HANDLE, 1, &this->CreateInfo, NULL, &this->GraphicsPipeline);

	// Submit to engine. Needed for update and render operations. 
	aEngine->submit(this);
}

