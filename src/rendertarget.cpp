#include <geodesuka/core/object/rendertarget.h>

namespace geodesuka::core::object {

	rendertarget::~rendertarget() {

	}

	rendertarget::rendertarget(engine* aEngine, gcl::context* aContext) : object_t(aEngine, aContext) {

		this->FrameCount = 0;
		this->FrameRate = 0.0;
		this->FPSTimer.set(1.0 / this->FrameRate);
		//this->Resolution = math::natural2(0, 0);
		this->Resolution.x = 0;
		this->Resolution.y = 0;

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

	void rendertarget::present_frame(uint32_t aWaitSemaphoreCount, VkSemaphore* aWaitSemaphoreList) {
	}

}
