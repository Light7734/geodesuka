#include <geodesuka/core/object/camera3d.h>

namespace geodesuka::core::object {

	const char* camera3d::DefaultPerVertexShaderSource = "";

	const char* camera3d::DefaultPerPixelShaderSource = "";

	//void camera3d::draw(object_t* aObject) {
	//	// Checks if this and aObject are the same object.
	//	if ((object_t*)this == aObject) return;
	//
	//	// Checks if both camera3d instance and aObject have
	//	// the same rendering context.
	//	//if (this->RenderingContext != aObject->RenderingContext) return -2;
	//
	//	// New idea for rendering objects to camera, sort
	//	// from nearest to farthest to make efficient rendering.
	//	// How to deal with alpha?
	//
	//	// DepthList:
	//	// The depth list is a list of sorted objects based
	//	// on the distance from the camera they are. The opaque
	//	// objects nearest to the camera will be rendered first.
	//
	//	// AlphaList:
	//	// Objects with that have translucency or are transparent
	//	// (i.e. Alpha != 1.0) will be drawn where the furthest objects
	//	// are rendered first for appropriate ordering.
	//
	//	//math::real DeltaPos = math::length(temp);
	//
	//	aObject->draw(this);
	//
	//}

	int camera3d::id() {
		return ID;
	}

	VkSubmitInfo camera3d::draw(size_t aObjectCount, object_t** aObject) {
		VkSubmitInfo DrawBatch{};
		DrawBatch.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		DrawBatch.pNext = NULL;
		return DrawBatch;
	}

}