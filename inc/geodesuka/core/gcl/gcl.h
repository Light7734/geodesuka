#pragma once
#ifndef GCL_H
#define GCL_H

/* 
------------------------- Graphics & Computation Library -------------------------

The goal of this project is to serve as an access point for other projects
for both gpu graphics and computation. There are special functions which allow
the communication between OpenGL and OpenCL contexts. The goal of this library
is to be readily usable for other projects on rapid demand.

Graphics API: OpenGL, DirectX, Vulkan
Computation API: OpenCL, CUDA, Vulkan

TODO: Create Stateless API from OpenGL.
TODO: Records OpenGL State Machine in the Backend.

------------------------- Graphics & Computation Library -------------------------
*/


/* Standard C Libraries */
#include <stdint.h>
#include <float.h>
#include <limits.h>

/* Standard C++ Libraries */
#include <string>
#include <vector>

/* OpenGL API */
#include <glad/glad.h>

/* OpenCL API */
#define CL_TARGET_OPENCL_VERSION 120
#ifdef __APPLE__ // is garbage
 #include <OpenCL/opencl.h>
 #include <OpenCL/cl_gl.h>
 #include <OpenCL/cl_gl_ext.h>
#else
 #include <CL/cl.h>
 #include <CL/cl_gl.h>
 #include <CL/cl_gl_ext.h>
#endif

/* Vulkan API */
#include <vulkan/vulkan.h>

/* GLFW API */
//#define VK_USE_PLATFORM_WIN32_KHR
//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

//#include <openvr.h>

//namespace geodesuka {
//	namespace core {
//		namespace gcl {
//
//			/*
//			There are two apis with respective types and functions calls. The point of this api
//			is to regroup them into meaningful categories for an easy api that blends the two.
//			The entitites we wish to represent in a meaningful manner.
//
//			Displays
//			Windows
//			Contexts
//			Devices
//			Memory Buffers
//
//			Types:
//				OpenGL:
//
//			*/
//			// Binding of Context -> FrameBuffer -> VertexArray -> ShaderProgram
//			// 
//			// These are blended types.
//
//			// These are modified OpenGL types.
//
//			namespace gl {
//				// OpenGL namespace.
//				
//				// This is synonymous with window. Within any context, the default framebuffer
//				// is the window framebuffer. To draw to the default frame buffer, is to draw
//				// to the window.
//				struct context {
//					// is equal to NULL if inactive.
//					GLFWwindow* Handle;
//
//					// Context Options
//					struct prop {
//						int ClientAPI;
//						int CreationAPI;
//						int Version[2];
//						int Robustness;
//						int ForwardCompat;
//						int DebugMode;
//						int NoError;
//						int Profile;
//						int ReleaseBehavior;
//						//int Revision;
//					} Property;
//				};
//
//				struct frame {
//					// ID = 0, is the default frame buffer for each context.
//					unsigned int ID;
//
//					// Required by GLFW
//					struct prop {
//						int ColorBits[4];
//						int DepthBits;
//						int StencilBits;
//						int AccumColorBits[4];
//						int AuxBuffers;
//						int Stereo;
//						int DoubleBuffer;
//						int Transparent;
//						int Samples;
//						int sRGBCapable;
//					} Property;
//				};
//
//				struct window {
//					struct context* Context;
//					struct frame Frame;
//					struct prop {
//						int Resizable;
//						int Decorated;
//						int UserFocused;
//						int AutoMinimize;
//						int Floating;
//						int Maximized;
//						int Minimized;
//						int Visible;
//						int ScaleToMonitor;
//						int CenterCursor;
//						int FocusOnShow;
//						int Hovered;
//						int RefreshRate;
//					} Property;
//				};
//
//				context::prop default_context_prop();
//				frame::prop default_frame_prop();
//				window::prop default_window_prop();
//
//
//				// Modified OpenGL functions
//				context create_context(const context::prop* aCP);
//				window create_window(context* aCP, const frame::prop* aFP, const window::prop* aWP);
//			}
//
//			namespace vk {
//				// Vulkan namespace.
//			}
//
//			namespace dx {
//				// DirectX namespace.
//			}
//
//			namespace cl {
//				// OpenCL namespace.
//				
//				// These are modified OpenCL types.
//				typedef cl_context context;
//
//				// OpenCL functions
//
//			}
//
//			namespace cu {
//				// This is the CUDA namespace.
//			}
//
//			// Initializes/Terminates all backend apis.
//			int initiate();
//			int terminate();
//
//		}
//	}
//}

#endif // !GCL_H