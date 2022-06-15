#pragma once
#ifndef GEODESUKA_CORE_APP_H
#define GEODESUKA_CORE_APP_H

#include <atomic>

#include "gcl/context.h"

namespace geodesuka::core {


	class app {
	public:

		friend class engine;

		std::atomic<bool> ExitApp;

		virtual ~app() = default;

	protected:

		engine* Engine;
		double TimeStep;
		//std::atomic<double> TimeStep;

		app(engine *aEngine);

		virtual void run() = 0;

	private:

		void prerun();

	};

}

#endif // !GEODESUKA_CORE_APP_H

