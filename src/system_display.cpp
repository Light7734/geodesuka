#include <geodesuka/core/object/system_display.h>

#include <geodesuka/core/object.h>

//#include <geodesuka/engine.h>

namespace geodesuka::core::object {

	system_display::system_display(engine *aEngine, gcl::context* aContext, GLFWmonitor* aMonitor) : window(aEngine, aContext) {
		this->Property = window::prop();

		this->Handle = aMonitor;

		this->Title = glfwGetMonitorName(this->Handle);
		
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