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

#include <vector>

#include <mutex>

#include "object.h"

namespace geodesuka::core {

	class stage_t {
	public:

		std::mutex Mutex;
		
		~stage_t();

		virtual void update(double aDeltaTime);
		virtual void render() = 0;

	protected:

		std::vector<object_t*> Object;

	private:


	};

}

#endif // !GEODESUKA_CORE_STAGE_H
