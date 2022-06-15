#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA3D_H
#define GEODESUKA_CORE_OBJECT_CAMERA3D_H

#include "../gcl/context.h"
#include "../gcl/pipeline.h"

#include "../object.h"
#include "camera.h"

//#include "../stage.h"
//#include "../stage/scene3d.h"

namespace geodesuka::core::object {

	class camera3d : public camera {
	public:

		struct geometry_buffer {
			gcl::image PixelColor;
			gcl::image PixelPosition;
			gcl::image PixelNormal;
			gcl::image PixelSpecular;
		};

		/*
		* Input Table
		* layout (location = 0) in vec3 VertexPosition;
		* layout (location = 1) in vec3 VertexNormal;
		* layout (location = 2) in vec2 VertexTextureCoordinate;
		*/

		/*
		* Output Table:
		* layout (location = 0) out vec3 PixelColor;
		* layout (location = 1) out vec3 PixelPosition;
		* layout (location = 2) out vec3 PixelNormal;
		* layout (location = 3) out vec3 PixelSpecular;
		*/

		static constexpr int ID = 5;

		// These are the built in shaders needed for the default renderer.
		// They are made public to other classes so they can be modified or reused
		// on draw command creation.
		static const char* OpaquePerVertexShaderSource;
		static const char* OpaquePerPixelShaderSource;


		gcl::shader* OpaqueVertexShader;
		gcl::shader* OpaquePixelShader;




		// Used for rendering opaque objects.
		gcl::pipeline* OpaquePipeline;
		gcl::pipeline* TransparentPipeline;

		geometry_buffer *GeometryBuffer;

		camera3d(engine* aEngine, gcl::context* aContext, stage_t* aScene3D);
		~camera3d();

		// ----- object_t methods ----- //

		// ----- rendertarget methods ----- //

		virtual int id() override;

		virtual gcl::command_batch render(stage_t* aStage);

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
