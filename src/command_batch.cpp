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

	command_batch::command_batch(vk_submit_info aSubmission) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = NULL;
		PresentationCount = 0;
		*this += command_batch(1, &aSubmission);
	}

	command_batch::command_batch(size_t aSubmissionCount, vk_submit_info* aSubmission) {
		Submission = (vk_submit_info*)malloc(aSubmissionCount * sizeof(vk_submit_info));
		if (Submission != NULL) {
			memcpy(Submission, aSubmission, aSubmissionCount * sizeof(vk_submit_info));
			SubmissionCount = aSubmissionCount;
		}
		else {
			SubmissionCount = 0;
		}
		Presentation = NULL;
		PresentationCount = 0;
	}

	command_batch::command_batch(vk_present_info_khr aPresentation) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = NULL;
		PresentationCount = 0;
		*this += command_batch(1, &aPresentation);
	}

	command_batch::command_batch(size_t aPresentationCount, vk_present_info_khr* aPresentation) {
		Submission = NULL;
		SubmissionCount = 0;
		Presentation = (vk_present_info_khr*)malloc(aPresentationCount * sizeof(vk_present_info_khr));
		if (Presentation != NULL) {
			memcpy(Presentation, aPresentation, aPresentationCount * sizeof(vk_present_info_khr));
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
			Submission = (vk_submit_info*)malloc(aInput.SubmissionCount * sizeof(vk_submit_info));
			if (Submission != NULL) {
				memcpy(Submission, aInput.Submission, aInput.SubmissionCount * sizeof(vk_submit_info));
			}
		}
		Presentation = NULL;
		PresentationCount = 0;
		if (aInput.PresentationCount > 0) {
			Presentation = (vk_present_info_khr*)malloc(aInput.PresentationCount * sizeof(vk_present_info_khr));
			if (Presentation != NULL) {
				memcpy(Presentation, aInput.Presentation, aInput.PresentationCount * sizeof(vk_present_info_khr));
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
				nptr = malloc(aRhs.SubmissionCount * sizeof(vk_submit_info));
			}
			else if (SubmissionCount != aRhs.SubmissionCount) {
				nptr = realloc(Submission, aRhs.SubmissionCount * sizeof(vk_submit_info));
			}
			else {
				nptr = Submission;
			}
			if (nptr != (void*)Submission) Submission = (vk_submit_info*)nptr;
			if ((Submission != NULL) && (aRhs.Submission != NULL) && (aRhs.SubmissionCount != 0)) {
				memcpy(Submission, aRhs.Submission, aRhs.SubmissionCount * sizeof(vk_submit_info));
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
				nptr = malloc(aRhs.PresentationCount * sizeof(vk_present_info_khr));
			}
			else if (PresentationCount != aRhs.PresentationCount) {
				nptr = realloc(Presentation, aRhs.PresentationCount * sizeof(vk_present_info_khr));
			}
			else {
				nptr = Presentation;
			}
			if (nptr != (void*)Presentation) Presentation = (vk_present_info_khr*)nptr;
			if ((Presentation != NULL) && (aRhs.Presentation != NULL) && (aRhs.PresentationCount != 0)) {
				memcpy(Presentation, aRhs.Presentation, aRhs.PresentationCount * sizeof(vk_present_info_khr));
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

	command_batch& command_batch::operator+=(vk_submit_info aRhs) {
		if (aRhs.pCommandBuffers == NULL) return *this;
		return (*this += command_batch(1, &aRhs));
	}

	command_batch& command_batch::operator+=(vk_present_info_khr aRhs) {
		if (aRhs.pImageIndices == NULL) return *this;
		return (*this += command_batch(1, &aRhs));
	}

	command_batch& command_batch::operator+=(const command_batch& aRhs) {

		if ((aRhs.Submission != NULL) && (aRhs.SubmissionCount > 0)) {
			// Allocate memory for more subs
			void* nptr = NULL;
			if (Submission == NULL) {
				nptr = malloc(aRhs.SubmissionCount * sizeof(vk_submit_info));
			}
			else {
				nptr = realloc(Submission, (SubmissionCount + aRhs.SubmissionCount) * sizeof(vk_submit_info));
			}

			// Check for allocation failure.
			assert(nptr != NULL);
			// Use new pointer if reallocated.
			if (nptr != Submission) Submission = (vk_submit_info*)nptr;
			// Copy new elements
			memcpy(&Submission[SubmissionCount], aRhs.Submission, aRhs.SubmissionCount * sizeof(vk_submit_info));
			SubmissionCount += aRhs.SubmissionCount;
		}

		if ((aRhs.Presentation != NULL) && (aRhs.PresentationCount > 0)) {
			// Allocate memory for more subs
			void* nptr = NULL;
			if (Presentation == NULL) {
				nptr = malloc(aRhs.PresentationCount * sizeof(vk_present_info_khr));
			}
			else {
				nptr = realloc(Presentation, (PresentationCount + aRhs.PresentationCount) * sizeof(vk_present_info_khr));
			}

			// Check for allocation failure.
			assert(nptr != NULL);
			// Use new pointer if reallocated.
			if (nptr != Presentation) Presentation = (vk_present_info_khr*)nptr;
			// Copy new elements
			memcpy(&Presentation[PresentationCount], aRhs.Presentation, aRhs.PresentationCount * sizeof(vk_present_info_khr));
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