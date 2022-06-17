#include <geodesuka/engine.h>
#include <geodesuka/core/stage.h>

namespace geodesuka::core {

	// Base destructor.
	stage_t::~stage_t() {
		// If engine is in destruction state, do not attempt to remove from engine.
		//isReadyToBeProcessed.store(false);
		if (Engine->StateID != engine::state::id::DESTRUCTION) {
			// Removes Object from Engine State.
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(true);
				Engine->ThreadTrap.wait_until(2);
			}
			// Finds object in engine, and removes it.
			for (size_t i = 0; i < Engine->Stage.size(); i++) {
				if (Engine->Stage[i] == this) {
					Engine->Stage.erase(Engine->Stage.begin() + i);
				}
			}
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(false);
			}
		}
	}


	// Base constructor.
	stage_t::stage_t(engine* aEngine, gcl::context* aContext) {
		Engine				= aEngine;
		Context				= aContext;

		isReadyToBeProcessed.store(false);
		if (Engine->StateID != engine::state::id::CREATION) {
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(true);
				Engine->ThreadTrap.wait_until(2);
			}
			Engine->Stage.push_back(this);
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(false);
			}
		}
	}

	int stage_t::generate_renderops() {
		for (size_t i = 0; i < this->Object.size(); i++) {
			for (size_t j = 0; j < this->RenderTarget.size(); j++) {
				this->Object[i]->generate_renderops(this->RenderTarget[j]);
			}
		}
		return 0;
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

	/* Legacy Code, code should be runtime changeble. */
	//gcl::command_batch stage_t::render() {
	//	gcl::command_batch Batch;
	//	this->Mutex.lock();
	//	// Iterate through render targets and gather render commands.
	//	for (size_t i = 0; i < this->RenderTarget.size(); i++) {
	//		// Check if time to perform render operations on render target.
	//		if (!this->RenderTarget[i]->isReadyToBeProcessed.load()) continue;
	//		if (this->RenderTarget[i]->FrameRateTimer.check_and_reset()) {
	//			// Acquire next available frame from target.
	//			this->RenderTarget[i]->next_frame();

	//			// Use next_frame semaphore to pause render operations until
	//			Batch += this->RenderTarget[i]->draw(this->Object.size(), this->Object.data());

	//			// Use Submission Semaphore to hold present.
	//			Batch += this->RenderTarget[i]->present_frame();
	//		}
	//	}
	//	this->Mutex.unlock();
	//	return Batch;
	//}

	gcl::command_batch stage_t::render() {
		gcl::command_batch Batch;
		this->Mutex.lock();
		// Iterate through render targets and gather render commands.
		for (size_t i = 0; i < this->RenderTarget.size(); i++) {
			// Check if time to perform render operations on render target.
			if (!this->RenderTarget[i]->isReadyToBeProcessed.load()) continue;
			// Check if rendertarget is ready to render parent stage.
			if (this->RenderTarget[i]->FrameRateTimer.check_and_reset()) {
				// 
				
				// Render target calls user specific stage rendering methods.
				//this->RenderTarget[i]->render(this);
			}
		}
		this->Mutex.unlock();
		return Batch;
	}

}
