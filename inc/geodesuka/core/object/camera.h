#pragma once
#ifndef CAMERA_H
#define CAMERA_H

// I'm still concerned how this will fit in as
// an object. It is an object, but is it a window?

// To be or not to be, is camera a type of window, 
// does it just contain a window.

// A camera shouldn't be a window since
// If it direct draws, it should contain windows.
// If it stream draws, it should 

/*

*/

#include <vector>
#include <string>

#include "../math/math.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "object.h"

//#include "../graphical/frame_buffer.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class camera : public object {
			public:

				math::real4x4 Translation;
				math::real4x4 Rotation;
				math::real4x4 Projection;

				//mouse Mouse;
				//keyboard Keyboard;
				//joystick Joystick;

				//math::real Time;
				//math::real3 Position;
				//math::real Mass;
				//math::real3 Momentum;
				//math::real3 Force;

				math::real Theta, Phi;
				math::real3 Right;
				math::real3 Up;
				math::real3 Forward;

				math::real FieldOfView;
				math::real AspectRatio;
				math::real MinDistance;
				math::real MaxDistance;

				virtual math::integer draw(object* aObject) = 0;

			protected:

				// WASD
				enum action {
					MOVE_FORWARD,
					MOVE_LEFT,
					MOVE_BACK,
					MOVE_RIGHT,
					MOVE_DOWN,
					MOVE_UP
				};

				float AngularVelTheta;
				float AngularVelPhi;

				float RotationalVelocity;
				float MovementVelocity;
				bool MoveDirection[6];

			};

		}
	}
}
#endif // !CAMERA_H
