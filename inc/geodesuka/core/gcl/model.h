#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "../gcl/gcl.h"

#include "mesh.h"
#include "material.h"
#include "shader_program.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class model {
			public:

				std::vector<mesh*> Mesh;
				std::vector<material*> Material;
				std::vector<shader_program> Program;

				model();
				~model();

			};

		}
	}
}

#endif // !MODEL_H