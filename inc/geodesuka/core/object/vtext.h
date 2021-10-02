#pragma once
#ifndef GEODESUKA_CORE_OBJECT_VTEXT_H
#define GEODESUKA_CORE_OBJECT_VTEXT_H

#include "../util/text.h"

#include "../object.h"

namespace geodesuka::core::object {

	class vtext : public util::text, public object_t {
	public:

		// Is both a child of text.h and object.h. Used for
		// direct text rendering to 
	};

}

#endif // !GEODESUKA_CORE_OBJECT_VTEXT_H
