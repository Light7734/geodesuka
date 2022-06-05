#include <geodesuka/engine.h>
#include <geodesuka/core/object.h>

namespace geodesuka::core {

	object_t::object_t(engine* aEngine, gcl::context* aContext, stage_t* aStage) {

		// Internal API.
		Engine = aEngine;
		Context = aContext;
		Stage = aStage;

		// Submit new object instance to engine.
		isReadyToBeProcessed.store(false);
		if (Engine->StateID != engine::state::id::CREATION) {
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(true);
				Engine->ThreadTrap.wait_until(2);
			}
			Engine->Object.push_back(this);
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(false);
			}
		}

		InputVelocity	= float3(0.0, 0.0, 0.0);
		InputForce		= float3(0.0, 0.0, 0.0);

		Mass			= 1.0;
		Time			= logic::get_time();
		Position		= float3(0.0, 0.0, 0.0);
		Momentum		= float3(0.0, 0.0, 0.0);
		Force			= float3(0.0, 0.0, 0.0);
		DirectionX		= float3(1.0, 0.0, 0.0);
		DirectionY		= float3(0.0, 1.0, 0.0);
		DirectionZ		= float3(0.0, 0.0, 1.0);
	}

	object_t::~object_t() {
		// If engine is in destruction state, do not attempt to remove from engine.
		this->Mutex.lock();
		if (Engine->StateID != engine::state::id::DESTRUCTION) {
			// Removes Object from Engine State.
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(true);
				Engine->ThreadTrap.wait_until(2);
			}
			// Finds object in engine, and removes it.
			for (size_t i = 0; i < Engine->Object.size(); i++) {
				if (Engine->Object[i] == this) {
					Engine->Object.erase(Engine->Object.begin() + i);
				}
			}
			if (Engine->StateID == engine::state::id::RUNNING) {
				Engine->ThreadTrap.set(false);
			}
		}
		this->Mutex.unlock();
	}

	void object_t::set_position(float3 aPosition) {}

	float3 object_t::get_position() const {
		return this->Position;
	}

	VkCommandBuffer object_t::draw(object::rendertarget* aRenderTarget) {
		VkCommandBuffer DrawCommand = VK_NULL_HANDLE;
		this->Mutex.lock();
		if (DrawPack.count(aRenderTarget) > 0) {
			DrawCommand = (*(DrawPack[aRenderTarget]))[aRenderTarget->FrameDrawIndex];
		}
		this->Mutex.unlock();
		return DrawCommand;
	}

	void object_t::input(const hid::keyboard& aKeyboard) {

	}

	void object_t::input(const hid::mouse& aMouse) {

	}

	VkSubmitInfo object_t::update(double aDeltaTime) {
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

		//tex:
		// Update equations for generic object type with applied forces.
		// $$ d\vec{p} = \big( \vec{F}_{\text{applied}} + \vec{F}_{user} \big) dt $$ 
		// $$ d \vec{x} = \big( \frac{\vec{p}}{m} + \vec{v}_{user} \big) dt $$

		this->Mutex.lock();

		// Generic Free body motion equations.
		Momentum += (Force + InputForce) * aDeltaTime;
		Position += ((Momentum / Mass) + InputVelocity) * aDeltaTime;

		this->Mutex.unlock();
		return TransferBatch;
	}

	VkSubmitInfo object_t::compute() {
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

}