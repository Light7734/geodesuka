#include <geodesuka/core/object.h>

#include <geodesuka/engine.h>

namespace geodesuka::core {

	object_t::~object_t() {
		this->Engine->remove(this);
	}

	void object_t::input(const hid::keyboard& aKeyboard) {

	}

	void object_t::input(const hid::mouse& aMouse) {

	}

	void object_t::update(double aDeltaTime) {
		//tex:
		// Update equations for generic object type with applied forces.
		// $$ d\vec{p} = \big( \vec{F}_{\text{applied}} + \vec{F}_{user} \big) dt $$ 
		// $$ d \vec{x} = \big( \frac{\vec{p}}{m} + \vec{v}_{user} \big) dt $$

		this->Mutex.lock();

		// Generic Free body motion equations.
		this->Momentum += (this->Force + this->InputForce) * aDeltaTime;
		this->Position += ((this->Momentum / this->Mass) + this->InputVelocity) * aDeltaTime;


		this->Mutex.unlock();
	}

	void object_t::draw(object::system_display* aTargetSystemDisplay) {}

	void object_t::draw(object::system_window* aTargetSystemWindow) {}

	void object_t::draw(object::virtual_window* aTargetVirtualWindow) {}

	void object_t::draw(object::camera2d* aTargetCamera2D) {}

	void object_t::draw(object::camera3d* aTargetCamera3D) {}

	void object_t::set_position(math::real3 aPosition) {}

	math::real3 object_t::get_position() const {
		return this->Position;
	}

	object_t::object_t(engine* aEngine, gcl::context* aContext) {

		// Internal API.
		this->Engine = aEngine;
		this->Context = aContext;

		this->InputVelocity = math::real3(0.0, 0.0, 0.0);
		this->InputForce = math::real3(0.0, 0.0, 0.0);

		this->Mass = 1.0;
		this->Time = core::logic::get_time();
		this->Position = math::real3(0.0, 0.0, 0.0);
		this->Momentum = math::real3(0.0, 0.0, 0.0);
		this->Force = math::real3(0.0, 0.0, 0.0);
		this->DirectionX = math::real3(1.0, 0.0, 0.0);
		this->DirectionY = math::real3(0.0, 1.0, 0.0);
		this->DirectionZ = math::real3(0.0, 0.0, 1.0);

		//std::cout << "Object Created" << std::endl;
	}

}