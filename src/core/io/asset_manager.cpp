#include "asset_manager.h"

#include "../util/text.h"

#include "asset.h"
//#include "../graphical/shader.h"
//#include "../graphical/texture.h"
//#include "../graphical/mesh.h"

asset_manager::asset_manager() {
	Asset = nullptr;
	AssetCount = 0;
}

asset_manager::~asset_manager() {
	if (Asset != nullptr) {
		for (int i = 0; i < AssetCount; i++) {
			if (Asset[i] != nullptr) {
				delete Asset[i];
				Asset[i] = nullptr;
			}
		}
		delete[] Asset;
		Asset = nullptr;
	}
	AssetCount = 0;
}