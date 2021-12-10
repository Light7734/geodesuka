#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA3D_H
#define GEODESUKA_CORE_OBJECT_CAMERA3D_H

#include "../object.h"
#include "camera.h"

namespace geodesuka::core::object {

	class camera3d : public camera {
	public:

		/*
		* The output of a pixel shader using this as a render target
		* must use the following form.
		* layout (location = 0) out vec3 PixelColor;
		* layout (location = 1) out vec3 PixelPosition;
		* layout (location = 2) out vec3 PixelNormal;
		*/

		//camera3d(engine *aEngine, gcl::context *aContext);
		//~camera3d();



	protected:

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

	private:

		// The structure of each frame.
		struct frame {
			// Depth Attachments.
			gcl::texture DepthBuffer;
			// Color Attachments
			gcl::texture PixelColor;		// R32G32B32
			gcl::texture PixelPosition;		// R32G32B32
			gcl::texture PixelNormal;		// R32G32B32

		};

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


	};

}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA3D_H
