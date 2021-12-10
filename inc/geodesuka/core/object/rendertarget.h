#pragma once
#ifndef GEODESUKA_CORE_OBJECT_RENDERTARGET_H
#define GEODESUKA_CORE_OBJECT_RENDERTARGET_H

#include <vector>

#include "../gcl.h"
#include "../gcl/context.h"
#include "../gcl/texture.h"

#include "../logic/timer.h"

#include "../object.h"

/*
* For a class to be considered a render_target, it must be able to
* be drawn to and must have attachments to be drawn to. How exactly
* a render_target is drawn to is decided by the user, and not the 
* engine API.
*/

namespace geodesuka::core::stage {
	class canvas;
	class scene2d;
	class scene3d;
}

namespace geodesuka::core::object {

	class rendertarget : public object_t {
	public:

		//friend class stage_t;
		friend class stage::canvas;
		friend class stage::scene2d;
		friend class stage::scene3d;

		// Might move this somewhere else.
		struct submission {

			submission();
			submission(VkCommandBuffer aCommandBuffer);
			submission(uint32_t aCommandBufferCount, VkCommandBuffer* aCommandBuffer);
			submission(const submission& aInput);
			submission(submission&& aInput);
			~submission();

			submission& operator=(const submission& aRhs);
			submission& operator=(submission&& aRhs);

			submission& operator+=(const submission& aRhs);
			submission& operator+=(submission&& aRhs);
			submission& operator+=(VkCommandBuffer aRhs);


			VkSubmitInfo info();
		private:
			uint32_t CommandBufferCount;
			VkCommandBuffer *CommandBuffer;
		};


		int FrameCount;					// The total number of back buffer frames of the rendertarget.
		double FramesPerSecond;			// The rate at which the frames will be cycled through by the engine.
		math::natural2 Resolution;		// The grid resolution of every frame and frame attachment of the rendertarget.
		
		int FrameAttachmentCount;									// The number of attachments for each frame.
		VkAttachmentDescription* FrameAttachmentDescription;		// The attachment descriptions of each frame.
		VkImageView** FrameAttachment;								// The image view handles of each frame attachment.

		int FrameDrawIndex;
		//int FrameReadIndex;


		~rendertarget();

		void set_framerate(double aFPS);

		double framerate();

	protected:

		rendertarget(engine* aEngine, gcl::context* aContext);

		// Propose a collection of objects (Most likely from a stage), to 
		// draw those objects to the render target. The objects will
		// produce user implemented draw commands to the rendertarget
		// for aggregation and eventual execution by the geodesuka engine.
		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) = 0;

		//virtual void swap() = 0;

	private:

		logic::timer RefreshTimer;

	};
}

#endif // !GEODESUKA_CORE_OBJECT_RENDERTARGET_H
