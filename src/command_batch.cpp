#include <geodesuka/core/gcl/command_batch.h>

#include <stdlib.h>
#include <string.h>

#include <vulkan/vulkan.h>

namespace geodesuka::core::gcl {

	command_batch::command_batch() {
		this->SubmissionCount = 0;
		this->Submission = NULL;
	}

	command_batch::command_batch(VkSubmitInfo aSubmission) {
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

	command_batch::command_batch(size_t aSubmissionCount, VkSubmitInfo* aSubmission) {
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

	command_batch::command_batch(command_batch& aInput) {
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

	command_batch::command_batch(command_batch&& aInput) noexcept {
		this->SubmissionCount = aInput.SubmissionCount;
		this->Submission = aInput.Submission;
		aInput.SubmissionCount = 0;
		aInput.Submission = NULL;
	}

	command_batch::~command_batch() {
		this->clear();
	}

	VkSubmitInfo& command_batch::operator[](int aIndex) {
		return this->Submission[aIndex];
	}

	command_batch& command_batch::operator=(command_batch& aRhs) {
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

	command_batch& command_batch::operator=(command_batch&& aRhs) noexcept {
		this->clear();
		this->SubmissionCount = aRhs.SubmissionCount;
		this->Submission = aRhs.Submission;
		aRhs.SubmissionCount = 0;
		aRhs.Submission = NULL;
		return *this;
	}

	void command_batch::operator+=(VkSubmitInfo aRhs) {
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

	void command_batch::operator+=(command_batch aRhs) {
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

	size_t command_batch::count() {
		return this->SubmissionCount;
	}

	VkSubmitInfo* command_batch::ptr() {
		return this->Submission;
	}

	void command_batch::clear() {
		free(this->Submission);
		this->Submission = NULL;
		this->SubmissionCount = 0;
	}
}