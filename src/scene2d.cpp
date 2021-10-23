#include <geodesuka/core/stage/scene2d.h>

namespace geodesuka::core::stage {



	scene2d::scene2d() {

	}

	scene2d::~scene2d() {

	}

	void scene2d::render() {
		for (size_t i = 0; i < this->Camera.size(); i++) {
			for (size_t j = 0; j < this->Object.size(); j++) {
				this->Camera[i]->draw(this->Object[j]);
			}
		}
	}

}