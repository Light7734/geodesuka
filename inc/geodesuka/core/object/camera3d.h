#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA3D_H
#define GEODESUKA_CORE_OBJECT_CAMERA3D_H

#include "../object.h"
#include "camera.h"

namespace geodesuka::core::object {

	class camera3d : public camera {
	public:

		virtual void draw(object_t* aObject) override;

	};

}
#endif // !GEODESUKA_CORE_OBJECT_CAMERA3D_H
