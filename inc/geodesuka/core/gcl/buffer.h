#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#include <stdarg.h>

#include "gcl.h"

#include "../math/math.h"

#include "variable.h"
#include "context.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class buffer {
			public:

				enum class id {
					none
				};

				// Will generate vertex buffer according to VertexLayout, with VertexCount.
				buffer(context* aContext, id aType, int aVertexCount, variable aVertexLayout, void *aVertexData);

				buffer(const buffer& Inp);																					// Copy Constructor
				buffer(buffer&& Inp);																						// Move Constructor

				~buffer();

				buffer& operator=(const buffer& Rhs);																		// Copy Assign
				buffer& operator=(buffer&& Rhs);																			// Move Assign


				// Grabs sub buffers from memory layout memory layout
				buffer operator[](const char* Str);
				buffer operator[](int Index);

				//int get_type_id_of(const char* TypeSpecifier);
				//const char* get_type_name_of(int TypeSpecifier);
				//size_t get_size_of(int TypeSpecifier);

				//int get_element_count_of(int TypeSpecifier);
				//int get_data_type_id_of(int TypeSpecifier);
				//int get_row_count_of(int TypeSpecifier);
				//int get_col_count_of(int TypeSpecifier);

				//// --------------- Memory Operations --------------- //
				//// reserve, release, read, write

				//int reserve_memory(int VertexCount);
				//int resize_memory(int VertexCount);
				//int release_memory();

				////int set(int VertexIndex, ...);
				//int set(int VertexIndex, const void *Arg, size_t ArgMemSize);
				////void *get(int VertexIndex, size_t *ArgMemSize, int *ReturnErrorCode);




				// --------------- Class Utilities --------------- //

			private:

				// Is not nullptr if hollow reference.
				buffer* SuperBuffer;
				context* Context;

				id Type;
				int Count;
				variable Layout;

				void* hptr;
				unsigned int ID;

				//boolean is_identifier_valid(const char* IdentifierString);
				//boolean is_identifier_taken(const char* IdentifierString);
			};

		}
	}
}

#endif // !BUFFER_H
