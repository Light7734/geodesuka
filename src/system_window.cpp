#include <geodesuka/core/object/system_window.h>

#include <algorithm>

#include <geodesuka/engine.h>

namespace geodesuka::core::object {

	const std::vector<const char*> system_window::RequiredExtension = { /*VK_KHR_SURFACE_EXTENSION_NAME,*/ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	system_window::system_window(engine* aEngine, gcl::context* aContext, create_info* aCreateInfo, int aWidth, int aHeight, const char* aTitle) : window(aEngine, aContext) {

		this->ParentEngine = aEngine;
		this->ParentDisplay = aCreateInfo->Display;
		this->ParentContext = aContext;

		// ------------------------- System Window Creation ------------------------- //

		this->Property = prop();
		glfwWindowHint(GLFW_RESIZABLE,			this->Property.Resizable);
		glfwWindowHint(GLFW_DECORATED,			this->Property.Decorated);
		glfwWindowHint(GLFW_FOCUSED,			this->Property.UserFocused);
		glfwWindowHint(GLFW_AUTO_ICONIFY,		this->Property.AutoMinimize);
		glfwWindowHint(GLFW_FLOATING,			this->Property.Floating);
		glfwWindowHint(GLFW_MAXIMIZED,			this->Property.Maximized);
		glfwWindowHint(GLFW_VISIBLE,			this->Property.Visible);
		glfwWindowHint(GLFW_SCALE_TO_MONITOR,	this->Property.ScaleToMonitor);
		glfwWindowHint(GLFW_CENTER_CURSOR,		this->Property.CenterCursor);
		glfwWindowHint(GLFW_FOCUS_ON_SHOW,		this->Property.FocusOnShow);
		glfwWindowHint(GLFW_CLIENT_API,			GLFW_NO_API);
		glfwWindowHint(GLFW_REFRESH_RATE,		this->Property.RefreshRate); // TODO: Change to GLFW_DONT_CARE, and remove option.

		//this->SizeSC = this->phys2scrn(this->Size);
		this->Handle = glfwCreateWindow(640, 480, "", NULL, NULL);

		// Post Creation Options

		if (this->Handle != NULL) {
			// Get frame_buffer size. Will be same as SizeSC except on retina display. (Mac is Garbage)

			// User pointer to forward input stream.
			glfwSetWindowUserPointer(this->Handle, (void*)this);

			// system_window callbacks
			glfwSetWindowPosCallback(this->Handle,			system_window::position_callback);
			glfwSetWindowSizeCallback(this->Handle,			system_window::size_callback);
			glfwSetWindowCloseCallback(this->Handle,		system_window::close_callback);
			glfwSetWindowRefreshCallback(this->Handle,		system_window::refresh_callback);
			glfwSetWindowFocusCallback(this->Handle,		system_window::focus_callback);
			glfwSetWindowIconifyCallback(this->Handle,		system_window::iconify_callback);
			glfwSetWindowMaximizeCallback(this->Handle,		system_window::maximize_callback);
			glfwSetWindowContentScaleCallback(this->Handle, system_window::content_scale_callback);

			// framebuffer callbacks
			glfwSetFramebufferSizeCallback(this->Handle,	system_window::framebuffer_size_callback);

			// Mouse callbacks
			glfwSetMouseButtonCallback(this->Handle,		system_window::mouse_button_callback);
			glfwSetCursorPosCallback(this->Handle,			system_window::cursor_position_callback);
			glfwSetCursorEnterCallback(this->Handle,		system_window::cursor_enter_callback);
			glfwSetScrollCallback(this->Handle,				system_window::scroll_callback);

			// Keyboard callbacks
			glfwSetKeyCallback(this->Handle,				system_window::key_callback);
			glfwSetCharCallback(this->Handle,				system_window::character_callback);

			// File drop
			glfwSetDropCallback(this->Handle,				system_window::file_drop_callback);

			//glfwGetWindowFrameSize(this->Context->Handle, system_window::framebuffer_size_callback);

		}

		// ------------------------- Surface Creation ------------------------- //
		VkResult Result = VkResult::VK_SUCCESS;
		Result = glfwCreateWindowSurface(aEngine->handle(), this->Handle, NULL, &this->Surface);

		this->Swapchain = new gcl::swapchain(aContext, this->Surface, aCreateInfo->SwapchainProperty, aWidth, aHeight, nullptr);
	}

	//system_window::system_window(engine* aEngine, gcl::context* aContext, create_info* aCreateInfo, float aSizeX, int aSizeY, const char* aTitle) : window(aEngine, aContext) {}

	system_window::~system_window() {
		// Destroys swapchain.
		delete Swapchain;
		// Destroys suface.
		vkDestroySurfaceKHR(this->ParentEngine->handle(), this->Surface, NULL);
		// Destroys window handle.
		glfwDestroyWindow(this->Handle);

		std::cout << "System Window Destroyed" << std::endl;
	}

	void system_window::update(double aDeltaTime) {
		this->Mutex.lock();
		this->Time += aDeltaTime;

		this->Mutex.unlock();
	}

	void system_window::draw(system_display* aTargetDisplay) {
		// This method is responsible for rendering window to display.
		this->Mutex.lock();

		if (this->Property.RefreshRate) {

		}
		this->Mutex.unlock();
	}

	void system_window::draw(object_t* aObject) {
		if ((object_t*)this == aObject) return;
		aObject->draw(this);
	}

	void system_window::set_position(math::real3 aPosition) {
		//tex:
		// Centers system_display and system_window.
		// $$ \vec{r}_{tmp} = \vec{r}_{sc}^{w} + \frac{\vec{s}_{sc}^{w}}{2} - \Big(\vec{r}_{sc}^{m} + \frac{\vec{s}_{sc}^{m}}{2} \Big) $$
		// $$ x_{tmp} = $$

		// Converts Direction and length.
		this->Position = aPosition;
		math::integer2 r_tmp = math::integer2(
			(math::integer)(this->Position.x * (((math::real)(ParentDisplay->Resolution.x)) / (ParentDisplay->Size.x))),
			(math::integer)(-this->Position.y * (((math::real)(ParentDisplay->Resolution.y)) / (ParentDisplay->Size.y)))
		);

		// Compensate for shift.
		this->PositionSC =
			r_tmp
			- math::integer2(((double)Resolution.x / 2.0), ((double)Resolution.y / 2.0))
			+ ParentDisplay->PositionSC
			+ math::integer2(((double)ParentDisplay->Resolution.x / 2.0), ((double)ParentDisplay->Resolution.y / 2.0));

		glfwSetWindowPos(this->Handle, this->PositionSC.x, this->PositionSC.y);
	}

	void system_window::set_size(math::real2 aSize) {
		this->Resolution.x = aSize.x * ((double)this->ParentDisplay->Resolution.x / (double)this->ParentDisplay->Size.x);
		this->Resolution.y = aSize.y * ((double)this->ParentDisplay->Resolution.y / (double)this->ParentDisplay->Size.y);
		glfwSetWindowSize(this->Handle, this->Resolution.x, this->Resolution.y);
		// TODO: make more efficient
		this->set_position(this->Position);
	}

	void system_window::set_resolution(math::natural2 aResolution) {
		this->Size.x = aResolution.x * ((double)this->ParentDisplay->Size.x / (double)this->ParentDisplay->Resolution.x);
		this->Size.y = aResolution.y * ((double)this->ParentDisplay->Size.y / (double)this->ParentDisplay->Resolution.y);
		glfwSetWindowSize(this->Handle, aResolution.x, aResolution.y);
		// TODO: make more efficient
		this->set_position(this->Position);
	}

	math::integer2 system_window::phys2scrn(math::real2 R) {
		math::integer2 temp;

		//// Converts Direction and length.
		//this->Position = aPosition;
		//math::integer2 r_tmp = math::integer2(
		//	(math::integer)(this->Position.x * (((math::real)(ParentDisplay->Resolution.x)) / (ParentDisplay->Size.x))),
		//	(math::integer)(-this->Position.y * (((math::real)(ParentDisplay->Resolution.y)) / (ParentDisplay->Size.y)))
		//);

		//// Compensate for shift.
		//this->PositionSC = 
		//	r_tmp
		//	- math::integer2(((double)Resolution.x / 2.0), ((double)Resolution.y / 2.0))
		//	+ ParentDisplay->PositionSC
		//	+ math::integer2(((double)ParentDisplay->Resolution.x / 2.0), ((double)ParentDisplay->Resolution.y / 2.0));

		return temp;
	}

	math::real2 system_window::scrn2phys(math::integer2 R) {
		math::real2 temp;
		return temp;
	}

	// --------------- These are the system_window callbacks --------------- //

	void system_window::position_callback(GLFWwindow* ContextHandle, int PosX, int PosY) {
		//tex:
		// Centers system_display and system_window.
		// $$ \vec{r}_{tmp} = \vec{r}_{sc}^{w} + \frac{\vec{s}_{sc}^{w}}{2} - \Big(\vec{r}_{sc}^{m} + \frac{\vec{s}_{sc}^{m}}{2} \Big) $$
		// $$ x_{tmp} = $$

		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

		// Shifts to new origin at parent display center.
		math::integer2 r_tmp =
			math::integer2(PosX, PosY)
			+ math::integer2((double)Win->Resolution.x / 2.0, (double)Win->Resolution.y / 2.0)
			- Win->ParentDisplay->PositionSC
			- math::integer2((double)Win->ParentDisplay->Resolution.x / 2.0, (double)Win->ParentDisplay->Resolution.y / 2.0);

		// Converts to physical position on display (meters)
		Win->Position = math::real3(
			(double)r_tmp.x * ((double)Win->ParentDisplay->Size.x / (double)Win->ParentDisplay->Resolution.x),
			-(double)r_tmp.y * ((double)Win->ParentDisplay->Size.y / (double)Win->ParentDisplay->Resolution.y),
			0.0
		);

		// Debug position.
		//std::cout << Win->Name << ".Position =\t" << Win->Position.x << ", " << Win->Position.y << std::endl;
	}

	void system_window::size_callback(GLFWwindow* ContextHandle, int SizeX, int SizeY) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

		Win->Resolution.x = SizeX;
		Win->Resolution.y = SizeY;

	}

	void system_window::close_callback(GLFWwindow* ContextHandle) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
		std::cout << Win->Title.str() << " wants to fucking close" << std::endl;
		//Win->CloseMe = true;
	}

	void system_window::refresh_callback(GLFWwindow* ContextHandle) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::focus_callback(GLFWwindow* ContextHandle, int Focused) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::iconify_callback(GLFWwindow* ContextHandle, int Iconified) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::maximize_callback(GLFWwindow* ContextHandle, int Maximized) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);


	}

	void system_window::content_scale_callback(GLFWwindow* ContextHandle, float XScale, float YScale) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
	}

	// framebuffer callbacks

	void system_window::framebuffer_size_callback(GLFWwindow* ContextHandle, int FrameSizeX, int FrameSizeY) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	// Mouse callbacks

	void system_window::mouse_button_callback(GLFWwindow* ContextHandle, int Button, int Action, int Mods) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
	}

	void system_window::cursor_position_callback(GLFWwindow* ContextHandle, double PosX, double PosY) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::cursor_enter_callback(GLFWwindow* ContextHandle, int Entered) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::scroll_callback(GLFWwindow* ContextHandle, double OffsetX, double OffsetY) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	void system_window::key_callback(GLFWwindow* ContextHandle, int Key, int Scancode, int Action, int Mods) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);
	}

	void system_window::character_callback(GLFWwindow* ContextHandle, unsigned int Codepoint) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

	// File Drops

	void system_window::file_drop_callback(GLFWwindow* ContextHandle, int PathCount, const char** Path) {
		system_window* Win = (system_window*)glfwGetWindowUserPointer(ContextHandle);

	}

}




//
//system_window::system_window() {
//	this->Property = this->m_default_window_properties();
//	//this->CTX = NULL;
//
//	this->Title = NULL;
//
//	this->Time = 0.0f;
//	this->PositionVS = { 0, 0 };
//	this->SizeVS = { 0, 0 };
//
//	this->SwapInterval = 1;
//	this->PositionPX = { 0, 0 };
//	this->SizePX = { 0, 0 };
//	this->FrameColor = { 0.0f, 0.0f, 0.0f, 0.0f };
//
//	this->ExitCall = false;
//	this->RefreshCall = false;
//
//	this->LockBoundary = false;
//	this->LowBound = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//	this->HighBound = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//
//	this->LockAspectRatio = false;
//	this->AspectRatio = { GLFW_DONT_CARE, GLFW_DONT_CARE };
//
//	this->PositionMM = { 0.0f, 0.0f };
//	this->SizeMM = { 0.0f, 0.0f };
//}
//
//system_window::~system_window() {
//
//}
//
//void system_window::set_context(integer ContextAPI, integer ContextMajor, integer ContextMinor, integer ContextProfile, integer ContextForwardCompat, integer ContextDebugMode) {
//	Property.Context.ClientAPI = ContextAPI;
//	Property.Context.Version = { ContextMajor, ContextMinor };
//	Property.Context.Profile = ContextProfile;
//	Property.Context.ForwardCompat = ContextForwardCompat;
//	Property.Context.DebugMode = ContextDebugMode;
//}
//
//integer system_window::create(integer WindowWidth, integer WindowHeight, const char* WindowTitle, GLFWmonitor* WindowDisplay, GLFWwindow* WindowShare) {
//	this->annihilate();
//
//	if ((WindowWidth > 0) && (WindowHeight > 0)) { SizeVS = { WindowWidth, WindowHeight }; }
//	if (WindowTitle != NULL) { this->set_title(WindowTitle); }
//	//if (WindowDisplay != nullptr) { Display = WindowDisplay; }
//	//if (WindowShare != nullptr) { SharingContext = WindowShare->Context; }
//
//	// --------------- Window Creation --------------- //
//
//	CTX = gcl::create_ctx(&Property, SizeVS.x, SizeVS.y, Title, WindowDisplay, WindowShare);
//
//	if (Property.Minimized) {
//		glfwIconifyWindow(CTX);
//	}
//	glfwWindowHint();
//	// Minimized > FullScreen > Maximized
//	if (!(ParentDisplay != NULL) && !Property.Maximized && !Property.Minimized) {
//		glfwGetWindowSize(CTX, &SizeVS.x, &SizeVS.y);
//		glfwGetFramebufferSize(CTX, &SizePX.x, &SizePX.y);
//		glfwSetWindowPos(CTX, PositionVS.x, PositionVS.y);
//	}
//
//	if (CTX != NULL) {
//		void* nptr = reinterpret_cast<void*>(this);
//		glfwSetWindowUserPointer(CTX, nptr);
//	}
//
//	//if (Display != nullptr) {
//	//	PositionMM = {
//	//		((float)PositionVS.x + (float)SizeVS.x / 2.0f - (float)Display->Position.x - (float)Display->Size.x / 2.0f)*((float)Display->SizeMM.x / (float)Display->Size.x),
//	//		((float)PositionVS.y + (float)SizeVS.y / 2.0f - (float)Display->Position.y - (float)Display->Size.y / 2.0f)*((float)Display->SizeMM.y / (float)Display->Size.y)
//	//	};
//	//	SizeMM = {
//	//		(float)SizeVS.x*(float)Display->SizeMM.x / (float)Display->Size.x,
//	//		(float)SizeVS.y*(float)Display->SizeMM.y / (float)Display->Size.y
//	//	};
//	//}
//
//	return 0;
//}
//
//integer system_window::annihilate() {
//	if (CTX != NULL) {
//		glfwDestroyWindow(CTX); CTX = NULL;
//	}
//	return 0;
//}
//
//integer system_window::set_title(const char* Str) {
//	if (Str == NULL) { return true; }
//	if (Title != NULL) {
//		free(Title); Title = NULL;
//	}
//
//	Title = (char*)malloc((strlen(Str) + 1) * sizeof(char));
//	if (Title != NULL) {
//		memcpy(Title, Str, strlen(Str) * sizeof(char));
//		Title[strlen(Str)] = '\0';
//	}
//
//	if ((CTX != NULL) && (Title != NULL)) {
//		glfwSetWindowTitle(CTX, Title);
//	}
//	return 0;
//}
//
//integer system_window::set_pos(integer x, integer y) {
//	if (ParentDisplay != NULL) { return -1; }
//	glfwSetWindowPos(CTX, x, y);
//	glfwGetWindowPos(CTX, &PositionVS.x, &PositionVS.y);
//	//if (Display != nullptr) {
//	//	PositionMM = {
//	//		((float)PositionVS.x + (float)SizeVS.x / 2.0f - (float)Display->Position.x - (float)Display->Size.x / 2.0f)*((float)Display->SizeMM.x / (float)Display->Size.x),
//	//		((float)PositionVS.y + (float)SizeVS.y / 2.0f - (float)Display->Position.y - (float)Display->Size.y / 2.0f)*((float)Display->SizeMM.y / (float)Display->Size.y)
//	//	};
//	//}
//	return 0;
//}
//
//integer system_window::set_size(integer w, integer h) {
//	if (ParentDisplay != NULL) { return -1; }
//	glfwSetWindowSize(CTX, w, h);
//	glfwGetWindowSize(CTX, &SizeVS.x, &SizeVS.y);
//	//if (Display != nullptr) {
//	//	SizeMM = {
//	//		(float)SizeVS.x*(float)Display->SizeMM.x / (float)Display->Size.x,
//	//		(float)SizeVS.y*(float)Display->SizeMM.y / (float)Display->Size.y
//	//	};
//	//}
//	return 0;
//}
//
//integer system_window::set_size_limits(integer x1, integer y1, integer x2, integer y2) {
//	LowBound = { x1, y1 }; HighBound = { x2, y2 };
//	if (LockBoundary) {
//		glfwSetWindowSizeLimits(CTX, x1, y1, x2, y2);
//	}
//	else {
//		glfwSetWindowSizeLimits(CTX, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);
//	}
//	return 0;
//}
//
//integer system_window::set_aspect_ratio(integer Numerator, integer Denominator) {
//	AspectRatio = { Numerator, Denominator };
//	if (LockAspectRatio) {
//		glfwSetWindowAspectRatio(CTX, Numerator, Denominator);
//	}
//	else {
//		glfwSetWindowAspectRatio(CTX, GLFW_DONT_CARE, GLFW_DONT_CARE);
//	}
//	return 0;
//}
//
//integer system_window::swap_interval(integer NewInterval) {
//	glfwSwapInterval(NewInterval);
//	return 0;
//}
//
//integer system_window::swap_buffers() {
//	glfwSwapBuffers(CTX);
//	return 0;
//}
//
//
//integer system_window::set(integer pname, integer pval) {
//	if (this->CTX == NULL) {
//		return this->m_set_hint(pname, pval);
//	}
//	else {
//		if (this->m_set_attrib(pname, pval) == 0) {
//			glfwSetWindowAttrib(this->CTX, pname, pval);
//		}
//		else {
//			switch (pname) {
//			default: return -1;
//			case GLFW_FOCUSED:
//				if ((Property.UserFocused == GLFW_FALSE) && (pval == GLFW_TRUE)) {
//					glfwFocusWindow(CTX);
//					Property.UserFocused = GLFW_TRUE;
//				}
//				break;
//			case GLFW_VISIBLE:
//				if (Property.Visible != pval) {
//					if (pval) {
//						glfwShowWindow(CTX);
//					}
//					else {
//						glfwHideWindow(CTX);
//					}
//					Property.Visible = pval;
//				}
//				break;
//			case GLFW_ICONIFIED:
//				if (this->Property.Minimized != pval) {
//					if (pval) {
//						glfwIconifyWindow(this->CTX);
//					}
//					else {
//						glfwRestoreWindow(this->CTX);
//					}
//				}
//				break;
//			case GLFW_MAXIMIZED:
//				if (this->Property.Maximized != pval) {
//					if (pval) {
//						glfwMaximizeWindow(this->CTX);
//					}
//					else {
//						glfwRestoreWindow(this->CTX);
//					}
//				}
//				break;
//			}
//
//		}
//	}
//	return 0;
//}
//
//integer system_window::get(integer pname) {
//	if (CTX == NULL) {
//		return this->m_get_hint(pname);
//	}
//	return -1;
//}
//
//gl_frame_properties system_window::m_default_frame_properties() {
//	gl_frame_properties temp;
//	temp.ColorBits.r				= 8							   ;
//	temp.ColorBits.g				= 8							   ;
//	temp.ColorBits.b				= 8							   ;
//	temp.ColorBits.a				= 8							   ;
//	temp.DepthBits					= 24						   ;
//	temp.StencilBits				= 8							   ;
//	temp.AccumColorBits.r			= 0							   ;
//	temp.AccumColorBits.g			= 0							   ;
//	temp.AccumColorBits.b			= 0							   ;
//	temp.AccumColorBits.a			= 0							   ;
//	temp.AuxBuffers					= 0							   ;
//	temp.Stereo						= GLFW_FALSE				   ;
//	temp.DoubleBuffer				= GLFW_TRUE					   ;
//	temp.Transparent				= GLFW_FALSE				   ;
//	temp.Samples					= 0							   ;
//	temp.sRGBCapable				= GLFW_FALSE				   ;
//	return temp;
//}
//
//gl_context_properties system_window::m_default_context_properties() {
//	gl_context_properties temp;
//	temp.ClientAPI						= GLFW_OPENGL_API			   ;
//	temp.CreationAPI					= GLFW_NATIVE_CONTEXT_API	   ;
//	temp.Version.x						= 1							   ;
//	temp.Version.y						= 0							   ;
//	temp.Robustness						= GLFW_NO_ROBUSTNESS		   ;
//	temp.ForwardCompat					= GLFW_FALSE				   ;
//	temp.DebugMode						= GLFW_FALSE				   ;
//	temp.NoError						= GLFW_FALSE				   ;
//	temp.Profile						= GLFW_OPENGL_ANY_PROFILE	   ;
//	temp.ReleaseBehavior				= GLFW_ANY_RELEASE_BEHAVIOR	   ;
//	return temp;
//}
//
//gl_window_properties system_window::m_default_window_properties() {
//	gl_window_properties temp;
//	temp.Frame = this->m_default_frame_properties();
//	temp.Resizable								= GLFW_TRUE					   ;
//	temp.Decorated								= GLFW_TRUE					   ;
//	temp.UserFocused							= GLFW_TRUE					   ;
//	temp.AutoMinimize							= GLFW_TRUE					   ;
//	temp.Floating								= GLFW_FALSE				   ;
//	temp.Maximized								= GLFW_FALSE				   ;
//	temp.Minimized								= GLFW_FALSE				   ;
//	temp.Visible								= GLFW_TRUE					   ;
//	temp.ScaleToMonitor							= GLFW_FALSE				   ;
//	temp.CenterCursor							= GLFW_TRUE					   ;
//	temp.FocusOnShow							= GLFW_TRUE					   ;
//	temp.Hovered								= GLFW_FALSE				   ;
//	temp.Context = this->m_default_context_properties();
//	temp.RefreshRate							= GLFW_DONT_CARE			   ;
//	return temp;
//}
//
//integer system_window::m_set_attrib(integer aname, integer aval) {
//	switch (aname) {
//	default: return -1;
//	case GLFW_AUTO_ICONIFY		:	Property.AutoMinimize		= aval;		break;
//	case GLFW_RESIZABLE			:	Property.Resizable			= aval;		break;
//	case GLFW_DECORATED			:	Property.Decorated			= aval;		break;
//	case GLFW_FLOATING			:	Property.Floating			= aval;		break;
//	case GLFW_FOCUS_ON_SHOW		:	Property.FocusOnShow		= aval;		break;
//	}
//	return 0;
//}
//
//integer system_window::m_get_attrib(integer aname) {
//	switch (aname) {
//	default: return -1;
//	case GLFW_FOCUSED:							return Property.UserFocused					;
//	case GLFW_ICONIFIED:						return Property.Minimized					;
//	case GLFW_VISIBLE:							return Property.Visible						;
//	case GLFW_MAXIMIZED:						return Property.Maximized					;
//	case GLFW_HOVERED:							return Property.Hovered						;
//	case GLFW_FOCUS_ON_SHOW:					return Property.FocusOnShow					;
//	case GLFW_TRANSPARENT_FRAMEBUFFER:			return Property.Frame.Transparent			;
//	case GLFW_RESIZABLE:						return Property.Resizable					;
//	case GLFW_DECORATED:						return Property.Decorated					;
//	case GLFW_FLOATING:							return Property.Floating					;
//	case GLFW_AUTO_ICONIFY:						return Property.AutoMinimize				;
//	case GLFW_CLIENT_API:						return Property.Context.ClientAPI			;
//	case GLFW_CONTEXT_CREATION_API:				return Property.Context.CreationAPI			;
//	case GLFW_CONTEXT_VERSION_MAJOR:			return Property.Context.Version.x			;
//	case GLFW_CONTEXT_VERSION_MINOR:			return Property.Context.Version.y			;
//	case GLFW_CONTEXT_ROBUSTNESS:				return Property.Context.Robustness			;
//	case GLFW_OPENGL_FORWARD_COMPAT:			return Property.Context.ForwardCompat		;
//	case GLFW_OPENGL_DEBUG_CONTEXT:				return Property.Context.DebugMode			;
//	case GLFW_OPENGL_PROFILE:					return Property.Context.Profile				;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR:			return Property.Context.ReleaseBehavior		;
//	case GLFW_CONTEXT_NO_ERROR:					return Property.Context.NoError				;
//    }
//}
//
//integer system_window::m_set_hint(integer hname, integer hval) {
//	switch(hname) {
//	default: return -1;
//	case GLFW_RED_BITS						: Property.Frame.ColorBits.r					= hval	;	break;
//	case GLFW_GREEN_BITS					: Property.Frame.ColorBits.g					= hval	;	break;
//	case GLFW_BLUE_BITS						: Property.Frame.ColorBits.b					= hval	;	break;
//	case GLFW_ALPHA_BITS					: Property.Frame.ColorBits.a					= hval	;	break;
//	case GLFW_DEPTH_BITS					: Property.Frame.DepthBits						= hval	;	break;
//	case GLFW_STENCIL_BITS					: Property.Frame.StencilBits					= hval	;	break;
//	case GLFW_ACCUM_RED_BITS				: Property.Frame.AccumColorBits.r				= hval  ;   break;
//	case GLFW_ACCUM_GREEN_BITS				: Property.Frame.AccumColorBits.g				= hval  ;   break;
//	case GLFW_ACCUM_BLUE_BITS				: Property.Frame.AccumColorBits.b				= hval  ;   break;
//	case GLFW_ACCUM_ALPHA_BITS				: Property.Frame.AccumColorBits.a				= hval  ;   break;
//	case GLFW_AUX_BUFFERS					: Property.Frame.AuxBuffers						= hval  ;   break;
//	case GLFW_STEREO						: Property.Frame.Stereo							= hval	;	break;
//	case GLFW_DOUBLEBUFFER					: Property.Frame.DoubleBuffer					= hval	;	break;
//	case GLFW_TRANSPARENT_FRAMEBUFFER		: Property.Frame.Transparent					= hval  ;   break;
//	case GLFW_SAMPLES						: Property.Frame.Samples						= hval	;	break;
//	case GLFW_SRGB_CAPABLE					: Property.Frame.sRGBCapable					= hval	;	break;
//	case GLFW_RESIZABLE						: Property.Resizable							= hval	;	break;
//	case GLFW_DECORATED						: Property.Decorated							= hval	;	break;
//	case GLFW_FOCUSED						: Property.UserFocused							= hval	;	break;
//	case GLFW_AUTO_ICONIFY					: Property.AutoMinimize							= hval	;	break;
//	case GLFW_FLOATING						: Property.Floating								= hval	;	break;
//	case GLFW_MAXIMIZED						: Property.Maximized							= hval	;	break;
//	case GLFW_VISIBLE						: Property.Visible								= hval	;	break;
//	case GLFW_SCALE_TO_MONITOR				: Property.ScaleToMonitor						= hval  ;   break;
//	case GLFW_CENTER_CURSOR					: Property.CenterCursor							= hval  ;   break;
//	case GLFW_FOCUS_ON_SHOW					: Property.FocusOnShow							= hval  ;   break;
//	case GLFW_CLIENT_API             		: Property.Context.ClientAPI					= hval	;	break;
//	case GLFW_CONTEXT_CREATION_API   		: Property.Context.CreationAPI					= hval	;	break;
//	case GLFW_CONTEXT_VERSION_MAJOR  		: Property.Context.Version.x					= hval	;	break;
//	case GLFW_CONTEXT_VERSION_MINOR  		: Property.Context.Version.y					= hval	;	break;
//	case GLFW_CONTEXT_ROBUSTNESS     		: Property.Context.Robustness					= hval	;	break;
//	case GLFW_OPENGL_FORWARD_COMPAT  		: Property.Context.ForwardCompat				= hval	;	break;
//	case GLFW_OPENGL_DEBUG_CONTEXT   		: Property.Context.DebugMode					= hval	;	break;
//	case GLFW_CONTEXT_NO_ERROR       		: Property.Context.NoError						= hval	;	break;
//	case GLFW_OPENGL_PROFILE         		: Property.Context.Profile						= hval	;	break;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR		: Property.Context.ReleaseBehavior				= hval	;	break;
//	case GLFW_REFRESH_RATE					: Property.RefreshRate							= hval	;	break;
//	}
//	return 0;
//}
//
//integer system_window::m_get_hint(integer hname) {
//	switch(hname) {
//	default: return -1;
//	case GLFW_RED_BITS						: return Property.Frame.ColorBits.r				;
//	case GLFW_GREEN_BITS					: return Property.Frame.ColorBits.g				;
//	case GLFW_BLUE_BITS						: return Property.Frame.ColorBits.b				;
//	case GLFW_ALPHA_BITS					: return Property.Frame.ColorBits.a				;
//	case GLFW_DEPTH_BITS					: return Property.Frame.DepthBits				;
//	case GLFW_STENCIL_BITS					: return Property.Frame.StencilBits				;
//	case GLFW_ACCUM_RED_BITS				: return Property.Frame.AccumColorBits.r		;
//	case GLFW_ACCUM_GREEN_BITS				: return Property.Frame.AccumColorBits.g		;
//	case GLFW_ACCUM_BLUE_BITS				: return Property.Frame.AccumColorBits.b		;
//	case GLFW_ACCUM_ALPHA_BITS				: return Property.Frame.AccumColorBits.a		;
//	case GLFW_AUX_BUFFERS					: return Property.Frame.AuxBuffers				;
//	case GLFW_STEREO						: return Property.Frame.Stereo					;
//	case GLFW_DOUBLEBUFFER					: return Property.Frame.DoubleBuffer			;
//	case GLFW_TRANSPARENT_FRAMEBUFFER		: return Property.Frame.Transparent				;
//	case GLFW_SAMPLES						: return Property.Frame.Samples					;
//	case GLFW_SRGB_CAPABLE					: return Property.Frame.sRGBCapable				;
//	case GLFW_RESIZABLE						: return Property.Resizable						;
//	case GLFW_DECORATED						: return Property.Decorated						;
//	case GLFW_FOCUSED						: return Property.UserFocused					;
//	case GLFW_AUTO_ICONIFY					: return Property.AutoMinimize					;
//	case GLFW_FLOATING						: return Property.Floating						;
//	case GLFW_MAXIMIZED						: return Property.Maximized						;
//	case GLFW_VISIBLE						: return Property.Visible						;
//	case GLFW_SCALE_TO_MONITOR				: return Property.ScaleToMonitor				;
//	case GLFW_CENTER_CURSOR					: return Property.CenterCursor					;
//	case GLFW_FOCUS_ON_SHOW					: return Property.FocusOnShow					;
//	case GLFW_CLIENT_API             		: return Property.Context.ClientAPI				;
//	case GLFW_CONTEXT_CREATION_API   		: return Property.Context.CreationAPI			;
//	case GLFW_CONTEXT_VERSION_MAJOR  		: return Property.Context.Version.x				;
//	case GLFW_CONTEXT_VERSION_MINOR  		: return Property.Context.Version.y				;
//	case GLFW_CONTEXT_ROBUSTNESS     		: return Property.Context.Robustness			;
//	case GLFW_OPENGL_FORWARD_COMPAT  		: return Property.Context.ForwardCompat			;
//	case GLFW_OPENGL_DEBUG_CONTEXT   		: return Property.Context.DebugMode				;
//	case GLFW_CONTEXT_NO_ERROR       		: return Property.Context.NoError				;
//	case GLFW_OPENGL_PROFILE         		: return Property.Context.Profile				;
//	case GLFW_CONTEXT_RELEASE_BEHAVIOR		: return Property.Context.ReleaseBehavior		;
//	case GLFW_REFRESH_RATE					: return Property.RefreshRate					;
//	}
//}
