#include <geodesuka/core/gcl/graphical_program.h>

#include <vector>
#include <string>

#include <geodesuka/core/gcl/gcl.h>

#include <geodesuka/core/gcl/buffer.h>
#include <geodesuka/core/gcl/shader.h>
#include <geodesuka/core/gcl/texture.h>

#include <geodesuka/core/gcl/vertex_array.h>
#include <geodesuka/core/gcl/shader_program.h>
#include <geodesuka/core/gcl/frame_buffer.h>

namespace geodesuka {
	namespace core {
		namespace gcl {

			//graphical_program::graphical_program() {

			//	FBO = 0;
			//	VAO = 0;
			//	SPO = 0;
			//	IBO = 0;

			//	//VertexShader = nullptr;
			//	//PixelShader = nullptr;

			//	//InputCount = 0;
			//	//InputBuffer = nullptr;
			//	//InputAttribute = NULL;
			//	//InputLocation = NULL;
			//	////InputEnabled = NULL;
			//	//InputDivisor = NULL;

			//	//UniformCount = 0;
			//	//UniformLocation = NULL;

			//	//OutputCount = 0;
			//	//OutputTexture = nullptr;
			//	//OutputDepth = NULL;
			//	//OutputLocation = NULL;
			//	//OutputAttachment = NULL;

			//	EnableFaceCulling = false;
			//	EnableScissorTest = false;
			//	EnableMultisample = false;
			//	EnableStencilTest = false;
			//	EnableDepthTest = false;
			//	EnableBlending = false;
			//	EnableDithering = false;

			//	FrontFaceSelect = GL_CCW;
			//	CullFaceSelect = GL_BACK;

			//	ScissorPositionX = 0; ScissorPositionY = 0;
			//	ScissorSizeX = 0; ScissorSizeY = 0;

			//	MultisampleValue = 1.0;
			//	MultisampleInversion = GL_FALSE;

			//	DepthOperation = GL_LESS;
			//	DepthFlag = GL_TRUE;
			//	DepthNear = 0.0;
			//	DepthFar = 1.0;

			//	StencilOperation = GL_ALWAYS;
			//	StencilReferenceValue = 0;
			//	StencilMask = 1;
			//	StencilTestFailureAction = GL_KEEP;
			//	DepthTestFailureAction = GL_KEEP;
			//	StencilAndDepthPassAction = GL_KEEP;

			//	BlendingSourceMultiplier = GL_ONE;
			//	BlendingDestinationMultiplier = GL_ZERO;
			//	BlendingOperation = GL_FUNC_ADD;
			//	BlendRed = 0.0f; BlendGreen = 0.0f; BlendBlue = 0.0f; BlendAlpha = 0.0f;

			//	ClearOptions = GL_COLOR_BUFFER_BIT;
			//	FramePositionX = 0; FramePositionY = 0;
			//	FrameSizeX = 0; FrameSizeY = 0;
			//	FrameClearRed = 0.0f; FrameClearGreen = 0.0f; FrameClearBlue = 0.0f; FrameClearAlpha = 0.0f;
			//	FrameClearDepth = 1.0;
			//	FrameClearStencil = 0;
			//}

			//graphical_program::~graphical_program() {
			//	SPO = 0;
			//	VAO = 0;
			//	FBO = 0;
			//}

			//bool graphical_program::link(const shader& lhs, const shader& rhs) {
			//	//if ((lhs.Type == GL_VERTEX_SHADER) && (rhs.Type == GL_FRAGMENT_SHADER)) {
			//	//	VertexShader = &lhs; PixelShader = &rhs;
			//	//}
			//	//else if ((lhs.Type == GL_FRAGMENT_SHADER) && (rhs.Type == GL_VERTEX_SHADER)) {
			//	//	VertexShader = &rhs; PixelShader = &lhs;
			//	//}
			//	//else {
			//	//	VertexShader = nullptr; PixelShader = nullptr;
			//	//	return true;
			//	//}

			//	//if ((VertexShader == nullptr) || (PixelShader == nullptr)) { return true; }
			//	//if ((VertexShader->ID == 0) || (PixelShader->ID == 0) || (ID == 0)) { return true; }

			//	if ((lhs.isCompiled == GL_FALSE) || (rhs.isCompiled == GL_FALSE)) { return true; }

			//	glAttachShader(SPO, lhs.ID);
			//	glAttachShader(SPO, rhs.ID);
			//	glLinkProgram(SPO);
			//	glDetachShader(SPO, rhs.ID);
			//	glDetachShader(SPO, lhs.ID);
			//	glGetProgramiv(SPO, GL_LINK_STATUS, &isLinked);

			//	if (isLinked == GL_TRUE) {
			//		return false;
			//	}
			//	else {
			//		return true;
			//	}

			//	//glGetUniformBlockIndex(SPO, "");
			//	//glUniformBlockBinding(SPO, 0, 0);


			//	//if (VAO != 0) {
			//	//	if (VAO != BoundVAO) { glBindVertexArray(VAO); BoundVAO = VAO; }
			//	//	for (int i = 0; i < InputCount; i++) {
			//	//		if (InputLocation[i] != -1) {
			//	//			glEnableVertexAttribArray(InputLocation[i]);
			//	//		}
			//	//	}
			//	//}

			//	//if (FBO != 0) {
			//	//	if (FBO != BoundFBO) { glBindFramebuffer(GL_FRAMEBUFFER, FBO); BoundFBO = FBO; }
			//	//	glDrawBuffers(OutputCount, OutputAttachment);
			//	//}

			//}

			//bool graphical_program::load() {
			//	if (SPO == 0) { return true; }

			//	int InputCount;
			//	glsl::attribute *Input;

			//	int UniformCount;
			//	glsl::uniform *Uniform;

			//	int OutputCount;
			//	glsl::frag_data *Output;
			//	GLenum *OutputAttachment;

			//	int UniformBlockCount;

			//	glGetProgramInterfaceiv(SPO, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &InputCount);
			//	glGetProgramInterfaceiv(SPO, GL_UNIFORM, GL_ACTIVE_RESOURCES, &UniformCount);
			//	glGetProgramInterfaceiv(SPO, GL_PROGRAM_OUTPUT, GL_ACTIVE_RESOURCES, &OutputCount);
			//	//glGetProgramInterfaceiv(ID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &UniformBlockCount);

			//	Input = (glsl::attribute*)malloc(InputCount*sizeof(glsl::attribute));
			//	Uniform = (glsl::uniform*)malloc(UniformCount*sizeof(glsl::uniform));
			//	Output = (glsl::frag_data*)malloc(OutputCount*sizeof(glsl::frag_data));
			//	OutputAttachment = (GLenum*)malloc(OutputCount * sizeof(GLenum));

			//	const GLint InputPropCount = 5;
			//	const GLenum InputProps[] = {
			//		GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_SIZE, GL_LOCATION, GL_IS_PER_PATCH
			//	};
			//	GLint InputParams[5];

			//	const GLint UniformPropCount = 8;
			//	const GLenum UniformProps[] = {
			//		GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_SIZE, GL_OFFSET, GL_BLOCK_INDEX, GL_ARRAY_STRIDE, GL_MATRIX_STRIDE, GL_LOCATION
			//	};
			//	GLint UniformParams[8];

			//	const GLint OutputPropCount = 6;
			//	const GLenum OutputProps[] = {
			//		GL_NAME_LENGTH, GL_TYPE, GL_ARRAY_SIZE, GL_LOCATION, GL_LOCATION_INDEX, GL_IS_PER_PATCH
			//	};
			//	GLint OutputParams[6];

			//	for (int i = 0; i < InputCount; i++) {
			//		Input[i].Storage = GL_PROGRAM_INPUT;
			//		glGetProgramResourceiv(SPO, GL_PROGRAM_INPUT, i, InputPropCount, InputProps, InputPropCount, NULL, InputParams);
			//		Input[i].Name = (char*)malloc(InputParams[0]*sizeof(char));
			//		glGetProgramResourceName(SPO, GL_PROGRAM_INPUT, i, InputParams[0], NULL, Input[i].Name);
			//		Input[i].Type = InputParams[1];
			//		Input[i].ArrayCount = InputParams[2];
			//		Input[i].Location = InputParams[3];
			//		Input[i].LocationComponent = InputParams[5];
			//	}
			//	for (int i = 0; i < UniformCount; i++) {
			//		Uniform[i].Storage = GL_UNIFORM;
			//		glGetProgramResourceiv(SPO, GL_UNIFORM, i, UniformPropCount, UniformProps, UniformPropCount, NULL, UniformParams);
			//		Uniform[i].Name = (char*)malloc(UniformParams[0]*sizeof(char));
			//		glGetProgramResourceName(SPO, GL_UNIFORM, i, UniformParams[0], NULL, Uniform[i].Name);
			//		Uniform[i].Type = UniformParams[1];
			//		Uniform[i].ArrayCount = UniformParams[2];
			//		Uniform[i].Offset = UniformParams[3];
			//		Uniform[i].BlockIndex = UniformParams[4];
			//		Uniform[i].ArrayStride = UniformParams[5];
			//		Uniform[i].MatrixStride = UniformParams[6];
			//		Uniform[i].Location = UniformParams[7];
			//	}
			//	for (int i = 0; i < OutputCount; i++) {
			//		Output[i].Storage = GL_PROGRAM_OUTPUT;
			//		glGetProgramResourceiv(SPO, GL_PROGRAM_OUTPUT, i, OutputPropCount, OutputProps, OutputPropCount, NULL, OutputParams);
			//		Output[i].Name = (char*)malloc(OutputParams[0] * sizeof(char));
			//		glGetProgramResourceName(SPO, GL_PROGRAM_OUTPUT, i, OutputParams[0], NULL, Output[i].Name);
			//		Output[i].Type = OutputParams[1];
			//		Output[i].ArrayCount = OutputParams[2];
			//		Output[i].Location = OutputParams[3];
			//		Output[i].LocationIndex = OutputParams[4];
			//		Output[i].LocationComponent = OutputParams[6];

			//		//Output[i].MemSize = get_mem_size(Output[i].Type);
			//		//Output[i].ElementType = get_element_type(Output[i].Type);
			//		//Output[i].ElementCount = get_element_count(Output[i].Type);

			//		OutputAttachment[i] = Output[i].Location + GL_COLOR_ATTACHMENT0;
			//	}

			//	if (VAO != 0) {
			//		if (VAO != BoundVAO) { glBindVertexArray(VAO); BoundVAO = VAO; }
			//		for (int i = 0; i < InputCount; i++) {
			//			if (Input[i].Location != -1) {
			//				glEnableVertexAttribArray(Input[i].Location);
			//			}
			//		}
			//	}

			//	if (FBO != 0) {
			//		if (FBO != BoundFBO) { glBindFramebuffer(GL_FRAMEBUFFER, FBO); BoundFBO = FBO; }
			//		glDrawBuffers(OutputCount, OutputAttachment);
			//	}
			//	return false;
			//}

			//bool shader_program::print() {
			//	std::cout << "Loc\tASize\tOffset\tBIndex\tAStride\tMStride" << std::endl;
			//	for (int i = 0; i < InputCount; i++) {
			//		std::cout << Input[i].Location << "\t" << Input[i].ArrayCount << "\t\t\t\t\t";
			//		std::cout << glsl::get_type_string(Input[i].Storage) << " " << glsl::get_type_string(Input[i].Type) << " " << Input[i].Name << std::endl;
			//	}
			//	//std::cout << std::endl;
			//	for (int i = 0; i < UniformCount; i++) {
			//		std::cout << Uniform[i].Location << "\t" << Uniform[i].ArrayCount << "\t" << Uniform[i].Offset << "\t" << Uniform[i].BlockIndex << "\t" << Uniform[i].ArrayStride << "\t" << Uniform[i].MatrixStride << "\t";
			//		std::cout << glsl::get_type_string(Uniform[i].Storage) << " " << glsl::get_type_string(Uniform[i].Type) << " " << Uniform[i].Name << std::endl;
			//	}
			//	//std::cout << std::endl;
			//	for (int i = 0; i < OutputCount; i++) {
			//		std::cout << Output[i].Location << "\t" << Output[i].ArrayCount << "\t\t\t\t\t";
			//		std::cout << glsl::get_type_string(Output[i].Storage) << " " << glsl::get_type_string(Output[i].Type) << " " << Output[i].Name << std::endl;
			//	}
			//	return false;
			//}

			//bool shader_program::link(shader& lhs, shader& rhs) {
			//	if ((lhs.Type == GL_VERTEX_SHADER) && (rhs.Type == GL_FRAGMENT_SHADER)) {
			//		VertexShader = &lhs; PixelShader = &rhs;
			//	}
			//	else if ((lhs.Type == GL_FRAGMENT_SHADER) && (rhs.Type == GL_VERTEX_SHADER)) {
			//		VertexShader = &rhs; PixelShader = &lhs;
			//	}
			//	else {
			//		VertexShader = nullptr; PixelShader = nullptr;
			//		return true;
			//	}
			//
			//	if ((VertexShader == nullptr) || (PixelShader == nullptr)) { return true; }
			//	if ((VertexShader->ID == 0) || (PixelShader->ID == 0) || (ID == 0)) { return true; }
			//	
			//	reserve_args(VertexShader->Input.size(), VertexShader->Uniform.size() + PixelShader->Uniform.size(), PixelShader->Output.size());
			//
			//	glAttachShader(ID, VertexShader->ID);
			//	glAttachShader(ID, PixelShader->ID);
			//	glLinkProgram(ID);
			//	glDetachShader(ID, PixelShader->ID);
			//	glDetachShader(ID, VertexShader->ID);
			//
			//	// Gather Attributes
			//	for (int i = 0; i < VertexShader->Input.size(); i++) {
			//		InputLocation[i] = glGetAttribLocation(ID, VertexShader->Input[i].Identifier);
			//	}
			//
			//	// Gather Uniform Variables.
			//	for (int i = 0; i < VertexShader->Uniform.size(); i++) {
			//		UniformLocation[i] = glGetUniformLocation(ID, VertexShader->Uniform[i].Identifier);
			//	}
			//	for (int i = 0; i < PixelShader->Uniform.size(); i++) {
			//		UniformLocation[i + VertexShader->Uniform.size()] = glGetUniformLocation(ID, PixelShader->Uniform[i].Identifier);
			//	}
			//
			//	// Get Frag data locations for pixel output.
			//	for (int i = 0; i < PixelShader->Output.size(); i++) {
			//		OutputLocation[i] = glGetFragDataLocation(ID, PixelShader->Output[i].Identifier);
			//		OutputAttachment[i] = OutputLocation[i] + GL_COLOR_ATTACHMENT0;
			//	}
			//
			//	if (VAO != 0) {
			//		if (VAO != BoundVAO) { glBindVertexArray(VAO); BoundVAO = VAO; }
			//		for (int i = 0; i < InputCount; i++) {
			//			if (InputLocation[i] != -1) {
			//				glEnableVertexAttribArray(InputLocation[i]);
			//			}
			//		}
			//	}
			//
			//	if (FBO != 0) {
			//		if (FBO != BoundFBO) { glBindFramebuffer(GL_FRAMEBUFFER, FBO); BoundFBO = FBO; }
			//		glDrawBuffers(OutputCount, OutputAttachment);
			//	}
			//
			//	return false;
			//}

			//bool shader_program::set(int Index, buffer & Buffer, int AttributeIndex) {
			//	if (VAO == 0) { return false; }
			//	if ((Index < 0) || (Index > InputCount)) { return true; }
			//	if ((AttributeIndex < 0) || (AttributeIndex > Buffer.AttributeCount)) { return true; }
			//	InputBuffer[Index] = &Buffer;
			//	InputAttribute[Index] = AttributeIndex;
			//	if (VAO != BoundVAO) { glBindVertexArray(VAO); BoundVAO = VAO; }
			//	glBindBuffer(Buffer.dType, Buffer.ID);
			//	glVertexAttribPointer(InputLocation[Index], Buffer.Size[AttributeIndex], Buffer.DataType[AttributeIndex], Buffer.Normalized[AttributeIndex], Buffer.Stride, (GLvoid*)(Buffer.Offset[AttributeIndex]));
			//	glBindBuffer(Buffer.dType, 0);
			//	return false;
			//}

			//bool shader_program::attrib_divisor(int Index, int Div) {
			//	if ((Index < 0) || (Index > InputCount)) { return true; }
			//	if (VAO == 0) { return false; }
			//	if (VAO != BoundVAO) { glBindVertexArray(VAO); BoundVAO = VAO; }
			//	glVertexAttribDivisor(InputLocation[Index], InputDivisor[Index]);
			//	return false;
			//}

			//int shader_program::set_uniform(int Index, float X) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniform1f(Uniform[Index].Location, X);
			//	return false;
			//}
			//
			//int shader_program::set_uniform(int Index, vec2 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniform2f(Uniform[Index].Location, arg.x, arg.y);
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, vec3 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniform3f(Uniform[Index].Location, arg.x, arg.y, arg.z);
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, vec4 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniform4f(Uniform[Index].Location, arg.x, arg.y, arg.z, arg.t);
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat2 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix2fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat3x2 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix3x2fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat4x2 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix4x2fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat2x3 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix2x3fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat3 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix3fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat4x3 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix4x3fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat2x4 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix2x4fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat3x4 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix3x4fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}
			//
			//int shader_program::set_uniform(int Index, mat4 arg) {
			//	if (SPO == 0) { return true; }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); BoundSPO = SPO; }
			//	glUniformMatrix4fv(Uniform[Index].Location, 1, GL_FALSE, ((const GLfloat*)(&arg)));
			//	return 0;
			//}

			//bool shader_program::set(int Index, glm::mat2 Arg) {
			//	if (ID == 0) { return true; }
			//	if (ID != BoundID) { glUseProgram(ID); BoundID = ID; }
			//	glUniformMatrix2fv(UniformLocation[Index], 1, GL_FALSE, &Arg[0][0]);
			//	return false;
			//}
			//
			//bool shader_program::set(int Index, glm::mat3 Arg) {
			//	if (ID == 0) { return true; }
			//	if (ID != BoundID) { glUseProgram(ID); BoundID = ID; }
			//	glUniformMatrix3fv(UniformLocation[Index], 1, GL_FALSE, &Arg[0][0]);
			//	return false;
			//}
			//
			//bool shader_program::set(int Index, glm::mat4 Arg) {
			//	if (ID == 0) { return true; }
			//	if (ID != BoundID) { glUseProgram(ID); BoundID = ID; }
			//	glUniformMatrix4fv(UniformLocation[Index], 1, GL_FALSE, &Arg[0][0]);
			//	return false;
			//}

			//bool shader_program::set(int Index, GLenum Slot, texture & Tex) {
			//	if (ID == 0) { return true; }
			//	if (ID != BoundID) { glUseProgram(ID); BoundID = ID; }
			//	glActiveTexture(Slot);
			//	glBindTexture(Tex.dType, Tex.ID);
			//	glUniform1i(UniformLocation[Index], (Slot - GL_TEXTURE0));
			//	return false;
			//}

			//bool shader_program::set(int Index, texture & RenderTarget, int DepthIndex) {
			//	if ((!FBOEnable) && (FBO == 0)) { return true; }
			//	if ((Index < 0) || (Index > OutputCount)) { return true; }
			//	
			//	if (FBO != BoundFBO) { glBindFramebuffer(GL_FRAMEBUFFER, FBO); BoundFBO = FBO; }
			//
			//	Output[Index].Texture = &RenderTarget;
			//	Output[Index].Depth = DepthIndex;
			//
			//	switch (RenderTarget.dType) {
			//	default:
			//		break;
			//	case GL_TEXTURE_1D:
			//		glFramebufferTexture1D(GL_FRAMEBUFFER, OutputAttachment[Index], RenderTarget.dType, RenderTarget.ID, RenderTarget.LevelOfDetail);
			//		break;
			//	case GL_TEXTURE_2D: case GL_TEXTURE_1D_ARRAY:
			//		glFramebufferTexture2D(GL_FRAMEBUFFER, OutputAttachment[Index], RenderTarget.dType, RenderTarget.ID, RenderTarget.LevelOfDetail);
			//		break;
			//	case GL_TEXTURE_3D: case GL_TEXTURE_2D_ARRAY:
			//		glFramebufferTexture3D(GL_FRAMEBUFFER, OutputAttachment[Index], RenderTarget.dType, RenderTarget.ID, RenderTarget.LevelOfDetail, DepthIndex);
			//		break;
			//	}
			//	return false;
			//}

			//int shader_program::draw_arrays(GLenum DrawMode, GLint VertexStart, GLint VertexCount) {
			//	glDrawArrays(DrawMode, VertexStart, VertexCount);
			//	return 0;
			//}
			//
			//int shader_program::multi_draw_arrays(GLenum DrawMode, GLint * VertexStart, GLsizei * VertexCount, GLsizei PrimitiveCount) {
			//	glMultiDrawArrays(DrawMode, VertexStart, VertexCount, PrimitiveCount);
			//	return 0;
			//}
			//
			//int shader_program::draw_arrays_instanced(GLenum DrawMode, GLint VertexStart, GLsizei VertexCount, GLsizei PrimitiveCount) {
			//	glDrawArraysInstanced(DrawMode, VertexStart, VertexCount, PrimitiveCount);
			//	return 0;
			//}
			//
			//int shader_program::draw_elements(GLenum DrawMode, GLsizei IndexCount, GLenum IndexDataType, GLvoid* Indices) {
			//	glDrawElements(DrawMode, IndexCount, IndexDataType, Indices);
			//	return 0;
			//}
			//
			//int shader_program::draw_range_elements(GLenum DrawMode, GLuint IndexStart, GLuint IndexEnd, GLsizei IndexCount, GLenum IndexDataType, GLvoid * Indices) {
			//	glDrawRangeElements(DrawMode, IndexStart, IndexEnd, IndexCount, IndexDataType, Indices);
			//	return false;
			//}
			//
			//int shader_program::multi_draw_elements(GLenum DrawMode, GLsizei * IndexCount, GLenum IndexDataType, GLvoid ** Indices, GLsizei PrimitiveCount) {
			//	glMultiDrawElements(DrawMode, IndexCount, IndexDataType, Indices, PrimitiveCount);
			//	return 0;
			//}
			//
			//int shader_program::draw_elements_instanced(GLenum DrawMode, GLsizei IndexCount, GLenum DataType, GLvoid * Indices, GLsizei PrimitiveCount) {
			//	glDrawElementsInstanced(DrawMode, IndexCount, DataType, Indices, PrimitiveCount);
			//	return 0;
			//}

			//bool shader_program::reserve_args(int InCount, int UniCount, int OutCount) {
			//	if (InputBuffer != nullptr) { delete[] InputBuffer; InputBuffer = nullptr; }
			//	if (InputAttribute != NULL) { free(InputAttribute); InputAttribute = NULL; }
			//	if (InputLocation != NULL) { free(InputLocation); InputLocation = NULL; }
			//	if (InputDivisor != NULL) { free(InputDivisor); InputDivisor = NULL; }
			//	if (UniformLocation != NULL) { free(UniformLocation); UniformLocation = NULL; }
			//	if (OutputTexture != nullptr) { delete[] OutputTexture; OutputTexture = nullptr; }
			//	if (OutputDepth != NULL) { free(OutputDepth); OutputDepth = NULL; }
			//	if (OutputLocation != NULL) { free(OutputLocation); OutputLocation = NULL; }
			//	InputCount = 0;
			//	UniformCount = 0;
			//	OutputCount = 0;
			//
			//	InputCount = InCount;
			//	UniformCount = UniCount;
			//	OutputCount = OutCount;
			//	if (InputCount > 0) {
			//		InputBuffer = new buffer*[InputCount];
			//		InputAttribute = (int*)malloc(InputCount * sizeof(int));
			//		InputLocation = (GLint*)malloc(InputCount * sizeof(GLint));
			//		InputDivisor = (GLint*)malloc(InputCount * sizeof(GLint));
			//	}
			//
			//	if (UniformCount > 0) {
			//		UniformLocation = (GLint*)malloc(UniformCount * sizeof(GLint));
			//	}
			//
			//	if (OutputCount > 0) {
			//		OutputTexture = new texture*[OutputCount];
			//		OutputDepth = (int*)malloc(OutputCount * sizeof(int));
			//		OutputLocation = (GLint*)malloc(OutputCount * sizeof(GLint));
			//		OutputAttachment = (GLenum*)malloc(OutputCount * sizeof(GLenum));
			//	}
			//
			//	for (int i = 0; i < InputCount; i++) {
			//		InputBuffer[i] = nullptr;
			//		InputAttribute[i] = 0;
			//		InputLocation[i] = -1;
			//		InputDivisor[i] = 0;
			//	}
			//
			//	for (int i = 0; i < UniformCount; i++) {
			//		UniformLocation[i] = -1;
			//	}
			//
			//	for (int i = 0; i < OutputCount; i++) {
			//		OutputTexture[i] = nullptr;
			//		OutputDepth[i] = 0;
			//		OutputLocation[i] = -1;
			//		OutputAttachment[i] = NULL;
			//	}
			//
			//	return false;
			//}
			//
			//bool shader_program::release_args() {
			//
			//	if (InputBuffer != nullptr) { delete[] InputBuffer; InputBuffer = nullptr; }
			//	if (InputAttribute != NULL) { free(InputAttribute); InputAttribute = NULL; }
			//	if (InputLocation != NULL) { free(InputLocation); InputLocation = NULL; }
			//	if (InputDivisor != NULL) { free(InputDivisor); InputDivisor = NULL; }
			//
			//	if (UniformLocation != NULL) { free(UniformLocation); UniformLocation = NULL; }
			//
			//	if (OutputTexture != nullptr) { delete[] OutputTexture; OutputTexture = nullptr; }
			//	if (OutputDepth != NULL) { free(OutputDepth); OutputDepth = NULL; }
			//	if (OutputLocation != NULL) { free(OutputLocation); OutputLocation = NULL; }
			//
			//	InputCount = 0;
			//	UniformCount = 0;
			//	OutputCount = 0;
			//
			//	return false;
			//}

			//bool shader_program::bind() {
			//	if (FBO != BoundFBO) { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }
			//	if (VAO != BoundVAO) { glBindVertexArray(VAO); }
			//	if (SPO != BoundSPO) { glUseProgram(SPO); }
			//
			//	if ((FBOEnable) && (FBO != BoundFBO) && (FBO != 0)) {
			//		// FACE CULLING
			//		if (EnableFaceCulling != isFaceCullingEnabled) {
			//			if (EnableFaceCulling) {
			//				glEnable(GL_CULL_FACE);
			//				glFrontFace(FrontFaceSelect);
			//				glCullFace(CullFaceSelect);
			//			}
			//			else {
			//				glDisable(GL_CULL_FACE);
			//			}
			//			isFaceCullingEnabled = EnableFaceCulling;
			//		}
			//
			//		// SCISSOR TEST
			//		if (EnableScissorTest != isScissorTestEnabled) {
			//			if (EnableScissorTest) {
			//				glEnable(GL_SCISSOR_TEST);
			//				glScissor(ScissorPositionX, ScissorPositionY, ScissorSizeX, ScissorSizeY);
			//			}
			//			else {
			//				glDisable(GL_SCISSOR_TEST);
			//			}
			//			isScissorTestEnabled = EnableScissorTest;
			//		}
			//
			//		// MULTISAMPLE
			//		if (EnableMultisample != isMultisampleEnabled) {
			//			if (EnableMultisample) {
			//				glEnable(GL_MULTISAMPLE);
			//				glSampleCoverage(MultisampleValue, MultisampleInversion);
			//			}
			//			else {
			//				glDisable(GL_MULTISAMPLE);
			//			}
			//			isMultisampleEnabled = EnableMultisample;
			//		}
			//
			//		// DEPTH TEST
			//		if (EnableDepthTest != isDepthTestEnabled) {
			//			if (EnableDepthTest) {
			//				glEnable(GL_DEPTH);
			//				glDepthFunc(DepthOperation);
			//				glDepthRange(DepthNear, DepthFar);
			//				glDepthMask(DepthFlag);
			//			}
			//			else {
			//				glDisable(GL_DEPTH);
			//			}
			//			isDepthTestEnabled = EnableDepthTest;
			//		}
			//
			//		// STENCIL TEST
			//		if (EnableStencilTest != isStencilTestEnabled) {
			//			if (EnableStencilTest) {
			//				glEnable(GL_STENCIL_TEST);
			//				glStencilFunc(StencilOperation, StencilReferenceValue, StencilMask);
			//				glStencilOp(StencilTestFailureAction, DepthTestFailureAction, StencilAndDepthPassAction);
			//				glStencilMask(StencilMask);
			//			}
			//			else {
			//				glDisable(GL_STENCIL_TEST);
			//			}
			//			isStencilTestEnabled = EnableStencilTest;
			//		}
			//
			//		// BLENDING
			//		if (EnableBlending != isBlendingEnabled) {
			//			if (EnableBlending) {
			//				glEnable(GL_BLEND);
			//				glBlendColor(BlendRed, BlendGreen, BlendBlue, BlendAlpha);
			//				glBlendFunc(BlendingSourceMultiplier, BlendingDestinationMultiplier);
			//				glBlendEquation(BlendingOperation);
			//			}
			//			else {
			//				glDisable(GL_BLEND);
			//			}
			//			isBlendingEnabled = EnableBlending;
			//		}
			//
			//		// DITHERING
			//		if (EnableDithering != isDitheringEnabled) {
			//			if (EnableDithering) {
			//				glEnable(GL_DITHER);
			//			}
			//			else {
			//				glDisable(GL_DITHER);
			//			}
			//			isDitheringEnabled = EnableDithering;
			//		}
			//	}
			//
			//
			//	if ((FBOEnable) && (FBO != BoundFBO) && (FBO != 0)) {
			//		glViewport(FramePositionX, FramePositionY, FrameSizeX, FrameSizeY);
			//
			//		ClearOptions = GL_COLOR_BUFFER_BIT;
			//		if (EnableDepthTest) { ClearOptions |= GL_DEPTH_BUFFER_BIT; }
			//		if (EnableStencilTest) { ClearOptions |= GL_STENCIL_BUFFER_BIT; }
			//
			//		glClear(ClearOptions);
			//		glClearColor(FrameClearRed, FrameClearGreen, FrameClearBlue, FrameClearAlpha);
			//		if (EnableDepthTest) { glClearDepth(FrameClearDepth); }
			//		if (EnableStencilTest) { glClearStencil(FrameClearStencil); }
			//	}
			//
			//	if (FBO != BoundFBO) { BoundFBO = FBO; }
			//	if (VAO != BoundVAO) { BoundVAO = VAO; }
			//	if (SPO != BoundSPO) { BoundSPO = SPO; }
			//	return false;
			//}
			//
			//void shader_program::bind_fbo() {
			//	if (FBO != BoundFBO) { 
			//		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
			//		BoundFBO = FBO;
			//	}
			//
			//	// FACE CULLING
			//	if (EnableFaceCulling != isFaceCullingEnabled) {
			//		if (EnableFaceCulling) {
			//			glEnable(GL_CULL_FACE);
			//			glFrontFace(FrontFaceSelect);
			//			glCullFace(CullFaceSelect);
			//		}
			//		else {
			//			glDisable(GL_CULL_FACE);
			//		}
			//		isFaceCullingEnabled = EnableFaceCulling;
			//	}
			//
			//	// SCISSOR TEST
			//	if (EnableScissorTest != isScissorTestEnabled) {
			//		if (EnableScissorTest) {
			//			glEnable(GL_SCISSOR_TEST);
			//			glScissor(ScissorPositionX, ScissorPositionY, ScissorSizeX, ScissorSizeY);
			//		}
			//		else {
			//			glDisable(GL_SCISSOR_TEST);
			//		}
			//		isScissorTestEnabled = EnableScissorTest;
			//	}
			//
			//	// MULTISAMPLE
			//	if (EnableMultisample != isMultisampleEnabled) {
			//		if (EnableMultisample) {
			//			glEnable(GL_MULTISAMPLE);
			//			glSampleCoverage(MultisampleValue, MultisampleInversion);
			//		}
			//		else {
			//			glDisable(GL_MULTISAMPLE);
			//		}
			//		isMultisampleEnabled = EnableMultisample;
			//	}
			//
			//	// DEPTH TEST
			//	if (EnableDepthTest != isDepthTestEnabled) {
			//		if (EnableDepthTest) {
			//			glEnable(GL_DEPTH);
			//			glDepthFunc(DepthOperation);
			//			glDepthRange(DepthNear, DepthFar);
			//			glDepthMask(DepthFlag);
			//		}
			//		else {
			//			glDisable(GL_DEPTH);
			//		}
			//		isDepthTestEnabled = EnableDepthTest;
			//	}
			//
			//	// STENCIL TEST
			//	if (EnableStencilTest != isStencilTestEnabled) {
			//		if (EnableStencilTest) {
			//			glEnable(GL_STENCIL_TEST);
			//			glStencilFunc(StencilOperation, StencilReferenceValue, StencilMask);
			//			glStencilOp(StencilTestFailureAction, DepthTestFailureAction, StencilAndDepthPassAction);
			//			glStencilMask(StencilMask);
			//		}
			//		else {
			//			glDisable(GL_STENCIL_TEST);
			//		}
			//		isStencilTestEnabled = EnableStencilTest;
			//	}
			//
			//	// BLENDING
			//	if (EnableBlending != isBlendingEnabled) {
			//		if (EnableBlending) {
			//			glEnable(GL_BLEND);
			//			glBlendColor(BlendRed, BlendGreen, BlendBlue, BlendAlpha);
			//			glBlendFunc(BlendingSourceMultiplier, BlendingDestinationMultiplier);
			//			glBlendEquation(BlendingOperation);
			//		}
			//		else {
			//			glDisable(GL_BLEND);
			//		}
			//		isBlendingEnabled = EnableBlending;
			//	}
			//
			//	// DITHERING
			//	if (EnableDithering != isDitheringEnabled) {
			//		if (EnableDithering) {
			//			glEnable(GL_DITHER);
			//		}
			//		else {
			//			glDisable(GL_DITHER);
			//		}
			//		isDitheringEnabled = EnableDithering;
			//	}
			//
			//	glViewport(FramePositionX, FramePositionY, FrameSizeX, FrameSizeY);
			//
			//	ClearOptions = GL_COLOR_BUFFER_BIT;
			//	if (EnableDepthTest) { ClearOptions |= GL_DEPTH_BUFFER_BIT; }
			//	if (EnableStencilTest) { ClearOptions |= GL_STENCIL_BUFFER_BIT; }
			//
			//	glClear(ClearOptions);
			//	glClearColor(FrameClearRed, FrameClearGreen, FrameClearBlue, FrameClearAlpha);
			//	if (EnableDepthTest) { glClearDepth(FrameClearDepth); }
			//	if (EnableStencilTest) { glClearStencil(FrameClearStencil); }
			//
			//}
			//
			//void shader_program::bind_vao() {
			//	if (VAO != BoundVAO) { 
			//		glBindVertexArray(VAO);
			//		BoundVAO = VAO; 
			//	}
			//	//if (IBO != buffer::BoundIBO) { 
			//	//	buffer::BoundIBO = IBO; 
			//	//}
			//}
			//
			//void shader_program::bind_id() {
			//	if (SPO != BoundSPO) { 
			//		glUseProgram(SPO); 
			//		BoundSPO = SPO; 
			//	}
			//}

		}
	}
}