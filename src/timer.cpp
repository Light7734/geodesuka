#include <geodesuka/core/logic/timer.h>

#include <cmath>
#include <mutex>

/* --------------- Platform Dependent Libraries --------------- */
#if defined(_WIN32) || defined(_WIN64)
 #include <Windows.h>
#elif defined(__APPLE__) || defined(MACOSX)

#elif defined(__linux__) && !defined(__ANDROID__)
 #include <unistd.h>
#elif defined(__ANDROID__)
 #include <unistd.h>
#endif

#include <GLFW/glfw3.h>

namespace geodesuka::core::logic {

	timer::timer() {
		this->Duration = 0.0;
		this->ElapsedTime = 0.0;
	}

	timer::timer(double aDuration) {
		this->Duration = aDuration;
		this->ElapsedTime = 0.0;
	}

	timer::~timer() {}

	void timer::set(double aDuration) {
		this->Mutex.lock();
		this->Duration = aDuration;
		this->Mutex.unlock();
	}

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

	double get_time() {
		return glfwGetTime();
	}

	void set_time(double aTime) {
		glfwSetTime(aTime);
	}

	void waitfor(double aSeconds) {
		double Microseconds = 1000.0 * aSeconds;
#if defined(_WIN32) || defined(_WIN64)
		DWORD Duration = (DWORD)std::floor(Microseconds);
		Sleep(Duration);
#elif defined(__APPLE__) || defined(MACOSX)

#elif defined(__linux__) && !defined(__ANDROID__)
		int Duration = (int)std::floor(Microseconds);
		usleep(Duration);
#elif defined(__ANDROID__)

#endif
	}

}

