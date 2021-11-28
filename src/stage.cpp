#include <geodesuka/engine.h>
#include <geodesuka/core/stage.h>

namespace geodesuka::core {

	stage_t::batch::batch() {
		this->SubmissionCount = 0;
		this->Submission = NULL;
	}

	stage_t::batch::batch(VkSubmitInfo aSubmission) {
		// Discard if no command buffers.
		if ((aSubmission.commandBufferCount > 0) && (aSubmission.pCommandBuffers != NULL)) {
			this->Submission = (VkSubmitInfo*)malloc(sizeof(VkSubmitInfo));
			if (this->Submission != NULL) {
				memcpy(this->Submission, &aSubmission, sizeof(VkSubmitInfo));
				this->SubmissionCount = 1;
			}
			else {
				this->SubmissionCount = 0;
			}
		}
		else {
			this->SubmissionCount = 0;
			this->Submission = NULL;
		}
	}

	stage_t::batch::batch(size_t aSubmissionCount, VkSubmitInfo* aSubmission) {
		if (aSubmissionCount > 0) {
			this->Submission = (VkSubmitInfo*)malloc(aSubmissionCount * sizeof(VkSubmitInfo));
			if (this->Submission != NULL) {
				this->SubmissionCount = aSubmissionCount;
				memcpy(this->Submission, aSubmission, this->SubmissionCount * sizeof(VkSubmitInfo));
			}
			else {
				this->SubmissionCount = 0;
			}
		}
		else {
			this->SubmissionCount = 0;
			this->Submission = NULL;
		}
	}

	stage_t::batch::batch(batch& aInput) {
		if (aInput.SubmissionCount > 0) {
			this->Submission = (VkSubmitInfo*)malloc(aInput.SubmissionCount * sizeof(VkSubmitInfo));
			if (this->Submission != NULL) {
				this->SubmissionCount = aInput.SubmissionCount;
				memcpy(this->Submission, aInput.Submission, this->SubmissionCount * sizeof(VkSubmitInfo));
			}
			else {
				this->SubmissionCount = 0;
			}
		}
		else {
			this->SubmissionCount = 0;
			this->Submission = NULL;
		}
	}

	stage_t::batch::batch(batch&& aInput) noexcept {
		this->SubmissionCount = aInput.SubmissionCount;
		this->Submission = aInput.Submission;
		aInput.SubmissionCount = 0;
		aInput.Submission = NULL;
	}

	stage_t::batch::~batch() {
		this->clear();
	}

	stage_t::batch& stage_t::batch::operator=(batch& aRhs) {
		this->clear();
		if (aRhs.SubmissionCount > 0) {
			this->Submission = (VkSubmitInfo*)malloc(aRhs.SubmissionCount * sizeof(VkSubmitInfo));
			if (this->Submission != NULL) {
				this->SubmissionCount = aRhs.SubmissionCount;
				memcpy(this->Submission, aRhs.Submission, this->SubmissionCount * sizeof(VkSubmitInfo));
			}
			else {
				this->SubmissionCount = 0;
			}
		}
		else {
			this->SubmissionCount = 0;
			this->Submission = NULL;
		}
		return *this;
	}

	stage_t::batch& stage_t::batch::operator=(batch&& aRhs) noexcept {
		this->clear();
		this->SubmissionCount = aRhs.SubmissionCount;
		this->Submission = aRhs.Submission;
		aRhs.SubmissionCount = 0;
		aRhs.Submission = NULL;
		return *this;
	}

	void stage_t::batch::operator+=(VkSubmitInfo aRhs) {
		// Discard if no command buffers.
		if ((aRhs.commandBufferCount == 0) || (aRhs.pCommandBuffers == NULL)) return;
		void* nptr = NULL;
		if (this->Submission == NULL) {
			nptr = malloc(sizeof(VkSubmitInfo));
		}
		else {
			nptr = realloc(this->Submission, (this->SubmissionCount + 1) * sizeof(VkSubmitInfo));
		}
		if (nptr == NULL) return;
		this->Submission = (VkSubmitInfo*)nptr;
		memcpy(&(this->Submission[this->SubmissionCount]), &aRhs, sizeof(VkSubmitInfo));
		this->SubmissionCount += 1;
	}

	void stage_t::batch::operator+=(batch aRhs) {
		void* nptr = NULL;
		if (this->Submission == NULL) {
			nptr = malloc(aRhs.SubmissionCount * sizeof(VkSubmitInfo));
		}
		else {
			nptr = realloc(this->Submission, (this->SubmissionCount + aRhs.SubmissionCount) * sizeof(VkSubmitInfo));
		}
		if (nptr == NULL) return;
		this->Submission = (VkSubmitInfo*)nptr;
		memcpy(&(this->Submission[this->SubmissionCount]), aRhs.Submission, aRhs.SubmissionCount * sizeof(VkSubmitInfo));
		this->SubmissionCount += aRhs.SubmissionCount;
	}

	size_t stage_t::batch::count() {
		return this->SubmissionCount;
	}

	VkSubmitInfo* stage_t::batch::ptr() {
		return this->Submission;
	}

	void stage_t::batch::clear() {
		free(this->Submission);
		this->Submission = NULL;
		this->SubmissionCount = 0;
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

	void stage_t::submit() {
		//this->Engine->submit(this);
		this->Engine->submit(this);
	}

}