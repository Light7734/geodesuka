#ifndef MOUSE_H
#define MOUSE_H

//#include "../gcl/gcl.h"

#include "../math/math.h"

namespace geodesuka {
	namespace core {
		namespace hid {

			class mouse {
			public:

				enum button {
					BUTTON_LEFT = 0,
					BUTTON_RIGHT = 1,
					BUTTON_MIDDLE = 2,
					BUTTON_4 = 3,
					BUTTON_5 = 4,
					BUTTON_6 = 5,
					BUTTON_7 = 6,
					BUTTON_LAST = 7
				};
				enum action {
					BUTTON_RELEASE = 0,
					BUTTON_PRESS = 1,
					BUTTON_REPEAT = 2
				};

				enum mode {
					MODE_NORMAL = 0x00034001,
					MODE_HIDDEN = 0x00034002,
					MODE_DISABLED = 0x00034003
				};

				// Mouse Input
				math::integer Action[8];
				math::integer Modifier[8];
				math::real2 Scroll;

				// Cursor Variables
				math::integer Mode;
				math::boolean InWindow;
				math::real2 Position;
				math::real2 Velocity;
				math::real2 Acceleration;

				mouse();
				~mouse();

				math::boolean operator[](math::integer buttonID);

			};

		}
	}
}

#endif // !MOUSE_H