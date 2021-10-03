#include <geodesuka/core/object.h>

#include <geodesuka/engine.h>

namespace geodesuka::core {

	object_t::~object_t() {
		// Clear everything, then remove.

		// If parent engine exists and is not in desctruction state, clear from engine.
		if ((this->ParentEngine != nullptr) && (this->ParentEngine->State != engine::state::ENGINE_DESTRUCTION_STATE)) {
			for (size_t i = 0; i < this->ParentEngine->Object.size(); i++) {
				if (this == this->ParentEngine->Object[i]) {
					this->ParentEngine->Object.erase(this->ParentEngine->Object.begin() + i);
				}
			}
		}
	}

	void object_t::input(const hid::keyboard& aKeyboard) {

	}

	void object_t::input(const hid::mouse& aMouse) {

	}

	void object_t::update(math::real aDt) {
		//tex:
		// Update equations for generic object type with applied forces.
		// $$ d\vec{p} = \big( \vec{F}_{\text{applied}} + \vec{F}_{user} \big) dt $$ 
		// $$ d \vec{x} = \big( \frac{\vec{p}}{m} + \vec{v}_{user} \big) dt $$

		this->Momentum += (this->Force + this->InputForce) * aDt;
		this->Position += ((this->Momentum / this->Mass) + this->InputVelocity) * aDt;


	}

	void object_t::draw(object::system_display* aTargetSystemDisplay) {

	}

	void object_t::draw(object::system_window* aTargetSystemWindow) {

	}

	void object_t::draw(object::virtual_window* aTargetVirtualWindow) {

	}

	void object_t::draw(object::camera2d* aTargetCamera2D) {

	}

	void object_t::draw(object::camera3d* aTargetCamera3D) {

	}

	void object_t::set_position(math::real3 aPosition) {

	}

	math::real3 object_t::get_position() const {
		return this->Position;
	}

	object_t::object_t(engine& aEngine, gcl::context* aContext) {

	}

}