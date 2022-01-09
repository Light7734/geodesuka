#pragma once
#ifndef GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H
#define GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H

#include "../math.h"

//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"

#include "../object.h"
#include "window.h"

//#include "../graphical/frame_buffer.h"

namespace geodesuka::core::object {

	class virtual_window : public window {
	public:

		static const int RTID;
		virtual int rtid() override;

	protected:

		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) override;

		virtual void swap() override;

	};

}

#endif // !GEODESUKA_CORE_OBJECT_VIRTUAL_WINDOW_H
