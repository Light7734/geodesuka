#pragma once
#ifndef GEODESUKA_CORE_STAGE_SCENE2D_H
#define GEODESUKA_CORE_STAGE_SCENE2D_H

#include <vector>

#include "../object.h"
#include "../object/rendertarget.h"
#include "../object/camera2d.h"
#include "../object/light.h"

#include "../stage.h"

namespace geodesuka::core::stage {

	class scene2d : public stage_t {
	public:

		static constexpr int ID = 2;

		~scene2d();

		virtual int id() override;

	protected:

		std::vector<object::light*> Light;

		scene2d(engine* aEngine, gcl::context* aContext);

		//virtual batch render() override;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_SCENE2D_H
