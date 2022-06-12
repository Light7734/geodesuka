/*
* skybox.h is a component of the geodesuka engine, it contains a series of images
* which will be used to generate the background of a 
*/

#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SKYBOX_H
#define GEODESUKA_CORE_OBJECT_SKYBOX_H

#include "../gcl/device.h"
#include "../gcl/context.h"

#include "../object.h"

#include "../stage.h"
#include "../stage/scene3d.h"

namespace geodesuka::core::object {

	class skybox : public object_t {
	public:

		skybox(geodesuka::engine* aEngine, gcl::context* aContext, stage::scene3d* aScene3D);
		~skybox();

	};

}

#endif // !GEODESUKA_CORE_OBJECT_SKYBOX_H
