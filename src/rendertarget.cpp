#include <geodesuka/core/object/rendertarget.h>

namespace geodesuka::core::object {

	rendertarget::~rendertarget() {

	}

	rendertarget::rendertarget(engine* aEngine, gcl::context* aContext, stage_t* aStage) : object_t(aEngine, aContext, aStage) {

		this->FrameCount = 0;
		this->FrameRate = 0.0;
		this->FPSTimer.set(1.0 / this->FrameRate);
		//this->Resolution = math::natural2(0, 0);
		this->Resolution = uint2(0, 0);

		this->FrameAttachmentCount = 0;
		this->FrameAttachmentDescription = NULL;
		this->FrameAttachment = NULL;

		this->FrameDrawIndex = 0;
	}

	VkSemaphore rendertarget::next_frame() {
		this->Mutex.lock();
		this->FrameDrawIndex = ((this->FrameDrawIndex == (this->FrameCount - 1)) ? 0 : (this->FrameDrawIndex + 1));
		this->Mutex.unlock();
		return VK_NULL_HANDLE;
	}

	VkPresentInfoKHR rendertarget::present_frame(uint32_t aWaitSemaphoreCount, VkSemaphore* aWaitSemaphoreList) {
		VkPresentInfoKHR PresentInfo;
		PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		PresentInfo.pNext = NULL;

		return PresentInfo;
	}

}
