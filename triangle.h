#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <geodesuka/engine.h>

class triangle : public geodesuka::core::object_t {
public:

	//triangle(geodesuka::engine* aEngine);
	triangle(geodesuka::engine &aEngine, geodesuka::core::gcl::device_context* aDeviceContext);

	// overriden fron object.h
	// Should be called if input stream is directed to it
	virtual geodesuka::core::math::integer input(const geodesuka::core::hid::keyboard& aKeyboard)					override;
	virtual geodesuka::core::math::integer input(const geodesuka::core::hid::mouse& aMouse)							override;
	//virtual math::integer process_input(const hid::joystick& Joystick)		override;

	// Update the object in time, requires implementation in child
	virtual geodesuka::core::math::integer update(geodesuka::core::math::real aDeltaTime)							override;

	// Target specific methods for windows being drawn to.
	virtual geodesuka::core::math::integer draw(geodesuka::core::object::system_display* aTargetSystemDisplay)		override;
	virtual geodesuka::core::math::integer draw(geodesuka::core::object::system_window* aTargetSystemWindow)		override;
	virtual geodesuka::core::math::integer draw(geodesuka::core::object::virtual_window* aTargetVirtualWindow)		override;

	// Does Nothing
	virtual geodesuka::core::math::integer draw(geodesuka::core::object::camera2d* aTargetCamera2D)					override;
	virtual geodesuka::core::math::integer draw(geodesuka::core::object::camera3d* aTargetCamera3D)					override;

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

#endif // !TRIANGLE_H
