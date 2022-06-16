#include <geodesuka/core/object/window.h>

// Standard C Library.
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>

#include <geodesuka/core/math.h>

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include <geodesuka/core/object.h>

namespace geodesuka::core::object {

	window::option::option() {
		Resizable		= GLFW_TRUE;
		Decorated		= GLFW_TRUE;
		UserFocused		= GLFW_TRUE;
		AutoMinimize	= GLFW_TRUE;
		Floating		= GLFW_FALSE;
		Maximized		= GLFW_FALSE;
		Minimized		= GLFW_FALSE;
		Visible			= GLFW_TRUE;
		ScaleToMonitor	= GLFW_FALSE;
		CenterCursor	= GLFW_TRUE;
		FocusOnShow		= GLFW_TRUE;

		Hovered			= GLFW_TRUE;
	}

	window::~window() {

	}

	void window::set_title(util::str aTitle) {

	}

	void window::set_size(float2 aSize) {
		this->Size = aSize;
	}

	void window::set_resolution(uint2 aResolution) {
		this->Resolution = uint3(aResolution.x, aResolution.y, 1u);

	}

	bool window::should_close() {
		return false;
	}

	window::window(engine* aEngine, gcl::context* aContext, stage_t* aStage) : render_target(aEngine, aContext, aStage) {
		Title = "";
		Size = float2(0.0, 0.0);
	}

}