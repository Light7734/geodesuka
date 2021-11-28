#include <geodesuka/core/object/render_target.h>

namespace geodesuka::core::object {

	render_target::~render_target() {

	}

	void render_target::set_framerate(double aFPS) {
		this->FPS = aFPS;
		// Sets the update wait time.
		this->RefreshTimer.set(1.0 / this->FPS);

	}

	double render_target::framerate() {
		return this->FPS;
	}

	render_target::render_target(engine* aEngine, gcl::context* aContext) : object_t(aEngine, aContext) {
		this->TextureCount = 0;
		this->Texture = nullptr;
		this->FPS = 0.0;
	}

}
