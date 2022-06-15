#pragma once
#ifndef GEODESUKA_CORE_GRAPHICS_MESH_H
#define GEODESUKA_CORE_GRAPHICS_MESH_H

#include "../gcl/variable.h"

#include "../gcl/context.h"
#include "../gcl/buffer.h"

namespace geodesuka::core::graphics {

	class mesh {
	public:

		struct vertex {
			float3 Position;
			float3 Normal;
		};
		
		size_t VertexCount;
		vertex* Vertex;

		size_t IndexCount;
		gcl::type::id IndexType;
		void* Index;

		// Per Vertex Texture Coordinate.
		size_t TexCoordCount;
		float2* TexCoord; // Size = TexCoordCount*VertexCount

		// Per Vertex Coloring.
		size_t ColorCount;
		float4* Color; // Size = ColorCount*VertexCount;

		gcl::context* Context;
		gcl::buffer* VertexBuffer;
		gcl::buffer* TexCoordBuffer;
		gcl::buffer* ColorBuffer;

		mesh(gcl::context* aContext, size_t aVertexCount, vertex* aVertex, size_t aIndexCount, unsigned short* aIndex);
		mesh(gcl::context* aContext, size_t aVertexCount, vertex* aVertex, size_t aIndexCount, unsigned int* aIndex);
		mesh(const mesh& aInput);
		mesh(mesh&& aInput);
		~mesh();

	private:

	};

}

#endif // !GEODESUKA_CORE_GRAPHICS_MESH_H
