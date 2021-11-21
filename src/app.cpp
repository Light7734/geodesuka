#include <geodesuka/core/app.h>

#include <geodesuka/engine.h>

namespace geodesuka::core {

	app::app(engine* aEngine, int argc, char* argv[]) {
		this->Engine = aEngine;
	}

}
