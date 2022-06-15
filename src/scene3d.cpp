#include <geodesuka/core/stage/scene3d.h>

namespace geodesuka::core::stage {

	scene3d::scene3d(engine* aEngine, gcl::context* aContext) : stage_t(aEngine, aContext) {
		this->Engine = aEngine;
		this->Context = aContext;
	}

	scene3d::~scene3d() {

	}

	int scene3d::id() {
		return ID;
	}

	//stage_t::batch scene3d::render() {
	//	batch DrawBatch;
	//	return DrawBatch;
	//}

}