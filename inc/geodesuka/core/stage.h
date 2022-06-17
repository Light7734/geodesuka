//
// ------------------------- stage.h ------------------------- //
// A stage is simply a collection of objects that share the
// same space and therefore the same coordinate vectors. While
// the engine holds all created objects and updates, to be rendered
// they must be in the same coordinate space along with possible
// render targets. 
// 
// A stage is a collection of objects that firstly, share the same space
// which gives meaning to their position vector. Secondly, since they share
// the same space, they can be interpreted to interact with one and another.
//
// It is a assumed that stages and the context they create share the same
// rendering and compute context.

#pragma once
#ifndef GEODESUKA_CORE_STAGE_H
#define GEODESUKA_CORE_STAGE_H

#include "stage_t.h"
#include "stage/desktop.h"
#include "stage/canvas.h"
#include "stage/scene2d.h"
#include "stage/scene3d.h"

#endif // !GEODESUKA_CORE_STAGE_H
