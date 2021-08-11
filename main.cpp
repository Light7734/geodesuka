#include <iostream>

#include <geodesuka/engine.h>

#include "src/dep/glslang/glslang/Public/ShaderLang.h"
#include "src/dep/glslang/StandAlone/ResourceLimits.h"

#include "src/dep/glslang/SPIRV/GlslangToSpv.h"

#include <Windows.h>

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
	
	std::cout << "Geodesuka Engine v20210807" << std::endl << std::endl;
	geodesuka::engine Engine(argc, argv);

	////int mbstowcs(wchar_t* out, const char* in, size_t size);
	//const char* aName = "test.dll";
	//const wchar_t* aExample = L"test.dll";
	//wchar_t* aName2 = (wchar_t *)malloc((strlen(aName) + 1)*sizeof(wchar_t));
	//aName2[strlen(aName)] = '\0';
	//std::cout << mbstowcs(aName2, aName, strlen(aName) * sizeof(wchar_t)) << std::endl;
	////std::cout << aName2 << std::endl;
	////HMODULE Module = LoadLibrary(TEXT("opengl32.dll"));

	//HMODULE Module = LoadLibrary(aName2);
	////HMODULE Module = LoadLibrary(TEXT("test.dll"));

	//FreeLibrary(Module);

	//io::dynalib DynamicLibrary("opengl32.dll");
	//std::cout << GetLastError() << std::endl;
	//HMODULE Module = reinterpret_cast<HMODULE>(DynamicLibrary.Handle);
	//void (*proc)();
	//proc = (void(*)(void))GetProcAddress(Module, "wglGetProcAddress");

	io::dynalib DynamicLibrary("test.dll");
	std::cout << GetLastError() << std::endl;
	HMODULE Module = reinterpret_cast<HMODULE>(DynamicLibrary.Handle);
	int (*add)(int, int);
	add = (int(*)(int, int))GetProcAddress(Module, "add");
	std::cout << GetLastError() << std::endl;

	return 0;

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

	// Simple Triangle Vertices.
	float Vertices[] = {
		-1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
		1.0, 0.0, 0.0, 0.0, 0.0, 1.0
	};

	const char* VertexShaderSource =
		"#version 450\n\
		\n\
		layout(location = 0) out vec3 fragColor;\n\
		\n\
		vec2 positions[3] = vec2[](\n\
		    vec2(0.0, -0.5),\n\
		    vec2(0.5, 0.5),\n\
		    vec2(-0.5, 0.5)\n\
		);\n\
		\n\
		vec3 colors[3] = vec3[](\n\
		    vec3(1.0, 0.0, 0.0),\n\
		    vec3(0.0, 1.0, 0.0),\n\
		    vec3(0.0, 0.0, 1.0)\n\
		);\n\
		\n\
		void main() {\n\
		    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);\n\
		    fragColor = colors[gl_VertexIndex];\n\
		}";

	const char* FragmentShaderSource =
		"#version 450\n\
		\n\
		layout(location = 0) in vec3 fragColor;\n\
		\n\
		layout(location = 0) out vec4 outColor;\n\
		\n\
		void main() {\n\
		    outColor = vec4(fragColor, 1.0);\n\
		}";

	std::cout << VertexShaderSource << std::endl;
	std::cout << FragmentShaderSource << std::endl;

	//bool Success = false;
	//glslang::TShader VertexShader(EShLanguage::EShLangVertex);
	//glslang::TShader FragmentShader(EShLanguage::EShLangFragment);
	//std::vector<unsigned int> VertexShaderSPIRV;
	//std::vector<unsigned int> FragmentShaderSPIRV;

	//VertexShader.setStrings(&VertexShaderSource, 1);
	//VertexShader.setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientVulkan, 120);
	//VertexShader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
	//VertexShader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetLanguageVersionCount);
	//VertexShader.setEntryPoint("main");

	//FragmentShader.setStrings(&VertexShaderSource, 1);
	//FragmentShader.setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientVulkan, 120);
	//FragmentShader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
	//FragmentShader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetLanguageVersionCount);
	//FragmentShader.setEntryPoint("main");

	//EShMessages Options = (EShMessages)(EShMessages::EShMsgDebugInfo | EShMessages::EShMsgVulkanRules | EShMessages::EShMsgSpvRules | EShMessages::EShMsgAST | EShMessages::EShMsgDefault);

	//Success = VertexShader.parse(&glslang::DefaultTBuiltInResource, 120, EProfile::ECoreProfile, false, false, Options);
	//if (Success) {
	//	// If parsing successful, take AST and compile to SPIRV.
	//	glslang::GlslangToSpv(*VertexShader.getIntermediate(), VertexShaderSPIRV);
	//}
	//else {
	//	// Print error message.
	//	std::cout << VertexShader.getInfoDebugLog() << std::endl;
	//}

	//Success = FragmentShader.parse(&glslang::DefaultTBuiltInResource, 120, EProfile::ECoreProfile, false, false, Options);
	//if (Success) {
	//	// If parsing successful, take AST and compile to SPIRV.
	//	glslang::GlslangToSpv(*FragmentShader.getIntermediate(), FragmentShaderSPIRV);
	//}
	//else {
	//	// Print error message.
	//	std::cout << FragmentShader.getInfoDebugLog() << std::endl;
	//}

	//// Creat Shader Modules for compiled shader code.
	//VkShaderModuleCreateInfo VertexShaderModuleCreateInfo;
	//VertexShaderModuleCreateInfo.sType		= VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	//VertexShaderModuleCreateInfo.pNext		= NULL;
	//VertexShaderModuleCreateInfo.flags		= 0; // Reserved for Future Use.
	//VertexShaderModuleCreateInfo.codeSize	= VertexShaderSPIRV.size()*sizeof(uint32_t);
	//VertexShaderModuleCreateInfo.pCode		= reinterpret_cast<const uint32_t*>(VertexShaderSPIRV.data());

	//VkShaderModule VertexShaderModule;
	//// Create Shader Modules.
	//Engine.ErrorCode = vkCreateShaderModule(DeviceContext->get_handle(), &VertexShaderModuleCreateInfo, NULL, &VertexShaderModule);
	//std::cout << Engine.get_er_str(Engine.ErrorCode) << std::endl;


	//VkShaderModuleCreateInfo FragmentShaderModuleCreateInfo;
	//FragmentShaderModuleCreateInfo.sType		= VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	//FragmentShaderModuleCreateInfo.pNext		= NULL;
	//FragmentShaderModuleCreateInfo.flags		= 0; // Reserved for Future Use.
	//FragmentShaderModuleCreateInfo.codeSize		= FragmentShaderSPIRV.size()*sizeof(uint32_t);
	//FragmentShaderModuleCreateInfo.pCode		= reinterpret_cast<const uint32_t*>(FragmentShaderSPIRV.data());

	//VkShaderModule FragmentShaderModule;
	//// Create Shader Modules.
	//Engine.ErrorCode = vkCreateShaderModule(DeviceContext->get_handle(), &FragmentShaderModuleCreateInfo, NULL, &FragmentShaderModule);
	//std::cout << Engine.get_er_str(Engine.ErrorCode) << std::endl;

	// Does everything above but in two lines.
	shader VertexShader(DeviceContext, shader::VERTEX, VertexShaderSource);
	shader FragmentShader(DeviceContext, shader::FRAGMENT, FragmentShaderSource);

	std::cout << "Vertex Shader Compile Status: " << Engine.get_er_str(VertexShader.ErrorCode) << std::endl;
	std::cout << "Fragment Shader Compile Status: " << Engine.get_er_str(FragmentShader.ErrorCode) << std::endl;

	VkRenderPassCreateInfo RenderPassCI{};
	VkRenderPass RenderPass;

	VkFramebufferCreateInfo FramebufferCI{};
	VkFramebuffer Framebuffer;


	FramebufferCI.sType				= VkStructureType::VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCI.pNext				= NULL;
	FramebufferCI.flags				= 0;
	//FramebufferCI.renderPass		= Describes the images and attachment layouts?;
	//FramebufferCI.attachmentCount	= 1;
	//FramebufferCI.pAttachments		= Image Views go here.;
	FramebufferCI.width				= Window->FrameBuffer.Property.Extent2D.width;
	FramebufferCI.height			= Window->FrameBuffer.Property.Extent2D.height;
	FramebufferCI.layers			= 1;

	vkCreateFramebuffer(DeviceContext->get_handle(), &FramebufferCI, NULL, &Framebuffer);

	// ---------------------------------------- Graphics Pipeline ---------------------------------------- //
	/*
	* This is a lot of information to describe a pipeline, but I do prefer this over the state machine model.
	* At least it is easy to know exactly what is going on. Rather than a global state machine, this is rather
	* contained.
	*/

	VkPipelineCache Cache;
	VkPipeline GraphicsPipeline;

	VkPipelineCacheCreateInfo CacheCI;
	VkGraphicsPipelineCreateInfo GraphicsPipelineCI;

	// Loads compiled shaders into graphics pipeline
	std::vector<VkPipelineShaderStageCreateInfo> ShaderStage(2);

	// Vertex Shader
	ShaderStage[0].sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStage[0].pNext					= NULL;
	ShaderStage[0].flags					= 0;
	ShaderStage[0].stage					= VertexShader.get_stage();
	ShaderStage[0].module					= VertexShader.get_handle();
	ShaderStage[0].pName					= "Vertex Shader";
	ShaderStage[0].pSpecializationInfo		= NULL;

	// Fragment Shader
	ShaderStage[1].sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStage[1].pNext					= NULL;
	ShaderStage[1].flags					= 0;
	ShaderStage[1].stage					= FragmentShader.get_stage();
	ShaderStage[1].module					= FragmentShader.get_handle();
	ShaderStage[1].pName					= "Fragment Shader";
	ShaderStage[1].pSpecializationInfo		= NULL;
	
	// Describes map for buffers to graphics pipeline.
	VkPipelineVertexInputStateCreateInfo VertexInputStateCI;
	VertexInputStateCI.sType								= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputStateCI.pNext								= NULL;
	VertexInputStateCI.flags								= 0; // Reserved for Future use. (Ignore)
	VertexInputStateCI.vertexBindingDescriptionCount		= 0;
	VertexInputStateCI.pVertexBindingDescriptions			= NULL;
	VertexInputStateCI.vertexAttributeDescriptionCount		= 0;
	VertexInputStateCI.pVertexAttributeDescriptions			= NULL;

	// Input assembly topology for how the rasterizer will interpret vertex data.
	VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCI;
	InputAssemblyStateCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyStateCI.pNext						= NULL;
	InputAssemblyStateCI.flags						= 0; // Reserved for future use. (Ignore)
	InputAssemblyStateCI.topology					= VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssemblyStateCI.primitiveRestartEnable		= VK_FALSE; // Most likely never going to use this.

	// sub windows maybe?
	VkViewport Viewport{};
	Viewport.x			= 0;
	Viewport.y			= 0;
	Viewport.width		= Window->Resolution.x;
	Viewport.height		= Window->Resolution.y;
	Viewport.minDepth	= 0.0f;
	Viewport.maxDepth	= 1.0f;

	// Kind of cool, might fuck with later
	VkRect2D Scissor{};
	Scissor.offset		= { 0, 0 };
	Scissor.extent		= Window->FrameBuffer.Property.Extent2D;

	// Creates Viewport, (How can there be multiple scissors and viewports? What does this mean?)
	VkPipelineViewportStateCreateInfo ViewportStateCI{};
	ViewportStateCI.sType			= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportStateCI.pNext			= NULL;
	ViewportStateCI.flags			= 0; // Reserved for future use (Ignored)
	ViewportStateCI.viewportCount	= 1;
	ViewportStateCI.pViewports		= &Viewport;
	ViewportStateCI.scissorCount	= 1;
	ViewportStateCI.pScissors		= &Scissor;

	VkPipelineRasterizationStateCreateInfo RasterizationStateCI;
	RasterizationStateCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationStateCI.pNext						= NULL;
	RasterizationStateCI.flags						= 0; // Cool, reserved for future use.
	RasterizationStateCI.depthClampEnable			= VK_FALSE;
	RasterizationStateCI.rasterizerDiscardEnable	= VK_FALSE; // Fuck no
	RasterizationStateCI.polygonMode				= VkPolygonMode::VK_POLYGON_MODE_FILL;
	RasterizationStateCI.cullMode					= VkCullModeFlagBits::VK_CULL_MODE_NONE;
	RasterizationStateCI.frontFace					= VkFrontFace::VK_FRONT_FACE_COUNTER_CLOCKWISE; // Defines CCW as front face.
	RasterizationStateCI.depthBiasEnable			= VK_FALSE;
	RasterizationStateCI.depthBiasConstantFactor	= 0.0f;
	RasterizationStateCI.depthBiasClamp				= 0.0f;
	RasterizationStateCI.depthBiasSlopeFactor		= 0.0f;
	RasterizationStateCI.lineWidth					= 1.0f;

	VkPipelineMultisampleStateCreateInfo MultisampleStateCI;
	MultisampleStateCI.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleStateCI.pNext					= NULL;
	MultisampleStateCI.flags					= 0; // Fuck yeah
	MultisampleStateCI.rasterizationSamples		= VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
	MultisampleStateCI.sampleShadingEnable		= VK_FALSE;
	MultisampleStateCI.minSampleShading			= 1.0f;
	MultisampleStateCI.pSampleMask				= NULL;
	MultisampleStateCI.alphaToCoverageEnable	= VK_FALSE;
	MultisampleStateCI.alphaToOneEnable			= VK_FALSE;
	
	/*
	VkPipelineDepthStencilStateCreateInfo DepthStencilStateCI;
	DepthStencilStateCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencilStateCI.pNext						= NULL;
	DepthStencilStateCI.flags						= 0; // NICE
	DepthStencilStateCI.depthTestEnable				;
	DepthStencilStateCI.depthWriteEnable			;
	DepthStencilStateCI.depthCompareOp				;
	DepthStencilStateCI.depthBoundsTestEnable		;
	DepthStencilStateCI.stencilTestEnable			;
	DepthStencilStateCI.front						;
	DepthStencilStateCI.back						;
	DepthStencilStateCI.minDepthBounds				;
	DepthStencilStateCI.maxDepthBounds				;
	*/

	// wtf? the fisrt vulkan struct that doesn't begin with sType and pNext?
	// Alpha channel is being used in this pipeline.
	VkPipelineColorBlendAttachmentState Attachment{};
	Attachment.blendEnable			= VK_TRUE;
	Attachment.srcColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_SRC_ALPHA;
	Attachment.dstColorBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	Attachment.colorBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
	Attachment.srcAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ONE;
	Attachment.dstAlphaBlendFactor	= VkBlendFactor::VK_BLEND_FACTOR_ZERO;
	Attachment.alphaBlendOp			= VkBlendOp::VK_BLEND_OP_ADD;
	//Attachment.colorWriteMask		= 0;

	VkPipelineColorBlendStateCreateInfo ColorBlendStateCI{};
	ColorBlendStateCI.sType					= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColorBlendStateCI.pNext					= NULL;
	ColorBlendStateCI.flags					= 0;
	ColorBlendStateCI.logicOpEnable			= VK_FALSE;
	ColorBlendStateCI.logicOp				= VK_LOGIC_OP_COPY;
	ColorBlendStateCI.attachmentCount		= 1;
	ColorBlendStateCI.pAttachments			= &Attachment;
	ColorBlendStateCI.blendConstants[0]		= 0.0f;
	ColorBlendStateCI.blendConstants[1]		= 0.0f;
	ColorBlendStateCI.blendConstants[2]		= 0.0f;
	ColorBlendStateCI.blendConstants[3]		= 0.0f;

	VkDynamicState DynamicState[] = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_LINE_WIDTH
	};

	// Heads up warning for what changes quickly
	VkPipelineDynamicStateCreateInfo DynamicStateCI{};
	DynamicStateCI.sType				= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStateCI.pNext				= NULL;
	DynamicStateCI.flags				= 0;
	DynamicStateCI.dynamicStateCount	= 2;
	DynamicStateCI.pDynamicStates		= DynamicState;

	// This will apparently be the interface for uniforms in shaders.
	VkPipelineLayout Layout;
	VkPipelineLayoutCreateInfo LayoutCI;
	LayoutCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	LayoutCI.pNext						= NULL;
	LayoutCI.flags						= 0; // Sweet.
	LayoutCI.setLayoutCount				= 0;
	LayoutCI.pSetLayouts				= NULL;
	LayoutCI.pushConstantRangeCount		= 0;
	LayoutCI.pPushConstantRanges		= NULL;
	Engine.ErrorCode = vkCreatePipelineLayout(DeviceContext->get_handle(), &LayoutCI, NULL, &Layout);
	std::cout << "PipelineLayout Creation Status: " << Engine.get_er_str(Engine.ErrorCode) << std::endl;

	// Finalizes previous steps into graphics pipeline creation info.
	GraphicsPipelineCI.sType						= VkStructureType::VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	GraphicsPipelineCI.pNext						= NULL;
	GraphicsPipelineCI.flags						= 0;
	GraphicsPipelineCI.stageCount					= 2;
	GraphicsPipelineCI.pStages						= ShaderStage.data();
	GraphicsPipelineCI.pVertexInputState			= &VertexInputStateCI;
	GraphicsPipelineCI.pInputAssemblyState			= &InputAssemblyStateCI;
	GraphicsPipelineCI.pTessellationState			= NULL; // Not using this right now
	GraphicsPipelineCI.pViewportState				= &ViewportStateCI;
	GraphicsPipelineCI.pRasterizationState			= &RasterizationStateCI;
	GraphicsPipelineCI.pMultisampleState			= &MultisampleStateCI;
	GraphicsPipelineCI.pDepthStencilState			= NULL; // Ignore for now
	GraphicsPipelineCI.pColorBlendState				= &ColorBlendStateCI;
	GraphicsPipelineCI.pDynamicState				= &DynamicStateCI;
	GraphicsPipelineCI.layout						= Layout;
	GraphicsPipelineCI.renderPass					;
	/*
	GraphicsPipelineCI.subpass						;
	GraphicsPipelineCI.basePipelineHandle			;
	GraphicsPipelineCI.basePipelineIndex			;
	*/

	vkCreatePipelineCache(DeviceContext->get_handle(), &CacheCI, NULL, &Cache);
	vkCreateGraphicsPipelines(DeviceContext->get_handle(), Cache, 1, &GraphicsPipelineCI, NULL, &GraphicsPipeline);

	for (size_t i = 0; i < 7; i++) {
		std::cout << io::file::BuiltInTypes[i].Type << " ";
		for (size_t j = 0; j < io::file::BuiltInTypes[i].Extension.size(); j++) {
			std::cout << io::file::BuiltInTypes[i].Extension[j].str() << " ";
		}
		std::cout << std::endl;
	}
	
	std::cout << io::file::str2type("fsh") << std::endl;

	io::file File("assets/shaders/BasicVertex.fsh");

	std::cout << File.get_path().str() << std::endl;
	std::cout << File.get_dir().str() << std::endl;
	std::cout << File.get_name().str() << std::endl;
	std::cout << File.get_ext().str() << std::endl;

	//VkGraphicsPipelineCreateInfo GraphicsPipelineCreateInfo;

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
