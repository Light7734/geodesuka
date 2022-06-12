/*
* 
*/

#pragma once
#ifndef GEODESUKA_CORE_OBJECT_LIGHT_H
#define GEODESUKA_CORE_OBJECT_LIGHT_H

#include "../object.h"

namespace geodesuka::core::object {

	class light : object_t {
	public:

		enum type {
			AMBIENT,
			DIRECTIONAL,
			POINT
		};

		//// Ambient Light.
		//light(engine* aEngine, gcl::context* aContext, stage_t* aStage, float3 aColor);
		//// Directional Light.
		//light(engine* aEngine, gcl::context* aContext, stage_t* aStage, float3 aColor, float3 aDirection);
		//// Point Light.
		//light(engine* aEngine, gcl::context* aContext, stage_t* aStage, float3 aColor, float3 aPosition);

		float3 Color;
		float3 Direction;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_LIGHT_H
