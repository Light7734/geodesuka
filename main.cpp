#include <iostream>

#include <geodesuka/engine.h>

#include "src/dep/glslang/glslang/Public/ShaderLang.h"

using namespace geodesuka::core;
//using namespace gcl;
//using namespace object;

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
    
	//// Don't care, I hate OpenGL.
	//// Vulkan is a proper API that respects the hardware.
	//glfwInit();
	//
	//// Used Objects.
	//VkResult ErrorCode = VkResult::VK_SUCCESS;
	//VkApplicationInfo AppProp;
 //   VkInstanceCreateInfo InstanceProp{};
	//VkInstance Instance;

 //   VkSurfaceKHR Surface;
 //   GLFWwindow* Window = NULL;

	//// Fills out App Info.
	//AppProp.sType				= VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
	//AppProp.pApplicationName	= "Vulkan Demo";
	//AppProp.applicationVersion	= VK_MAKE_VERSION(0, 0, 1);
	//AppProp.pEngineName			= "Geodesuka Engine";
	//AppProp.engineVersion		= VK_MAKE_VERSION(0, 0, 12);
	//AppProp.apiVersion			= VK_API_VERSION_1_2;
	////AppProp.pNext				= NULL;

	//// Gathers extensions for vulkan.
	//uint32_t glfwExtensionCount = 0;
	//const char** glfwExtension = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	//// Fills out Instance Info.
	//InstanceProp.sType						= VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//InstanceProp.pApplicationInfo			= &AppProp;
	//InstanceProp.enabledExtensionCount		= glfwExtensionCount;
	//InstanceProp.ppEnabledExtensionNames	= glfwExtension;
	//InstanceProp.enabledLayerCount			= 0;

 //   // Creates instance object.
	//ErrorCode = vkCreateInstance(&InstanceProp, NULL, &Instance);
 //   std::cout << "Instance Creation Status: " << get_er_str(ErrorCode) << std::endl;

 //   // Create OS window.
 //   glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
 //   Window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
 //   ErrorCode = glfwCreateWindowSurface(Instance, Window, NULL, &Surface);
 //   std::cout << "Window Surface Creation Status: " << get_er_str(ErrorCode) << std::endl;

 //   uint32_t ExtCount = 0;
 //   //VkExtensionProperties* ExtProperty = NULL;
 //   // Gets number of extensions.
 //   vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, NULL);
 //   std::vector<VkExtensionProperties> ExtProperty(ExtCount);
 //   vkEnumerateInstanceExtensionProperties(NULL, &ExtCount, ExtProperty.data());

 //   // Iterates through available devices.
 //   uint32_t PhysicalDeviceCount = 0;
 //   //bool SelectedPhysicalDeviceValid = false;
 //   VkPhysicalDevice SelectedPhysicalDevice;
 //   VkPhysicalDeviceFeatures SelectedPhysicalDeviceFeatures;
 //   vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, NULL);
 //   std::vector<VkPhysicalDevice> PhysicalDeviceList(PhysicalDeviceCount);
 //   vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysicalDeviceList.data());
 //   
 //   for (size_t i = 0; i < PhysicalDeviceList.size(); i++) {
 //       // Queries Physical Device Properties
 //       VkPhysicalDeviceProperties PhysicalDeviceProp{};
 //       vkGetPhysicalDeviceProperties(PhysicalDeviceList[i], &PhysicalDeviceProp);
 //       // Queries Physical Device Features.
 //       VkPhysicalDeviceFeatures PhysicalDeviceFeatures{};
 //       vkGetPhysicalDeviceFeatures(PhysicalDeviceList[i], &PhysicalDeviceFeatures);

 //       // Prints device name
 //       std::cout << "Device Name: " << PhysicalDeviceProp.deviceName << std::endl;
 //       switch (PhysicalDeviceProp.deviceType) {
 //       case VK_PHYSICAL_DEVICE_TYPE_OTHER:
 //           std::cout << "Device Type: Unknown" << std::endl;
 //           break;
 //       case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
 //           std::cout << "Device Type: Integrated GPU" << std::endl;
 //           break;
 //       case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
 //           std::cout << "Device Type: Discrete GPU" << std::endl;
 //           break;
 //       case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
 //           std::cout << "Device Type: Virtual GPU" << std::endl;
 //           break;
 //       case VK_PHYSICAL_DEVICE_TYPE_CPU:
 //           std::cout << "Device Type: CPU" << std::endl;
 //           break;
 //       }
 //       std::cout << std::endl;
 //       //DeviceProp.limits.

 //       if (PhysicalDeviceProp.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
 //           SelectedPhysicalDevice = PhysicalDeviceList[i];
 //           SelectedPhysicalDeviceFeatures = PhysicalDeviceFeatures;
 //       }
 //   }

 //   uint32_t SelectedQueueIndex = UINT32_MAX;
 //   // Search queue families.
 //   uint32_t QueueFamilyPropCount = 0;

 //   float QueuePriority = 1.0f;
 //   VkDeviceQueueCreateInfo DeviceQueueCreateInfo{};
 //   VkDeviceCreateInfo LogicalDeviceProp{};
 //   VkDevice LogicalDevice;

 //   vkGetPhysicalDeviceQueueFamilyProperties(SelectedPhysicalDevice, &QueueFamilyPropCount, NULL);
 //   std::vector<VkQueueFamilyProperties> QueueFamilyPropList(QueueFamilyPropCount);
 //   vkGetPhysicalDeviceQueueFamilyProperties(SelectedPhysicalDevice, &QueueFamilyPropCount, QueueFamilyPropList.data());
 //   for (size_t i = 0; i < QueueFamilyPropList.size(); i++) {
 //       std::cout << "Index: " << i << std::endl;
 //       VkBool32 isSupported;
 //       // Checks if Window Surface and Physical Device Queue Family Index are capable of presentation support
 //       ErrorCode = vkGetPhysicalDeviceSurfaceSupportKHR(SelectedPhysicalDevice, i, Surface, &isSupported);
 //       //std::cout << "Physical Device Surface Support Status: " << get_er_str(ErrorCode) << std::endl;
 //       std::cout << "Queue Count:\t" << QueueFamilyPropList[i].queueCount << std::endl;
 //       std::cout << "Graphics:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) >> 0) << std::endl;
 //       std::cout << "Compute:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) >> 1) << std::endl;
 //       std::cout << "Transfer:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT) >> 2) << std::endl;
 //       // No idea what sparse binding is..
 //       //std::cout << "Sparse Binding:\t" << ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT) >> 3) << std::endl << std::endl;
 //       std::cout << "Presentation:\t" << isSupported << std::endl << std::endl;

 //       //0x00000007;
 //       // I want it to support Graphics and Compute at the minimum.
 //       if ((QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT) &&
 //           (QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT) &&
 //           (QueueFamilyPropList[i].queueFlags & VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT)) {
 //           //std::cout << "Selected Index: " << i << std::endl;
 //           SelectedQueueIndex = i;

 //           DeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
 //           //DeviceQueueCreateInfo.pNext = NULL;
 //           //DeviceQueueCreateInfo.flags = 0;
 //           DeviceQueueCreateInfo.queueFamilyIndex = i;
 //           DeviceQueueCreateInfo.queueCount = QueueFamilyPropList[i].queueCount;
 //           DeviceQueueCreateInfo.pQueuePriorities = &QueuePriority; // Why would you do it like this? It's a fucking float.

 //       }
 //   }
 //   if (SelectedQueueIndex == UINT32_MAX) return -1;


 //   // Device Creation Properties
 //   LogicalDeviceProp.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
 //   //LogicalDeviceProp.pNext = NULL;
 //   //LogicalDeviceProp.flags = 0;
 //   LogicalDeviceProp.queueCreateInfoCount = 1;
 //   LogicalDeviceProp.pQueueCreateInfos = &DeviceQueueCreateInfo;
 //   //LogicalDeviceProp.enabledLayerCount = 0;
 //   //LogicalDeviceProp.ppEnabledLayerNames = NULL;
 //   LogicalDeviceProp.enabledExtensionCount = 0;
 //   //LogicalDeviceProp.ppEnabledExtensionNames = NULL;
 //   LogicalDeviceProp.pEnabledFeatures = &SelectedPhysicalDeviceFeatures;

 //   // Creates vulkan logical device to do shit with.
 //   ErrorCode = vkCreateDevice(SelectedPhysicalDevice, &LogicalDeviceProp, NULL, &LogicalDevice);
 //   std::cout << "Logical Device Creation Status: " << get_er_str(ErrorCode) << std::endl;

 //   VkQueue GraphicsQueue;
 //   VkQueue PresentationQueue;
 //   vkGetDeviceQueue(LogicalDevice, SelectedQueueIndex, 0, &GraphicsQueue);
 //   //vkGetDeviceQueue(LogicalDevice, SelectedQueueIndex, 0, &PresentationQueue);

 //   // Now that logical device which shit can be done with, now setup window.

 //   //// Create OS window.
 //   //glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
 //   //Window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
 //   //ErrorCode = glfwCreateWindowSurface(Instance, Window, NULL, &Surface);
 //   //std::cout << "Window Surface Creation Status: " << get_er_str(ErrorCode) << std::endl;

 //   // Checks if presentation queue is possible between PhysicalDevice, QueueFamilyIndex, and Surface (i.e. system window).
 //   //VkBool32 isSupported;
 //   //ErrorCode = vkGetPhysicalDeviceSurfaceSupportKHR(SelectedPhysicalDevice, SelectedQueueIndex, Surface, &isSupported);
 //   //std::cout << "Physical Device Surface Support Status: " << get_er_str(ErrorCode) << std::endl;
 //   //std::cout << "Device Presentation Support: " << isSupported << std::endl;
 //   
 //   //VkQueue GraphicsQueue;
 //   //VkQueue PresentationQueue;
 //   //vkGetDeviceQueue(LogicalDevice, SelectedQueueIndex, 0, &GraphicsQueue);
 //   //vkGetDeviceQueue(LogicalDevice, SelectedQueueIndex, 0, &PresentationQueue);

 //   


 //   while (!glfwWindowShouldClose(Window)) {
 //       glfwPollEvents();
 //   }

 //   vkDestroySurfaceKHR(Instance, Surface, NULL);
 //   glfwDestroyWindow(Window);

 //   // No return code.
 //   vkDestroyDevice(LogicalDevice, NULL);

 //   // No return code.
 //   vkDestroyInstance(Instance, NULL);

	//glfwTerminate();
	///*
	std::cout << "Geodesuka Engine v20210807" << std::endl << std::endl;
	geodesuka::engine Engine(argc, argv);

	// Choose from provided Device List. Just an example.
	geodesuka::core::gcl::device *ChosenDevice;
	geodesuka::core::gcl::device_context* DeviceContext = nullptr;
	for (size_t i = 0; i < Engine.DeviceList.size(); i++) {
		if (Engine.DeviceList[i]->Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			DeviceContext = new geodesuka::core::gcl::device_context(Engine.DeviceList[i]);
			std::cout << "Device Context Creation Status: " << Engine.get_er_str(DeviceContext->ErrorCode) << std::endl;
			break;
		}
	}

	// Window properties constructor.
	object::window::prop WindowProperties = object::window::prop();
	gcl::frame_buffer::prop FramebufferProperties = gcl::frame_buffer::prop();
	
	WindowProperties.Decorated			= GLFW_TRUE;
	WindowProperties.PresentationMode	= VK_PRESENT_MODE_FIFO_KHR;

	FramebufferProperties.Count			= 2;
	FramebufferProperties.Format		= VK_FORMAT_R8G8B8A8_SRGB;
	FramebufferProperties.ColorSpace	= VK_COLORSPACE_SRGB_NONLINEAR_KHR;

	object::system_display* PrimaryDisplay = Engine.get_primary_display();
	object::system_window* Window = new object::system_window(DeviceContext, PrimaryDisplay, FramebufferProperties, WindowProperties,
		math::real3(0.0, 0.0, 0.0), math::real2(0.1, 0.1), util::text("I hate OpenGL"));
	std::cout << "Window Creation Status: " << Engine.get_er_str(Window->ErrorCode) << std::endl;

	// Simple Triangle Vertices.
	float Vertices[] = {
		-1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0, 0.0, 0.0, 1.0
	};

	// Makes simple graphics pipline
	VkPipeline GraphicsPipeline;

	while (!Window->CloseMe) {
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
	}

	//// Create OS window.
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//VkSurfaceKHR Surface;
	//GLFWwindow *Window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
	//VkResult ErrorCode = glfwCreateWindowSurface(Engine.Instance, Window, NULL, &Surface);
	//std::cout << "Window Surface Creation Status: " << Engine.get_er_str(ErrorCode) << std::endl;

	//vkDestroySurfaceKHR(Engine.Instance, Surface, NULL);
	//glfwDestroyWindow(Window);

	delete Window;

	delete DeviceContext;


	//context Context = context(context::OpenGL, 3, 3, context::CoreProfile);
	//frame_buffer::prop FBOProp = frame_buffer::prop();
	//object::window::prop WINProp = object::window::prop();
	//
	//// Opens a Window at the center of every display.
	//std::vector<object::system_display*> Display = Engine.get_display_list();
	//object::window** Window = new object::window*[Display.size()];
	//for (int i = 0; i < Display.size(); i++) {
	//	Window[i] = (object::window*)Engine.create(new object::system_window(&Context, &FBOProp, &WINProp, 0.125, 0.125, "Window", Display[i]));
	//}


	//object::object* Cube = new object::cube(&Context);
	
	//system_display* Display = Engine.get_primary_display();
	//window* Window = (window*)Engine.create(new system_window(&Context, &FBOProp, &WINProp, 0.05, 0.05, "cock", Display));
	//window* Window2 = (window*)Engine.create(new system_window(&Context, &FBOProp, &WINProp, 0.05, 0.05, "cock2", Display));

	//while (!Engine.ExitApp) {
	//	// Game Loop Time difference
	//	Engine.dt = Engine.get_time() - Engine.t;
	//	Engine.t = Engine.get_time();

	//	Engine.input();

	//	Engine.update(Engine.dt);

	//	//Window->set_position(0.1*math::real3(cos(Engine.t), sin(Engine.t), 0.0));
	//	////Window->set_size(0.5 * (sin(20.0 * Engine.t) + 1.0) * math::real2(0.05, 0.05));
	//	//Window2->set_size(0.5 * (sin(0.5*Engine.t) + 1.0) * math::real2(0.05, 0.05));

	//	//for (size_t i = 0; i < Display.size(); i++) {
	//	//	Window[i]->set_size(0.5 * (sin(5.0*Engine.t) + 1.0) * math::real2(0.05, 0.05));
	//	//
	//	//}

	//	Engine.render();

	//	//std::cout << Engine.dt << std::endl;
	//}

	//delete[] Window;
	//*/

	return 0;
}
