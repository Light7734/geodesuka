#pragma once
#ifndef GEODESUKA_CORE_GCL_PIPELINE_H
#define GEODESUKA_CORE_GCL_PIPELINE_H

#include <vector>

#include "config.h"

#include "device.h"
#include "context.h"
#include "shader.h"
#include "renderpass.h"

namespace geodesuka::core::gcl {

	class pipeline {
	public:

		/*
		The point of these structure is a straightforward api to map vulkan managed resources,
		to slots indicated by the shaders provided.
		*/

		// Pre creation options for a rasterizer pipeline.
		struct rasterizer {

			vk_pipeline_bind_point BindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

			std::vector<std::vector<vk_descriptor_set_layout_binding>> UniformSet;

			uint32_t UniformSetCount;
			uint32_t UniformSetBindingCount[4];
			vk_descriptor_set_layout_binding* UniformSetBindingList[4];

			uint32_t InputCount;
			vk_vertex_input_attribute_description* InputList;

			uint32_t OutputCount;
			vk_attachment_description* OutputList;

			uint32_t										StageCount;
			vk_pipeline_shader_stage_create_info*			StageList;
			vk_pipeline_vertex_input_state_create_info		VertexInput{};
			vk_pipeline_input_assembly_state_create_info	InputAssembly{};
			vk_pipeline_tessellation_state_create_info		Tesselation{};
			vk_pipeline_viewport_state_create_info			Viewport{};
			vk_pipeline_rasterization_state_create_info		Rasterizer{};
			vk_pipeline_multisample_state_create_info		Multisample{};
			vk_pipeline_depth_stencil_state_create_info		DepthStencil{};
			vk_pipeline_color_blend_state_create_info		ColorBlend{};
			vk_pipeline_dynamic_state_create_info			DynamicState{};

			vk_graphics_pipeline_create_info				CreateInfo{};

			rasterizer();
			rasterizer(uint32_t aShaderCount, shader** aShaderList);

			void set_inputs(uint32_t aInputCount, vk_vertex_input_attribute_description* aInputList);

		};

		// Pre creation options for a raytracer pipeline.
		struct raytracer {

			vk_pipeline_bind_point BindPoint = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR;

			vk_ray_tracing_pipeline_create_info_khr CreateInfo{};

			raytracer();
			//raytracer(uint32_t aShaderCount, shader** aShaderList);

		};

		// Pre creation options for a compute pipeline.
		// Requires on a single compute shader.
		struct compute {

			vk_pipeline_bind_point BindPoint = VK_PIPELINE_BIND_POINT_COMPUTE;

			vk_compute_pipeline_create_info CreateInfo{};

			compute();
			//compute(shader* aComputeShader);

		};

		/*
		* Render passes should be a KHR extension, not a part of core.
		* VkRenderPass only makes sense on mobile, and therefore should
		* not be a part of the core standard.
		*/

		// RenderPass created if no master render pass is provided to rasterizer.
		vk_render_pass RenderPass;
		uint32_t SubpassIndex;

		// This will be used for creating descriptor sets as well.
		uint32_t DescriptorSetLayoutCount;
		vk_descriptor_set_layout *DescriptorSetLayoutList;

		vk_pipeline_bind_point BindPoint;
		vk_pipeline_layout Layout;
		vk_pipeline_cache Cache;
		vk_pipeline Handle;

		// Creates rasterizer pipeline.
		pipeline(context* aContext, rasterizer& aRasterizer);

		// Creates raytracer pipeline.
		pipeline(context* aContext, raytracer& aRaytracer);

		// Creates compute pipeline.
		pipeline(context* aContext, compute& aCompute);

	private:

		context* Context;
		rasterizer Rasterizer;
		raytracer Raytracer;
		compute Compute;

		// This is backended for tracking.
		uint32_t AttachmentReferenceCount;
		vk_attachment_reference * AttachmentReferenceList;
		vk_subpass_description SubpassDescription{};
		vk_subpass_dependency SubpassDependency{};
		vk_render_pass_create_info RenderPassCreateInfo;

	};

	//vkCmdBindPipeline(aCommandBuffer, BindPoint, Handle);
	//vkCmdBindDescriptorSets(aCommandBuffer, BindPoint, Layout, 0, 0, NULL, 0, NULL);

}

#endif // !GEODESUKA_CORE_GCL_PIPELINE_H
