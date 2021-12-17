#pragma once
#ifndef GEODESUKA_CORE_STAGE_CANVAS_H
#define GEODESUKA_CORE_STAGE_CANVAS_H

#include <vector>

#include "../object.h"
#include "../object/rendertarget.h"
#include "../object/window.h"

#include "../stage.h"


namespace geodesuka::core::stage {

	class canvas : public stage_t {
	public:

		~canvas();

	protected:

		canvas(engine* aEngine, gcl::context* aContext);

		//virtual batch render() override;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_CANVAS_H
