#pragma once
#ifndef GEODESUKA_CORE_GRAPHICS_MODEL_H
#define GEODESUKA_CORE_GRAPHICS_MODEL_H

#include <vector>

#include "mesh.h"
#include "material.h"

namespace geodesuka::core::graphics {

	class model {
	public:

		std::vector<mesh*> Mesh;
		std::vector<material*> Material;

		model();
		~model();

	};

}

#endif // !GEODESUKA_CORE_GRAPHICS_MODEL_H
