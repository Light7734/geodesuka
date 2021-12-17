#include <geodesuka/core/stage/scene2d.h>

namespace geodesuka::core::stage {

	scene2d::scene2d(engine* aEngine, gcl::context* aContext) : stage_t(aEngine, aContext) {
		this->Engine = aEngine;
		this->Context = aContext;
	}

	scene2d::~scene2d() {

	}

	//stage_t::batch scene2d::render() {
	//	batch DrawBatch;
	//	return DrawBatch;
	//}

}