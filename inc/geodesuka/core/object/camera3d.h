#pragma once
#ifndef CAMERA3D_H
#define CAMERA3D_H


#include "camera.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class camera3d : public camera {

				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;

				virtual math::integer update(math::real aDeltaTime)						override;

				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

				virtual math::integer draw(object* aObject)								override;

			};

		}
	}
}
#endif // !CAMERA3D_H
