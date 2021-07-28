#pragma once
#ifndef SHADER_H
#define SHADER_H

//#include <glslang/Include/intermediate.h>
//#include <glslang/Public/ShaderLang.h>

#include "gcl.h"

#include "context.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class shader /*: public glslang::TIntermTraverser*/ {
			public:

				//enum stage {
				//	VERTEX						= EShLanguage::EShLangVertex,
				//	TESSELLATION_CONTROL		= EShLanguage::EShLangTessControl,
				//	TESSELLATION_EVALUATION		= EShLanguage::EShLangTessEvaluation,
				//	GEOMETRY					= EShLanguage::EShLangGeometry,
				//	PIXEL						= EShLanguage::EShLangFragment,
				//	COMPUTE						= EShLanguage::EShLangCompute
				//};

				//enum language {
				//	UNK			= glslang::EShSource::EShSourceNone,
				//	GLSL		= glslang::EShSource::EShSourceGlsl,
				//	HLSL		= glslang::EShSource::EShSourceHlsl
				//};

				//enum type_id {
				//	VERTEX_			= GL_VERTEX_SHADER,
				//	GEOMETRY		= GL_GEOMETRY_SHADER,
				//	PIXEL			= GL_FRAGMENT_SHADER
				//};

				//// Raw Shader Source
				//glslang::TShader *Shader;
				//char *Sauce;

				//stage Stage;
				//language Language;

				int Type;
				unsigned int ID;

				int ErrorCode;
				int isLoaded;
				int isCompiled;

				shader();
				//shader(const gcl::gl::context& Context, int ShaderType);
				~shader();

				GLenum set_source(const char* Source);
				const char* get_source() const;

				GLenum get_param(GLenum ParamName, GLint* ParamVal);

				// ---------- Util ---------- //

				// Deprecate ASAP
				int read(const char* FilePath);
				int write(const char* FilePath);

				int load(const char* Source);
				int clear();

				int parse();
				int compile();

				//virtual void visitSymbol(glslang::TIntermSymbol* Symbol)											override;
				//virtual void visitConstantUnion(glslang::TIntermConstantUnion* ConstantUnion)						override;
				//virtual bool visitBinary(glslang::TVisit VisitType, glslang::TIntermBinary* Binary)					override;
				//virtual bool visitUnary(glslang::TVisit VisitType, glslang::TIntermUnary* Unary)					override;
				//virtual bool visitSelection(glslang::TVisit VisitType, glslang::TIntermSelection* Selection)		override;
				//virtual bool visitAggregate(glslang::TVisit VisitType, glslang::TIntermAggregate* Aggregate)		override;
				//virtual bool visitLoop(glslang::TVisit VisitType, glslang::TIntermLoop* Loop)						override;
				//virtual bool visitBranch(glslang::TVisit VisitType, glslang::TIntermBranch* Branch)					override;
				//virtual bool visitSwitch(glslang::TVisit VisitType, glslang::TIntermSwitch* Switch)					override;

			};

		}
	}
}

#endif // !SHADER_H