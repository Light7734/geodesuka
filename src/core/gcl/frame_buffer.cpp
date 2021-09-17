#include <geodesuka/core/gcl/frame_buffer.h>

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
				VkRenderPassCreateInfo;

			}

			frame_buffer::frame_buffer(context* aDeviceContext) {

			}

			frame_buffer::~frame_buffer() {

			}

		}
	}
}