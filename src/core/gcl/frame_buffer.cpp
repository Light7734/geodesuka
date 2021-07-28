#include <geodesuka/core/gcl/frame_buffer.h>

#include <geodesuka/core/gcl/gcl.h>


namespace geodesuka {
	namespace core {
		namespace gcl {

			frame_buffer::prop::prop() {
					this->ColorBits[0]			= 8;
					this->ColorBits[1]			= 8;
					this->ColorBits[2]			= 8;
					this->ColorBits[3]			= 8;
					this->DepthBits				= 24;
					this->StencilBits			= 8;
					this->AccumColorBits[0]		= 0;
					this->AccumColorBits[1]		= 0;
					this->AccumColorBits[2]		= 0;
					this->AccumColorBits[3]		= 0;
					this->AuxBuffers			= 0;
					this->Stereo				= GLFW_FALSE;
					this->DoubleBuffer			= GLFW_TRUE;
					this->Transparent			= GLFW_FALSE;
					this->Samples				= 0;
					this->sRGBCapable			= GLFW_FALSE;
			}

			frame_buffer::frame_buffer() {
				this->Context = nullptr;
				this->Property = prop();
				this->ID = -1;
			}

			frame_buffer::frame_buffer(const prop& aProperty) {
				this->Context = nullptr;
				this->Property = aProperty;
				this->ID = -1;
			}

			frame_buffer::frame_buffer(context* aContext, const prop& aProperty) {
				this->Context = aContext;
				this->Property = aProperty;
				if (aContext->Handle != NULL) {
					// Check is context is current!
					GLuint temp;
					glGenFramebuffers(1, &temp);
					this->ID = (math::integer)temp;
				}
				else {
					this->ID = -1;
				}
			}

			frame_buffer::~frame_buffer() {

			}

		}
	}
}