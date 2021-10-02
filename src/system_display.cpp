#include <geodesuka/core/object/system_display.h>

#include <geodesuka/core/object.h>
#include <geodesuka/core/object/window.h>
#include <geodesuka/core/object/system_display.h>
#include <geodesuka/core/object/system_window.h>
#include <geodesuka/core/object/virtual_window.h>
#include <geodesuka/core/object/camera.h>

namespace geodesuka::core::object {

	system_display::system_display(GLFWmonitor* aMonitor) {
		this->Property = window::prop();

		this->Handle = aMonitor;

		this->Name = glfwGetMonitorName(this->Handle);
		//const char* aName = glfwGetMonitorName(this->Handle);
		//if (aName != NULL) {
		//	size_t NameSize = strlen(aName);
		//	this->Name = (char*)malloc((NameSize + 1) * sizeof(char));
		//	if (this->Name != NULL) {
		//		memcpy(this->Name, aName, NameSize * sizeof(char));
		//		this->Name[NameSize] = '\0';
		//	}
		//}
		
		glfwGetMonitorPos(this->Handle, &this->PositionSC.x, &this->PositionSC.y);
		// Loads and converts to meters.
		int Width, Height;
		glfwGetMonitorPhysicalSize(this->Handle, &Width, &Height);
		this->Size.x = (math::real)(((double)Width) / 1000.0);
		this->Size.y = (math::real)(((double)Height) / 1000.0);

		const GLFWvidmode* lMode = glfwGetVideoMode(this->Handle);
		// TODO: add constructors for math::naturalx.
		this->Resolution.x = lMode->width;
		this->Resolution.y = lMode->height;
		//this->SizeSC = math::integer2(lMode->width, lMode->height);
		this->Property.RefreshRate = lMode->refreshRate;

	}

	system_display::~system_display() {

	}

	void system_display::draw(object_t* aObject) {}
}