#include <geodesuka/core/object/camera2d.h>

namespace geodesuka {
	namespace core {
		namespace object {

			math::integer camera2d::input(const hid::keyboard& aKeyboard) {
				return 0;
			}

			math::integer camera2d::input(const hid::mouse& aMouse) {
				return 0;
			}

			math::integer camera2d::update(math::real aDeltaTime) {
				return 0;
			}

			math::integer camera2d::draw(system_display* aTargetSystemDisplay) {
				return 0;
			}

			math::integer camera2d::draw(system_window* aTargetSystemWindow) {
				return 0;
			}

			math::integer camera2d::draw(virtual_window* aTargetVirtualWindow) {
				return 0;
			}

			math::integer camera2d::draw(camera2d* aTargetCamera2D) {
				return 0;
			}

			math::integer camera2d::draw(camera3d* aTargetCamera3D) {
				return 0;
			}

			math::integer camera2d::draw(object_t* aObject) {
				if ((object_t*)this == aObject) return -1;
				return aObject->draw(this);
			}

		}
	}
}
