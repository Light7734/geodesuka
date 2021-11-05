#pragma once
#ifndef GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
#define GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H

#include <geodesuka/engine.h>

namespace geodesuka::builtin::object {

	class triangle : public core::object_t {
	public:

		//triangle(geodesuka::engine* aEngine);
		triangle(engine* aEngine, core::gcl::context* aContext);
		~triangle();

		//virtual void input(const core::hid::keyboard& aKeyboard)					override;
		//virtual void input(const core::hid::mouse& aMouse)							override;

		//virtual void update(double aDeltaTime)										override;

		//// Specifies how cube will be drawn to these respective targets
		//virtual void draw(core::object::system_display* aTargetSystemDisplay)		override;
		virtual void draw(core::object::system_window* aTargetSystemWindow)			override;
		//virtual void draw(core::object::virtual_window* aTargetVirtualWindow)		override;

		//virtual void draw(core::object::camera2d* aTargetCamera2D)					override;
		//virtual void draw(core::object::camera3d* aTargetCamera3D)					override;

	private:


		// Describes the bound vertex buffers in draw call.
		std::vector<VkVertexInputBindingDescription> InputBindingDescription;
		// Describes the per vertex memory layout of bound buffers.
		std::vector<VkVertexInputAttributeDescription> InputAttributeDescription;
		// Shader stages of the graphics pipeline.
		std::vector<VkPipelineShaderStageCreateInfo> ShaderStage;

		// Shader Stages for triangle.
		VkPipelineVertexInputStateCreateInfo VertexInput;
		VkPipelineInputAssemblyStateCreateInfo InputAssembly;
		//VkPipelineTessellationStateCreateInfo Tessellation;
		VkPipelineViewportStateCreateInfo Viewport;
		VkPipelineRasterizationStateCreateInfo Rasterizer;
		VkPipelineMultisampleStateCreateInfo Multisample;
		VkPipelineDepthStencilStateCreateInfo DepthStencil;
		VkPipelineColorBlendStateCreateInfo ColorBlend;
		VkPipelineDynamicStateCreateInfo DynamicState;

		VkGraphicsPipelineCreateInfo CreateInfo;
		VkPipeline GraphicsPipeline;

	};

}

#endif // !GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
