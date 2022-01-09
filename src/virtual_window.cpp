#include <geodesuka/core/object/virtual_window.h>

namespace geodesuka::core::object {

	const int virtual_window::ID = 3;

	int virtual_window::id() {
		return ID;
	}

	VkSubmitInfo virtual_window::draw(size_t aObjectCount, object_t** aObject) {
		VkSubmitInfo DrawBatch{};
		DrawBatch.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
		DrawBatch.pNext = NULL;
		return DrawBatch;
	}

	void virtual_window::swap() {

	}

}