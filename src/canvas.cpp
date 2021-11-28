#include <geodesuka/core/stage/canvas.h>

namespace geodesuka::core::stage {

    canvas::canvas(engine* aEngine, gcl::context* aContext) {
        this->Engine = aEngine;
        this->Context = aContext;
    }

    canvas::~canvas() {
        // Will be used to clear out all windows.
    }

    stage_t::batch canvas::render() {
        stage_t::batch DrawBatch;
        return DrawBatch;
    }

}
