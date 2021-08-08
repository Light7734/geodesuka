#pragma once
#ifndef SYSTEM_DISPLAY_H
#define SYSTEM_DISPLAY_H

#include "../gcl/gcl.h"
#include "../gcl/frame_buffer.h"

#include "../object.h"

#include "window.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class system_display : public window {
			public:

				friend class system_window;

				GLFWmonitor* Handle;

				system_display(GLFWmonitor * aMonitor);
				~system_display();

				// Inherited fron object.h
				// Should be called if input stream is directed to it
				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;

				// Update the object in time, requires implementation in child
				virtual math::integer update(math::real aDeltaTime)						override;

				// Target specific methods for windows being drawn to.
				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

				// Mandatory implementation required by window.h
				virtual math::integer draw(object* aObject)								override;

			private:

				math::integer2 PositionSC;
				//math::integer2 SizeSC;



			};

		}
	}
}

#endif // !SYSTEM_DISPLAY_H
