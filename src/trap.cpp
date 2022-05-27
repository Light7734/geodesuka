#include <geodesuka/core/logic/trap.h>

#include <mutex>
//#include <iostream>
//std::mutex IOMutex;

namespace geodesuka::core::logic {

	trap::trap() {
		this->Active.store(false);
		this->Count.store(0);
	}

	trap::~trap() {
		// On destruction, releases trapped threads.
		this->Active.store(false);
		//this->Count = 0;
	}

	void trap::set(bool aState) {
		this->Active.store(aState);
	}

	void trap::door() {
		if (this->Active.load()) {
			this->Count.fetch_add(1);
			//IOMutex.lock();
			//std::cout << "Thread ID " << std::this_thread::get_id() << std::endl;
			//IOMutex.unlock();
			while (this->Active.load()) {
				// TODO: Add sleep timer.
			};
			this->Count.fetch_sub(1);
		}
	}

	int trap::count() {
		return this->Count.load();
	}

	void trap::wait_until(int aCount) {
		while (this->Count.load() != aCount) {
			// TODO: Put thread to sleep.
		}
	}

}
