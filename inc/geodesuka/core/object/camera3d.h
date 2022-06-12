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

		// These are the built in shaders needed for the default renderer.
		static const char* DefaultPerVertexShaderSource;
		static const char* DefaultPerPixelShaderSource;

		struct geometry_buffer {
			//gcl::image OpaquePixelColor;
			//gcl::image OpaqueDepthBuffer;
			//gcl::image TranslucentPixelColor;
			//gcl::image TranslucentDepthBuffer;
			//gcl::image PixelPosition;
			//gcl::image PixelNormal;

			gcl::image PixelColor;

			gcl::image PixelPosition;
			gcl::image PixelNormal;
		};

		static constexpr int RTID = 5;

		geometry_buffer *GeometryBuffer;

		//camera3d(engine* aEngine, gcl::context* aContext, stage::scene3d* aScene3D);
		//~camera3d();

		// ----- object_t methods ----- //

		// ----- rendertarget methods ----- //

		virtual int rtid() override;

		// ----- camera methods ----- //

		// ----- camera3d methods ----- //

	protected:

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

	private:



		// DepthList:
		// The depth list is a list of sorted objects based
		// on the distance from the camera they are. The opaque
		// objects nearest to the camera will be rendered first.
		std::vector<object_t*> OpaqueObject;

		// AlphaList:
		// Objects with that have translucency or are transparent
		// (i.e. Alpha != 1.0) will be drawn where the furthest objects
		// are rendered first for appropriate ordering.
		std::vector<object_t*> TranslucentObject;


	};

}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA3D_H
