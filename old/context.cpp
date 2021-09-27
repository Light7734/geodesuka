#include <geodesuka/core/gcl/context.h>

#include <geodesuka/core/gcl/gcl.h>

#include <geodesuka/core/gcl/variable.h>

#include <geodesuka/core/gcl/buffer.h>
#include <geodesuka/core/gcl/shader.h>
#include <geodesuka/core/gcl/texture.h>

#include <geodesuka/core/gcl/vertex_array.h>
#include <geodesuka/core/gcl/shader_program.h>
#include <geodesuka/core/gcl/frame_buffer.h>

namespace geodesuka {
	namespace core {
		namespace gcl {

			/*
			* TODO: Figure out how to copy data objects meaningfully.
			*/
			context::prop::prop() {
				this->ClientAPI				= GLFW_OPENGL_API;
				this->CreationAPI			= GLFW_NATIVE_CONTEXT_API;
				this->Version[0]			= 3;
				this->Version[1]			= 3;
				this->Robustness			= GLFW_NO_ROBUSTNESS;
				this->ForwardCompat			= GLFW_FALSE;
				this->DebugMode				= GLFW_FALSE;
				this->NoError				= GLFW_FALSE;
				this->Profile				= GLFW_OPENGL_CORE_PROFILE; // CORE
				this->ReleaseBehavior		= GLFW_ANY_RELEASE_BEHAVIOR;
			}

			context::prop::prop(client_api aClientAPI, int aVersionMajor, int aVersionMinor, profile aProfile) {
				this->ClientAPI				= aClientAPI;
				this->CreationAPI			= GLFW_NATIVE_CONTEXT_API;
				this->Version[0]			= aVersionMajor;
				this->Version[1]			= aVersionMinor;
				this->Robustness			= GLFW_NO_ROBUSTNESS;
				this->ForwardCompat			= GLFW_FALSE;
				this->DebugMode				= GLFW_FALSE;
				this->NoError				= GLFW_FALSE;
				this->Profile				= aProfile;
				this->ReleaseBehavior		= GLFW_ANY_RELEASE_BEHAVIOR;
			}

			context::context() {
				this->Parent = nullptr;
				this->Handle = NULL;
				this->Property = prop();

				this->FunctionQueueCount = 0;
				this->FunctionQueue = nullptr;
			}

			context::context(client_api aClientAPI, int aVersionMajor, int aVersionMinor, profile aProfile) {
				this->Parent = nullptr;
				this->Handle = NULL;
				this->Property = prop(aClientAPI, aVersionMajor, aVersionMinor, aProfile);

				this->FunctionQueueCount = 0;
				this->FunctionQueue = nullptr;
			}

			context::context(context* aContext, prop* aProperty) {
				this->Parent = aContext;
				this->Handle = NULL;
				if (aProperty != NULL) {
					// Maybe memcpy?
					this->Property = *aProperty;
				}
				else {
					this->Property = context::prop();
				}

				this->FunctionQueueCount = 0;
				this->FunctionQueue = nullptr;
			}

			context::~context() {
				if (this->Handle != NULL) {
					glfwDestroyWindow(this->Handle);
				}
				this->Property = prop();
			}

			//buffer* context::create_buffer(int aType, int aCount, variable aLayout, void* aData) {
			//	buffer* temp = new buffer(this, aType, aCount, aLayout, aData);
			//	Buffer.push_back(temp);
			//	return temp;
			//}

			math::integer context::finish() {
				// Roll through function queue.
				return 0;
			}

		}
	}
}
