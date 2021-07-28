#include <iostream>

#include <geodesuka/engine.h>

using namespace geodesuka::core;
using namespace gcl;
//using namespace object;

/*
* setProcessDPIAwarenessContext()
* dpichagned
* Checks for monitor swaps.
*/

// Creates a window on every display
int main(int argc, char *argv[]) {
	///*
	std::cout << "Geodesuka Engine v20210717" << std::endl << std::endl;
	geodesuka::engine Engine(argc, argv);

	context Context = context(context::OpenGL, 3, 3, context::CoreProfile);
	frame_buffer::prop FBOProp = frame_buffer::prop();
	object::window::prop WINProp = object::window::prop();
	
	// Opens a Window at the center of every display.
	std::vector<object::system_display*> Display = Engine.get_display_list();
	object::window** Window = new object::window*[Display.size()];
	for (int i = 0; i < Display.size(); i++) {
		Window[i] = (object::window*)Engine.create(new object::system_window(&Context, &FBOProp, &WINProp, 0.125, 0.125, "Window", Display[i]));
	}


	//object::object* Cube = new object::cube(&Context);
	
	//system_display* Display = Engine.get_primary_display();
	//window* Window = (window*)Engine.create(new system_window(&Context, &FBOProp, &WINProp, 0.05, 0.05, "cock", Display));
	//window* Window2 = (window*)Engine.create(new system_window(&Context, &FBOProp, &WINProp, 0.05, 0.05, "cock2", Display));

	while (!Engine.ExitApp) {
		// Game Loop Time difference
		Engine.dt = Engine.get_time() - Engine.t;
		Engine.t = Engine.get_time();

		Engine.input();

		Engine.update(Engine.dt);

		//Window->set_position(0.1*math::real3(cos(Engine.t), sin(Engine.t), 0.0));
		////Window->set_size(0.5 * (sin(20.0 * Engine.t) + 1.0) * math::real2(0.05, 0.05));
		//Window2->set_size(0.5 * (sin(0.5*Engine.t) + 1.0) * math::real2(0.05, 0.05));

		//for (size_t i = 0; i < Display.size(); i++) {
		//	Window[i]->set_size(0.5 * (sin(5.0*Engine.t) + 1.0) * math::real2(0.05, 0.05));
		//
		//}

		Engine.render();

		std::cout << Engine.dt << std::endl;
	}

	//delete[] Window;
	//*/

	return 0;
}
