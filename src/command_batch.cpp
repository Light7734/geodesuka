#include <geodesuka/core/gcl/command_batch.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <vulkan/vulkan.h>

namespace geodesuka::core::gcl {

	command_batch::command_batch() {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = NULL;
		PresentationCount = 0;
	}

	command_batch::command_batch(VkSubmitInfo aSubmission) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = NULL;
		PresentationCount = 0;
		*this += command_batch(1, &aSubmission);
	}

	command_batch::command_batch(size_t aSubmissionCount, VkSubmitInfo* aSubmission) {
		Submission = (VkSubmitInfo*)malloc(aSubmissionCount * sizeof(VkSubmitInfo));
		if (Submission != NULL) {
			memcpy(Submission, aSubmission, aSubmissionCount * sizeof(VkSubmitInfo));
			SubmissionCount = aSubmissionCount;
		}
		else {
			SubmissionCount = 0;
		}
		Presentation = NULL;
		PresentationCount = 0;
	}

	command_batch::command_batch(VkPresentInfoKHR aPresentation) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = NULL;
		PresentationCount = 0;
		*this += command_batch(1, &aPresentation);
	}

	command_batch::command_batch(size_t aPresentationCount, VkPresentInfoKHR* aPresentation) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = (VkPresentInfoKHR*)malloc(aPresentationCount * sizeof(VkPresentInfoKHR));
		if (Presentation != NULL) {
			memcpy(Presentation, aPresentation, aPresentationCount * sizeof(VkPresentInfoKHR));
			PresentationCount = aPresentationCount;
		}
		else {
			PresentationCount = 0;
		}
	}

	command_batch::command_batch(const command_batch& aInput) {
		Submission = NULL;
		SubmissionCount = 0;
		if (aInput.SubmissionCount > 0) {
			Submission = (VkSubmitInfo*)malloc(aInput.SubmissionCount * sizeof(VkSubmitInfo));
			if (Submission != NULL) {
				memcpy(Submission, aInput.Submission, aInput.SubmissionCount * sizeof(VkSubmitInfo));
			}
		}
		Presentation = NULL;
		PresentationCount = 0;
		if (aInput.PresentationCount > 0) {
			Presentation = (VkPresentInfoKHR*)malloc(aInput.PresentationCount * sizeof(VkPresentInfoKHR));
			if (Presentation != NULL) {
				memcpy(Presentation, aInput.Presentation, aInput.PresentationCount * sizeof(VkPresentInfoKHR));
			}
		}
	}

	command_batch::command_batch(command_batch&& aInput) noexcept {
		Submission					= aInput.Submission;
		SubmissionCount				= aInput.SubmissionCount;
		Presentation				= aInput.Presentation;
		PresentationCount			= aInput.PresentationCount;
		aInput.Submission			= NULL;
		aInput.SubmissionCount		= 0;
		aInput.Presentation			= NULL;
		aInput.PresentationCount	= 0;
	}

	command_batch::~command_batch() {
		this->clear();
	}

	command_batch& command_batch::operator=(const command_batch& aRhs) {
		if (aRhs.Submission != NULL) {
			void* nptr = NULL;
			if (Submission == NULL) {
				nptr = malloc(aRhs.SubmissionCount * sizeof(VkSubmitInfo));
			}
			else if (SubmissionCount != aRhs.SubmissionCount) {
				nptr = realloc(Submission, aRhs.SubmissionCount * sizeof(VkSubmitInfo));
			}
			else {
				nptr = Submission;
			}
			if (nptr != (void*)Submission) Submission = (VkSubmitInfo*)nptr;
			if ((Submission != NULL) && (aRhs.Submission != NULL) && (aRhs.SubmissionCount != 0)) {
				memcpy(Submission, aRhs.Submission, aRhs.SubmissionCount * sizeof(VkSubmitInfo));
				SubmissionCount = aRhs.SubmissionCount;
			}
		}
		else {
			free(Submission);
			SubmissionCount = 0;
			Submission = NULL;
		}

		if (aRhs.Presentation != NULL) {
			void* nptr = NULL;
			if (Presentation == NULL) {
				nptr = malloc(aRhs.PresentationCount * sizeof(VkPresentInfoKHR));
			}
			else if (PresentationCount != aRhs.PresentationCount) {
				nptr = realloc(Presentation, aRhs.PresentationCount * sizeof(VkPresentInfoKHR));
			}
			else {
				nptr = Presentation;
			}
			if (nptr != (void*)Presentation) Presentation = (VkPresentInfoKHR*)nptr;
			if ((Presentation != NULL) && (aRhs.Presentation != NULL) && (aRhs.PresentationCount != 0)) {
				memcpy(Presentation, aRhs.Presentation, aRhs.PresentationCount * sizeof(VkPresentInfoKHR));
				PresentationCount = aRhs.PresentationCount;
			}
		}
		else {
			free(Presentation);
			PresentationCount = 0;
			Presentation = NULL;
		}

		return *this;
	}

	command_batch& command_batch::operator=(command_batch&& aRhs) noexcept {
		this->clear();
		Submission				= aRhs.Submission;
		SubmissionCount			= aRhs.SubmissionCount;
		Presentation			= aRhs.Presentation;
		PresentationCount		= aRhs.PresentationCount;
		aRhs.Submission			= NULL;
		aRhs.SubmissionCount	= 0;
		aRhs.Presentation		= NULL;
		aRhs.PresentationCount	= 0;
		return *this;
	}

	command_batch& command_batch::operator+=(VkSubmitInfo aRhs) {
		if (aRhs.pCommandBuffers == NULL) return *this;
		return (*this += command_batch(1, &aRhs));
	}

	command_batch& command_batch::operator+=(VkPresentInfoKHR aRhs) {
		if (aRhs.pImageIndices == NULL) return *this;
		return (*this += command_batch(1, &aRhs));
	}

	command_batch& command_batch::operator+=(const command_batch& aRhs) {

		if ((aRhs.Submission != NULL) && (aRhs.SubmissionCount > 0)) {
			// Allocate memory for more subs
			void* nptr = NULL;
			if (Submission == NULL) {
				nptr = malloc(aRhs.SubmissionCount * sizeof(VkSubmitInfo));
			}
			else {
				nptr = realloc(Submission, (SubmissionCount + aRhs.SubmissionCount) * sizeof(VkSubmitInfo));
			}

			// Check for allocation failure.
			assert(nptr != NULL);
			// Use new pointer if reallocated.
			if (nptr != Submission) Submission = (VkSubmitInfo*)nptr;
			// Copy new elements
			memcpy(&Submission[SubmissionCount], aRhs.Submission, aRhs.SubmissionCount * sizeof(VkSubmitInfo));
			SubmissionCount += aRhs.SubmissionCount;
		}

		if ((aRhs.Presentation != NULL) && (aRhs.PresentationCount > 0)) {
			// Allocate memory for more subs
			void* nptr = NULL;
			if (Presentation == NULL) {
				nptr = malloc(aRhs.PresentationCount * sizeof(VkPresentInfoKHR));
			}
			else {
				nptr = realloc(Presentation, (PresentationCount + aRhs.PresentationCount) * sizeof(VkPresentInfoKHR));
			}

			// Check for allocation failure.
			assert(nptr != NULL);
			// Use new pointer if reallocated.
			if (nptr != Presentation) Presentation = (VkPresentInfoKHR*)nptr;
			// Copy new elements
			memcpy(&Presentation[PresentationCount], aRhs.Presentation, aRhs.PresentationCount * sizeof(VkPresentInfoKHR));
			PresentationCount += aRhs.PresentationCount;
		}

		return *this;
	}

	void command_batch::clear() {
		free(Submission);
		Submission = NULL;
		SubmissionCount = 0;
		free(Presentation);
		Presentation = NULL;
		PresentationCount = 0;
	}

}