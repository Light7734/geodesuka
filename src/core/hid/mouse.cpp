#include <geodesuka/core/hid/mouse.h>

#include <geodesuka/core/math.h>

namespace geodesuka {
	namespace core {
		namespace hid {

			mouse::mouse() {
				Mode = MODE_NORMAL;
			}

			mouse::~mouse() {

			}

			math::boolean mouse::operator[](math::integer buttonID) {
				if ((Action[buttonID] == BUTTON_PRESS) || (Action[buttonID] == BUTTON_REPEAT)) {
					return true;
				}
				else {
					return false;
				}
			}

		}
	}
}
