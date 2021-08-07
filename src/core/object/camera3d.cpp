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

			// Does nothing because no idea what this should do.
			math::integer camera3d::draw(system_display* aTargetSystemDisplay) { return 0; }

			math::integer camera3d::draw(system_window* aTargetSystemWindow) {
				// Deferred Rendering, will forward output to system window.
				return 0;
			}

			math::integer camera3d::draw(virtual_window* aTargetVirtualWindow) {
				// Deferred Rendering, will forward output to virtual window.
				return 0;
			}

			// Does nothing because they don't exist in the same space.
			math::integer camera3d::draw(camera2d* aTargetCamera2D) { return 0; }

			math::integer camera3d::draw(camera3d* aTargetCamera3D) {
				// must use camera model for camera to be drawn to
				// another camera.
				return 0;
			}

			math::integer camera3d::draw(object* aObject) {
				// Checks if this and aObject are the same object.
				if ((object*)this == aObject) return -1;

				// Checks if both camera3d instance and aObject have
				// the same rendering context.
				//if (this->RenderingContext != aObject->RenderingContext) return -2;

				// New idea for rendering objects to camera, sort
				// from nearest to farthest to make efficient rendering.
				// How to deal with alpha?
				
				// DepthList:
				// The depth list is a list of sorted objects based
				// on the distance from the camera they are. The opaque
				// objects nearest to the camera will be rendered first.

				// AlphaList:
				// Objects with that have translucency or are transparent
				// (i.e. Alpha != 1.0) will be drawn where the furthest objects
				// are rendered first for appropriate ordering.

				//math::real DeltaPos = math::length(temp);
				return aObject->draw(this);
			}

		}
	}
}