#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA3D_H
#define GEODESUKA_CORE_OBJECT_CAMERA3D_H

#include "../object.h"
#include "camera.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class camera3d : public camera {

				// Will produce a camera3d that is perspective rendering.
				//camera3d(gcl::context* aRenderingContext, math::real FOV, math::real aAspectRatio, math::real aNear, math::real aFar);

				//camera3d()

				virtual math::integer input(const hid::keyboard& aKeyboard)				override;
				virtual math::integer input(const hid::mouse& aMouse)					override;

				virtual math::integer update(math::real aDeltaTime)						override;

				virtual math::integer draw(system_display* aTargetSystemDisplay)		override;
				virtual math::integer draw(system_window* aTargetSystemWindow)			override;
				virtual math::integer draw(virtual_window* aTargetVirtualWindow)		override;

				virtual math::integer draw(camera2d* aTargetCamera2D)					override;
				virtual math::integer draw(camera3d* aTargetCamera3D)					override;

				virtual math::integer draw(object_t* aObject)							override;

			};

		}
	}
}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA3D_H
