#pragma once
#ifndef GEODESUKA_BUILTIN_STAGE_EXAMPLE_H
#define GEODESUKA_BUILTIN_STAGE_EXAMPLE_H

#include <geodesuka/engine.h>

#include <geodesuka/builtin/object/triangle.h>

namespace geodesuka::builtin::stage {

	class example /*: core::stage::canvas*/ {
	public:

		example(engine* aEngine, core::gcl::context* aContext);
		~example();

	protected:

	private:

	};

}

#endif // !GEODESUKA_BUILTIN_STAGE_EXAMPLE_H
