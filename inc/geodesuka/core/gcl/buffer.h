#pragma once
#ifndef GEODESUKA_CORE_GCL_BUFFER_H
#define GEODESUKA_CORE_GCL_BUFFER_H

#include <stdarg.h>

#include "../math.h"

#include "../util/variable.h"

#include "device.h"
#include "context.h"

namespace geodesuka::core::gcl {

	class buffer {
	public:

		enum memory {
			DEVICE_LOCAL			= 0x00000001,
			HOST_VISIBLE			= 0x00000002,
			HOST_COHERENT			= 0x00000004,
			HOST_CACHED				= 0x00000008,
			LAZILY_ALLOCATED		= 0x00000010,
			PROTECTED				= 0x00000020
		};

		enum usage {
			TRANSFER_SRC			= 0x00000001,
			TRANSFER_DST			= 0x00000002,
			UNIFORM_TEXEL			= 0x00000004,
			STORAGE_TEXEL			= 0x00000008,
			UNIFORM					= 0x00000010,
			STORAGE					= 0x00000020,
			INDEX					= 0x00000040,
			VERTEX					= 0x00000080,
			INDIRECT				= 0x00000100,
			SHADER_DEVICE_ADDRESS	= 0x00020000
		};

		buffer(context* aContext, int aMemType, int aUsage, int aCount, util::variable aMemoryLayout, void* aBufferData);

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

		context* Context;

		VkBufferCreateInfo CreateInfo{};
		VkBuffer Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;

		int Count;
		util::variable MemoryLayout;

		uint32_t memfilter(VkMemoryPropertyFlags MemPropFlags);

	};

}

#endif // !GEODESUKA_CORE_GCL_BUFFER_H
