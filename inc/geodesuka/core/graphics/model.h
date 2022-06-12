/// <summary>
/// This class will serve as the model class of any object. An object is not required to have one, therefore has no geomtry.
/// It will contain a contigious array of meshes which can be used in rendering operations. A form of early depth sorting
/// of meshes may be neccessary to perform early depth testing, but that may require the creation Draw Command Buffers
/// per mesh rather than per model in the object_t class. The model class must also contain a tree of transformation information.
/// TWW must continue reading 
/// </summary>

#pragma once
#ifndef GEODESUKA_CORE_GRAPHICS_MODEL_H
#define GEODESUKA_CORE_GRAPHICS_MODEL_H

#include "mesh.h"
#include "material.h"

namespace geodesuka::core::graphics {

	class model {
	public:

		int MeshCount;
		mesh** Mesh;

		model();
		~model();

	};

}

#endif // !GEODESUKA_CORE_GRAPHICS_MODEL_H
