#include <geodesuka/core/object/window.h>

// Standard C Library.
#include <stdlib.h>
#include <string.h>

#include <geodesuka/core/math.h>

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include <geodesuka/core/object.h>

namespace geodesuka::core::object {

	window::prop::prop() {
		this->Resizable = GLFW_TRUE;
		this->Decorated = GLFW_TRUE;
		this->UserFocused = GLFW_TRUE;
		this->AutoMinimize = GLFW_TRUE;
		this->Floating = GLFW_FALSE;
		this->Maximized = GLFW_FALSE;
		this->Minimized = GLFW_FALSE;
		this->Visible = GLFW_TRUE;
		this->ScaleToMonitor = GLFW_FALSE;
		this->CenterCursor = GLFW_TRUE;
		this->FocusOnShow = GLFW_TRUE;
		this->Hovered = GLFW_TRUE;
		this->RefreshRate = GLFW_DONT_CARE;
	}

	void window::set_title(util::text aTitle) {

	}

	void window::set_size(math::real2 aSize) {
		this->Size = aSize;
	}

	void window::set_resolution(math::natural2 aResolution) {
		this->Resolution = aResolution;

	}

	math::boolean window::should_close() {
		return false;
	}

}