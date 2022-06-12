#include <geodesuka/engine.h>

#include <geodesuka/core/object.h>
#include <geodesuka/core/object/system_display.h>
#include <geodesuka/core/object/system_window.h>
#include <geodesuka/core/object/system_display.h>
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
		VkCommandBuffer ReturnDrawCommand = VK_NULL_HANDLE;
		this->Mutex.lock();
		/*(this->DrawCommand.find(aRenderTarget) != this->DrawCommand.end())*/
		if (this->DrawCommand.count(aRenderTarget) != 0) {
			ReturnDrawCommand = this->DrawCommand[aRenderTarget][aRenderTarget->FrameDrawIndex];
		}
		this->Mutex.unlock();
		return ReturnDrawCommand;
	}

	// Discriminator for generic render targets. Only works for built in rendertargets.
	// User is free to create new render targets if he/she/they wish to expand.
	void object_t::generate_draw_commands(object::rendertarget* aRenderTarget) {
		this->Mutex.lock();
		// Return previously generated command buffers to render target.
		if (this->DrawCommand.count(aRenderTarget) != 0) {
			// Command Buffers have already been created, delete.
			if (this->DrawCommand[aRenderTarget] != NULL) {
				// TODO: insure that command buffers aren't destroyed while in use.
				// Return command buffers to command pool.
				aRenderTarget->DrawCommandPool.release(aRenderTarget->FrameCount, this->DrawCommand[aRenderTarget]);
			}
			free(this->DrawCommand[aRenderTarget]);
			this->DrawCommand.erase(aRenderTarget);
		}

		VkResult Result = VkResult::VK_ERROR_UNKNOWN;

		// Generate new pair for render target.
		std::pair<object::rendertarget*, VkCommandBuffer*> NewPair = std::pair<object::rendertarget*, VkCommandBuffer*>(aRenderTarget, NULL);
		// Allocate space for command buffers, one for each frame.
		NewPair.second = (VkCommandBuffer*)malloc(aRenderTarget->FrameCount * sizeof(VkCommandBuffer));
		// Allocate command buffers for rendering.
		if (NewPair.second != NULL) {
			// TODO: Check for Errors
			Result = aRenderTarget->DrawCommandPool.allocate(VK_COMMAND_BUFFER_LEVEL_PRIMARY, aRenderTarget->FrameCount, NewPair.second);
		}

		// Insert if allocation succesful.
		if (Result == VkResult::VK_SUCCESS) {
			this->DrawCommand.insert(NewPair);
		}

		// Determine the type of render target, then record commands.
		aRenderTarget->DrawCommandPool.Mutex.lock();
		switch (aRenderTarget->rtid()) {
		default:
			break;
		case object::system_display::RTID:
			this->generate_draw_commands((object::system_display*)aRenderTarget);
			break;
		case object::system_window::RTID:
			this->generate_draw_commands((object::system_window*)aRenderTarget);
			break;
		case object::virtual_window::RTID:
			this->generate_draw_commands((object::virtual_window*)aRenderTarget);
			break;
		case object::camera2d::RTID:
			this->generate_draw_commands((object::camera2d*)aRenderTarget);
			break;
		case object::camera3d::RTID:
			this->generate_draw_commands((object::camera3d*)aRenderTarget);
			break;
		}
		aRenderTarget->DrawCommandPool.Mutex.unlock();
		this->Mutex.unlock();
	}

	void object_t::generate_draw_commands(object::system_display* aSystemDisplay) {
	}

	void object_t::generate_draw_commands(object::system_window* aSystemWindow) {

	}

	void object_t::generate_draw_commands(object::virtual_window* aVirtualWindow) {

	}

	void object_t::generate_draw_commands(object::camera2d* aCamera2D) {

	}

	// This section of the code will define the default renderer.
	void object_t::generate_draw_commands(object::camera3d* aCamera3D) {
		for (uint32_t i = 0; i < aCamera3D->FrameCount; i++) {
			VkResult Result = VkResult::VK_SUCCESS;

			VkCommandBuffer CommandBuffer = this->DrawCommand[aCamera3D][i];
			VkCommandBufferBeginInfo CommandBufferBeginInfo{};
			VkRenderPassBeginInfo RenderPassBeginInfo{};

			CommandBufferBeginInfo.sType				= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			CommandBufferBeginInfo.pNext				= NULL;
			CommandBufferBeginInfo.flags				= 0;
			CommandBufferBeginInfo.pInheritanceInfo		= NULL;

			RenderPassBeginInfo.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			RenderPassBeginInfo.pNext					= NULL;
			RenderPassBeginInfo.renderPass				;
			RenderPassBeginInfo.framebuffer				;
			RenderPassBeginInfo.renderArea				;
			RenderPassBeginInfo.clearValueCount			;
			RenderPassBeginInfo.pClearValues			;

			// Record Draw Commands

			
			Result = vkBeginCommandBuffer(CommandBuffer, &CommandBufferBeginInfo);

			vkCmdBeginRenderPass(CommandBuffer, &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
			//vkCmdBindPipeline(CommandBuffer,)
			//vkCmdBindDescriptorSets();
			//vkCmdBindVertexBuffers();
			//vkCmdBindIndexBuffer();
			vkCmdEndRenderPass(CommandBuffer);

			Result = vkEndCommandBuffer(CommandBuffer);
		}
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