#pragma once
#ifndef GEODESUKA_CORE_STAGE_CANVAS_H
#define GEODESUKA_CORE_STAGE_CANVAS_H

#include <vector>

#include "../object.h"
#include "../object/render_target.h"
#include "../object/window.h"

#include "../stage.h"


namespace geodesuka::core::stage {

	class canvas : public stage_t {
	public:

		~canvas();

	protected:

		// Render targets of the stage.
		std::vector<object::window*> Window;

		canvas(engine* aEngine, gcl::context* aContext);

		virtual batch render() override;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_CANVAS_H
