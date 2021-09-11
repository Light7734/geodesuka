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