#pragma once
#ifndef GEODESUKA_CORE_STAGE_SCENE3D_H
#define GEODESUKA_CORE_STAGE_SCENE3D_H

#include <vector>

#include "../object.h"
#include "../object/rendertarget.h"
#include "../object/camera3d.h"

#include "../stage.h"

namespace geodesuka::core::stage {

	class scene3d : public stage_t {
	public:

		~scene3d();

	protected:


		//object::skybox* Skybox;

		//std::vector<object::light*> Light;
		std::vector<object::camera3d*> Camera;

		scene3d(engine* aEngine, gcl::context* aContext);

		//virtual batch render() override;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_SCENE3D_H
