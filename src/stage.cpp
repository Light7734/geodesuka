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
			this->RenderTarget[i]->FrameRateTimer.update(aDeltaTime);
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

	void stage_t::render() {
		gcl::command_batch Batch;
		this->Mutex.lock();
		for (size_t i = 0; i < this->RenderTarget.size(); i++) {
			// Check if time to perform render operations on render target.
			if (this->RenderTarget[i]->FrameRateTimer.check()) {
				// Reset ellapsed timer.
				this->RenderTarget[i]->FrameRateTimer.reset();

				// Two are only relevant to system_window
				//vkAcquireNextImageKHR();
				//vkQueueSubmit();
				//vkQueuePresentKHR();

				// Acquire next available frame from target.
				this->RenderTarget[i]->next_frame();

				// Use next_frame semaphore to pause render operations until
				this->RenderTarget[i]->draw(this->Object.size(), this->Object.data());

				VkPresentInfoKHR;
				// Use Submission Semaphore to hold present.
				this->RenderTarget[i]->present_frame();
			}
		}
		this->Mutex.unlock();
	}

}