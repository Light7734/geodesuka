#pragma once
#ifndef GEODESUKA_CORE_OBJECT_CAMERA2D_H
#define GEODESUKA_CORE_OBJECT_CAMERA2D_H

#include "../gcl/context.h"

#include "../object.h"

#include "camera.h"

namespace geodesuka::core::object {

	class camera2d : public camera {
	public:

		static const int RTID;

		camera2d(engine* aEngine, gcl::context* aContext, stage_t* aStage);
		~camera2d();

		virtual int rtid() override;

	protected:

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

		virtual void swap() override;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_CAMERA2D_H
