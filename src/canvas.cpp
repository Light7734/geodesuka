#include <geodesuka/core/stage/canvas.h>

namespace geodesuka::core::stage {

    canvas::canvas(engine* aEngine, gcl::context* aContext) : stage_t(aEngine, aContext) {
        this->Engine = aEngine;
        this->Context = aContext;
    }

    canvas::~canvas() {
        // Will be used to clear out all windows.
    }

    stage_t::batch canvas::render() {
        stage_t::batch DrawBatch;
        this->Mutex.lock();
        //for (size_t i = 0; i < this->Window.size(); i++) {
        //    object::rendertarget* RT = this->Window[i];
        //    DrawBatch += RT->draw(this->ObjectCount, this->Object);
        //}
        this->Mutex.unlock();
        return DrawBatch;
    }

}
