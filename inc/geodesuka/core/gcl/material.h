#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include "../gcl/gcl.h"

#include "texture.h"
#include "shader.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class material {
			public:

				std::vector<texture*> Texture;
				shader* VertexShader;
				shader* PixelShader;

				material();
				~material();

			};

		}
	}
}

#endif // !MATERIAL_H