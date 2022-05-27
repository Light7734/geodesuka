#pragma once
#ifndef GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
#define GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H

#include <geodesuka/engine.h>

namespace geodesuka::builtin::object {

	class triangle : public core::object_t {
	public:

		triangle(engine* aEngine, core::gcl::context* aContext, core::stage_t* aStage);
		~triangle();

	protected:

	private:

		core::gcl::buffer* VertexBuffer;
		core::gcl::shader* VertexShader;
		core::gcl::shader* PixelShader;

		VkPipeline Pipeline;

	};

}

#endif // !GEODESUKA_BUILTIN_OBJECT_TRIANGLE_H
