#include <geodesuka/core/object/camera3d.h>

namespace geodesuka {
	namespace core {
		namespace object {



			math::integer camera3d::input(const hid::keyboard& aKeyboard) {
				return 0;
			}

			math::integer camera3d::input(const hid::mouse& aMouse) {
				return 0;
			}

			math::integer camera3d::update(math::real aDeltaTime) {
				return 0;
			}

			math::integer camera3d::draw(system_display* aTargetSystemDisplay) {
				return 0;
			}

			math::integer camera3d::draw(system_window* aTargetSystemWindow) {
				return 0;
			}

			math::integer camera3d::draw(virtual_window* aTargetVirtualWindow) {
				return 0;
			}

			math::integer camera3d::draw(camera2d* aTargetCamera2D) {
				return 0;
			}

			math::integer camera3d::draw(camera3d* aTargetCamera3D) {
				return 0;
			}

			math::integer camera3d::draw(object* aObject) {
				if ((object*)this == aObject) return -1;
				return aObject->draw(this);
			}

		}
	}
}