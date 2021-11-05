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

using namespace geodesuka::builtin::object;

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

	/*
	math::real Vertices[] = {
		-1.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.0, 0.0,
		 0.0, 1.0, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0,
		 1.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 1.0
	};

	math::real VertexReturn[] = {
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
	};

	memset(VertexReturn, 0xAA, 24 * sizeof(float));

	util::variable Variable(util::type::id::STRUCT, "Vertex");
	Variable.Type.push(util::type::id::REAL3, "Position");
	Variable.Type.push(util::type::id::REAL2, "TexCoord");
	Variable.Type.push(util::type::id::REAL3, "Color");

	//buffer* Buffer = new buffer(
	//	Context, 
	//	buffer::memory::HOST_VISIBLE | buffer::memory::HOST_COHERENT, 
	//	buffer::usage::VERTEX,
	//	3, 
	//	Variable,
	//	Vertices
	//);

	buffer* Buffer = new buffer(
		Context,
		buffer::memory::DEVICE_LOCAL,
		buffer::usage::VERTEX,
		3,
		Variable,
		Vertices
	);

	Buffer->read(0, 24 * sizeof(math::real), VertexReturn);

	if (memcmp(Vertices, VertexReturn, 24 * sizeof(math::real)) == 0) {
		std::cout << "Data matches" << std::endl;
	}
	else {
		std::cout << "Data doesn't match" << std::endl;
	}

	// No longer in use.
	delete Buffer;
	//*/

	Engine.tsleep(1);

	system_window::create_info CreateInfo;
	CreateInfo.Display				= Engine.get_primary_display();
	CreateInfo.WindowProperty		= window::prop();
	CreateInfo.SwapchainProperty	= swapchain::prop();
	CreateInfo.Position				= math::real3(0.0, 0.0, 0.0);

	system_window* SystemWindow = new system_window(&Engine, Context, &CreateInfo, 480, 640, "cock");
	triangle* Triangle = new triangle(&Engine, Context);

	while (true) {

		Triangle->draw(SystemWindow);

		Engine.tsleep(0.02);
	}

	return 0;
}
