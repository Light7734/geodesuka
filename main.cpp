#include <iostream>

#include <geodesuka/engine.h>

#include "triangle.h"

//#include "src/dep/glslang/glslang/Public/ShaderLang.h"
//#include "src/dep/glslang/StandAlone/ResourceLimits.h"
//
//#include "src/dep/glslang/SPIRV/GlslangToSpv.h"
//
//#include <Windows.h>

using namespace geodesuka::core;
using namespace gcl;
using namespace object;

/*
* setProcessDPIAwarenessContext()
* dpichagned
* Checks for monitor swaps.
*/

/*
* Currently I am unsure how I wish to queue render calls.
* I want a sorting algorithm to be implemented for sorting
* objects queued to be rendered. The idea is to sort based
* on distance from camera, and by whether or not the object
* has an opaque component.
*/
// Creates a window on every display

int main(int argc, char *argv[]) {
	std::cout << "Geodesuka Engine v20210807" << std::endl << std::endl;
	geodesuka::engine Engine(argc, argv);

	// Choose from provided Device List. Just an example.
	//device *ChosenDevice = nullptr;
	device_context* DeviceContext = nullptr;
	for (size_t i = 0; i < Engine.DeviceList.size(); i++) {
		if (Engine.DeviceList[i]->Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Creates a context for the chosen device.
			DeviceContext = new device_context(Engine.DeviceList[i]);
			std::cout << "Device Context Creation Status: " << Engine.get_er_str(DeviceContext->ErrorCode) << std::endl;
			break;
		}
	}

	// Window properties constructor.
	window::prop WindowProperties = window::prop();
	frame_buffer::prop FramebufferProperties = frame_buffer::prop();
	
	WindowProperties.Decorated			= GLFW_TRUE;
	WindowProperties.PresentationMode	= VK_PRESENT_MODE_FIFO_KHR;

	FramebufferProperties.Count			= 2;
	FramebufferProperties.Format		= VK_FORMAT_R8G8B8A8_SRGB;
	FramebufferProperties.ColorSpace	= VK_COLORSPACE_SRGB_NONLINEAR_KHR;

	system_display* PrimaryDisplay = Engine.get_primary_display();
	system_window* Window = new system_window(DeviceContext, PrimaryDisplay, FramebufferProperties, WindowProperties,
		math::real3(0.0, 0.0, 0.0), math::real2(0.1, 0.1), util::text("I hate OpenGL"));
	std::cout << "Window Creation Status: " << Engine.get_er_str(Window->ErrorCode) << std::endl;

	//triangle Triangle(&Engine, DeviceContext);
	object_t* Triangle = new triangle(Engine, DeviceContext);

	while (!Window->CloseMe) {

		//Window->set_position(0.1*math::real3(cos(Engine.t), sin(Engine.t), 0.0));
		////Window->set_size(0.5 * (sin(20.0 * Engine.t) + 1.0) * math::real2(0.05, 0.05));
		//Window2->set_size(0.5 * (sin(0.5*Engine.t) + 1.0) * math::real2(0.05, 0.05));

		//for (size_t i = 0; i < Display.size(); i++) {
		//	Window[i]->set_size(0.5 * (sin(5.0*Engine.t) + 1.0) * math::real2(0.05, 0.05));
		//
	}

	delete Triangle;

	delete Window;

	delete DeviceContext;

	return 0;
}
