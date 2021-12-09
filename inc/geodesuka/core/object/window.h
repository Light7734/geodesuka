#pragma once
#ifndef GEODESUKA_CORE_OBJECT_WINDOW_H
#define GEODESUKA_CORE_OBJECT_WINDOW_H

//#include "../mathematics/mathematics.h"
//
//#include "../hid/mouse.h"
//#include "../hid/keyboard.h"
//#include "../hid/joystick.h"
//
//#include "object.h"
//
//#include "../graphical/frame_buffer.h"


/*
Types of Windows
	system_window: Not the Windows OS in particular, but a window that is 
	managed by the OS. Holds rendering context, and allows draw calls. A
	system window holds a context and is the default frame buffer.

	virtual_window: Does not hold a rendering context, and is a virtual window
	managed by an established 

	[NOT IMPLEMENTED]
	hmd_window: This will be for virtual reality headsets.

	camera: Does not hold a rendering context, but still serves as a rendering target.

Property List:
	Property I:
		A window object can stream it's contents to another window.

	Property II:
		Any window can be transformed into another window

*/

/*
VS = Virtual Screen Coordinates
PX = Pixel Coordinates
PS = Physical Screen Coordinates
*/

//for (int i = 0; i < WindowCount; i++) {
//	for (int j = 0; j < ObjectCount; j++) {
//		Window[i].draw(Object[j]);
//	}
//}
//
//Object->render(*this)

//class object;

#include "../util/text.h"

#include "../math.h"

#include "../gcl/framebuffer.h"

#include "../object.h"
#include "rendertarget.h"

namespace geodesuka::core::object {

	// A window is a general type object that can be drawn to, which also has the properties
	// of every object, which it too can be drawn. Each window has a canvas, which is what is actually drawn
	// to. A full window is Canvas + Frame.
	class window : public rendertarget {
	public:

		//
		struct prop {
			int Resizable;
			int Decorated;
			int UserFocused;
			int AutoMinimize;
			int Floating;
			int Maximized;
			int Minimized;
			int Visible;
			int ScaleToMonitor;
			int CenterCursor;
			int FocusOnShow;
			int Hovered;
			int RefreshRate;
			//VkPresentModeKHR PresentationMode;

			prop();
		};

		~window();

		// This is to discern what type of target is being drawn to, referenced by object.h
		//virtual void draw(object_t* aObject) = 0;

		virtual void set_title(util::text aTitle);
		virtual void set_size(math::real2 aSize);
		virtual void set_resolution(math::natural2 aResolution);
		virtual math::boolean should_close();

		// Will forward input stream to target object. Can be set to null if
		// no forwarding is chosen.
		// virtual math::integer forward_input_stream_to(object* aObject);

	protected:

		util::text Title;
		math::real2 Size;				// [m]
		math::natural2 Resolution;		// [pixels]
		struct prop Property;

		window(engine *aEngine, gcl::context* aContext);

	};

}

#endif // !GEODESUKA_CORE_OBJECT_WINDOW_H
