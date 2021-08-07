#pragma once
#ifndef GEODESUKA_CORE_GCL_SHADER_H
#define GEODESUKA_CORE_GCL_SHADER_H

#include "gcl.h"

#include "device.h"
#include "device_context.h"

#include "../io/file.h"

#ifndef _COMPILER_INTERFACE_INCLUDED_
// Forward Declaration for glslang
namespace glslang {
	class TShader;
}
#endif // !_COMPILER_INTERFACE_INCLUDED_

namespace geodesuka {
	namespace core {
		namespace gcl {

			class shader /*: public glslang::TIntermTraverser*/ {
			public:

				enum stage {
					VERTEX,
					TESSELLATION_CONTROL,
					TESSELLATION_EVALUATION,
					GEOMETRY,
					PIXEL,
					COMPUTE
				};

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

				shader(device_context* aDeviceContext, io::file* File);
				 
				//virtual void visitSymbol(glslang::TIntermSymbol* Symbol)											override;
				//virtual void visitConstantUnion(glslang::TIntermConstantUnion* ConstantUnion)						override;
				//virtual bool visitBinary(glslang::TVisit VisitType, glslang::TIntermBinary* Binary)					override;
				//virtual bool visitUnary(glslang::TVisit VisitType, glslang::TIntermUnary* Unary)					override;
				//virtual bool visitSelection(glslang::TVisit VisitType, glslang::TIntermSelection* Selection)		override;
				//virtual bool visitAggregate(glslang::TVisit VisitType, glslang::TIntermAggregate* Aggregate)		override;
				//virtual bool visitLoop(glslang::TVisit VisitType, glslang::TIntermLoop* Loop)						override;
				//virtual bool visitBranch(glslang::TVisit VisitType, glslang::TIntermBranch* Branch)					override;
				//virtual bool visitSwitch(glslang::TVisit VisitType, glslang::TIntermSwitch* Switch)					override;

			private:

				// Interface with 
				glslang::TShader mTShader;
			};

		}
	}
}

#endif // !GEODESUKA_CORE_GCL_SHADER_H