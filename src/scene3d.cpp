#include <geodesuka/core/stage/scene3d.h>

namespace geodesuka::core::stage {

	scene3d::scene3d(engine* aEngine, gcl::context* aContext) {
		this->Engine = aEngine;
		this->Context = aContext;
	}

	scene3d::~scene3d() {

	}

	stage_t::batch scene3d::render() {
		batch DrawBatch;
		return DrawBatch;
	}

}