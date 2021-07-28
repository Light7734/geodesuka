#ifndef GRAPHICAL_PROGRAM_H
#define GRAPHICAL_PROGRAM_H

// TODO: Yes, I put the VAO and FBO into the shader program.

#include <vector>
#include <string>

#include "../gcl/gcl.h"

#include "buffer.h"
#include "shader.h"
#include "texture.h"

#include "vertex_array.h"
#include "shader_program.h"
#include "frame_buffer.h"


// OpenGL 3.3 Attribute Variable API
//Loc = glGetAttribLocation(ID, Name);
//glEnableVertexAttribArray(Loc);
//glDisableVertexAttribArray(Loc);
//glVertexAttribPointer();

// OpenGL 3.3 Uniform Variable API
//Loc = glGetUniformLocation(ID, Name);
//glGetUniformBlockIndex();
//glUniformBlockBinding();

// OpenGL 3.3 FragData Variable API
//Loc = glGetFragDataLocation(ID, Name);
//glDrawBuffers(FramebufferCount, FramebufferList);

/*
struct glow {			  //
	struct particle {	  //
		vec3 Position;	  //			O
		vec3 Momentum;	  //			O
		vec3 Force;		  //			O
		float Mass;		  //			O
	} Particle;			  //		X
	struct light {		  //
		vec3 Position;	  //			O
		vec3 Color;		  //			O
	} Light;			  //		X
	mat4 Transform;		  //		O
	vec3 Position;		  //		O
	float Scale;		  //		O
} Glow;					  //	X
*/

// graphical_program shall have the ability
// to make draw calls, and preserves the entire
// state of a draw call.

namespace geodesuka {
	namespace core {
		namespace gcl {

			class graphical_program {
			public:

				enum draw_mode {
					POINTS = GL_POINTS,
					LINES = GL_LINES,
					LINE_STRIP = GL_LINE_STRIP,
					LINE_LOOP = GL_LINE_LOOP,
					TRIANGLES = GL_TRIANGLES,
					TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
					TRIANGLE_FAN = GL_TRIANGLE_FAN
				};

				int isLinked;
				bool FBOEnable;

				std::vector<buffer> Buffer;
				std::vector<shader> Shader;
				std::vector<texture> Texture;

				std::vector<vertex_array> VertexArray;
				std::vector<shader_program> ShaderProgram;
				std::vector<frame_buffer> FrameBuffer;

				graphical_program();
				~graphical_program();

				//void create();
				//void annihilate();

				//bool link(const shader& lhs, const shader& rhs);

				//bool load();

				//// These are for REFERENCE ONLY. Do not try and free them!
				//const variable& operator[](int Index) const;
				//const variable& operator[](std::string Str) const;

				//// --------------- Program Args --------------- //
				//
				///* MEMORY SIZE MUST MATCH, OR ERROR WILL BE THROWN! */
				//int set_input(const variable& ShaderVariable, const buffer& VertexAttrib);
				//int set_input(const variable& ShaderVariable, const variable& VertexAttrib);

				math::integer set_input(const char* LocationName, const buffer& VertexBuffer, const char* AttributeName);


				//int set_uniform(const variable& ShaderVariable, const signed int& Arg);
				//int set_uniform(const variable& ShaderVariable, const ivec2& Arg);
				//int set_uniform(const variable& ShaderVariable, const ivec3& Arg);
				//int set_uniform(const variable& ShaderVariable, const ivec4& Arg);
				//int set_uniform(const variable& ShaderVariable, const unsigned int& Arg);
				//int set_uniform(const variable& ShaderVariable, const uvec2& Arg);
				//int set_uniform(const variable& ShaderVariable, const uvec3& Arg);
				//int set_uniform(const variable& ShaderVariable, const uvec4& Arg);
				//int set_uniform(const variable& ShaderVariable, const float& Arg);
				//int set_uniform(const variable& ShaderVariable, const vec2& Arg);
				//int set_uniform(const variable& ShaderVariable, const vec3& Arg);
				//int set_uniform(const variable& ShaderVariable, const vec4& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat2& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat3x2& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat4x2& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat2x3& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat3& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat4x3& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat2x4& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat3x4& Arg);
				//int set_uniform(const variable& ShaderVariable, const mat4& Arg);
				//int set_uniform(const variable& ShaderVariable, int Slot, const texture& Arg);
				//
				//int set_output(const variable& ShaderVariable, const texture& FragData);
				//int set_output(const variable& ShaderVariable, const variable& FragData);

				// --------------- Draw Commands --------------- //

				//int draw_arrays(GLenum DrawMode, GLint Start, GLsizei Count);
				//int multi_draw_arrays(GLenum DrawMode, GLint *Start, GLsizei *Count, GLsizei PrimitiveCount);
				//int draw_arrays_instanced(GLenum DrawMode, GLint Start, GLsizei Count, GLsizei PrimitiveCount);
				//int draw_elements(GLenum DrawMode, GLsizei Count, GLenum DataType, GLvoid *Indices);
				//int multi_draw_elements(GLenum DrawMode, GLsizei *Count, GLenum DataType, GLvoid **Indices, GLsizei PrimitiveCount);
				//int draw_elements_instanced(GLenum DrawMode, GLsizei Count, GLenum DataType, GLvoid *Indices, GLsizei PrimitiveCount);
				//int draw_range_elements(GLenum DrawMode, GLuint Start, GLuint End, GLsizei Count, GLvoid* Indices);

				// If this argument is null,
				math::integer draw(frame_buffer* Framebuffer);

			private:

				//GLFWwindow* CTX; // S
				GLuint FBO;
				GLuint VAO;
				GLuint SPO;
				GLuint IBO;

				GLboolean EnableBlending;
				//GLboolean EnableColorLogic;
				GLboolean EnableFaceCulling;
				//GLboolean EnableDepthClamp;
				GLboolean EnableDepthTest;
				GLboolean EnableDithering;
				//GLboolean EnableFramebufferSRGB;
				//GLboolean EnableLineSmooth;
				GLboolean EnableMultisample;
				//GLboolean EnablePolygonSmooth;
				GLboolean EnableScissorTest;
				GLboolean EnableStencilTest;


				//shader *VertexShader;
				//shader *PixelShader;

				struct input_map {
					GLint Location;
					GLboolean Enabled;
					GLint Divisor;
				};

				//int InputCount;
				//GLint InputLocation;
				//GLboolean InputEnabled;
				//GLint InputDivisor;
				//GLuint IBO;

				//int UniformCount;
				//GLint UniformLocation;

				//int OutputCount;
				//GLint OutputLocation;
				//GLenum AttachmentPoint;

				// --------------- Shader Render Options --------------- //

				// Face Culling Options
				GLenum FrontFaceSelect;
				GLenum CullFaceSelect;

				// Scissor Options
				GLint ScissorPositionX, ScissorPositionY;
				GLsizei ScissorSizeX, ScissorSizeY;

				// Multisample Options
				GLclampf MultisampleValue;
				GLboolean MultisampleInversion;

				// Depth Test Options
				GLenum DepthOperation;
				GLboolean DepthFlag;
				GLclampd DepthNear, DepthFar;

				// Stencil Test Options
				GLenum StencilOperation;
				GLint StencilReferenceValue;
				GLuint StencilMask;
				GLenum StencilTestFailureAction, DepthTestFailureAction, StencilAndDepthPassAction;

				// Blending Options
				GLclampf BlendRed, BlendGreen, BlendBlue, BlendAlpha;
				GLenum BlendingSourceMultiplier, BlendingDestinationMultiplier, BlendingOperation;

				// Refresh Frame buffer
				GLint FramePositionX, FramePositionY;
				GLsizei FrameSizeX, FrameSizeY;

				GLbitfield ClearOptions;
				GLclampf FrameClearRed, FrameClearGreen, FrameClearBlue, FrameClearAlpha;
				GLclampd FrameClearDepth;
				GLint FrameClearStencil;

			};

		}
	}
}

#endif // !GRAPHICAL_PROGRAM_H