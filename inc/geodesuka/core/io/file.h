#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

#include <vector>

#include "../util/text.h"

/*
Maybe this should maintain of all accessed files and directories
throughout its life.
*/

//#include "../util/text.h"

namespace geodesuka {
	namespace core {
		namespace io {

			/*
			* This can be seen as a simple file handle type, it will be the responsibility
			* of the game engine to insure that identical files are not loaded in twice.
			*/

			class file {
			public:

				enum type {
					EXT_UNK = -1,
					// Image Files
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
					// 3D Model
					// Font
					EXT_TTF,
					EXT_TTC,
					EXT_OTF,
					EXT_PFM,
					// OpenGL Shader
					EXT_VSH,
					EXT_GSH,
					EXT_FSH,
					// OpenCL Kernel
					EXT_CL,
					// Lua Script
					EXT_LUA
				};

				// This is just a lookup table for file type extensions.
				static struct built_in_type {
					type Type;
					const char* Extension;
				} BuiltInTypes[];

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

				/*
				* This will be the raw data loaded, maybe even possibly
				* just partial loading to save memory usage.
				*/
				size_t DataSize;
				void* Data;

			public:

			};

		}
	}
}

#endif // FILE_H
