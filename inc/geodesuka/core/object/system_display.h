#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
#define GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H

#include "../gcl/framebuffer.h"

#include "../object.h"

#include "window.h"

namespace geodesuka::core::object {

	class system_display : public window {
	public:

		friend class system_window;

		GLFWmonitor* Handle;

		system_display(/*engine& aEngine, gcl::context* aDeviceContext,*/ GLFWmonitor* aMonitor);
		~system_display();

		virtual void draw(object_t* aObject) override;

	private:

		math::integer2 PositionSC;
		//math::integer2 SizeSC;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
