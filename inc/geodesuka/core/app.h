#pragma once
#ifndef GEODESUKA_CORE_APP_H
#define GEODESUKA_CORE_APP_H

#include "gcl/context.h"

namespace geodesuka::core {


	class app {
	public:

		virtual ~app() = default;

		virtual void run() = 0;


	protected:

		engine* Engine;

		app(engine *aEngine, int argc, char* argv[]);

	//private:


	};

}

#endif // !GEODESUKA_CORE_APP_H

