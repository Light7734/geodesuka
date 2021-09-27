#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "gcl.h"

#include "context.h"

#include "buffer.h"

// Holds no data, only references.
// This uses an internal index to attribute map.
// This is for convenient single call action for
// matrix types.

namespace geodesuka {
	namespace core {
		namespace gcl {

			class vertex_array {
			public:

				//vertex_array(gcl::gl::context &Context);
				vertex_array(context* aContext);
				~vertex_array();

				// If making repeated attrib calls, call bind() to minimize state changes.
				int bind();
				int index_attrib(const buffer& IndexBuffer);
				int vertex_attrib_enable();
				int vertex_attrib_pointer();
				int vertex_attrib_divisor();

				//int set_input(const variable& Target, const buffer& Variable);
			private:

				context* Parent;

				unsigned int ID;
				buffer* IBO;

				// Reference
				int BufferCount;
				buffer** Buffer;
			};

		}
	}
}

#endif // !VERTEX_ARRAY_H
