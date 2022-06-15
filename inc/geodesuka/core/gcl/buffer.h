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


#include "config.h"

#include "variable.h"
#include "device.h"
#include "context.h"

namespace geodesuka::core::gcl {

	class image;

	class buffer {
	public:

		friend class image;

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

		// Empty buffer
		buffer();
		// Vertex/Index Buffer Creation.
		buffer(context* aContext, vk_memory_property_flags aMemoryPropertyFlags, vk_buffer_usage_flags aBufferUsageFlags, int aVertexCount, variable aVertexLayout, void* aVertexData);
		// General Buffer creation.
		buffer(context* aContext, vk_memory_property_flags aMemoryProperty, vk_buffer_usage_flags aBufferUsage, size_t aBufferSize, void* aBufferData);
		// Desctructor
		~buffer();

		buffer(buffer& aInp);																					// Copy Constructor
		buffer(buffer&& aInp) noexcept;																			// Move Constructor

		buffer& operator=(buffer& aRhs);																		// Copy Assign
		buffer& operator=(buffer&& aRhs) noexcept;																// Move Assign

		// The following four commands will produce command buffers to be
		// used for transfer operations. 
		
		// Will copy data from from right to left.
		vk_command_buffer operator<<(buffer& aRhs);
		// Will copy data from left to right.
		vk_command_buffer operator>>(buffer& aRhs);
		// Will copy data from right to left.
		vk_command_buffer operator<<(image& aRhs);
		// Will copy data from left to right.
		vk_command_buffer operator>>(image& aRhs);

		// Use Command Buffers to update. vkCmdUpdateBuffer() 64kB limit.
		// Has to be host memory to be used.
		void write(size_t aMemOffset, size_t aMemSize, void* aData);
		void write(uint32_t aRegionCount, vk_buffer_copy *aRegion, void *aData);
		void read(size_t aMemOffset, size_t aMemSize, void* aData);
		void read(uint32_t aRegionCount, vk_buffer_copy* aRegion, void* aData);

		vk_buffer& handle();

	private:

		context* Context;
		int Count;
		variable MemoryLayout;

		vk_buffer_create_info CreateInfo{};
		vk_buffer Handle;
		vk_memory_allocate_info AllocateInfo{};
		vk_device_memory MemoryHandle;

		void pmclearall();

	};

}

#endif // !GEODESUKA_CORE_GCL_BUFFER_H
