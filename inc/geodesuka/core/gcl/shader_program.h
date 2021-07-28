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

				int ShaderCount;
				shader** Shader;

				variable Input;
				variable Uniform;
				variable Output;

				shader_program(context* aContext, int aShaderCount, const shader **aShader);
				shader_program(context* aContext, shader* aVertexShader, shader* aPixelShader);
				~shader_program();


				int set_input(const variable& Target, const buffer& Variable);
				int set_uniform(const variable& Target, const buffer& Variable);
				int set_uniform(const variable& Target, const texture& Variable);
				int set_output(const variable& Target, const texture& Variable);

			private:

			};

		}
	}
}

#endif // !SHADER_PROGRAM_H

