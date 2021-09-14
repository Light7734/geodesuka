#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "../gcl/gcl.h"

#include "variable.h"

#include "context.h"

#include "buffer.h"
#include "shader.h"
#include "texture.h"

// Linking can now be done with index maps for quickness.

//shader_program Program;
//...
//Program.set_input(Program.Input["Pos"][1], Buffer["Pos"][2]);
//Program.set_uniform(Program.Uniform[1]["cock"][4], Buffer[2][5]);
//Program.set_uniform(Program.Uniform["Tex0"], OWOTexture);
//Program.set_output(Program.Output["Color"], RenderTarget);

namespace geodesuka {
	namespace core {
		namespace gcl {

			class shader_program {
			public:


			};

		}
	}
}

#endif // !SHADER_PROGRAM_H

