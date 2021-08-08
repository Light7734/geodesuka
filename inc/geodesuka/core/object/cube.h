#pragma once
#ifndef CUBE_H
#define CUBE_H

/*
// -------------------------------------------------- cube.h -------------------------------------------------- \\
This object should serve as an example of how to extend "object.h" to create custom objects which can be used
with the game engine. As of right now there are four types of windows that can be drawn to. When object.h is
extended, the derivative class has full control over how the particular derived class is drawn to the target
window.


\\ -------------------------------------------------- cube.h -------------------------------------------------- //
*/

#include "../gcl/buffer.h"
#include "../gcl/shader.h"
#include "../gcl/texture.h"

#include "../gcl/vertex_array.h"
#include "../gcl/shader_program.h"
#include "../gcl/frame_buffer.h"

#include "../hid/keyboard.h"
#include "../hid/mouse.h"
#include "../hid/joystick.h"

#include "../object.h"

#include "system_display.h"
#include "system_window.h"
#include "virtual_window.h"
#include "camera.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class cube : public object {
			public:

				//buffer* VertexBuffer;
				//buffer* IndexBuffer;

				//shader* VertexShader;
				//shader* PixelShader;



				cube(gcl::context *Context);
				~cube();

				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;

				virtual math::integer update(math::real aDeltaTime)						override;

				// Specifies how cube will be drawn to these respective targets
				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

			};

		}
	}
}

#endif // !CUBE_H

