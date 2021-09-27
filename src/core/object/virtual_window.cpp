#include <geodesuka/core/object/virtual_window.h>

namespace geodesuka {
	namespace core {
		namespace object {

			math::integer virtual_window::input(const hid::keyboard& aKeyboard) {
				return 0;
			}

			math::integer virtual_window::input(const hid::mouse& aMouse) {
				return 0;
			}

			math::integer virtual_window::update(math::real aDt) {
				return 0;
			}

			math::integer virtual_window::draw(system_display* aTargetSystemDisplay) {
				return 0;
			}

			math::integer virtual_window::draw(system_window* aTargetSystemWindow) {
				return 0;
			}

			math::integer virtual_window::draw(virtual_window* aTargetVirtualWindow) {
				return 0;
			}

			math::integer virtual_window::draw(camera2d* aTargetCamera2D) { return 0; }

			math::integer virtual_window::draw(camera3d* aTargetCamera3D) { return 0; }

			math::integer virtual_window::draw(object_t* aObject) {
				return 0;
			}

		}
	}
}