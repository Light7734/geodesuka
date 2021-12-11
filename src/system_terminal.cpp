#include <geodesuka/core/object/system_terminal.h>

#include <iostream>

namespace geodesuka::core::object {

	system_terminal::system_terminal(engine* aEngine, gcl::context* aContext) : object_t(aEngine, aContext) {
		// It doesn't matter what the Context is, it isn't used
		// here for rendering at all.
	}

	system_terminal::~system_terminal() {

	}

	bool system_terminal::operator>>(util::str& aRhs) {
		bool temp = false;
		this->Mutex.lock();

		this->Mutex.unlock();
		return temp;
	}

	bool system_terminal::operator<<(util::str& aRhs) {
		(*this) << aRhs.ptr();
		return false;
	}

	bool system_terminal::operator<<(const char* aRhs) {
		this->Mutex.lock();
		std::cout << aRhs;
		this->Mutex.unlock();
		return false;
	}

}