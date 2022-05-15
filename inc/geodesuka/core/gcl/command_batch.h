#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_BATCH_H
#define GEODESUKA_CORE_GCL_COMMAND_BATCH_H

#include <vulkan/vulkan.h>

namespace geodesuka::core::gcl {

	/*
	* Simply a utility to manage batched queue submissions for execution.
	*/
	class command_batch {
	public:

		command_batch();
		command_batch(VkSubmitInfo aSubmission);
		command_batch(size_t aSubmissionCount, VkSubmitInfo* aSubmission);
		command_batch(command_batch& aInput);
		command_batch(command_batch&& aInput) noexcept;
		~command_batch();

		VkSubmitInfo& operator[](int aIndex);

		command_batch& operator=(command_batch& aRhs);
		command_batch& operator=(command_batch&& aRhs) noexcept;

		// Will be used to aggregate render_target submissions.
		void operator+=(VkSubmitInfo aRhs);
		void operator+=(command_batch aRhs);

		// Used for final submission.
		size_t count();
		VkSubmitInfo* ptr();
		void clear();

	private:
		size_t SubmissionCount;
		VkSubmitInfo* Submission;
	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_BATCH_H
