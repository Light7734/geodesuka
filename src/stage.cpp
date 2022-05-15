#include <geodesuka/engine.h>
#include <geodesuka/core/stage.h>

namespace geodesuka::core {

	stage_t::stage_t(engine* aEngine, gcl::context* aContext) {


		this->Engine				= aEngine;
		this->Context				= aContext;
	}

	stage_t::~stage_t() {
		// Will be used to delete all contained
		// objects explicitly.

	}

	VkSubmitInfo stage_t::update(double aDeltaTime) {
        VkSubmitInfo TransferBatch{};
		TransferBatch.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		TransferBatch.pNext					= NULL;
		TransferBatch.waitSemaphoreCount	= 0;
		TransferBatch.pWaitSemaphores		= NULL;
		TransferBatch.pWaitDstStageMask		= NULL;
		TransferBatch.commandBufferCount	= 0;
		TransferBatch.pCommandBuffers		= NULL;
		TransferBatch.signalSemaphoreCount	= 0;
		TransferBatch.pSignalSemaphores		= NULL;
		this->Mutex.lock();
		for (size_t i = 0; i < this->RenderTarget.size(); i++) {
			this->RenderTarget[i]->FPSTimer.update(aDeltaTime);
		}
		this->Mutex.unlock();
        return TransferBatch;
    }

	VkSubmitInfo stage_t::compute() {
        VkSubmitInfo ComputeBatch{};
		ComputeBatch.sType					= VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		ComputeBatch.pNext					= NULL;
		ComputeBatch.waitSemaphoreCount		= 0;
		ComputeBatch.pWaitSemaphores		= NULL;
		ComputeBatch.pWaitDstStageMask		= NULL;
		ComputeBatch.commandBufferCount		= 0;
		ComputeBatch.pCommandBuffers		= NULL;
		ComputeBatch.signalSemaphoreCount	= 0;
		ComputeBatch.pSignalSemaphores		= NULL;

        return ComputeBatch;
	}

	void stage_t::present(uint32_t aWaitSemaphoreCount, VkSemaphore* aWaitSemaphoreList) {
		for (int i = 0; i < this->RenderTargetCount; i++) {
			if (this->RenderTarget[i]->FPSTimer.check()) {
				//this->RenderTarget[i]->swap();
				this->RenderTarget[i]->present_frame(aWaitSemaphoreCount, aWaitSemaphoreList);
				this->RenderTarget[i]->FPSTimer.reset();
			}
		}
	}

	void stage_t::submit() {
		//this->Engine->submit(this);
		this->Engine->submit(this);
	}

	stage_t::renderop stage_t::render() {
		renderop RenderOperations;
		this->Mutex.lock();
		for (int i = 0; i < this->RenderTargetCount; i++) {
			// Check if render target is ready for new draw.
			if (this->RenderTarget[i]->FPSTimer.check()) {
				// Reset timer loop.
				this->RenderTarget[i]->FPSTimer.reset();
				/*
				
				vkAcquireNextImageKHR();
				VkResult vkAcquireNextImageKHR(
					VkDevice                                    device,
					VkSwapchainKHR                              swapchain,
					uint64_t                                    timeout,
					VkSemaphore                                 semaphore,
					VkFence                                     fence,
					uint32_t*                                   pImageIndex);

				// Use semaphore to wait for next image before render operations.
				vkQueueSubmit(Graphics & Compute Operations);

				// Wait for G&C Ops to complete (Semaphore)
				vkQueuePresentKHR(Present Newly rendered frame);

				*/

				// Get Next Frame (system_window will get new image).
				this->RenderTarget[i]->next_frame();

				VkSubmitInfo Submission = this->RenderTarget[i]->draw(this->ObjectCount, this->Object);

				// Get all render operations.
				RenderOperations;

				//this->RenderTarget[i]->present_frame(aWaitSemaphoreCount, aWaitSemaphoreList);
			}
		}
		this->Mutex.unlock();
		return RenderOperations;
	}

}