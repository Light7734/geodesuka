#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA_H
#define GEODESUKA_CORE_OBJECT_CAMERA_H

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

#include "../math.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "../object.h"

//#include "../graphical/frame_buffer.h"

namespace geodesuka::core::object {

	class camera : public object_t {
	public:

		~camera();

		virtual void draw(object_t* aObject);

	protected:

		// Generates the Perspective Projection Matrix.
		math::real FieldOfView;
		math::real AspectRatio;
		math::real MinDistance;
		math::real MaxDistance;

		// Camera Transforms for vertices.
		math::real4x4 PRT;
		math::real4x4 Projection;
		math::real4x4 Rotation;
		math::real4x4 Translation;

		camera(engine* aEngine, gcl::context* aContext);

	};

}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA_H
