#pragma once
#ifndef GEODESUKA_CORE_STAGE_H
#define GEODESUKA_CORE_STAGE_H

//
// ------------------------- stage.h ------------------------- //
// A stage is simply a collection of objects that share the
// same space and therefore the same coordinate vectors. While
// the engine holds all created objects and updates, to be rendered
// they must be in the same coordinate space along with possible
// render targets. 
// 
// A stage is a collection of objects that firstly, share the same space
// which gives meaning to their position vector. Secondly, since they share
// the same space, they can be interpreted to interact with one and another.
//
// It is a assumed that stages and the context they create share the same
// rendering and compute context.

#include <vector>

#include <mutex>

#include "gcl/context.h"

#include "object.h"

namespace geodesuka::core {

	class stage_t {
	public:

		friend class engine;

		class batch {
		public:

			batch();
			batch(VkSubmitInfo aSubmission);
			batch(size_t aSubmissionCount, VkSubmitInfo* aSubmission);
			batch(batch& aInput);
			batch(batch&& aInput) noexcept;
			~batch();

			batch& operator=(batch& aRhs);
			batch& operator=(batch&& aRhs) noexcept;

			// Will be used to aggregate render_target submissions.
			void operator+=(VkSubmitInfo aRhs);
			void operator+=(batch aRhs);

			// Used for final submission.
			size_t count();
			VkSubmitInfo* ptr();
			void clear();

		private:
			size_t SubmissionCount;
			VkSubmitInfo* Submission;
		};

		std::mutex Mutex;

		~stage_t();

	protected:

		engine* Engine;
		gcl::context* Context;

		int ObjectCount;
		object_t** Object;

		virtual VkSubmitInfo update(double aDeltaTime);

		virtual VkSubmitInfo compute();

		virtual batch render() = 0;

		void submit();

	//private:

	};

}

#endif // !GEODESUKA_CORE_STAGE_H
