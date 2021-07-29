#include <geodesuka/core/object/object.h>

namespace geodesuka {
	namespace core {
		namespace object {

			math::integer object::update(math::real aDt) {
				//tex:
				// Update equations for generic object type with applied forces.
				// $$ d\vec{p} = \big( \vec{F}_{\text{applied}} + \vec{F}_{user} \big) dt $$ 
				// $$ d \vec{x} = \big( \frac{\vec{p}}{m} + \vec{v}_{user} \big) dt $$

				this->Momentum += (this->Force + this->InputForce) * aDt;
				this->Position += ((this->Momentum / this->Mass) + this->InputVelocity) * aDt;

				return 0;
			}

			math::integer object::set_position(math::real3 aPosition) {
				return 0;
			}

			math::real3 object::get_position() const {
				return this->Position;
			}

		}
	}
}