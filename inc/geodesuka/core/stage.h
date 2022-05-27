#pragma once
#ifndef GEODESUKA_CORE_STAGE_H
#define GEODESUKA_CORE_STAGE_H

//
// ------------------------- stage.h ------------------------- //
// A stage is simply a collection of objects that share the
// same space and therefore the same coordinate vectors. While
// the engine holds all created objects and updates, to be rendered
// they must be in the same coordinate space along with possible
// render targets. 
// 
// A stage is a collection of objects that firstly, share the same space
// which gives meaning to their position vector. Secondly, since they share
// the same space, they can be interpreted to interact with one and another.
//
// It is a assumed that stages and the context they create share the same
// rendering and compute context.

#include <vector>

#include <mutex>

#include "gcl/context.h"

#include "object.h"

namespace geodesuka::core {

	class stage_t {
	public:

		friend class engine;

		std::vector<object_t*> Object;
		std::vector<object::rendertarget*> RenderTarget;

		~stage_t();

	protected:

		std::mutex Mutex;
		std::atomic<bool> isReadyToBeProcessed;

		engine* Engine;
		gcl::context* Context;


		stage_t(engine* aEngine, gcl::context* aContext);

	private:

		virtual VkSubmitInfo update(double aDeltaTime);

		virtual VkSubmitInfo compute();

		virtual gcl::command_batch render();

	};

}

#endif // !GEODESUKA_CORE_STAGE_H
