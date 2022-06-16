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

		// Stage Objects and Render Targets.
		std::vector<object_t*> Object;
		std::vector<object::render_target*> RenderTarget;

		~stage_t();

		// Used for runtime stage discrimination.
		virtual int id() = 0;

		

	protected:

		engine* Engine;
		gcl::context* Context;
		std::mutex Mutex;
		std::atomic<bool> isReadyToBeProcessed;


		stage_t(engine* aEngine, gcl::context* aContext);

		// This function can be called after all objects and render targets have been created.
		// It will then generate draw commands for each object_t/rendertarget pair on the stage.
		int generate_renderops();

		// Base class method does nothing, but can be overriden to update stage resources.
		virtual VkSubmitInfo update(double aDeltaTime);

		// Base class does nothing
		virtual VkSubmitInfo compute();

	private:

		// This is fixed by the engine, and cannot be overriden.
		gcl::command_batch render();

	};

}

#endif // !GEODESUKA_CORE_STAGE_H
