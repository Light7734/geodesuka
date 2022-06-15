#pragma once
#ifndef GEODESUKA_CORE_GCL_SHADER_H
#define GEODESUKA_CORE_GCL_SHADER_H

#include <vector>

#include "../io/file.h"

#include "config.h"
#include "device.h"
#include "context.h"

namespace geodesuka::core::gcl {

	class shader /*: public glslang::TIntermTraverser*/ {
	public:

		friend class engine;

		enum stage {
			UNKNOWN,
			VERTEX,
			TESSELLATION_CONTROL,
			TESSELLATION_EVALUATION,
			GEOMETRY,
			FRAGMENT,
			COMPUTE
		};

		vk_result ErrorCode;

		// Create a shader from provided source string.
		shader(context* aDeviceContext, stage aStage, const char* aSource);

		// Create a shader from plain_text object.
		//shader(device_context* aDeviceContext, io::plaintext &aPlainText);

		// Create a shader from SPIRV bytecode object.
		//shader(device_context *aDeviceContext, io::byte_code &aByteCode);

		// Just clears shader up.
		~shader();

		vk_shader_stage_flag_bits get_stage();
		vk_shader_module get_handle();

		VkPipelineShaderStageCreateInfo stageci();

	private:

		static bool initialize();
		static void terminate();

		io::file* FileHandle;						// Reference Asset File.
		context* ParentDC;					// Parent Device Context of this Shader

		stage Stage;
		VkShaderStageFlagBits VkStage;

		bool isValid;
		std::vector<unsigned int> Binary;			// Compiled SPIRV Binary
		VkShaderModuleCreateInfo CreateInfo{};		// Creation Info
		VkShaderModule Handle;						// Simple Handle

	};

}

#endif // !GEODESUKA_CORE_GCL_SHADER_H
