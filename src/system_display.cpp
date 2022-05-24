//#include <geodesuka/engine.h>
#include <geodesuka/core/object/system_display.h>

#include <geodesuka/core/object.h>

#include <GLFW/glfw3.h>

namespace geodesuka::core::object {

	const int system_display::RTID = 1;

	system_display::system_display(engine *aEngine, gcl::context* aContext, GLFWmonitor* aMonitor) : window(aEngine, aContext, nullptr) {

		Handle = aMonitor;

		Title = glfwGetMonitorName(Handle);
		

		// Gather video modes of monitor.
		int MonitorVideoModeCount = 0;
		const GLFWvidmode *MonitorVideoMode = glfwGetVideoModes(Handle, &MonitorVideoModeCount);

		VideoMode = (GLFWvidmode*)malloc(MonitorVideoModeCount * sizeof(GLFWvidmode));
		if (VideoMode != NULL) {
			memcpy(VideoMode, MonitorVideoMode, MonitorVideoModeCount * sizeof(GLFWvidmode));
		}

		CurrentVideoMode = glfwGetVideoMode(Handle);

		glfwGetMonitorPos(Handle, &PositionVSC.x, &PositionVSC.y);

		// Returns units in mm, converts to meters.
		int2 PhysicalSize = int2(0, 0);
		glfwGetMonitorPhysicalSize(Handle, &PhysicalSize.x, &PhysicalSize.y);
		Size.x = (math::real)(((double)PhysicalSize.x) / 1000.0);
		Size.y = (math::real)(((double)PhysicalSize.y) / 1000.0);

		// Load resolution
		SizeVSC.x = CurrentVideoMode->width;
		SizeVSC.y = CurrentVideoMode->height;
		Resolution.x = CurrentVideoMode->width;
		Resolution.y = CurrentVideoMode->height;
		Resolution.z = 1u;
		FrameRate = CurrentVideoMode->refreshRate;
	}

	system_display::~system_display() {

	}

	int system_display::rtid() {
		return RTID;
	}

	VkSubmitInfo system_display::draw(size_t aObjectCount, object_t** aObject) {
		VkSubmitInfo DrawBatch{};
		DrawBatch.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		DrawBatch.pNext = NULL;
		return DrawBatch;
	}

}