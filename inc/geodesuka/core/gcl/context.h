#pragma once
#ifndef CONTEXT_H
#define CONTEXT_H

/*
* // ------------------------- context.h ------------------------- \\
* context.h is used for managing OpenGL contexts, OpenCL contexts, and Vulkan
* instances. These are all synonymous terms within the scope of this engine,
* and shall be treated similarly.
* \\ ------------------------- context.h ------------------------- //
*/

#include <vector>

#include "gcl.h"

#include "variable.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class buffer;
			class shader;
			class texture;

			class vertex_array;
			class shader_program;
			class frame_buffer;

			class context {
			public:

				// OpenGL
				enum client_api {
					None			= GLFW_NO_API,
					OpenGL			= GLFW_OPENGL_API,
					OpenGLES		= GLFW_OPENGL_ES_API
				};

				enum profile {
					AnyProfile		= GLFW_OPENGL_ANY_PROFILE,
					CoreProfile		= GLFW_OPENGL_CORE_PROFILE,
					CompatProfile	= GLFW_OPENGL_COMPAT_PROFILE
				};

				enum creation_api {
					Native			= GLFW_NATIVE_CONTEXT_API,
					EGL				= GLFW_EGL_CONTEXT_API,
					OSMesa			= GLFW_OSMESA_CONTEXT_API
				};

				struct prop {
					int ClientAPI;
					int CreationAPI;
					int Version[2];
					int Robustness;
					int ForwardCompat;
					int DebugMode;
					int NoError;
					int Profile;
					int ReleaseBehavior;
					//int Revision;
					
					// Default Constructor.
					prop();

					// Set OpenGL type 
					prop(client_api aClientAPI, int aVersionMajor, int aVersionMinor, profile aProfile);
				};

				context* Parent;
				GLFWwindow* Handle;
				struct prop Property;

				// Default Constructor creates "OpenGL 3.3 Core Profile" Context.
				context();

				// Constructs contexts based on settings provided.
				context(client_api aClientAPI, int aVersionMajor, int aVersionMinor, profile aProfile);

				//context(prop *aProperty);

				context(context *aContext, prop *aProperty);

				~context();

				// Creates Resource Objects.
				buffer* create_buffer(int aType, int aVertexCount, variable aVertexLayout, void* aVertexData);
				int destroy_buffer(buffer* aBuffer);

				shader* create_shader();
				texture* create_texture();

				// Creates State Objects.
				vertex_array* create_vertex_array();
				shader_program* create_shader_program();
				frame_buffer* create_frame_buffer();

				//int flush();
				math::integer finish();

			private:

				// ----- The OpenGL State ----- //
				// These are resource objects, can be shared between contexts.
				std::vector<buffer*> Buffer;
				std::vector<shader*> Shader;
				std::vector<texture*> Texture;

				// These are state objects, they CANNOT be shared between contexts.
				std::vector<vertex_array*> VertexArray;
				std::vector<shader_program*> ShaderProgram;
				std::vector<frame_buffer*> FrameBuffer;

				enum func_call {
					CTX_GL_VERTEX_ATTRIB_ARRAY
				};

				struct func_packet {
					func_call FunctionIndex;
					int ArgCount;
					void** Arg;
				};

				// This is simply a function queue.
				int FunctionQueueCount;
				struct func_packet **FunctionQueue;

			};

		}
	}
}

#endif // !CONTEXT_H

