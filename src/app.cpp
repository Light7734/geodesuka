#include <geodesuka/engine.h>

#include <geodesuka/core/app.h>

namespace geodesuka::core {

	app::app(engine* aEngine, int argc, char* argv[]) {
		this->Engine = aEngine;
	}

	// This is used engine side to generate thread for Application.
	void app::run() {
		// App is now ready to be run.
		this->ExitApp.store(false);
		// Initializes game loop.
		this->gameloop();
		// Forces all threads to finish.
		this->Engine->Shutdown.store(true);
	}

}
