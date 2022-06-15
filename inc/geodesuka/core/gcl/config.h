#pragma once
#ifndef GEODESUKA_CORE_GCL_CONFIG_H
#define GEODESUKA_CORE_GCL_CONFIG_H

#include "../../config.h"

/* Vulkan API */
#include <vulkan/vulkan.h>

/* GLFW Window System */
#include <GLFW/glfw3.h>

/* OpenCL API */
//#define CL_TARGET_OPENCL_VERSION GCL_OPENCL_VERSION
//#ifdef __APPLE__
// #include <OpenCL/opencl.h>
// #include <OpenCL/cl_gl.h>
// #include <OpenCL/cl_gl_ext.h>
//#else
// #include <CL/cl.h>
// #include <CL/cl_gl.h>
// #include <CL/cl_gl_ext.h>
//#endif

/* OpenVR API */
//#include <openvr.h>

// Typedefs for vulkan.


// Vulkan name space crap.

typedef GLFWwindow									glfw_window;

namespace vk {}

// snakeified vulkan api
typedef VkResult									vk_result;
typedef VkBool32									vk_bool_32;
typedef VkStructureType								vk_structure_type;
typedef VkSharingMode								vk_sharing_mode;

typedef VkApplicationInfo							vk_application_info;
typedef VkInstanceCreateInfo						vk_instance_create_info;
typedef VkInstance									vk_instance;

typedef VkPhysicalDevice							vk_physical_device;
typedef VkPhysicalDeviceProperties					vk_physical_device_properties;
typedef VkPhysicalDeviceFeatures					vk_physical_device_features;
typedef VkPhysicalDeviceMemoryProperties			vk_physical_device_memory_properties;
typedef VkExtensionProperties						vk_extension_properties;

typedef VkMemoryRequirements						vk_memory_requirements;

typedef VkQueueFamilyProperties						vk_queue_family_properties;
typedef VkQueueFlags								vk_queue_flags;
typedef VkQueue										vk_queue;

typedef VkCommandPoolCreateFlagBits					vk_command_pool_create_flag_bits;
typedef VkCommandPoolCreateInfo						vk_command_pool_create_info;
typedef VkCommandPool								vk_command_pool;

typedef VkCommandBufferAllocateInfo					vk_command_buffer_allocate_info;
typedef VkCommandBufferLevel						vk_command_buffer_level;
typedef VkCommandBuffer								vk_command_buffer;
typedef VkCommandBufferBeginInfo					vk_command_buffer_begin_info;

typedef VkDeviceQueueCreateInfo						vk_device_queue_create_info;
typedef VkDeviceCreateInfo							vk_device_create_info;
typedef VkDevice									vk_device;

typedef VkMemoryPropertyFlags						vk_memory_property_flags;
typedef VkMemoryPropertyFlagBits					vk_memory_property_flag_bits;

typedef VkMemoryAllocateInfo						vk_memory_allocate_info;
typedef VkDeviceMemory								vk_device_memory;

typedef VkBufferUsageFlags							vk_buffer_usage_flags;
typedef VkBufferUsageFlagBits						vk_buffer_usage_flag_bits;
typedef VkBufferCreateInfo							vk_buffer_create_info;
typedef VkBuffer									vk_buffer;

typedef VkImageMemoryBarrier						vk_image_memory_barrier;
typedef VkImageCreateInfo							vk_image_create_info;
typedef VkImage										vk_image;
typedef VkImageViewCreateInfo						vk_image_view_create_info;
typedef VkImageView									vk_image_view;

typedef VkBufferCopy								vk_buffer_copy;
typedef VkImageCopy									vk_image_copy;
typedef VkBufferImageCopy							vk_buffer_image_copy;

typedef VkShaderStageFlagBits						vk_shader_stage_flag_bits;
typedef VkShaderStageFlags							vk_shader_stage_flags;
typedef VkShaderModuleCreateInfo					vk_shader_module_create_info;
typedef VkShaderModule								vk_shader_module;

typedef VkAttachmentDescription						vk_attachment_description;
typedef VkSubpassDescription						vk_subpass_description;
typedef VkSubpassDependency							vk_subpass_dependency;
typedef VkRenderPassCreateInfo						vk_render_pass_create_info;
typedef VkRenderPass								vk_render_pass;

typedef VkFramebufferCreateInfo						vk_framebuffer_create_info;
typedef VkFramebuffer								vk_framebuffer;

typedef VkDescriptorSetLayoutBinding				vk_descriptor_set_layout_binding;
typedef VkDescriptorSetLayoutCreateInfo				vk_descriptor_set_layout_create_info;
typedef VkDescriptorSetLayout						vk_descriptor_set_layout;
typedef VkDescriptorPoolCreateInfo					vk_descriptor_pool_create_info;
typedef VkDescriptorPool							vk_descriptor_pool;
typedef VkDescriptorSetAllocateInfo					vk_descriptor_set_allocate_info;
typedef VkDescriptorSet								vk_descriptor_set;

typedef VkVertexInputAttributeDescription			vk_vertex_input_attribute_description;

typedef VkPipelineShaderStageCreateInfo				vk_pipeline_shader_stage_create_info;
typedef VkPipelineVertexInputStateCreateInfo		vk_pipeline_vertex_input_state_create_info;
typedef VkPipelineInputAssemblyStateCreateInfo		vk_pipeline_input_assembly_state_create_info;
typedef VkPipelineTessellationStateCreateInfo		vk_pipeline_tessellation_state_create_info;
typedef VkPipelineViewportStateCreateInfo			vk_pipeline_viewport_state_create_info;
typedef VkPipelineRasterizationStateCreateInfo		vk_pipeline_rasterization_state_create_info;
typedef VkPipelineMultisampleStateCreateInfo		vk_pipeline_multisample_state_create_info;
typedef VkPipelineDepthStencilStateCreateInfo		vk_pipeline_depth_stencil_state_create_info;
typedef VkPipelineColorBlendStateCreateInfo			vk_pipeline_color_blend_state_create_info;
typedef VkPipelineDynamicStateCreateInfo			vk_pipeline_dynamic_state_create_info;

typedef VkGraphicsPipelineCreateInfo				vk_graphics_pipeline_create_info;
typedef VkRayTracingPipelineCreateInfoKHR			vk_ray_tracing_pipeline_create_info_khr;
typedef VkComputePipelineCreateInfo					vk_compute_pipeline_create_info;

typedef VkPipelineLayoutCreateInfo					vk_pipeline_layout_create_info;
typedef VkPipelineBindPoint							vk_pipeline_bind_point;
typedef VkPipelineLayout							vk_pipeline_layout;
typedef VkPipelineCache								vk_pipeline_cache;
typedef VkPipeline									vk_pipeline;

// ----- Synchronization ----- //

typedef VkFenceCreateInfo							vk_fence_create_info;
typedef VkFence										vk_fence;

typedef VkSemaphoreCreateInfo						vk_semaphore_create_info;
typedef VkSemaphore									vk_semaphore;

// ----- KHR Extensions ----- //

typedef VkSurfaceKHR								vk_surface_khr;

typedef VkSubmitInfo								vk_submit_info;
typedef VkPresentInfoKHR							vk_present_info_khr;

#endif // !GEODESUKA_CORE_GCL_CONFIG_H
