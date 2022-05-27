#include <geodesuka/core/object/rendertarget.h>

namespace geodesuka::core::object {

	rendertarget::~rendertarget() {

	}

	rendertarget::rendertarget(engine* aEngine, gcl::context* aContext, stage_t* aStage/*, int aFrameCount, double aFrameRate*/) : 
		object_t(aEngine, aContext, aStage), 
		DrawCommandPool(aContext, 0, gcl::device::qfs::GRAPHICS_AND_COMPUTE)
	{

		this->FrameCount = 0;
		this->FrameRate = 0.0;
		this->FrameRateTimer.set(0.0);
		this->Resolution = uint3(0u, 0u, 0u);

		this->FrameAttachmentCount = 0;
		this->FrameAttachmentDescription = NULL;
		this->FrameAttachment = NULL;

		//this->FrameReadIndex = 0;
		this->FrameDrawIndex = 0;

		this->DrawCommandCount = NULL;
		this->DrawCommandList = NULL;
	}

	void rendertarget::next_frame() {
		this->Mutex.lock();
		//this->FrameReadIndex = this->FrameDrawIndex;
		this->FrameDrawIndex = ((this->FrameDrawIndex == (this->FrameCount - 1)) ? 0 : (this->FrameDrawIndex + 1));
		this->Mutex.unlock();
	}

	VkPresentInfoKHR rendertarget::present_frame() {
		// Is left empty, because it is not used for anything besides system_window.
		VkPresentInfoKHR PresentInfo{};
		PresentInfo.sType					= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		PresentInfo.pNext					= NULL;
		PresentInfo.waitSemaphoreCount		= 0;
		PresentInfo.pWaitSemaphores			= NULL;
		PresentInfo.swapchainCount			= 0;
		PresentInfo.pSwapchains				= NULL;
		PresentInfo.pImageIndices			= NULL;
		PresentInfo.pResults				= NULL;
		return PresentInfo;
	}

}
