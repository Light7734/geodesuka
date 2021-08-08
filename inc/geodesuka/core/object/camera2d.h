#pragma once
#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../object.h"

#include "camera.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class camera2d : public camera {
			public:

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

#endif // !CAMERA2D_H
