#pragma once
#ifndef GEODESUKA_CORE_IO_FILE_H
#define GEODESUKA_CORE_IO_FILE_H

#include <stdlib.h>

#include <vector>

#include "../util/text.h"

/*
Maybe this should maintain of all accessed files and directories
throughout its life.
*/

/*
* 
* Extension: A file may have an extension of what type of file it
* may be specifically.
*/

namespace geodesuka {
	namespace core {
		namespace io {

			/*
			* This can be seen as a simple file handle type, it will be the responsibility
			* of the game engine to insure that identical files are not loaded in twice.
			*/

			class file {
			public:

				enum extension {
					EXT_UNK = -1,
					// --------------- Dynamic Libraries --------------- //
					EXT_DYN,
					// --------------- Image Files --------------- //
					EXT_BMP,
					EXT_ICO,
					EXT_JPEG,
					EXT_JNG,
					EXT_KOALA,
					EXT_LBM,
					//EXT_IFF		= EXT_LBM,
					EXT_MNG,
					EXT_PBM,
					EXT_PBMRAW,
					EXT_PCD,
					EXT_PCX,
					EXT_PGM,
					EXT_PGMRAW,
					EXT_PNG,
					EXT_PPM,
					EXT_PPMRAW,
					EXT_RAS,
					EXT_TARGA,
					EXT_TIFF,
					EXT_WBMP,
					EXT_PSD,
					EXT_CUT,
					EXT_XBM,
					EXT_XPM,
					EXT_DDS,
					EXT_GIF,
					EXT_HDR,
					EXT_FAXG3,
					EXT_SGI,
					EXT_EXR,
					EXT_J2K,
					EXT_JP2,
					//EXT_PFM			,
					EXT_PICT,
					EXT_RAW,
					EXT_WEBP,
					EXT_JXR,
					// --------------- Model Files --------------- //
					// --------------- Type Face Files --------------- //
					EXT_TTF,
					EXT_TTC,
					EXT_OTF,
					EXT_PFM,
					// --------------- Shader Files --------------- //
					EXT_VSH,		// (Per) Vertex Shaders
					EXT_TCSH,		// Tesselation Control Shaders
					EXT_TESH,		// Tesselation Evaluation Shaders
					EXT_GSH,		// (Per Primitive) Geometry Shaders
					EXT_PSH,		// (Per Pixel) Fragment Shaders
					EXT_CSH,		// Compute Shaders
					EXT_GLSL,		// Include Shader Function Files
					EXT_SPV,		// SPIR-V Compiled Shaders
					// OpenCL Kernel
					EXT_CL,
					// Lua Script
					EXT_LUA
				};

				enum class category {

					PLAIN_TEXT,
					BYTE_CODE,
					IMAGE,
					AUDIO,
					MODEL

				};

				// A more general version grouping.
				enum type {
					DYNALIB,
					IMAGE,
					TYPEFACE,
					SHADER,
					KERNEL,
					SCRIPT,
				};


				static struct built_in_type {
					extension Type;
					std::vector<util::text> Extension;
				} BuiltInTypes[];

				static extension str2type(util::text aString);
				static util::text type2str(extension aType);

				file();
				file(const char* aFilePath);
				file(util::text& aFilePath);
				~file();

				util::text get_path();
				util::text get_dir();
				util::text get_name();
				util::text get_ext();
				void* get_data(size_t& ReturnSize);

			protected:

				bool mset_path(util::text aFilePath);

			private:

				/*
				* The path of a file is the path of the object,
				* can either be relative, or full path. A full path
				* starts from the system root and describs the exact
				* path on the system, while relative will be relative
				* to process working directory.
				* Path = Dir + '/' + Name + '.' + Ext
				*/

				util::text Path;
				util::text Dir;
				util::text Name;
				util::text Ext;
				extension ID;

				/*
				* This will be the raw data loaded, maybe even possibly
				* just partial loading to save memory usage.
				*/
				size_t DataSize;
				void* Data;

			};

		}
	}
}

#endif // GEODESUKA_CORE_IO_FILE_H
