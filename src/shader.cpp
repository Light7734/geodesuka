#include <geodesuka/core/gcl/shader.h>

#include <glslang/Public/ShaderLang.h>
#include <glslang/Include/ResourceLimits.h>
#include <StandAlone/ResourceLimits.h>

#include <SPIRV/GlslangToSpv.h>


namespace geodesuka {
	namespace core {
		namespace gcl {

			shader::shader(context* aDeviceContext, stage aStage, const char* aSource) {
				this->ErrorCode = VkResult::VK_SUCCESS;

				this->FileHandle = nullptr;
				this->ParentDC = aDeviceContext;

				this->Stage = aStage;


				this->isValid = true;
				this->Stage = aStage;
				EShLanguage lShaderStage;
				switch (this->Stage) {
				default:
					this->Stage = UNKNOWN;
					this->VkStage = (VkShaderStageFlagBits)0;
					this->isValid = false;
					break;
				case VERTEX:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
					lShaderStage = EShLanguage::EShLangVertex;
					break;
				case TESSELLATION_CONTROL:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
					lShaderStage = EShLanguage::EShLangTessControl;
					break;
				case TESSELLATION_EVALUATION:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
					lShaderStage = EShLanguage::EShLangTessEvaluation;
					break;
				case GEOMETRY:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_GEOMETRY_BIT;
					lShaderStage = EShLanguage::EShLangGeometry;
					break;
				case FRAGMENT:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
					lShaderStage = EShLanguage::EShLangFragment;
					break;
				case COMPUTE:
					this->VkStage = VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;
					lShaderStage = EShLanguage::EShLangCompute;
					break;
				}

				if (this->isValid) {
					glslang::TShader lShader(lShaderStage);

					// Clean me up later
					lShader.setStrings(&aSource, 1);
					lShader.setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientVulkan, 120);
					lShader.setEnvClient(glslang::EShClient::EShClientVulkan, glslang::EShTargetClientVersion::EShTargetVulkan_1_2);
					lShader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv, glslang::EShTargetLanguageVersion::EShTargetLanguageVersionCount);
					lShader.setEntryPoint("main");

					EShMessages Options = (EShMessages)(EShMessages::EShMsgDebugInfo | EShMessages::EShMsgVulkanRules | EShMessages::EShMsgSpvRules | EShMessages::EShMsgAST | EShMessages::EShMsgDefault);
					this->isValid = lShader.parse(&glslang::DefaultTBuiltInResource, 120, EProfile::ECoreProfile, false, false, Options);
					if (this->isValid) {
						// returns Binary data after compiling from AST.
						glslang::GlslangToSpv(*lShader.getIntermediate(), this->Binary);
					}
				}

				if (this->isValid) {
					this->CreateInfo.sType			= VkStructureType::VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
					this->CreateInfo.pNext			= NULL;
					this->CreateInfo.flags			= 0; // Reserved for future use. (Ignored)
					this->CreateInfo.codeSize		= this->Binary.size()*sizeof(uint32_t);
					this->CreateInfo.pCode			= reinterpret_cast<const uint32_t*>(this->Binary.data());

					this->ErrorCode = vkCreateShaderModule(this->ParentDC->handle(), &this->CreateInfo, NULL, &this->Handle);
					if (this->ErrorCode != VkResult::VK_SUCCESS) this->isValid = false;
				}
			}

			shader::~shader() {
				//this->FileHandle	= nullptr;
				//this->ParentDC		= nullptr;
				//this->Stage			= UNKNOWN;
				//this->VkStage		= (VkShaderStageFlagBits)0;
				//this->isValid		= false;
				this->Binary.clear();
				vkDestroyShaderModule(this->ParentDC->handle(), this->Handle, NULL);
			}

			VkShaderStageFlagBits shader::get_stage() {
				return this->VkStage;
			}

			VkShaderModule shader::get_handle() {
				return this->Handle;
			}

		}
	}
}


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include <glslang/MachineIndependent/attribute.h>
//#include <glslang/MachineIndependent/gl_types.h>
////#include <glslang/MachineIndependent/glslang_tab.cpp.h>
//#include <glslang/MachineIndependent/Initialize.h>
//#include <glslang/MachineIndependent/iomapper.h>
//#include <glslang/MachineIndependent/LiveTraverser.h>
//#include <glslang/MachineIndependent/localintermediate.h>
//#include <glslang/MachineIndependent/ParseHelper.h>
//#include <glslang/MachineIndependent/parseVersions.h>
//#include <glslang/MachineIndependent/pch.h>
//#include <glslang/MachineIndependent/propagateNoContraction.h>
//#include <glslang/MachineIndependent/reflection.h>
//#include <glslang/MachineIndependent/RemoveTree.h>
//#include <glslang/MachineIndependent/Scan.h>
//#include <glslang/MachineIndependent/ScanContext.h>
//#include <glslang/MachineIndependent/SymbolTable.h>
//#include <glslang/MachineIndependent/Versions.h>
//
//#include <glslang/Include/arrays.h>
//#include <glslang/Include/BaseTypes.h>
//#include <glslang/Include/Common.h>
//#include <glslang/Include/InitializeGlobals.h>
//#include <glslang/Include/intermediate.h>
//#include <glslang/Include/PoolAlloc.h>
//#include <glslang/Include/ResourceLimits.h>
//#include <glslang/Include/revision.h>
//#include <glslang/Include/ShHandle.h>
//#include <glslang/Include/Types.h>
//
//#include <glslang/Public/ShaderLang.h>

//#include <StandAlone/ResourceLimits.h>


//#include "../gcl/gcl.h"


//shader::shader() {
//
//}
//
////shader::shader(int ShaderType) {
////	Type = ShaderType;
////	ID = glCreateShader(ShaderType);
////}
//
//shader::~shader() {
//	if (ID != 0) { glDeleteShader(ID); ID = 0; }
//}
//
//GLenum shader::set_source(const char * Source) {
//	if (Source != NULL) {
//		size_t StrLength = strlen(Source);
//		if (StrLength > 0) {
//			if (Sauce != NULL) { free(Sauce); Sauce = NULL; }
//			Sauce = (char *)malloc((StrLength + 1)*sizeof(char));
//			if (Sauce != NULL) {
//				memcpy(Sauce, Source, StrLength*sizeof(char));
//				Sauce[StrLength] = '\0';
//			}
//		}
//	}
//	if ((ID != 0) && (Sauce != NULL)) {
//		glShaderSource(ID, 1, &Sauce, NULL);
//	}
//	return glGetError();
//}
//
//const char * shader::get_source() const {
//	return Sauce;
//}
//
//GLenum shader::get_param(GLenum ParamName, GLint * ParamVal) {
//	if (ID == 0) return -1;
//	glGetShaderiv(ID, ParamName, ParamVal);
//	return glGetError();
//}

//int shader::read(const char* FilePath) {
//	FILE* File = fopen(FilePath, "r");
//	if (File == NULL) return -1;
//	size_t FileSize = 0;
//	size_t FileLength = 0;
//	size_t SauceLength = 0;
//	int tErrorCode = 0;
//	tErrorCode |= fseek(File, 0L, SEEK_END);
//	FileSize = ftell(File);
//	tErrorCode |= fseek(File, 0L, SEEK_SET);
//	FileLength = FileSize / sizeof(char);
//	if (this->Sauce != NULL) {
//		SauceLength = strlen(this->Sauce);
//	}
//
//	void* nptr = NULL;
//	if (FileLength > 0) {
//		if (this->Sauce == NULL) {
//			nptr = malloc((FileLength + 1) * sizeof(char));
//		}
//		else {
//			if (FileLength != SauceLength) {
//				nptr = realloc(this->Sauce, (FileLength + 1) * sizeof(char));
//			}
//			else {
//				nptr = (void *)this->Sauce;
//			}
//		}
//	}
//
//	if (nptr == NULL) {
//		fclose(File);
//		return -1;
//	}
//	if (nptr != (void*)this->Sauce) { this->Sauce = (char*)nptr; }
//	nptr = NULL;
//
//	fclose(File);
//
//	return 0;
//}

//int shader::write(const char* FilePath) {
//	return 0;
//}

//int shader::load(const char * ShaderSource) {
//	if (Sauce != NULL) { free(Sauce); Sauce = NULL; }
//
//	if (ShaderSource != NULL) {
//		Sauce = (char *)malloc((strlen(ShaderSource) + 1) * sizeof(char));
//		if (Sauce != NULL) {
//			memcpy(Sauce, ShaderSource, strlen(ShaderSource) * sizeof(char));
//			Sauce[strlen(ShaderSource)] = '\0';
//		}
//	}
//
//	if ((Sauce == NULL) && (ShaderSource != NULL)) { return -1; } // Probably out of memory...
//	if (ID == 0) { return 0; }
//
//	glShaderSource(ID, 1, &Sauce, NULL);
//	
//	return 0;
//}

//int shader::clear() {
//	if (Sauce != NULL) { free(Sauce); Sauce = NULL; }
//	return 0;
//}

/*
int shader::parse() {
	int Msgs = EShMessages::EShMsgDefault | EShMessages::EShMsgAST | EShMessages::EShMsgDebugInfo;

	glslang::TShader Shader(EShLanguage::EShLangVertex);
	Shader.setAutoMapLocations(true);
	Shader.setAutoMapBindings(true);

	Shader.setStrings(&Sauce, 1);
	Shader.setEnvInput(glslang::EShSource::EShSourceGlsl, EShLanguage::EShLangVertex, glslang::EShClient::EShClientOpenGL, 330);
	Shader.setEnvClient(glslang::EShClient::EShClientOpenGL, glslang::EShTargetClientVersion::EShTargetOpenGL_450);
	if (Shader.parse(&DefaultTBuiltInResource, 330, EProfile::ECoreProfile, false, false, (EShMessages)Msgs)) {
		std::cout << "SUCCESS" << std::endl;
	}
	else {
		std::cout << "FAILURE" << std::endl;
	}
	std::cout << Shader.getInfoLog() << std::endl;
	std::cout << Shader.getInfoDebugLog() << std::endl;
	std::cout << "\n\n\n";

	glslang::TIntermediate *AST = Shader.getIntermediate();
	TIntermNode *Root = AST->getTreeRoot();
	glslang::TIntermSequence Seq = Root->getAsAggregate()->getSequence();
	glslang::TIntermSequence LinkerSeq = Seq.back()->getAsAggregate()->getSequence();
	
	std::vector<glslang::TIntermSymbol*> Symbol;
	std::vector<glslang::TIntermTyped*> Type;
	for (int i = 0; i < LinkerSeq.size(); i++) {
		Symbol.push_back(LinkerSeq[i]->getAsSymbolNode());
		Type.push_back(LinkerSeq[i]->getAsSymbolNode()->getAsTyped());
	}


	return 0;
}
*/

//int shader::compile() {
//	if (ID == 0) { return true; }
//	glCompileShader(ID);
//	glGetShaderiv(ID, GL_COMPILE_STATUS, &isCompiled);
//	if (isCompiled == GL_TRUE) {
//		return false;
//	}
//	else {
//		char ErrorLog[512];
//		glGetShaderInfoLog(ID, 512, NULL, ErrorLog);
//		printf(ErrorLog);
//		//std::cout << ErrorLog << std::endl;
//		return true;
//	}
//}

