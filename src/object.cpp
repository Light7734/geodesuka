#include <geodesuka/engine.h>
#include <geodesuka/core/object.h>

namespace geodesuka::core {

	object_t::object_t(engine* aEngine, gcl::context* aContext, stage_t* aStage) {
		this->isReady.store(false);
		this->Engine->State->Object.push_back(this);


		// Internal API.
		this->Engine = aEngine;
		this->Context = aContext;
		this->Stage = aStage;

		this->InputVelocity = float3(0.0, 0.0, 0.0);
		this->InputForce	= float3(0.0, 0.0, 0.0);

		this->Mass			= 1.0;
		this->Time			= core::logic::get_time();
		this->Position		= float3(0.0, 0.0, 0.0);
		this->Momentum		= float3(0.0, 0.0, 0.0);
		this->Force			= float3(0.0, 0.0, 0.0);
		this->DirectionX	= float3(1.0, 0.0, 0.0);
		this->DirectionY	= float3(0.0, 1.0, 0.0);
		this->DirectionZ	= float3(0.0, 0.0, 1.0);
	}

	object_t::~object_t() {
		// Removes Object from Engine State.
		if (this->Engine->State->ID != engine::state::id::DESTRUCTION) {
			int Index = this->Engine->State->objidx(this);
			this->Engine->State->Object.erase(this->Engine->State->Object.begin() + Index);
		}
	}

	void object_t::set_position(float3 aPosition) {}

	float3 object_t::get_position() const {
		return this->Position;
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
		this->Momentum += (this->Force + this->InputForce) * aDeltaTime;
		this->Position += ((this->Momentum / this->Mass) + this->InputVelocity) * aDeltaTime;


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

	VkCommandBuffer object_t::draw(object::rendertarget* aRenderTarget){
		VkCommandBuffer DrawCommand = VK_NULL_HANDLE;
		return DrawCommand;
	}

}