#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "mesh.h"
#include "material.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class model {
			public:

				std::vector<mesh*> Mesh;
				std::vector<material*> Material;
				//std::vector<shader_program> Program;

				model();
				~model();

			};

		}
	}
}

#endif // !MODEL_H