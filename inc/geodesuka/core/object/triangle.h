#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../gcl/buffer.h"
#include "../gcl/shader.h"
#include "../gcl/texture.h"

#include "../gcl/vertex_array.h"
#include "../gcl/shader_program.h"
#include "../gcl/frame_buffer.h"

#include "../hid/keyboard.h"
#include "../hid/mouse.h"
#include "../hid/joystick.h"

#include "object.h"

#include "system_display.h"
#include "system_window.h"
#include "virtual_window.h"
#include "camera2d.h"
#include "camera3d.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class triangle : public object {
			public:

				triangle();
				~triangle();

			private:

				

			};

		}
	}
}

#endif // !TRIANGLE_H
