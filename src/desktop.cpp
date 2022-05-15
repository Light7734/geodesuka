#include <geodesuka/core/stage/desktop.h>

namespace geodesuka::core::stage {

	desktop::desktop(engine* aEngine, gcl::device* aDevice, object::system_display* aDisplay) : stage_t(aEngine, nullptr) {
		this->RenderTarget.push_back(aDisplay);
	}

	desktop::~desktop() {

	}

}
