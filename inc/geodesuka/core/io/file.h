#pragma once
#ifndef GEODESUKA_CORE_IO_FILE_H
#define GEODESUKA_CORE_IO_FILE_H

#include <stdlib.h>

#include <vector>

#include "../util/str.h"

namespace geodesuka::core::io {

	class file {
	public:

		// Support audio formats later.
		struct extension {
			enum id : int {
				UNKNOWN,
				// Dynamic Libraries.
				DYNALIB_DYN,
				// --------------- Plain Text Files --------------- //
				SCRIPT_LUA,
				// rasterizer shaders
				SHADER_GLSL,		// shader library file.
				SHADER_HLSL,		// shader library file.
				SHADER_PVSH,		// (Per) Vertex Shaders
				SHADER_TCSH,		// Tesselation Control Shaders
				SHADER_TESH,		// Tesselation Evaluation Shaders
				SHADER_PGSH,		// (Per Primitive) Geometry Shaders
				SHADER_PPSH,		// (Per Pixel) Fragment Shaders
				// raytracing shaders.
				SHADER_RGSH,		// Ray generation shader
				SHADER_AHSH,		// Any Hit Shader
				SHADER_CHSH,		// Closest Hit Shader
				SHADER_RISH,		// Ray Intersection Shader
				SHADER_RMSH,		// Ray Miss Shader
				SHADER_RCSH,		// Ray Callable Shader?
				// compute shaders
				SHADER_CSH,		// Compute Shaders
				// --------------- Byte Code Files --------------- //
				SHADER_SPV,		// SPIR-V Compiled Shaders
				// --------------- Image Files --------------- //
				IMAGE_BMP,
				IMAGE_ICO,
				IMAGE_JPEG,
				IMAGE_JNG,
				IMAGE_KOALA,
				IMAGE_LBM,
				//IMAGE_IFF		= IMAGE_LBM,
				IMAGE_MNG,
				IMAGE_PBM,
				IMAGE_PBMRAW,
				IMAGE_PCD,
				IMAGE_PCX,
				IMAGE_PGM,
				IMAGE_PGMRAW,
				IMAGE_PNG,
				IMAGE_PPM,
				IMAGE_PPMRAW,
				IMAGE_RAS,
				IMAGE_TARGA,
				IMAGE_TIFF,
				IMAGE_WBMP,
				IMAGE_PSD,
				IMAGE_CUT,
				IMAGE_XBM,
				IMAGE_XPM,
				IMAGE_DDS,
				IMAGE_GIF,
				IMAGE_HDR,
				IMAGE_FAXG3,
				IMAGE_SGI,
				IMAGE_EXR,
				IMAGE_J2K,
				IMAGE_JP2,
				IMAGE_PFM,
				IMAGE_PICT,
				IMAGE_RAW,
				IMAGE_WEBP,
				IMAGE_JXR,
				// --------------- Model Files --------------- //
				MODEL_COLLADA,
				MODEL_X,
				MODEL_STP,
				MODEL_OBJ,
				MODEL_OBJNOMTL,
				MODEL_STL,
				MODEL_STLB,
				MODEL_PLY,
				MODEL_PLYB,
				MODEL_3DS,
				MODEL_GLTF2,
				MODEL_GLB2,
				MODEL_GLTF,
				MODEL_GLB,
				MODEL_ASSBIN,
				MODEL_ASSXML,
				MODEL_X3D,
				MODEL_FBX,
				MODEL_FBXA,
				MODEL_M3D,
				MODEL_M3DA,
				MODEL_3MF,
				MODEL_PBRT,
				MODEL_ASSJSON,
				// --------------- Audio Files --------------- //
				// --------------- Type Face Files --------------- //
				FONT_TTF,
				FONT_TTC,
				FONT_OTF,
				FONT_PFM,
				// Lua Script

			};

			static struct data_base {
				extension::id ExtensionID;
				std::vector<const char*> ExtensionStr;
			} DataBase[];

			static id str2id(const char* aString);
			static id str2id(util::str aString);
			static const char* id2str(id aID);

		};

		struct type {
			enum id : int {
				UNKNOWN,
				DYNALIB,
				SCRIPT,
				SHADER,
				IMAGE,
				MODEL,
				AUDIO,
				FONT
			};

			static id extid2typeid(extension::id aID);

		};

		// Used for file loading for engine.
		static file* open(const char* aFilePath);
		static void close(file* aFile);

		~file();

		util::str get_path();
		util::str get_dir();
		util::str get_name();
		util::str get_ext();
		void* get_data(size_t& ReturnSize);

	protected:

		file();
		file(const char* aFilePath);
		file(util::str& aFilePath);

		bool mset_path(util::str aFilePath);

	private:

		/*
		* The path of a file is the path of the object,
		* can either be relative, or full path. A full path
		* starts from the system root and describs the exact
		* path on the system, while relative will be relative
		* to process working directory.
		* Path = Dir + '/' + Name + '.' + Ext
		*/

		util::str Path;
		util::str Dir;
		util::str Name;
		util::str Ext;
		extension::id ID;

		/*
		* This will be the raw data loaded, maybe even possibly
		* just partial loading to save memory usage.
		*/
		size_t DataSize;
		void* Data;

	};

}

#endif // GEODESUKA_CORE_IO_FILE_H
