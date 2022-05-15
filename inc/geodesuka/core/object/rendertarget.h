#pragma once
#ifndef GEODESUKA_CORE_OBJECT_RENDERTARGET_H
#define GEODESUKA_CORE_OBJECT_RENDERTARGET_H

#include <vector>

#include "../gcl.h"
#include "../gcl/context.h"
#include "../gcl/texture.h"

#include "../gcl/command_list.h"
#include "../gcl/command_batch.h"

#include "../logic/timer.h"

#include "../object.h"

/*
* For a class to be considered a render_target, it must be able to
* be drawn to and must have attachments to be drawn to. How exactly
* a render_target is drawn to is decided by the user, and not the 
* engine API.
*/



/*

// Gets next frame.
vkAcquireNextImageKHR(SignalSemaphore, Index);

Result = vkAcquireNextImageKHR(
	Context->handle(), 
	this->Swapchain->handle(), 
	0,
	FrameDrawIndexSemaphore, 
	VkFence fence, 
	&this->FrameDrawIndex
);

// 
vkQueueSubmit(SubmissionList, SignalSemaphore);

PresentInfo.sType				;
PresentInfo.pNext				;
PresentInfo.waitSemaphoreCount	;
PresentInfo.pWaitSemaphores		= ;
PresentInfo.swapchainCount		= 1;
PresentInfo.pSwapchains			= &this->Swapchain;
PresentInfo.pImageIndices		= &this->FrameDrawIndex;
PresentInfo.pResults			= &Result;

vkQueuePresentKHR(Present Image)

*/

namespace geodesuka::core::object {

	class rendertarget : public object_t {
	public:

		//friend class engine;
		friend class stage_t;

		//VkPresentInfoKHR;
		class presentation {

			// Will generate 
			VkPresentInfoKHR info(uint32_t aWaitSemaphoreCount, VkSemaphore* aWaitSemaphoreList);

		private:
			uint32_t Count;
			VkSwapchainKHR *Swapchain;
			uint32_t *ImageIndex;
			VkResult *Result;
		};

		int FrameCount;					// The total number of back buffer frames of the rendertarget.
		double FrameRate;				// The rate at which the frames will be cycled through by the engine per second.
		logic::timer FPSTimer;
		uint2 Resolution;				// [Pixels] The grid resolution of every frame and frame attachment of the rendertarget.
		
		int FrameAttachmentCount;									// The number of attachments for each frame.
		VkAttachmentDescription* FrameAttachmentDescription;		// The attachment descriptions of each frame.
		VkImageView** FrameAttachment;								// The image view handles of each frame attachment.

		// Must be used 
		VkSemaphore FrameDrawIndexSemaphore;
		// This index specifies the 
		uint32_t FrameDrawIndex;
		//int FrameReadIndex;


		~rendertarget();

		// Used for runtime rendertarget discrimination.
		virtual int rtid() = 0;

		// -------------------- Called By Stage.render() ------------------------- \\

		// Will acquire next frame index, if semephore is not VK_NULL_HANDLE, 
		// use as wait semaphore for render operations. This really only applies
		// to a system_window.
		virtual VkSemaphore next_frame();

		// Propose a collection of objects (Most likely from a stage), to 
		// draw those objects to the render target. The objects will
		// produce user implemented draw commands to the rendertarget
		// for aggregation and eventual execution by the geodesuka engine.
		virtual VkSubmitInfo draw(size_t aObjectCount, object_t** aObject) = 0;

		// This will present VKPresentInfoKHR. Must use a semaphore to make presentation
		// dependant on rendering operations to complete.
		virtual VkPresentInfoKHR present_frame(uint32_t aWaitSemaphoreCount, VkSemaphore* aWaitSemaphoreList);

	protected:

		// Derived classes can use this aggregate draw commands from objects.
		//submission* Submission;

		rendertarget(engine* aEngine, gcl::context* aContext, stage_t* aStage);


		// Will update to new draw index for rendering operations.
		virtual void swap() = 0;

	private:


	};
}

#endif // !GEODESUKA_CORE_OBJECT_RENDERTARGET_H
