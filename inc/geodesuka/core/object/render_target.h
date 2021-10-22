#pragma once
#ifndef GEODESUKA_CORE_OBJECT_RENDER_TARGET_H
#define GEODESUKA_CORE_OBJECT_RENDER_TARGET_H

#include <vector>

#include <vulkan/vulkan.h>

#include "../gcl/context.h"
#include "../gcl/texture.h"

#include "../object.h"

namespace geodesuka::core::object {

	class render_target : public object_t {
	public:

		std::vector<VkSubmitInfo> Submission;
		std::vector<gcl::texture*> Texture;
		
		~render_target();

		virtual void draw(object_t* aObject) = 0;

	protected:

		render_target(engine* aEngine, gcl::context* aContext);

	private:

	};
}

#endif // !GEODESUKA_CORE_OBJECT_RENDER_TARGET_H
