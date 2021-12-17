#pragma once
#ifndef GEODESUKA_CORE_APP_H
#define GEODESUKA_CORE_APP_H

#include "gcl/context.h"

namespace geodesuka::core {


	class app {
	public:

		friend class engine;

		std::atomic<bool> ExitApp;

		virtual ~app() = default;

		virtual void gameloop() = 0;


	protected:

		engine* Engine;

		app(engine *aEngine, int argc, char* argv[]);


	private:

		void run();

	};

}

#endif // !GEODESUKA_CORE_APP_H

