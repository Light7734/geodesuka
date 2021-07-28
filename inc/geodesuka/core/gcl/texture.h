#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "gcl.h"

#include "../math/gmath.h"

#include "variable.h"
#include "context.h"

namespace geodesuka {
	namespace core {
		namespace gcl {

			class texture {
			public:

				enum texture_type {
					TEXTURE_1D = GL_TEXTURE_1D,
					TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
					TEXTURE_2D = GL_TEXTURE_2D,
					TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
					TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
					TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
					TEXTURE_3D = GL_TEXTURE_3D,

					TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
					TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
					TEXTURE_BUFFER = GL_TEXTURE_BUFFER
				};

				enum channel_format {
					RED = GL_RED,
					RG = GL_RG,
					RGB = GL_RGB, BGR = GL_BGR,
					RGBA = GL_RGBA, BGRA = GL_BGRA
				};

				enum wrapping {
					CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
					CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
					REPEAT = GL_REPEAT,
					MIRRORED_REPEAT = GL_MIRRORED_REPEAT
				};

				enum filter {
					NEAREST = GL_NEAREST,
					LINEAR = GL_LINEAR,
					NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
					LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
					NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
					LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
				};

				int BindingPoint;
				unsigned int HandleID;
				//int BitsPerPixel;

				// -------------------- Image Info -------------------- //
				int LevelOfDetail;
				int InternalFormat;
				math::integer3 GridSize;
				int ChannelFormat;
				int DataType;
				size_t MemSize;
				void* hptr;

				bool EnableMipmap;
				math::integer2 Parameters[6];

				// --------------- Reflects Host Memory --------------- //
				int hInternalType;		// GL_FLOAT_VEC3
				int hInternalFormat;	// GL_RGB32F
				math::integer3 hGridSize;		// { 512, 512, 0 }
				int hBaseFormat;		// GL_RGB
				int hBaseDataType;		// GL_FLOAT

				texture();
				~texture();

				texture(const texture& inp);
				texture(texture&& inp);

				texture& operator=(const texture& rhs);
				texture& operator=(const texture&& rhs);

				int reserve_host_memory(int SamplerType, math::integer3 SamplerSize, int ChannelFormat, int DataType);

				int image_2d();

				//texture(texture& inp);
				//texture(texture&& inp);
				//texture& operator=(texture& rhs);
				//texture& operator=(texture&& rhs);

				//bool read(const char* FilePath);
				//bool write(const char* FilePath);


				bool reserve_host_memory(texture_type TextureType, math::integer3 TextureSize, channel_format TextureChannelFormat, int TextureDataType);
				bool release_host_memory();

				bool reserve_device_memory(texture_type TextureType, math::integer3 TextureSize, channel_format TextureChannelFormat, int TextureDataType);
				bool release_device_memory();

				bool send_to_device();

				void set_wrapping(int S, int T, int R);
				void set_filter(int Min, int Mag);
				void generate_mip_maps();

			};

		}
	}
}

#endif // !TEXTURE_H