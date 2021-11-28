#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA3D_H
#define GEODESUKA_CORE_OBJECT_CAMERA3D_H

#include "../object.h"
#include "camera.h"

namespace geodesuka::core::object {

	class camera3d : public camera {
	public:

		//camera3d(engine *aEngine, gcl::context *aContext);
		//~camera3d();



	protected:

		// DepthList:
		// The depth list is a list of sorted objects based
		// on the distance from the camera they are. The opaque
		// objects nearest to the camera will be rendered first.
		std::vector<object_t> OpaqueObject;

		// AlphaList:
		// Objects with that have translucency or are transparent
		// (i.e. Alpha != 1.0) will be drawn where the furthest objects
		// are rendered first for appropriate ordering.
		std::vector<object_t> TranslucentObject;

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

	private:


	};

}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA3D_H
