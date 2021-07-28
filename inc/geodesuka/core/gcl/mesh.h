#pragma once
#ifndef MESH_H
#define MESH_H

#include "../gcl/gcl.h"

#include "buffer.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class mesh {
			public:

				enum mesh_type {
					HOLLOW,
					QUAD,
					CUBE
				};

				// These will serve as references in a draw operation.
				// Derived instances must manage their own secondary memory allocation.
				buffer* Vertices;
				buffer* Indices;

				mesh();
				~mesh();

			};

		}
	}
}

#endif // !MESH_H