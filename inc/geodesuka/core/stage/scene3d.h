#pragma once
#ifndef GEODESUKA_CORE_STAGE_SCENE3D_H
#define GEODESUKA_CORE_STAGE_SCENE3D_H

#include <vector>

#include "../object.h"
#include "../object/camera3d.h"

#include "../stage.h"

namespace geodesuka::core::stage {

	class scene3d {
	public:

	protected:

		std::vector<object::camera3d*> Camera;

		//object::skybox* Skybox;
		//std::vector<object::light*> Light;

	private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_SCENE3D_H
