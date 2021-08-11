#pragma once
#ifndef GEODESUKA_CORE_GCL_SHADER_H
#define GEODESUKA_CORE_GCL_SHADER_H

#include <vector>

#include "gcl.h"

#include "device.h"
#include "device_context.h"

#include "../io/file.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class shader /*: public glslang::TIntermTraverser*/ {
			public:

				enum stage {
					UNKNOWN,
					VERTEX,
					TESSELLATION_CONTROL,
					TESSELLATION_EVALUATION,
					GEOMETRY,
					FRAGMENT,
					COMPUTE
				};

				VkResult ErrorCode;

				// Create a shader from provided source string.
				shader(device_context* aDeviceContext, stage aStage, const char* aSource);

				// Use for compiling a shader object and creating it.
				shader(device_context* aDeviceContext, const char* aFilePath);

				// Create a shader from plain_text object.
				//shader(device_context* aDeviceContext, io::plaintext &aPlainText);

				// Create a shader from SPIRV bytecode object.
				//shader(device_context *aDeviceContext, io::byte_code &aByteCode);
				 
				// Just clears shader up.
				~shader();

				//virtual void visitSymbol(glslang::TIntermSymbol* Symbol)											override;
				//virtual void visitConstantUnion(glslang::TIntermConstantUnion* ConstantUnion)						override;
				//virtual bool visitBinary(glslang::TVisit VisitType, glslang::TIntermBinary* Binary)					override;
				//virtual bool visitUnary(glslang::TVisit VisitType, glslang::TIntermUnary* Unary)					override;
				//virtual bool visitSelection(glslang::TVisit VisitType, glslang::TIntermSelection* Selection)		override;
				//virtual bool visitAggregate(glslang::TVisit VisitType, glslang::TIntermAggregate* Aggregate)		override;
				//virtual bool visitLoop(glslang::TVisit VisitType, glslang::TIntermLoop* Loop)						override;
				//virtual bool visitBranch(glslang::TVisit VisitType, glslang::TIntermBranch* Branch)					override;
				//virtual bool visitSwitch(glslang::TVisit VisitType, glslang::TIntermSwitch* Switch)					override;

				VkShaderStageFlagBits get_stage();
				VkShaderModule get_handle();

			private:

				io::file* FileHandle;						// Reference Asset File.
				device_context* ParentDC;					// Parent Device Context of this Shader

				stage Stage;
				VkShaderStageFlagBits VkStage;

				bool isValid;
				std::vector<unsigned int> Binary;			// Compiled SPIRV Binary
				VkShaderModuleCreateInfo CreateInfo{};		// Creation Info
				VkShaderModule Handle;						// Simple Handle

			};

		}
	}
}

#endif // !GEODESUKA_CORE_GCL_SHADER_H