#pragma once
#ifndef GEODESUKA_CORE_OBJECT_RENDER_TARGET_H
#define GEODESUKA_CORE_OBJECT_RENDER_TARGET_H

#include <vector>

#include <vulkan/vulkan.h>

#include "../gcl/context.h"
#include "../gcl/texture.h"

#include "../logic/timer.h"

#include "../object.h"

/*
* For a class to be considered a render_target, it must be able to
* be drawn to and must have attachments to be drawn to. How exactly
* a render_target is drawn to is decided by the user, and not the 
* engine API.
*/

namespace geodesuka::core::stage {
	class canvas;
	class scene2d;
	class scene3d;
}

namespace geodesuka::core::object {

	class render_target : public object_t {
	public:

		//friend class stage_t;
		friend class stage::canvas;
		friend class stage::scene2d;
		friend class stage::scene3d;

		// Attachments
		int TextureCount;
		gcl::texture* Texture;

		~render_target();

		void set_framerate(double aFPS);
		double framerate();

	protected:

		render_target(engine* aEngine, gcl::context* aContext);

		// Propose a collection of objects (Most likely from a stage), to 
		// draw those objects to the render target. The objects will
		// produce user implemented draw commands to the render_target
		// for aggregation and eventual execution by the geodesuka engine.
		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) = 0;

	private:

		double FPS; // Frames Per Second.
		logic::timer RefreshTimer;

	};
}

#endif // !GEODESUKA_CORE_OBJECT_RENDER_TARGET_H
