#pragma once
#ifndef GEODESUKA_CORE_GCL_BUFFER_H
#define GEODESUKA_CORE_GCL_BUFFER_H

#include <stdarg.h>

#include "../math.h"

#include "variable.h"

#include "device.h"
#include "device_context.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class buffer {
			public:

				enum class id {
					none
				};

				enum usage {
					TRANSFER_SRC_BIT			= 0x00000001,
					TRANSFER_DST_BIT			= 0x00000002,
					UNIFORM_TEXEL_BUFFER_BIT	= 0x00000004,
					STORAGE_TEXEL_BUFFER_BIT	= 0x00000008,
					UNIFORM_BUFFER_BIT			= 0x00000010,
					STORAGE_BUFFER_BIT			= 0x00000020,
					INDEX_BUFFER_BIT			= 0x00000040,
					VERTEX_BUFFER_BIT			= 0x00000080,
					INDIRECT_BUFFER_BIT			= 0x00000100,
					SHADER_DEVICE_ADDRESS_BIT	= 0x00020000,
				};

				buffer(device_context* aContext, int aFlags, int aUsage, int aCount, variable aMemoryLayout, void* aBufferData);
				buffer(device_context* aContext, int aFlags, int aUsage, int aCount, type aTypeSpecifier, const char* aIdentifier, void* aBufferData);
				
				~buffer();

				//buffer(const buffer& Inp);																					// Copy Constructor
				//buffer(buffer&& Inp);																						// Move Constructor
				//buffer& operator=(const buffer& Rhs);																		// Copy Assign
				//buffer& operator=(buffer&& Rhs);																			// Move Assign


				// Grabs sub buffers from memory layout memory layout
				//buffer operator[](const char* Str);
				//buffer operator[](int Index);

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

				// Does not hold an host memory data unless explicity requested by API.

				device_context* aParentDC;

				VkBufferCreateInfo CreateInfo;
				VkBuffer Handle;
				VkDeviceMemory MemoryHandle;

				int Flags;
				int Usage;
				int Count;
				variable MemoryLayout;

				// Internal: reduce code error from redundancy.
				bool init_all(device_context* aContext, int aFlags, int aUsage, int aCount, variable aMemoryLayout, void* aBufferData);
				bool clear_all();
			};

		}
	}
}

#endif // !GEODESUKA_CORE_GCL_BUFFER_H
