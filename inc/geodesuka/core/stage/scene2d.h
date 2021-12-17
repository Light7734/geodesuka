#pragma once
#ifndef GEODESUKA_CORE_STAGE_SCENE2D_H
#define GEODESUKA_CORE_STAGE_SCENE2D_H

#include <vector>

#include "../object.h"
#include "../object/rendertarget.h"
#include "../object/camera2d.h"

#include "../stage.h"

namespace geodesuka::core::stage {

	class scene2d : public stage_t {
	public:

		~scene2d();


	protected:

		std::vector<object::camera2d*> Camera;

		scene2d(engine* aEngine, gcl::context* aContext);

		//virtual batch render() override;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_SCENE2D_H
