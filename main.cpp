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

#include <Windows.h>

int main(int argc, char *argv[]) {
	geodesuka::engine Engine(argc, argv);
	if (!Engine.is_ready()) return -1;
	std::cout << "Geodesuka Engine";
	std::cout << " - Version: " << Engine.get_version().Major << "." << Engine.get_version().Minor << "." << Engine.get_version().Patch;
	std::cout << " - Date: 20210911" << std::endl;

	//int RunTime = 0;
	//while (true) {
	//	Sleep(1000);
	//	if (RunTime > 3 * 1000) {
	//		break;
	//	}
	//	else {
	//		RunTime += 1000;
	//	}
	//}

	///*

	size_t DeviceCount = 0;
	device** Device = Engine.get_device_list(&DeviceCount);
	context* Context = nullptr;
	for (size_t i = 0; i < DeviceCount; i++) {
		if (Device[i]->get_properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Provide required extensions to allow context to create system windows.
			Context = new context(Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
		}
	}

	//// Window properties constructor.
	//window::prop WindowProperties = window::prop();
	//frame_buffer::prop FramebufferProperties = frame_buffer::prop();
	//
	//WindowProperties.Decorated			= GLFW_TRUE;
	//WindowProperties.PresentationMode	= VK_PRESENT_MODE_FIFO_KHR;

	//FramebufferProperties.Count			= 2;
	//FramebufferProperties.Format		= VK_FORMAT_R8G8B8A8_SRGB;
	//FramebufferProperties.ColorSpace	= VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	//
	//system_display* PrimaryDisplay = Engine.get_primary_display();
	//window* Window = (window*)Engine.create(new system_window(Context, PrimaryDisplay, FramebufferProperties, WindowProperties,
	//	math::real3(0.0, 0.0, 0.0), math::real2(0.1, 0.1), util::text("I hate OpenGL")));
	//object_t* Triangle = Engine.create(new triangle(Engine, Context));

	//while (true) {

	//}

	delete Context;
	//*/
	return 0;
}
