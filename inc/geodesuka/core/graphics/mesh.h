#pragma once
#ifndef GEODESUKA_CORE_GRAPHICS_MESH_H
#define GEODESUKA_CORE_GRAPHICS_MESH_H

#include "../util/variable.h"

#include "../gcl/context.h"
#include "../gcl/buffer.h"

namespace geodesuka::core::graphics {

	class mesh {
	public:

		/*
		* NOTE: if the total number of vertices is less than 65,536, then use 16 bit integers.
		*/
		// Data format of mesh object.
		struct vertex {
			math::real3 Position;
			math::real3 Normal;
			math::real2 TexCoord;
		};

		
		mesh(gcl::context* aContext, size_t aVertexCount, vertex* aVertex, size_t aIndexCount, unsigned short* aIndex);
		mesh(gcl::context* aContext, size_t aVertexCount, vertex* aVertex, size_t aIndexCount, unsigned int* aIndex);
		mesh(const mesh& aInput);
		mesh(mesh&& aInput);
		~mesh();

	private:

		// Stores the vertex data of the mesh.
		size_t VertexCount;
		vertex* Vertex;

		// Indices indicate how vertex data forms primitives.
		size_t IndexCount;
		void* Index;

		// These are the device buffe
		gcl::context* Context;
		gcl::buffer VertexBuffer;
		gcl::buffer IndexBuffer;

	};

}

#endif // !GEODESUKA_CORE_GRAPHICS_MESH_H
