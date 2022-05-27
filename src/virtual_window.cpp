#include <geodesuka/core/object/virtual_window.h>

namespace geodesuka::core::object {

	int virtual_window::rtid() {
		return RTID;
	}

	VkSubmitInfo virtual_window::draw(size_t aObjectCount, object_t** aObject) {
		VkSubmitInfo DrawBatch{};
		DrawBatch.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		DrawBatch.pNext = NULL;
		return DrawBatch;
	}

}