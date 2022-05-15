#pragma once
#ifndef GEODESUKA_CORE_GCL_H
#define GEODESUKA_CORE_GCL_H

/* Vulkan API */
#include <vulkan/vulkan.h>

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


namespace vk {}

typedef VkInstance vk_instance;
typedef VkPhysicalDevice vk_physical_device;
typedef VkDevice vk_device;

#endif // !GEODESUKA_CORE_GCL_H
