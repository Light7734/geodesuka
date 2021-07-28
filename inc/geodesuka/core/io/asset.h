#pragma once
#ifndef ASSET_H
#define ASSET_H

// This is the base class the represents
// all loadable assets, shaders, scripts, 
// model files, 

#include "../util/text.h"

#include "file.h"

class asset {
public:

	// Child class ids.
	enum type {
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		PIXEL_SHADER,
		KERNEL,
		LUA_SCRIPT,
		FONT,
		IMAGE,

	};

	file File;

	asset();
	virtual ~asset() = 0;

};

#endif // !ASSET_H
