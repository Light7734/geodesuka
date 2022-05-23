#include <geodesuka/core/io/file.h>

#include <stdlib.h>

#include <string>
#include <vector>

#include <fstream>
#include <sstream>

// Used for generic file loading.
#include <geodesuka/core/io/dynalib.h>
//#include <geodesuka/core/io/image.h>
#include <geodesuka/core/io/font.h>
//#include <geodesuka/core/io/model.h>


// Image Loading
//#define FREEIMAGE_LIB
//#include <FreeImage.h>

// Font Loading
//#include <ft2build.h>
//#include FT_FREETYPE_H

//// Model Loading
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

//// Lua Script
//#include "lua.hpp"
//#include "printstack.h"

namespace geodesuka::core::io {

	// This is just a lookup table for file type extensions.
	// Extension ID, Extension String, Category
	file::built_in_type file::BuiltInTypes[] = {
		{ file::extension::DYN,		{"dll", "so", "dylib"}		},
		{ file::extension::VSH,		{"vsh"}						},
		{ file::extension::TCSH,	{"tcsh"}					},
		{ file::extension::TESH,	{"tesh"}					},
		{ file::extension::GSH,		{"gsh"}						},
		{ file::extension::PSH,		{"psh", "fsh"}				},
		{ file::extension::GLSL,	{"glsl"}					},
		{ file::extension::SPV,		{"spv"}						},
	};

	file::extension file::str2type(util::str aString) {
		extension temp = UNK;
		for (size_t i = 0; i < sizeof(BuiltInTypes) / sizeof(built_in_type); i++) {
			for (size_t j = 0; j < BuiltInTypes[i].Extension.size(); j++)
				if (BuiltInTypes[i].Extension[j] == aString) {
					return BuiltInTypes[i].Type;
				}
		}
		return temp;
	}

	util::str file::type2str(extension aType) {
		const char* temp = "";
		for (size_t i = 0; i < sizeof(BuiltInTypes) / sizeof(built_in_type); i++) {
			if (BuiltInTypes[i].Type == aType) {
				return BuiltInTypes[i].Extension[0].ptr();
			}
		}
		return temp;
	}

	file* file::open(const char* aFilePath) {
		util::str temp = aFilePath;
		temp.reverse();
		util::str Extension = temp.split_at('.');
		Extension.reverse();
		extension ExtID = str2type(Extension);

		switch (ExtID) {
		default:
			break;
			/*
			

			*/
		}

		return nullptr;
	}

	void file::close(file* aFile) {

	}

	file::~file() {
		free(this->Data);
		this->Data = NULL;
		this->DataSize = 0;
	}

	util::str file::get_path() {
		return this->Path;
	}

	util::str file::get_dir() {
		return this->Dir;
	}

	util::str file::get_name() {
		return this->Name;
	}

	util::str file::get_ext() {
		return this->Ext;
	}

	void* file::get_data(size_t& ReturnSize) {
		ReturnSize = this->DataSize;
		return this->Data;
	}

	file::file() {
		this->Path = "";
		this->Dir = "";
		this->Name = "";
		this->Ext = "";
		this->ID = UNK;
		this->Data = NULL;
		this->DataSize = 0;
	}

	file::file(const char* aFilePath) {
		this->mset_path(aFilePath);
	}

	file::file(util::str& aFilePath) {
		this->mset_path(aFilePath);
	}

	bool file::mset_path(util::str aFilePath) {
		this->Path = aFilePath;
		util::str temp = aFilePath;
		temp.reverse();
		this->Ext = temp.split_at('.');
		this->Ext.reverse();
		this->Name = temp.split_at('\/');
		this->Name.reverse();
		this->Dir = temp;
		this->Dir.reverse();
		this->ID = str2type(this->Ext);
		return false;
	}

}















//FIBITMAP*			ImageLoader = nullptr;
//FT_Library			FontLoader;
//Assimp::Importer*	ModelLoader = nullptr;
//
//file::extension get_extension_type(std::string ext);
//file::category get_category_type(std::string ext);
//
//file::file() {
//	isValid			= false;
//	Cat				= UNKNOWN;
//	Ext				= EXT_UNK;
//}
//
//file::~file() {
//
//}
//
//file::file(std::string FilePath) {
//	isValid			= false;
//	Cat				= UNKNOWN;
//	Ext				= EXT_UNK;
//
//	isValid = analyze_path(FilePath);
//}
//
//file & file::operator=(std::string FilePath) {
//	this->isValid			= false;
//	this->Cat				= UNKNOWN;
//	this->Ext				= EXT_UNK;
//
//	this->isValid = analyze_path(FilePath);
//
//	return *this;
//}
//
//void file::set_path(std::string FilePath) {
//	isValid		= false;
//	Cat			= UNKNOWN;
//	Ext			= EXT_UNK;
//
//	Directory.clear();
//	Name.clear();
//	Extension.clear();
//
//	isValid = analyze_path(FilePath);
//
//}
//
//std::string file::get_path() {
//	std::string path;
//	for (int i = 0; i < Directory.size(); i++) {
//		path += Directory[i] + "/";
//	}
//	path += Name + "." + Extension;
//	return path;
//}
//
//std::string file::get_sauce() {
//
//	std::string source;
//	std::string FilePath;
//
//	for (int i = 0; i < Directory.size(); i++) {
//		FilePath += Directory[i] + "/";
//	}
//	FilePath += Name + "." + Extension;
//
//	std::ifstream SauceFile;
//	std::stringstream SauceBuffer;
//	SauceFile.open(FilePath);
//
//	if (!SauceFile.fail()) {
//		SauceBuffer << SauceFile.rdbuf();
//		source = SauceBuffer.str();
//	}
//	SauceFile.close();
//
//	return source;
//}
//
//file::image_data file::get_image() {
//
//	image_data ImageData;
//	
//	ImageData.Buffer = NULL;
//	ImageData.MemSize = 0;
//	ImageData.BitCount = 0;
//	ImageData.Width = 0;
//	ImageData.Height = 0;
//	ImageData.Format = image_data_format::IDF_UNK;
//	ImageData.Type = image_data_type::IDT_UNK;
//
//	// Generate File path.
//	std::string FilePath;
//	for (int i = 0; i < Directory.size(); i++) {
//		FilePath += Directory[i] + "/";
//	}
//	FilePath += Name + "." + Extension;
//
//	FIBITMAP* fiBitmap;
//	FREE_IMAGE_FORMAT fiFormat;
//	FREE_IMAGE_TYPE fiType;
//
//	fiFormat = FreeImage_GetFileType(FilePath.c_str(), 0);
//	if (fiFormat == FIF_UNKNOWN) {
//		fiFormat = FreeImage_GetFIFFromFilename(FilePath.c_str());
//	}
//
//	fiBitmap = FreeImage_Load(fiFormat, FilePath.c_str());
//	fiType = FreeImage_GetImageType(fiBitmap);
//
//	ImageData.Width = FreeImage_GetWidth(fiBitmap);
//	ImageData.Height = FreeImage_GetHeight(fiBitmap);
//	ImageData.MemSize = FreeImage_GetMemorySize(fiBitmap);
//	ImageData.BitCount = FreeImage_GetBPP(fiBitmap);
//
//	switch (fiType) {
//	default:
//		ImageData.Format = image_data_format::IDF_UNK;
//		ImageData.Type = image_data_type::IDT_UNK;
//		break;
//	case FIT_BITMAP:
//		switch (ImageData.BitCount) {
//		default:
//			ImageData.Format = image_data_format::IDF_UNK;
//			ImageData.Type = image_data_type::IDT_UNK;
//			break;
//		case 1:
//			ImageData.Format = image_data_format::IDF_RED;
//			ImageData.Type = image_data_type::IDT_BOOL;
//			break;
//		case 4:
//			ImageData.Format = image_data_format::IDF_BGRA;
//			ImageData.Type = image_data_type::IDT_BOOL;
//			break;
//		case 8:
//			ImageData.Format = image_data_format::IDF_RED;
//			ImageData.Type = image_data_type::IDT_UINT08;
//			break;
//		case 16:
//			ImageData.Format = image_data_format::IDF_RG;
//			ImageData.Type = image_data_type::IDT_UINT08;
//			break;
//		case 24:
//			ImageData.Format = image_data_format::IDF_BGR;
//			ImageData.Type = image_data_type::IDT_UINT08;
//			break;
//		case 32:
//			ImageData.Format = image_data_format::IDF_BGRA;
//			ImageData.Type = image_data_type::IDT_UINT08;
//			break;
//		}
//		break;
//	case FIT_UINT16:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_UINT16;
//		break;
//	case FIT_INT16:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_SINT16;
//		break;
//	case FIT_UINT32:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_UINT32;
//		break;
//	case FIT_INT32:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_SINT32;
//		break;
//	case FIT_FLOAT:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_FLOAT32;
//		break;
//	case FIT_DOUBLE:
//		ImageData.Format = image_data_format::IDF_RED;
//		ImageData.Type = image_data_type::IDT_FLOAT64;
//		break;
//	case FIT_COMPLEX:
//		ImageData.Format = image_data_format::IDF_RG;
//		ImageData.Type = image_data_type::IDT_FLOAT64;
//		break;
//	case FIT_RGB16:
//		ImageData.Format = image_data_format::IDF_BGR;
//		ImageData.Type = image_data_type::IDT_UINT16;
//		break;
//	case FIT_RGBA16:
//		ImageData.Format = image_data_format::IDF_BGRA;
//		ImageData.Type = image_data_type::IDT_UINT16;
//		break;
//	case FIT_RGBF:
//		ImageData.Format = image_data_format::IDF_BGR;
//		ImageData.Type = image_data_type::IDT_FLOAT32;
//		break;
//	case FIT_RGBAF:
//		ImageData.Format = image_data_format::IDF_BGRA;
//		ImageData.Type = image_data_type::IDT_FLOAT32;
//		break;
//	}
//
//	if ((ImageData.MemSize > 0) && (ImageData.Format != image_data_format::IDF_UNK) && (ImageData.Type != image_data_type::IDT_UNK)) {
//		ImageData.Buffer = malloc(ImageData.MemSize);
//		if (ImageData.Buffer != NULL) {
//			memcpy(ImageData.Buffer, FreeImage_GetBits(fiBitmap), ImageData.MemSize);
//		}
//	}
//
//	if (fiBitmap != NULL) {
//		FreeImage_Unload(fiBitmap);
//		fiBitmap = NULL;
//	}
//
//	return ImageData;
//}
//
//std::vector<file::font_data> file::get_font() {
//
//	std::vector<font_data> temp;
//	font_data CharacterGlyph;
//
//	// Generate File path.
//	std::string FilePath;
//	for (int i = 0; i < Directory.size(); i++) {
//		FilePath += Directory[i] + "/";
//	}
//	FilePath += Name + "." + Extension;
//
//	FT_Face Face;
//
//	if (FT_New_Face(FontLoader, FilePath.c_str(), 0, &Face)) {
//		isValid = false;
//	}
//
//	if (isValid) {
//
//		FT_Set_Pixel_Sizes(Face, 0, 128);
//
//		for (unsigned char i = 0; i < 128; i++) {
//			if (FT_Load_Char(Face, i, FT_LOAD_RENDER)) {
//				continue;
//			}
//
//			CharacterGlyph.Index = i;									// Character Index
//			CharacterGlyph.Width = Face->glyph->bitmap.width;			// Number of pixels in bitmap row.
//			CharacterGlyph.Height = Face->glyph->bitmap.rows;			// Number of rows in pixels. (aka Height)
//			CharacterGlyph.BearingX = Face->glyph->bitmap_left;			// Units: Pixels
//			CharacterGlyph.BearingY = Face->glyph->bitmap_top;			// Units: Pixels
//			CharacterGlyph.AdvanceX = (Face->glyph->advance.x >> 6);	// Units: Pixels
//			CharacterGlyph.AdvanceY = (Face->glyph->advance.y >> 6);	// Units: Pixels
//			
//			CharacterGlyph.Buffer = malloc(Face->glyph->bitmap.width * Face->glyph->bitmap.rows *sizeof(unsigned char));
//			memcpy(CharacterGlyph.Buffer, (void*)Face->glyph->bitmap.buffer, Face->glyph->bitmap.width * Face->glyph->bitmap.rows *sizeof(unsigned char));
//
//			temp.push_back(CharacterGlyph);
//		}
//		FT_Done_Face(Face);
//	}
//
//	return temp;
//}
//
//bool file::initialize_system() {
//	FreeImage_Initialise();
//
//	if (FT_Init_FreeType(&FontLoader)) {
//		return true;
//	}
//
//	return false;
//}
//
//bool file::terminate_system() {
//	FreeImage_DeInitialise();
//
//	FT_Done_FreeType(FontLoader);
//
//	return false;
//}
//
//bool file::analyze_path(std::string path) {
//	// NULL
//	// Astolfo
//	// Astolfo.png
//	// assets/textures/Astolfo
//	// assets/textures/Astolfo.png
//
//	if (path.length() != 0) {
//		// Check if in same directory.
//		bool isLocalDir = true;
//		std::string Item;
//		bool ExtensionDetected = false;
//
//		for (int i = 0; i < path.length(); i++) {
//			if ((path[i] == '/') || (path[i] == '\\')) {
//				isLocalDir = false;
//				break;
//			}
//		}
//
//		if (!isLocalDir) {
//			// File is in another directory.
//			for (int i = 0; i < path.length(); i++) {
//				switch (path[i]) {
//				case '/':
//					Directory.push_back(Item);
//					Item.clear();
//					break;
//				case '\\':
//					Directory.push_back(Item);
//					Item.clear();
//					break;
//				default:
//					Item.push_back(path[i]);
//					break;
//				}
//			}
//		}
//		else {
//			// File is in same directory.
//			Item = path;
//		}
//
//		// Get extension if it exists.
//		for (int i = 0; i < Item.length(); i++) {
//			// No names with '.'
//			if (!ExtensionDetected) {
//				Name.push_back(Item[i]);
//				if (Item[i] == '.') {
//					Name.pop_back();
//					ExtensionDetected = true;
//				}
//			}
//			else {
//				Extension.push_back(Item[i]);
//			}
//		}
//
//		// Validate extension
//		if (ExtensionDetected) {
//			// Find Extension Number
//			Cat = get_category_type(Extension);
//			Ext = get_extension_type(Extension);
//			if ((Cat == file::category::UNKNOWN) || (Ext == file::extension::EXT_UNK)) {
//				return false;
//			}
//			else {
//				return true;
//			}
//		}
//		else {
//			// Throw error or something, not a valid extension.
//			return false;
//		}
//	}
//	else {
//		return false;
//	}
//
//	//std::string Item;
//	//for (int i = 0; i < path.length(); i++) {
//	//	switch (path[i]) {
//	//	case '/':
//	//		Directory.push_back(Item);
//	//		Item.clear();
//	//		break;
//	//	case '\\':
//	//		Directory.push_back(Item);
//	//		Item.clear();
//	//		break;
//	//	default:
//	//		Item.push_back(path[i]);
//	//		break;
//	//	}
//	//}
//
//	//// Example.vsh
//	//bool ExtensionDetected = false;
//	//for (int i = 0; i < Item.length(); i++) {
//	//	// No names with '.'
//	//	if (!ExtensionDetected) {
//	//		Name.push_back(Item[i]);
//	//		if (Item[i] == '.') {
//	//			Name.pop_back();
//	//			ExtensionDetected = true;
//	//		}
//	//	}
//	//	else {
//	//		Extension.push_back(Item[i]);
//	//	}
//	//}
//}
//
//file::extension get_extension_type(std::string ext) {
//	if (ext == "bmp") {
//		return file::extension::EXT_BMP;
//	}
//	else if (ext == "ico") {
//		return file::extension::EXT_ICO;
//	}
//	else if ((ext == "jpg") || (ext == "jpeg")) {
//		return file::extension::EXT_JPEG;
//	}
//	else if (ext == "jng") {
//		return file::extension::EXT_JNG;
//	}
//	else if (ext == "koala") {
//		return file::extension::EXT_KOALA;
//	}
//	else if ((ext == "iff") || (ext == "lbm")) {
//		return file::extension::EXT_LBM;
//	}
//	else if (ext == "mng") {
//		return file::extension::EXT_MNG;
//	}
//	else if (ext == "pbm") {
//		return file::extension::EXT_PBM;
//	}
//	else if (ext == "pbmraw") {
//		return file::extension::EXT_PBMRAW;
//	}
//	else if (ext == "pcd") {
//		return file::extension::EXT_PCD;
//	}
//	else if (ext == "pcx") {
//		return file::extension::EXT_PCX;
//	}
//	else if (ext == "pcx") {
//		return file::extension::EXT_PCX;
//	}
//	else if (ext == "pgm") {
//		return file::extension::EXT_PGM;
//	}
//	else if (ext == "pgmraw") {
//		return file::extension::EXT_PGMRAW;
//	}
//	else if (ext == "png") {
//		return file::extension::EXT_PNG;
//	}
//	else if (ext == "ppm") {
//		return file::extension::EXT_PPM;
//	}
//	else if (ext == "ppmraw") {
//		return file::extension::EXT_PPMRAW;
//	}
//	else if (ext == "ras") {
//		return file::extension::EXT_RAS;
//	}
//	else if ((ext == "tga") || (ext == "targa")) {
//		return file::extension::EXT_TARGA;
//	}
//	else if ((ext == "tif") || (ext == "tiff")) {
//		return file::extension::EXT_TIFF;
//	}
//	else if (ext == "wbmp") {
//		return file::extension::EXT_WBMP;
//	}
//	else if (ext == "psd") {
//		return file::extension::EXT_PSD;
//	}
//	else if (ext == "cut") {
//		return file::extension::EXT_CUT;
//	}
//	else if (ext == "xbm") {
//		return file::extension::EXT_XBM;
//	}
//	else if (ext == "xpm") {
//		return file::extension::EXT_XPM;
//	}
//	else if (ext == "dds") {
//		return file::extension::EXT_DDS;
//	}
//	else if (ext == "gif") {
//		return file::extension::EXT_GIF;
//	}
//	else if (ext == "hdr") {
//		return file::extension::EXT_HDR;
//	}
//	else if (ext == "g3") {
//		return file::extension::EXT_FAXG3;
//	}
//	else if (ext == "sgi") {
//		return file::extension::EXT_SGI;
//	}
//	else if (ext == "exr") {
//		return file::extension::EXT_EXR;
//	}
//	else if ((ext == "j2k") || (ext == "j2c")) {
//		return file::extension::EXT_EXR;
//	}
//	else if (ext == "jp2") {
//		return file::extension::EXT_JP2;
//	}
//	//else if (ext == "pfm") {
//	//	return file::extension_type::EXT_PFM;
//	//}
//	else if ((ext == "pct") || (ext == "pict") || (ext == "pic")) {
//		return file::extension::EXT_PICT;
//	}
//	else if (ext == "webp") {
//		return file::extension::EXT_WEBP;
//	}
//	else if ((ext == "jxr") || (ext == "wdp") || (ext == "hdp")) {
//		return file::extension::EXT_JXR;
//	}
//	else if (ext == "ttf") {
//		return file::extension::EXT_TTF;
//	}
//	else if (ext == "ttc") {
//		return file::extension::EXT_TTC;
//	}
//	else if (ext == "otf") {
//		return file::extension::EXT_OTF;
//	}
//	else if (ext == "pfm") {
//		return file::extension::EXT_PFM;
//	}
//	else if (ext == "vsh") {
//		return file::extension::EXT_VSH;
//	}
//	else if (ext == "gsh") {
//		return file::extension::EXT_GSH;
//	}
//	else if (ext == "fsh") {
//		return file::extension::EXT_FSH;
//	}
//	else if (ext == "cl") {
//		return file::extension::EXT_CL;
//	}
//	else if (ext == "lua") {
//		return file::extension::EXT_LUA;
//	}
//	else {
//		return file::extension::EXT_UNK;
//		//return file::extension_type::EXT_RAW;
//	}
//}
//
//file::category get_category_type(std::string ext) {
//	file::extension temp = get_extension_type(ext);
//	if ((temp >= file::extension::EXT_BMP) && (temp <= file::extension::EXT_JXR)) {
//		return file::category::IMAGE_DATA;
//	}
//	else if ((temp >= file::extension::EXT_TTF) && (temp <= file::extension::EXT_PFM)) {
//		return file::category::FONT_DATA;
//	}
//	else if ((temp >= file::extension::EXT_VSH) && (temp <= file::extension::EXT_FSH)) {
//		return file::category::OGL_SHADER;
//	}
//	else if (temp == file::extension::EXT_CL) {
//		return file::category::OCL_KERNEL;
//	}
//	else if (temp == file::extension::EXT_LUA) {
//		return file::category::LUA_SCRIPT;
//	}
//	else {
//		return file::category::UNKNOWN;
//	}
//}
