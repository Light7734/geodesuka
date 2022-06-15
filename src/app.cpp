#include <geodesuka/engine.h>

#include <geodesuka/core/app.h>

namespace geodesuka::core {

	app::app(engine* aEngine) {
		this->Engine = aEngine;
		this->TimeStep = 0.0;
	}

	// This is used engine side to generate thread for Application.
	void app::prerun() {
		// App is now ready to be run.
		this->ExitApp.store(false);
		// Initializes game loop.
		this->run();
		// Forces all threads to finish.
		this->Engine->Shutdown.store(true);
	}

}
