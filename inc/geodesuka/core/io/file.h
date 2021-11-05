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

namespace geodesuka::core::io {

	/*
	* This can be seen as a simple file handle type, it will be the responsibility
	* of the game engine to insure that identical files are not loaded in twice.
	*/

	class file {
	public:

		enum extension {
			UNK = -1,
			// --------------- Dynamic Libraries --------------- //
			DYN,
			// --------------- Image Files --------------- //
			BMP,
			ICO,
			JPEG,
			JNG,
			KOALA,
			LBM,
			//IFF		= LBM,
			MNG,
			PBM,
			PBMRAW,
			PCD,
			PCX,
			PGM,
			PGMRAW,
			PNG,
			PPM,
			PPMRAW,
			RAS,
			TARGA,
			TIFF,
			WBMP,
			PSD,
			CUT,
			XBM,
			XPM,
			DDS,
			GIF,
			HDR,
			FAXG3,
			SGI,
			EXR,
			J2K,
			JP2,
			//PFM			,
			PICT,
			RAW,
			WEBP,
			JXR,
			// --------------- Model Files --------------- //
			// --------------- Type Face Files --------------- //
			TTF,
			TTC,
			OTF,
			PFM,
			// --------------- Shader Files --------------- //
			VSH,		// (Per) Vertex Shaders
			TCSH,		// Tesselation Control Shaders
			TESH,		// Tesselation Evaluation Shaders
			GSH,		// (Per Primitive) Geometry Shaders
			PSH,		// (Per Pixel) Fragment Shaders
			CSH,		// Compute Shaders
			GLSL,		// Include Shader Function Files
			SPV,		// SPIR-V Compiled Shaders
			// OpenCL Kernel
			OCL,
			// Lua Script
			LUA
		};

		enum class category {

			PLAIN_TEXT,
			BYTE_CODE,
			IMAGE,
			AUDIO,
			MODEL

		};

		/*
		* Usage Table
		* image		-> texture
		* plaintext -> script
		* plaintext -> shader
		*/

		// A more general version grouping.
		enum type {
			DYNALIB,
			PLAINTEXT,
			BYTECODE,
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

		static file* open(const char* aFilePath);
		static void close(file* aFile);

		~file();

		util::text get_path();
		util::text get_dir();
		util::text get_name();
		util::text get_ext();
		void* get_data(size_t& ReturnSize);

	protected:

		file();
		file(const char* aFilePath);
		file(util::text& aFilePath);

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

#endif // GEODESUKA_CORE_IO_FILE_H
