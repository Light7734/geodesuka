#include <geodesuka/core/gcl/gcl.h>

#if defined(_WIN32) || defined(_WIN64)
 #define GLFW_EXPOSE_NATIVE_WIN32
 #define GLFW_EXPOSE_NATIVE_WGL
#elif defined(__APPLE__) || defined(MACOSX)
 #define GLFW_EXPOSE_NATIVE_COCOA
 #define GLFW_EXPOSE_NATIVE_NSGL
#elif defined(__linux__) && !defined(__ANDROID__)
 #define GLFW_EXPOSE_NATIVE_X11
 #define GLFW_EXPOSE_NATIVE_GLX
#elif defined(__ANDROID__)

#endif

#if defined(__APPLE__) || defined(MACOSX)
 #define GL_SHARING_EXTENSION "cl_APPLE_gl_sharing"
#else
 #define GL_SHARING_EXTENSION "cl_khr_gl_sharing"
#endif

// Standard C Libraries
//#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <math.h>

// Standard C++ Libraries
#include <string>
#include <vector>

// OpenGL Function Loader
#include <glad/glad.h>

#ifdef __APPLE__
 #include <OpenCL/opencl.h>
 #include <OpenCL/cl_gl.h>
 #include <OpenCL/cl_gl_ext.h>
#else
 #include <CL/cl.h>
 #include <CL/cl_gl.h>
 #include <CL/cl_gl_ext.h>
#endif

// Vulkan Library
//#include <vulkan/vulkan.h>

// OpenGL Window & Context Manager
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

//#include <openvr.h>
