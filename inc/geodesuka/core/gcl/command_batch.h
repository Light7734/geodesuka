#pragma once
#ifndef GEODESUKA_CORE_GCL_COMMAND_BATCH_H
#define GEODESUKA_CORE_GCL_COMMAND_BATCH_H

#include <vulkan/vulkan.h>

#include "config.h"

namespace geodesuka::core::gcl {

	/*
	* Simply a utility to manage batched queue submissions for execution.
	*/
	class command_batch {
	public:

		friend class engine;
		friend class context;

		command_batch();
		command_batch(vk_submit_info aSubmission);
		command_batch(size_t aSubmissionCount, vk_submit_info* aSubmission);
		command_batch(vk_present_info_khr aPresentation);
		command_batch(size_t aPresentationCount, vk_present_info_khr* aPresentation);
		command_batch(const command_batch& aInput);
		command_batch(command_batch&& aInput) noexcept;
		~command_batch();

		//vk_submit_info operator[](int aIndex) const;
		//vk_submit_info& operator[](int aIndex);

		command_batch& operator=(const command_batch& aRhs);
		command_batch& operator=(command_batch&& aRhs) noexcept;

		// Will be used to aggregate render_target submissions.
		command_batch& operator+=(vk_submit_info aRhs);
		command_batch& operator+=(vk_present_info_khr aRhs);
		command_batch& operator+=(const command_batch& aRhs);

		void clear();

	private:
		size_t SubmissionCount;
		vk_submit_info* Submission;

		size_t PresentationCount;
		vk_present_info_khr* Presentation;
	};

}

#endif // !GEODESUKA_CORE_GCL_COMMAND_BATCH_H
