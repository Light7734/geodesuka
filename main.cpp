#include <iostream>
#include <algorithm>

#include <geodesuka/engine.h>

#include <geodesuka/builtin/object/triangle.h>

/*
* This main file is just used for debugging library.
*/

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

// Updated buffer.h, testing 
int main(int argc, char *argv[]) {
	geodesuka::engine Engine(argc, argv);
	if (!Engine.is_ready()) return -1;
	std::cout << "Geodesuka Engine";
	std::cout << " - Version: " << Engine.get_version().Major << "." << Engine.get_version().Minor << "." << Engine.get_version().Patch;
	std::cout << " - Date: 20211023" << std::endl;

	size_t DeviceCount = 0;
	device** Device = Engine.get_device_list(&DeviceCount);
	context* Context = nullptr;
	context* Context2 = nullptr;
	for (size_t i = 0; i < DeviceCount; i++) {
		if (Device[i]->get_properties().deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			// Provide required extensions to allow context to create system windows.
			std::cout << "Transfer Index: " << Device[i]->qfi(device::qfs::PRESENT);
			Context = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
			Context2 = new context(&Engine, Device[i], system_window::RequiredExtension.size(), (const char**)system_window::RequiredExtension.data());
		}
	}

	//delete Context;
	free(Context);
	//// Creates a command pool, can generate command buffers of the designated type.
	//command_pool* CommandPool = new command_pool(Context, command_pool::flag::RESET_COMMAND_BUFFER, context::qid::GRAPHICS);



	//// Hard coded vertices
	//float Vertices[] = {
	//	-1.0, 0.0, 1.0, 0.0, 0.0,
	//	 0.0, 1.0, 0.0, 1.0, 0.0,
	//	 1.0, 0.0, 0.0, 0.0, 1.0
	//};

	//util::variable VML(util::type::id::STRUCT, "Vertex");
	//VML.Type.push(util::type::id::REAL3, "Position");
	//VML.Type.push(util::type::id::REAL3, "Color");
	//buffer* VertexBuffer = new buffer(Context, buffer::memory::DEVICE_LOCAL, buffer::usage::VERTEX | buffer::usage::TRANSFER_DST, 10, VML, Vertices);


	Engine.tsleep(5);

	//int a = 2;
	//int& b = a;
	//std::cout << "Address of a: " << &a << std::endl;
	//std::cout << "Address of b: " << &b << std::endl;

	//while (true) {
	//	char q = getc(stdin);
	//	if (q == 'q') delete Context2;
	//}

	//Context->submit(context::qid::COMPUTE, 0, NULL, VK_NULL_HANDLE);
	//{

	//	system_window::create_info CreateInfo;

	//	CreateInfo.Display = Engine.get_primary_display();
	//	CreateInfo.WindowProperty = window::prop();
	//	CreateInfo.SwapchainProperty = swapchain::prop();
	//	CreateInfo.Position = math::real3(0.0, 0.0, 0.0);

	//	object_t* ObjectList[3];
	//	ObjectList[0] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");
	//	ObjectList[1] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");
	//	ObjectList[2] = new system_window(&Engine, Context, &CreateInfo, 640, 480, "cock");

	//	object_t *Triangle = new triangle(&Engine, Context);

	//}

	return 0;
}
