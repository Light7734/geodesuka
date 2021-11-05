#pragma once
#ifndef GEODESUKA_CORE_LOGIC_TRAP_H
#define GEODESUKA_CORE_LOGIC_TRAP_H

/*
* This class is just a simple thread trap to
* be used with the engine, mostly to suspend
* active threads to allow main thread to modify
* the state of the engine and prevent race
* conditions. Not sure if this is going to cause
* a cache penalty to be incurred.
*/

#include <thread>
#include <mutex>
#include <atomic>

namespace geodesuka::core::logic {

	class trap {
	public:

		trap();
		~trap();
		
		// Enter 'true' to set trap, and 'false' to release.
		void set(bool aState);

		// Lay trap door to catch active threads.
		void door();

		// Returns number of threads currently trapped.
		int count();

		// Waits until a specified number of threads have been trapped.
		void wait_until(int aCount);

	private:

		std::atomic<bool> Active;	// Specifies whether the trap is active.
		std::atomic<int> Count;		// The number of currently trapped threads.

	};

}

#endif // !GEODESUKA_CORE_LOGIC_TRAP_H
