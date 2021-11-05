#pragma once
#ifndef GEODESUKA_CORE_GCL_BUFFER_H
#define GEODESUKA_CORE_GCL_BUFFER_H

/*
* TODO:
*	-Figure out how to schedule mem transfers with engine backend.
*	-Add an option to use dynamically created staging buffer.
*/

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

		void write(size_t aMemOffset, size_t aMemSize, void* aData);
		void write(uint32_t aRegionCount, VkBufferCopy *aRegion, void *aData);
		void read(size_t aMemOffset, size_t aMemSize, void* aData);
		void read(uint32_t aRegionCount, VkBufferCopy* aRegion, void* aData);

	private:

		// Does not hold an host memory data unless explicity requested by API.

		context* Context;

		VkBufferCreateInfo CreateInfo{};
		VkBuffer Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;
		int MemoryProperty;
		//int MemoryType;

		int Count;
		util::variable MemoryLayout;

		// Make staging buffer optional. Trade off.
		// Faster Transfer of Data at the cost of double mem usage.
		// Only device mem usage, but slower transfers.

		// To keep a staging buffer, or not to keep?
		// To keep a staging buffer means that twice the memory
		// usage on both host and device memory, or not to keep a
		// staging buffer would imply that every transfer operation
		// will have a new allocation.
		buffer* StagingBuffer;

	};

}

#endif // !GEODESUKA_CORE_GCL_BUFFER_H
