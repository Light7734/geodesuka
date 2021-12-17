#pragma once
#ifndef GEODESUKA_CORE_GCL_BUFFER_H
#define GEODESUKA_CORE_GCL_BUFFER_H

/*
* Usage:
*	When using this with other functions as non pointer stack type, please pass
*	by reference/pointer. If you pass by value, the constructor/assignment methods
*	will be called and you will unintentionally create, copy and move data on the 
*	device needlessly.
* 
* TODO:
*	-Figure out how to schedule mem transfers with engine backend.
*	-Add an option to use dynamically created staging buffer.
*/

#include "../math.h"

#include "../util/variable.h"

#include "device.h"
#include "context.h"

namespace geodesuka::core::gcl {

	class texture;

	class buffer {
	public:

		friend class texture;

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

		buffer();
		buffer(context* aContext, int aMemoryType, int aUsage, int aCount, util::variable aMemoryLayout, void* aBufferData);
		buffer(context* aContext, int aMemoryType, int aUsage, size_t aMemorySize, void* aBufferData);
		~buffer();

		buffer(buffer& aInp);																					// Copy Constructor
		buffer(buffer&& aInp) noexcept;																			// Move Constructor

		buffer& operator=(buffer& aRhs);																		// Copy Assign
		buffer& operator=(buffer&& aRhs) noexcept;																// Move Assign

		// The following four commands will produce command buffers to be
		// used for transfer operations. 
		
		// Will copy data from from right to left.
		VkCommandBuffer operator<<(buffer& aRhs);
		// Will copy data from left to right.
		VkCommandBuffer operator>>(buffer& aRhs);
		// Will copy data from right to left.
		VkCommandBuffer operator<<(texture& aRhs);
		// Will copy data from left to right.
		VkCommandBuffer operator>>(texture& aRhs);

		void write(size_t aMemOffset, size_t aMemSize, void* aData);
		void write(uint32_t aRegionCount, VkBufferCopy *aRegion, void *aData);
		void read(size_t aMemOffset, size_t aMemSize, void* aData);
		void read(uint32_t aRegionCount, VkBufferCopy* aRegion, void* aData);

		VkBuffer handle();

	private:

		context* Context;

		VkBufferCreateInfo CreateInfo{};
		VkBuffer Handle;
		VkMemoryAllocateInfo AllocateInfo{};
		VkDeviceMemory MemoryHandle;
		int MemoryProperty;

		int Count;
		util::variable MemoryLayout;

		void pmclearall();

	};

}

#endif // !GEODESUKA_CORE_GCL_BUFFER_H
