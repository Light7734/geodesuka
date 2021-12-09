#include <geodesuka/core/object/rendertarget.h>

namespace geodesuka::core::object {

	rendertarget::~rendertarget() {

	}

	void rendertarget::set_framerate(double aFPS) {
		this->FramesPerSecond = aFPS;
		// Sets the update wait time.
		this->RefreshTimer.set(1.0 / this->FramesPerSecond);

	}

	double rendertarget::framerate() {
		return this->FramesPerSecond;
	}

	rendertarget::rendertarget(engine* aEngine, gcl::context* aContext) : object_t(aEngine, aContext) {
		this->FramesPerSecond = 0.0;
	}

}
