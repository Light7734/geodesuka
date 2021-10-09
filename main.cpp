#include <iostream>
#include <algorithm>

#include <geodesuka/engine.h>

#include "triangle.h"

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
	geodesuka::engine Engine(argc, argv);
	if (!Engine.is_ready()) return -1;
	std::cout << "Geodesuka Engine";
	std::cout << " - Version: " << Engine.get_version().Major << "." << Engine.get_version().Minor << "." << Engine.get_version().Patch;
	std::cout << " - Date: 20210911" << std::endl;

	size_t DeviceCount = 0;
	device** Device = Engine.get_device_list(&DeviceCount);
	context* Context = nullptr;
	for (size_t i = 0; i < DeviceCount; i++) {
		if (Device[i]->get_properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Provide required extensions to allow context to create system windows.
			Context = new context(Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
		}
	}

	system_window::create_info CreateInfo;

	CreateInfo.Display				= Engine.get_primary_display();
	CreateInfo.WindowProperty		= window::prop();
	CreateInfo.SwapchainProperty	= swapchain::prop();
	CreateInfo.Position				= math::real3(0.0, 0.0, 0.0);

	object_t *ObjectList[3];
	ObjectList[0] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");
	ObjectList[1] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");
	ObjectList[2] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");

	delete Context;
	return 0;
}
