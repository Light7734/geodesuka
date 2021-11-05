#include <geodesuka/core/logic/timer.h>

#include <mutex>

namespace geodesuka::core::logic {

	timer::timer(double aDuration) {
		this->Duration = aDuration;
		this->ElapsedTime = 0.0;
	}

	timer::~timer() {}

	bool timer::check(double aDeltaTime) {
		bool temp = false;
		this->Mutex.lock();
		this->ElapsedTime += aDeltaTime;
		if (this->ElapsedTime >= this->Duration) {
			this->ElapsedTime = this->ElapsedTime - this->Duration;
			temp = true;
		}
		else {
			temp = false;
		}
		this->Mutex.unlock();
		return temp;
	}

}

