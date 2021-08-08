#pragma once
#ifndef VTEXT_H
#define VTEXT_H

#include "../util/text.h"

#include "../object.h"

namespace geodesuka {
	namespace core {
		namespace object {

			class vtext : public util::text, public object_t {
			public:

				// Is both a child of text.h and object.h. Used for
				// direct text rendering to 
			};

		}
	}
}

#endif // !VTEXT_H
