#pragma once
#ifndef GEODESUKA_BUILTIN_OBJECT_CUBE_H
#define GEODESUKA_BUILTIN_OBJECT_CUBE_H

/*
// -------------------------------------------------- cube.h -------------------------------------------------- \\
This object should serve as an example of how to extend "object.h" to create custom objects which can be used
with the game engine. As of right now there are four types of windows that can be drawn to. When object.h is
extended, the derivative class has full control over how the particular derived class is drawn to the target
window.


\\ -------------------------------------------------- cube.h -------------------------------------------------- //
*/

#include <geodesuka/engine.h>

namespace geodesuka::builtin::object {

	class cube : public core::object_t {
	public:

		//buffer* VertexBuffer;
		//buffer* IndexBuffer;

		//shader* VertexShader;
		//shader* PixelShader;

		//cube(engine* aEngine, core::gcl::context* aContext, stage_t* aStage);
		//~cube();

		//virtual void input(const core::hid::keyboard& aKeyboard)					override;
		//virtual void input(const core::hid::mouse& aMouse)							override;

		//virtual void update(double aDeltaTime)										override;

		//// Specifies how cube will be drawn to these respective targets
		//virtual void draw(core::object::system_display* aTargetSystemDisplay)		override;
		//virtual void draw(core::object::system_window* aTargetSystemWindow)			override;
		//virtual void draw(core::object::virtual_window* aTargetVirtualWindow)		override;

		//virtual void draw(core::object::camera2d* aTargetCamera2D)					override;
		//virtual void draw(core::object::camera3d* aTargetCamera3D)					override;

	};

}

#endif // !GEODESUKA_BUILTIN_OBJECT_CUBE_H
