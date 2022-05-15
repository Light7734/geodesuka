#pragma once
#ifndef GEODESUKA_CORE_OBJECT_H
#define GEODESUKA_CORE_OBJECT_H

// ------------------------------ object.h ------------------------------ //
/*
* object.h will serve as a generic object that is extendable for the user
* to implement custom object derivative classes. cube.h is an example of this
* and more examples will be provided. The difference here is that the extended
* classes of object.h will have full control over how they will be rendered to
* the target window.h or camera.h object.
* 
* Since an object will have part of itself associated with memory objects
* of particular GPUs, it is important to recognize that objects exist within
* a common space in which they are rendered. On top of that, a rendering context
* will indicate which graphics capable device it exists on. Maybe figure out
* how to stream line 
*/

#include <mutex>
#include <map>

#include "./math.h"

#include "gcl/device.h"
#include "gcl/context.h"

#include "graphics/mesh.h"
#include "graphics/material.h"
#include "graphics/model.h"

#include "hid/keyboard.h"
#include "hid/mouse.h"
#include "hid/joystick.h"

namespace geodesuka::core {

	class stage_t;

	namespace object {
		class rendertarget;
	}

	class object_t {
	public:

		friend class engine;
		friend class object::rendertarget;
		
		virtual ~object_t() /*= default*/;

		virtual void set_position(float3 aPosition);
		float3 get_position() const;

		/*
		* This function will be called by a particular rendertarget to gather Draw Commands
		* from the object in question. Base object class must provide default render methods for generic
		* runtime data.
		*/
		// This is public for rendertargets to access object draw commands.
		// This is public because it is needed for user defined rendertargets.
		virtual VkCommandBuffer draw(object::rendertarget* aRenderTarget);

	protected:

		// Used for shared usage between Engine & App.
		std::mutex Mutex;
		std::atomic<bool> isReady;

		// Parent Item References
		engine* Engine;
		gcl::context* Context;
		stage_t* Stage;

		/*
		* Do not forget, position is in reference to a particular space
		* the object is in. This is up to the user to decide how to
		* interpret and use an objects position.
		*/

		float3 InputVelocity;
		float3 InputForce;

		float Mass;				// Kilogram		[kg]
		float Time;				// Second 		[s]
		float3 Position;		// Meter		[m]
		float3 Momentum;		//				[kg*m/s]
		float3 Force;			// Newton		[kg*m^2/s^2]
		float3 DirectionX;		// Right		[Normalized]
		float3 DirectionY;		// Up			[Normalized]
		float3 DirectionZ;		// Forward		[Normalized]

		//boolean isStationary;			// Is this object stationary, or is it allowed to move?
		//boolean isDeterministic;		// Does this object have predefined motion?
		//boolean isAnimate;				// Is this object a living creature?
		//boolean isPickup;				// Can an entitiy pick up this object?

		//boolean isCollisionActive;
		//boolean isGraphicalActive;

		object_t(engine *aEngine, gcl::context *aContext, stage_t* aStage);

		/*
		* If input stream is being forwarded to a particular instance of an object,
		* this method will be called depending on input recieved by the engine. This
		* method is effectively a forwarded callback stream for the particular instance
		* of the object.
		*/
		virtual void input(const hid::keyboard& aKeyboard);

		/*
		* Basically a call back as well, but uses mouse info instead.
		*/
		virtual void input(const hid::mouse& aMouse);

		/*
		* The implementation of this method will allow the object to internally time evolve
		* itself with a provided time step. It will be the responsibility of the engine
		* to insure that the time step remains stable.
		*/
		virtual VkSubmitInfo update(double aDeltaTime);

		/*
		* Will produce compute operation submissions.
		*/
		virtual VkSubmitInfo compute();

	};


}

#endif // !GEODESUKA_CORE_OBJECT_H
