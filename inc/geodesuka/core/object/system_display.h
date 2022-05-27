#pragma once
#ifndef GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
#define GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H

#include "../object.h"
#include "window.h"

struct GLFWmonitor;
struct GLFWvidmode;

namespace geodesuka::core::object {

	class system_display : public window {
	public:

		friend class engine;
		friend class system_window;

		static constexpr int RTID = 1;

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

		GLFWmonitor* Handle;
		//VkDisplayKHR Handle;

		int VideoModeCount;
		GLFWvidmode* VideoMode;
		const GLFWvidmode* CurrentVideoMode;

		// Used internally to interact with OS size and positioning.
		int2 PositionVSC;
		int2 SizeVSC;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_SYSTEM_DISPLAY_H
