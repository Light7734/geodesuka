#pragma once
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

// The goal of this class it to manage loaded
// assets in chunks. This class is meant to 
// prevent duplicate asset loading. This should
// also prevent reloading as well since a second
// load will just skip file reading and handing
// over the preexisting asset pointer.

#include "../util/text.h"

#include "asset.h"

class asset_manager {
public:

	// These are absolute paths, not relative.
	static text ProcessWorkingDirectory; // This is the directory in which the process
	static text CurrentWorkingDirectory;

	asset** Asset;
	int AssetCount;

	asset_manager();
	~asset_manager();

	//asset* fetch_asset(const char* Path);
	//asset* fetch_asset(const text& Path);

	//asset* open_asset(const char *Path);
	//asset* open_asset(const text& Path);

};

#endif // !ASSET_MANAGER_H
