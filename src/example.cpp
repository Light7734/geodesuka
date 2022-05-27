#include <geodesuka/builtin/stage/example.h>

#include <geodesuka/engine.h>

namespace geodesuka::builtin::stage {

	example::example(engine* aEngine, core::gcl::context* aContext) : stage_t(aEngine, aContext) {
		
		Property.Window.Resizable			= true;
		Property.Window.Decorated			= true;
		Property.Window.UserFocused			= true;
		Property.Window.AutoMinimize		= false;
		Property.Window.Floating			= false;
		Property.Window.Maximized			= false;
		Property.Window.Minimized			= false;
		Property.Window.Visible				= true;
		Property.Window.ScaleToMonitor		= false;
		Property.Window.CenterCursor		= false;
		Property.Window.FocusOnShow			= false;

		Property.Swapchain.FrameCount		= 3;
		Property.Swapchain.FrameRate		= 30.0;
		Property.Swapchain.ColorSpace		= core::object::system_window::colorspace::SRGB_NONLINEAR;
		Property.Swapchain.Usage			= core::gcl::image::usage::COLOR_ATTACHMENT;
		Property.Swapchain.CompositeAlpha	= core::object::system_window::composite::ALPHA_OPAQUE;
		Property.Swapchain.PresentMode		= core::object::system_window::present_mode::FIFO;
		Property.Swapchain.Clipped			= true;
		Property.PixelFormat				= VkFormat::VK_FORMAT_B8G8R8A8_SRGB;
		Property.Position					= float3(0, 0, 0);
		Property.Size						= float2(0.3, 0.3);
		Property.Title						= "Triangle";

		SystemDisplay = Engine->get_primary_display();

		SystemWindow = new core::object::system_window(Engine, Context, SystemDisplay, Property);

		RenderTarget.push_back(SystemWindow);

		Triangle = new object::triangle(aEngine, aContext, this);

	}

	example::~example() {
		delete Triangle;
		delete SystemWindow;
	}



}