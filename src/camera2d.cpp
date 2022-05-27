#include <geodesuka/core/object/camera2d.h>

namespace geodesuka::core::object {

    camera2d::camera2d(engine* aEngine, gcl::context* aContext, stage_t* aStage) : camera(aEngine, aContext, aStage) {

    }

    camera2d::~camera2d() {

    }

    int camera2d::rtid() {
        return RTID;
    }

    VkSubmitInfo camera2d::draw(size_t aObjectCount, object_t** aObject) {
        VkSubmitInfo DrawBatch{};
        DrawBatch.sType = VkStructureType::VK_STRUCTURE_TYPE_SUBMIT_INFO;
        DrawBatch.pNext = NULL;
        return DrawBatch;
    }

}
