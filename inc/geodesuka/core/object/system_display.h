#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
#define GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H

#include "../object.h"
#include "window.h"

//#include <GLFW/glfw3.h>
struct GLFWmonitor;


namespace geodesuka::core::object {

	class system_display : public window {
	public:

		friend class engine;
		friend class system_window;

		static const int RTID;

		GLFWmonitor* Handle;
		//VkDisplayKHR Handle;

		// TODO: Move this constructor to private.
		system_display(engine *aEngine, gcl::context* aContext, GLFWmonitor* aMonitor);
		~system_display();

		// ----- object_t ----- //

		// ----- rendertarget ----- //

		virtual int rtid() override;

		// ----- window ----- //

		// ----- system_display ----- //


	protected:

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

	private:

		int2 PositionSC;
		//int2 SizeSC;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
