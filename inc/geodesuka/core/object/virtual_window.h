#pragma once
#ifndef GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H
#define GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H

#include "../math.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "../object.h"
#include "window.h"

//#include "../graphical/frame_buffer.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class virtual_window : public window {
			public:

				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;
				//virtual math::integer process_input(const hid::joystick& Joystick)		override;

				virtual math::integer update(math::real aDeltaTime)						override;

				// Target specific methods for windows being drawn to.
				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

				// Mandatory implementation required by window.h
				virtual math::integer draw(object_t* aObject)							override;

			};

		}
	}
}

#endif // !GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H
