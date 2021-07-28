#include <geodesuka/core/gcl/texture.h>

// Standard C Libs
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

#include <geodesuka/core/gcl/gcl.h>

#include <geodesuka/core/math/gmath.h>

#include <geodesuka/core/gcl/variable.h>

namespace geodesuka {
	namespace core {
		namespace gcl {

			texture::texture() {
				BindingPoint = NULL;
				HandleID = 0;

				EnableMipmap = false;
				LevelOfDetail = 0;
				InternalFormat = NULL;
				GridSize = { 0, 0, 0 };
				ChannelFormat = NULL;
				DataType = NULL;
				MemSize = 0;
				hptr = NULL;
			}

			texture::~texture() {
				if (HandleID != 0) { glDeleteTextures(1, &HandleID); HandleID = 0; }
				if (hptr != NULL) { free(hptr); hptr = NULL; }

				EnableMipmap = false;
				LevelOfDetail = 0;
				InternalFormat = NULL;
				GridSize = { 0, 0, 0 };
				ChannelFormat = NULL;
				DataType = NULL;
				MemSize = 0;
			}


			//texture::texture(texture & inp) {
			//	EnableMipmap = inp.EnableMipmap;
			//	BitsPerPixel = inp.BitsPerPixel;
			//	LevelOfDetail = inp.LevelOfDetail;
			//	InternalFormat = inp.InternalFormat;
			//
			//	// --------------- Copy Host Image --------------- //
			//
			//	hMemSize = inp.hMemSize;
			//	hType = inp.hType;
			//	hWidth = inp.hWidth;
			//	hHeight = inp.hHeight;
			//	hDepth = inp.hDepth;
			//	hChannelFormat = inp.hChannelFormat;
			//	hDataType = inp.hDataType;
			//
			//	if ((inp.hptr != NULL) && (hMemSize != 0)) {
			//		hptr = malloc(hMemSize);
			//	}
			//	else {
			//		hptr = NULL;
			//	}
			//
			//	if ((hptr != NULL) && (hMemSize != 0)) {
			//		memcpy(hptr, inp.hptr, hMemSize);
			//	}
			//
			//	// --------------- Copy Device Texture --------------- //
			//
			//	dMemSize = inp.dMemSize;
			//	dType = inp.dType;
			//	dWidth = inp.dWidth;
			//	dHeight = inp.dHeight;
			//	dDepth = inp.dDepth;
			//	dChannelFormat = inp.dChannelFormat;
			//	dDataType = inp.dDataType;
			//
			//	if (inp.ID != 0) {
			//		glGenTextures(1, &ID);
			//	}
			//	else {
			//		ID = 0;
			//	}
			//
			//	if ((ID != 0) && (dMemSize != 0)) {
			//		glBindTexture(dType, ID);
			//		switch (dType) {
			//		default:
			//			// Error Code
			//			break;
			//		case TEXTURE_1D:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage1D(dType, LevelOfDetail, InternalFormat, dWidth, 0, dChannelFormat, dDataType, hptr);
			//			break;
			//		case TEXTURE_2D: case TEXTURE_1D_ARRAY:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage2D(dType, LevelOfDetail, InternalFormat, dWidth, dHeight, 0, dChannelFormat, dDataType, hptr);
			//			break;
			//		case TEXTURE_3D: case TEXTURE_2D_ARRAY:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage3D(dType, LevelOfDetail, InternalFormat, dWidth, dHeight, dDepth, 0, dChannelFormat, dDataType, hptr);
			//			break;
			//		}
			//		if (EnableMipmap) { glGenerateMipmap(dType); }
			//		glBindTexture(dType, 0);
			//	}
			//
			//}
			//
			//texture::texture(texture && inp) {
			//
			//	EnableMipmap = inp.EnableMipmap;
			//	BitsPerPixel = inp.BitsPerPixel;
			//	LevelOfDetail = inp.LevelOfDetail;
			//	InternalFormat = inp.InternalFormat;
			//
			//	hptr = inp.hptr;
			//	hMemSize = inp.hMemSize;
			//	hType = inp.hType;
			//	hWidth = inp.hWidth;
			//	hHeight = inp.hHeight;
			//	hDepth = inp.hDepth;
			//	hChannelFormat = inp.hChannelFormat;
			//	hDataType = inp.hDataType;
			//
			//	ID = inp.ID;
			//	dMemSize = inp.dMemSize;
			//	dType = inp.dType;
			//	dWidth = inp.dWidth;
			//	dHeight = inp.dHeight;
			//	dDepth = inp.dDepth;
			//	dChannelFormat = inp.dChannelFormat;
			//	dDataType = inp.dDataType;
			//
			//	inp.EnableMipmap = false;
			//	inp.BitsPerPixel = 0;
			//	inp.LevelOfDetail = 0;
			//	inp.InternalFormat = NULL;
			//
			//	inp.hptr = NULL;
			//	inp.hMemSize = 0;
			//	inp.hType = NULL;
			//	inp.hWidth = 0;
			//	inp.hHeight = 0;
			//	inp.hDepth = 0;
			//	inp.hChannelFormat = NULL;
			//	inp.hDataType = NULL;
			//
			//	inp.ID = 0;
			//	inp.dMemSize = 0;
			//	inp.dType = NULL;
			//	inp.dWidth = 0;
			//	inp.dHeight = 0;
			//	inp.dDepth = 0;
			//	inp.dChannelFormat = NULL;
			//	inp.dDataType = NULL;
			//
			//}
			//
			//texture & texture::operator=(texture & rhs) {
			//	if ((this->hptr == rhs.hptr) || (this->ID == rhs.ID)) { return *this; }
			//
			//	if (this->hptr != NULL) {
			//		free(this->hptr);
			//		this->hptr = NULL;
			//	}
			//
			//	if (this->ID != 0) {
			//		glDeleteTextures(1, &this->ID);
			//		this->ID = 0;
			//	}
			//
			//	this->EnableMipmap = rhs.EnableMipmap;
			//	this->BitsPerPixel = rhs.BitsPerPixel;
			//	this->LevelOfDetail = rhs.LevelOfDetail;
			//	this->InternalFormat = rhs.InternalFormat;
			//
			//	// --------------- Copy Host Image --------------- //
			//
			//	this->hMemSize = rhs.hMemSize;
			//	this->hType = rhs.hType;
			//	this->hWidth = rhs.hWidth;
			//	this->hHeight = rhs.hHeight;
			//	this->hDepth = rhs.hDepth;
			//	this->hChannelFormat = rhs.hChannelFormat;
			//	this->hDataType = rhs.hDataType;
			//
			//	if ((rhs.hptr != NULL) && (this->hMemSize != 0)) {
			//		this->hptr = malloc(this->hMemSize);
			//	}
			//	else {
			//		this->hptr = NULL;
			//	}
			//
			//	if ((this->hptr != NULL) && (this->hMemSize != 0)) {
			//		memcpy(this->hptr, rhs.hptr, this->hMemSize);
			//	}
			//
			//	// --------------- Copy Device Texture --------------- //
			//
			//	this->dMemSize = rhs.dMemSize;
			//	this->dType = rhs.dType;
			//	this->dWidth = rhs.dWidth;
			//	this->dHeight = rhs.dHeight;
			//	this->dDepth = rhs.dDepth;
			//	this->dChannelFormat = rhs.dChannelFormat;
			//	this->dDataType = rhs.dDataType;
			//
			//	if (rhs.ID != 0) {
			//		glGenTextures(1, &this->ID);
			//	}
			//	else {
			//		this->ID = 0;
			//	}
			//
			//	if ((this->ID != 0) && (this->dMemSize != 0)) {
			//		glBindTexture(this->dType, this->ID);
			//		switch (this->dType) {
			//		default:
			//			// Error Code
			//			break;
			//		case TEXTURE_1D:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage1D(this->dType, this->LevelOfDetail, this->InternalFormat, this->dWidth, 0, this->dChannelFormat, this->dDataType, this->hptr);
			//			break;
			//		case TEXTURE_2D: case TEXTURE_1D_ARRAY:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage2D(this->dType, this->LevelOfDetail, this->InternalFormat, this->dWidth, this->dHeight, 0, this->dChannelFormat, this->dDataType, this->hptr);
			//			break;
			//		case TEXTURE_3D: case TEXTURE_2D_ARRAY:
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
			//			glTexParameteri(dType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//			glTexParameteri(dType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//			glTexImage3D(this->dType, this->LevelOfDetail, this->InternalFormat, this->dWidth, this->dHeight, this->dDepth, 0, this->dChannelFormat, this->dDataType, this->hptr);
			//			break;
			//		}
			//		if (this->EnableMipmap) { glGenerateMipmap(this->dType); }
			//		glBindTexture(this->dType, 0);
			//	}
			//
			//	return *this;
			//}
			//
			//texture & texture::operator=(texture && rhs) {
			//	if (this->hptr != NULL) {
			//		free(this->hptr);
			//		this->hptr = NULL;
			//	}
			//
			//	if (this->ID != 0) {
			//		glDeleteTextures(1, &this->ID);
			//		this->ID = 0;
			//	}
			//
			//	this->EnableMipmap = rhs.EnableMipmap;
			//	this->BitsPerPixel = rhs.BitsPerPixel;
			//	this->LevelOfDetail = rhs.LevelOfDetail;
			//	this->InternalFormat = rhs.InternalFormat;
			//
			//	this->hptr = rhs.hptr;
			//	this->hMemSize = rhs.hMemSize;
			//	this->hType = rhs.hType;
			//	this->hWidth = rhs.hWidth;
			//	this->hHeight = rhs.hHeight;
			//	this->hDepth = rhs.hDepth;
			//	this->hChannelFormat = rhs.hChannelFormat;
			//	this->hDataType = rhs.hDataType;
			//
			//	this->ID = rhs.ID;
			//	this->dMemSize = rhs.dMemSize;
			//	this->dType = rhs.dType;
			//	this->dWidth = rhs.dWidth;
			//	this->dHeight = rhs.dHeight;
			//	this->dDepth = rhs.dDepth;
			//	this->dChannelFormat = rhs.dChannelFormat;
			//	this->dDataType = rhs.dDataType;
			//
			//	rhs.EnableMipmap = false;
			//	rhs.BitsPerPixel = 0;
			//	rhs.LevelOfDetail = 0;
			//	rhs.InternalFormat = NULL;
			//
			//	rhs.hptr = NULL;
			//	rhs.hMemSize = 0;
			//	rhs.hType = NULL;
			//	rhs.hWidth = 0;
			//	rhs.hHeight = 0;
			//	rhs.hDepth = 0;
			//	rhs.hChannelFormat = NULL;
			//	rhs.hDataType = NULL;
			//
			//	rhs.ID = 0;
			//	rhs.dMemSize = 0;
			//	rhs.dType = NULL;
			//	rhs.dWidth = 0;
			//	rhs.dHeight = 0;
			//	rhs.dDepth = 0;
			//	rhs.dChannelFormat = NULL;
			//	rhs.dDataType = NULL;
			//
			//	return *this;
			//}
			//
			//texture & texture::operator=(const char * FilePath) {
			//	this->EnableMipmap = true;
			//	this->LevelOfDetail = 0;
			//	this->read(FilePath);
			//	this->reserve_device_memory(NULL, 0, 0, 0, NULL, NULL);
			//	return *this;
			//}
			//
			//bool texture::read(const char * FilePath) {
			//	bool ErrorDetected = false;
			//	if (!ErrorDetected) { ErrorDetected |= analyze_path(FilePath); }
			//
			//	size_t NewMemSize = 0;
			//	int ImageExtension;
			//	int ImageFormat;
			//	FIBITMAP *Bitmap;
			//
			//	ImageExtension = (int)FreeImage_GetFileType(FilePath);
			//	Bitmap = FreeImage_Load((FREE_IMAGE_FORMAT)ImageExtension, FilePath);
			//
			//	hType = TEXTURE_2D;
			//	hWidth = FreeImage_GetWidth(Bitmap);
			//	hHeight = FreeImage_GetHeight(Bitmap);
			//	hDepth = 0;
			//
			//	NewMemSize = hWidth * hHeight;
			//
			//	// Improper Image Dimensions!
			//	if (NewMemSize <= 0) { FreeImage_Unload(Bitmap); return true; }
			//
			//	ImageFormat = FreeImage_GetImageType(Bitmap);
			//	BitsPerPixel = FreeImage_GetBPP(Bitmap);
			//	switch (ImageFormat) {
			//	default:
			//		hChannelFormat = NULL;
			//		hDataType = NULL;
			//		break;
			//	case FIT_BITMAP:
			//		switch (BitsPerPixel) {
			//		default:
			//			hChannelFormat = NULL;
			//			hDataType = NULL;
			//			return true;
			//		case 1:
			//			hChannelFormat = RED;
			//			hDataType = BOOLEAN;
			//			break;
			//		case 4:
			//			hChannelFormat = BGRA;
			//			hDataType = BOOLEAN;
			//			break;
			//		case 8:
			//			InternalFormat = GL_RED;
			//			hChannelFormat = RED;
			//			hDataType = UNSIGNED_BYTE;
			//			break;
			//		case 16:
			//			InternalFormat = GL_RG;
			//			hChannelFormat = RG;
			//			hDataType = UNSIGNED_BYTE;
			//			break;
			//		case 24:
			//			InternalFormat = GL_RGB;
			//			hChannelFormat = BGR;
			//			hDataType = UNSIGNED_BYTE;
			//			break;
			//		case 32:
			//			InternalFormat = GL_RGBA;
			//			hChannelFormat = BGRA;
			//			hDataType = UNSIGNED_BYTE;
			//			break;
			//		}
			//		break;
			//	case FIT_UINT16:
			//		hChannelFormat = RED;
			//		hDataType = UNSIGNED_SHORT;
			//		break;
			//	case FIT_INT16:
			//		hChannelFormat = RED;
			//		hDataType = SIGNED_SHORT;
			//		break;
			//	case FIT_UINT32:
			//		hChannelFormat = RED;
			//		hDataType = UNSIGNED_INT;
			//		break;
			//	case FIT_INT32:
			//		hChannelFormat = RED;
			//		hDataType = SIGNED_INT;
			//		break;
			//	case FIT_FLOAT:
			//		hChannelFormat = RED;
			//		hDataType = FLOAT;
			//		break;
			//	case FIT_DOUBLE:
			//		hChannelFormat = RED;
			//		hDataType = DOUBLE;
			//		break;
			//	case FIT_COMPLEX:
			//		hChannelFormat = RG;
			//		hDataType = DOUBLE;
			//		break;
			//	case FIT_RGB16:
			//		hChannelFormat = RGB;
			//		hDataType = UNSIGNED_SHORT;
			//		break;
			//	case FIT_RGBA16:
			//		hChannelFormat = RGBA;
			//		hDataType = UNSIGNED_SHORT;
			//		break;
			//	case FIT_RGBF:
			//		hChannelFormat = RGB;
			//		hDataType = FLOAT;
			//		break;
			//	case FIT_RGBAF:
			//		hChannelFormat = RGBA;
			//		hDataType = FLOAT;
			//		break;
			//	}
			//
			//	if ((hChannelFormat == NULL) || (hDataType == NULL)) { FreeImage_Unload(Bitmap); return true; }
			//
			//	switch (hChannelFormat) {
			//	default:
			//		NewMemSize *= 0;
			//		break;
			//	case RED:
			//		NewMemSize *= 1;
			//		break;
			//	case RG:
			//		NewMemSize *= 2;
			//		break;
			//	case RGB: case BGR:
			//		NewMemSize *= 3;
			//		break;
			//	case RGBA: case BGRA:
			//		NewMemSize *= 4;
			//		break;
			//	}
			//
			//	// Return if Invalid Channel Format
			//	if (NewMemSize <= 0) { FreeImage_Unload(Bitmap); return true; }
			//
			//	switch (hDataType) {
			//	default:
			//		NewMemSize *= 0;
			//		break;
			//	case BOOLEAN:
			//		NewMemSize *= sizeof(unsigned char);
			//		break;
			//	case SIGNED_BYTE:
			//		NewMemSize *= sizeof(char);
			//		break;
			//	case SIGNED_SHORT:
			//		NewMemSize *= sizeof(short);
			//		break;
			//	case SIGNED_INT:
			//		NewMemSize *= sizeof(int);
			//		break;
			//	case UNSIGNED_BYTE:
			//		NewMemSize *= sizeof(unsigned char);
			//		break;
			//	case UNSIGNED_SHORT:
			//		NewMemSize *= sizeof(unsigned short);
			//		break;
			//	case UNSIGNED_INT:
			//		NewMemSize *= sizeof(unsigned int);
			//		break;
			//	case HALF_FLOAT:
			//		NewMemSize *= sizeof(unsigned short);
			//		break;
			//	case FLOAT:
			//		NewMemSize *= sizeof(float);
			//		break;
			//	case DOUBLE:
			//		NewMemSize *= sizeof(double);
			//		break;
			//	}
			//
			//	if (NewMemSize == 0) { FreeImage_Unload(Bitmap); return true; }
			//
			//	hMemSize = NewMemSize;
			//
			//	void *nptr;
			//	nptr = (void*)FreeImage_GetBits(Bitmap);
			//	hptr = malloc(hMemSize);
			//	memcpy(hptr, nptr, hMemSize);
			//	FreeImage_Unload(Bitmap);
			//
			//	return false;
			//}
			//
			//bool texture::write(const char * FilePath) {
			//	return true;
			//}

			bool texture::reserve_host_memory(texture_type TextureType, math::integer3 TextureSize, channel_format TextureChannelFormat, int TextureDataType) {
				int NewType = NULL;
				math::integer3 NewGridSize = { 0, 0, 0 };
				int NewChannelFormat = NULL;
				int NewDataType = NULL;
				size_t NewMemSize = 0;

				if (TextureType != NULL) {
					NewType = TextureType;
				}
				else {
					NewType = BindingPoint;
				}

				if (TextureSize.x > 0) {
					NewGridSize.x = TextureSize.x;
				}
				else {
					NewGridSize.x = GridSize.x;
				}
				if (TextureSize.y > 0) {
					NewGridSize.y = TextureSize.y;
				}
				else {
					NewGridSize.y = GridSize.y;
				}
				if (TextureSize.z > 0) {
					NewGridSize.z = TextureSize.z;
				}
				else {
					NewGridSize.z = GridSize.z;
				}

				if (TextureChannelFormat != NULL) {
					NewChannelFormat = TextureChannelFormat;
				}
				else {
					NewChannelFormat = ChannelFormat;
				}

				if (TextureDataType != NULL) {
					NewDataType = TextureDataType;
				}
				else {
					NewDataType = DataType;
				}

				//NewMemSize = gcl::get_size_of(NewType, NewGridSize, NewChannelFormat, NewDataType);

				if (NewMemSize == 0) { return true; }

				// Parameters validated, now load and store.
				BindingPoint = NewType;
				switch (NewType) {
				default:
					break;
				case GL_TEXTURE_1D:
					GridSize.x = NewGridSize.x;
					GridSize.y = 0;
					GridSize.z = 0;
					break;
				case GL_TEXTURE_2D: case GL_TEXTURE_1D_ARRAY:
					GridSize.x = NewGridSize.x;
					GridSize.y = NewGridSize.y;
					GridSize.z = 0;
					break;
				case GL_TEXTURE_3D: case GL_TEXTURE_2D_ARRAY:
					GridSize.x = NewGridSize.x;
					GridSize.y = NewGridSize.y;
					GridSize.z = NewGridSize.z;
					break;
				}
				ChannelFormat = NewChannelFormat;
				DataType = NewDataType;
				MemSize = NewMemSize;

				if (hptr != NULL) { free(hptr); hptr = NULL; }

				hptr = malloc(MemSize);

				if (hptr != NULL) {
					return false;
				}
				else {
					return true;
				}
			}

			bool texture::release_host_memory() {
				if (hptr != NULL) { free(hptr); hptr = NULL; }
				return false;
			}

			bool texture::reserve_device_memory(texture_type TextureType, math::integer3 TextureSize, channel_format TextureChannelFormat, int TextureDataType) {
				int NewType = NULL;
				math::integer3 NewGridSize = { 0, 0, 0 };
				int NewChannelFormat = NULL;
				int NewDataType = NULL;
				size_t NewMemSize = 0;

				if (TextureType != NULL) {
					NewType = TextureType;
				}
				else {
					NewType = BindingPoint;
				}

				if (TextureSize.x > 0) {
					NewGridSize.x = TextureSize.x;
				}
				else {
					NewGridSize.x = GridSize.x;
				}
				if (TextureSize.y > 0) {
					NewGridSize.y = TextureSize.y;
				}
				else {
					NewGridSize.y = GridSize.y;
				}
				if (TextureSize.z > 0) {
					NewGridSize.z = TextureSize.z;
				}
				else {
					NewGridSize.z = GridSize.z;
				}

				if (TextureChannelFormat != NULL) {
					NewChannelFormat = TextureChannelFormat;
				}
				else {
					NewChannelFormat = ChannelFormat;
				}

				if (TextureDataType != NULL) {
					NewDataType = TextureDataType;
				}
				else {
					NewDataType = DataType;
				}

				//NewMemSize = gcl::get_size_of(NewType, NewGridSize, NewChannelFormat, NewDataType);

				if (NewMemSize == 0) { return true; }

				// Parameters validated, now load and store.
				BindingPoint = NewType;
				switch (NewType) {
				default:
					break;
				case GL_TEXTURE_1D:
					GridSize.x = NewGridSize.x;
					GridSize.y = 0;
					GridSize.z = 0;
					break;
				case GL_TEXTURE_2D: case GL_TEXTURE_1D_ARRAY:
					GridSize.x = NewGridSize.x;
					GridSize.y = NewGridSize.y;
					GridSize.z = 0;
					break;
				case GL_TEXTURE_3D: case GL_TEXTURE_2D_ARRAY:
					GridSize.x = NewGridSize.x;
					GridSize.y = NewGridSize.y;
					GridSize.z = NewGridSize.z;
					break;
				}
				ChannelFormat = NewChannelFormat;
				DataType = NewDataType;
				MemSize = NewMemSize;

				//if (InternalFormat == NULL) {
				//	InternalFormat = gcl::get_iformat(ChannelFormat, DataType);
				//}

				if (HandleID != 0) { glDeleteTextures(1, &HandleID); HandleID = 0; }

				glGenTextures(1, &HandleID);
				//gcl::bind(BindingPoint, HandleID);
				switch (BindingPoint) {
				default:
					break;
				case TEXTURE_1D:
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(BindingPoint, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexImage1D(BindingPoint, LevelOfDetail, InternalFormat, GridSize.x, 0, ChannelFormat, DataType, hptr);
					break;
				case TEXTURE_2D: case TEXTURE_1D_ARRAY:
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(BindingPoint, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexImage2D(BindingPoint, LevelOfDetail, InternalFormat, GridSize.x, GridSize.y, 0, ChannelFormat, DataType, hptr);
					break;
				case TEXTURE_3D: case TEXTURE_2D_ARRAY:
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
					glTexParameteri(BindingPoint, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(BindingPoint, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexImage3D(BindingPoint, LevelOfDetail, InternalFormat, GridSize.x, GridSize.y, GridSize.z, 0, ChannelFormat, DataType, hptr);
					break;
				}
				if (EnableMipmap) { glGenerateMipmap(BindingPoint); }
				return false;
			}

			bool texture::release_device_memory() {
				if (HandleID != 0) { glDeleteTextures(1, &HandleID); HandleID = 0; }
				return false;
			}

			bool texture::send_to_device() {
				if (HandleID == NULL) { return true; }
				//gcl::bind(BindingPoint, HandleID);
				switch (BindingPoint) {
					return true;
				case TEXTURE_1D:
					glTexSubImage1D(BindingPoint, LevelOfDetail, 0, GridSize.x, ChannelFormat, DataType, hptr);
					break;
				case TEXTURE_2D: case TEXTURE_1D_ARRAY:
					glTexSubImage2D(BindingPoint, LevelOfDetail, 0, 0, GridSize.x, GridSize.y, ChannelFormat, DataType, hptr);
					break;
				case TEXTURE_3D: case TEXTURE_2D_ARRAY:
					glTexSubImage3D(BindingPoint, LevelOfDetail, 0, 0, 0, GridSize.x, GridSize.y, GridSize.z, ChannelFormat, DataType, hptr);
					break;
				}
				return false;
			}

			/*
			char * texture::get_path() {
				if (HollowPath == NULL) { return NULL; }
				// -------------------- Find Mem Size -------------------- //

				// "assets" / "shaders" / "Simple" "vsh"
				int CharCount = 0;
				if (Directory != NULL) {
					for (int i = 0; i < DirCount; i++) {
						CharCount += strlen(Directory[i]);
					}
					CharCount += DirCount;
				}
				if (Name != NULL) { CharCount += strlen(Name); }
				if (Extension != NULL) { CharCount += 1; CharCount += strlen(Extension); }
				if (CharCount == 0) { return NULL; }
				CharCount += 1;
				// -------------------- Copy Memory -------------------- //

				char* TempPath;
				TempPath = (char*)malloc(CharCount * sizeof(char));
				TempPath[CharCount - 1] = '\0';

				int IndexShift = 0;

				// "assets/shaders/Simple.vsh"
				if (Directory != NULL) {
					for (int i = 0; i < DirCount; i++) {
						memcpy((TempPath + IndexShift * sizeof(char)), Directory[i], strlen(Directory[i]) * sizeof(char));
						TempPath[strlen(Directory[i]) + IndexShift] = '/';
						IndexShift += (strlen(Directory[i]) + 1);
					}
				}
				if (Name != NULL) {
					memcpy((TempPath + IndexShift * sizeof(char)), Name, strlen(Name) * sizeof(char));
					IndexShift += strlen(Name);
				}
				if (Extension != NULL) {
					TempPath[IndexShift] = '.';
					IndexShift += 1;
					memcpy((TempPath + IndexShift * sizeof(char)), Extension, strlen(Extension) * sizeof(char));
				}

				return TempPath;
			}

			char * texture::get_name() {
				if (Name == NULL) { return NULL; }
				char* TempName;
				TempName = (char*)malloc((strlen(Name) + 1) * sizeof(char));
				memcpy(TempName, Name, strlen(Name) * sizeof(char));
				TempName[strlen(Name)] = '\0';
				return TempName;
			}

			char * texture::get_file_name() {
				if ((HollowPath == NULL) || (Name == NULL) || (Extension == NULL)) { return NULL; }
				// Fix this later

				int CharCount = 0;
				CharCount += strlen(Name);
				CharCount += 1;
				CharCount += strlen(Extension);
				CharCount += 1;

				char* TempFileName;
				TempFileName = (char*)malloc(CharCount * sizeof(char));

				memcpy(TempFileName, Name, strlen(Name) * sizeof(char));
				TempFileName[strlen(Name)] = '.';
				memcpy((TempFileName + (strlen(Name) + 1) * sizeof(char)), Extension, strlen(Extension) * sizeof(char));
				TempFileName[strlen(Name) + strlen(Extension) + 1] = '\0';

				return TempFileName;
			}

			char * texture::get_extension() {
				char* TempExt;
				TempExt = (char*)malloc((strlen(Extension) + 1) * sizeof(char));
				memcpy(TempExt, Extension, strlen(Extension) * sizeof(char));
				TempExt[strlen(Extension)] = '\0';
				return TempExt;
			}

			bool texture::analyze_path(const char * FilePath) {

				// -------------------- Pre  Check Work -------------------- //

				// This function assumes dirs are NULL
				if (FilePath == NULL) { return true; }
				if (strlen(FilePath) == 0) { return true; }

				// Delete Old Path Info
				DirCount = 0;
				if (Directory != NULL) { free(Directory); Directory = NULL; }
				Name = NULL;
				Extension = NULL;
				if (HollowPath != NULL) { free(HollowPath); HollowPath = NULL; }

				// -------------------- Post Check Work -------------------- //

				HollowPath = (char*)malloc((strlen(FilePath) + 1) * sizeof(char));
				memcpy(HollowPath, FilePath, strlen(FilePath) * sizeof(char));
				HollowPath[strlen(FilePath)] = '\0';

				// "assets/shaders/Simple.vsh"
				DirCount = character_count(HollowPath, "/\\");

				if (DirCount > 0) {
					int DirIndex;
					char *Word;

					Directory = (char**)malloc(DirCount * sizeof(char*));

					Word = strtok(HollowPath, "/\\");
					DirIndex = 0;
					while ((Word != NULL) && (DirIndex < DirCount)) {
						Directory[DirIndex] = Word;

						Word = strtok(NULL, "/\\");
						DirIndex += 1;
					}

					Name = Word;
					Word = strtok(NULL, "/\\");
					if (Word != NULL) { __debugbreak(); }
				}
				else {
					Name = HollowPath;
				}

				int DotCount;
				DotCount = character_count(Name, ".");

				if (DotCount == 1) {
					Name = strtok(Name, ".");
					Extension = strtok(NULL, ".");
				}
				else {
					Extension = NULL;
				}

				return false;
			}

			void texture::clear_path() {
				if (HollowPath != NULL) {
					free(HollowPath); HollowPath = NULL;
					if (Directory != NULL) { free(Directory); Directory = NULL; }
					Name = NULL;
					Extension = NULL;
				}
			}

			int texture::character_count(const char * Str, const char * CharacterSet) {
				if ((Str == NULL) || (CharacterSet == NULL)) { return -1; }
				if ((strlen(Str) == 0) || (strlen(CharacterSet) == 0)) { return -1; }
				int CharacterCount = 0;
				int StrLength = strlen(Str);
				int CharacterSetLength = strlen(CharacterSet);
				for (int i = 0; i < StrLength; i++) {
					for (int j = 0; j < CharacterSetLength; j++) {
						if (Str[i] == CharacterSet[j]) { CharacterCount += 1; }
					}
				}
				return CharacterCount;
			}
			//*/

		}
	}
}
