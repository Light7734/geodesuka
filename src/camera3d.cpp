#include <geodesuka/core/object/camera3d.h>

namespace geodesuka::core::object {

	const char* camera3d::OpaquePerVertexShaderSource = "";

	const char* camera3d::OpaquePerPixelShaderSource = "";

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