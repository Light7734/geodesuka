// ------------------------------ object.h ------------------------------ //
/*
* object.h will serve as a generic object that is extendable for the user
* to implement custom object derivative classes. cube.h is an example of this
* and more examples will be provided. The difference here is that the extended
* classes of object.h will have full control over how they will be rendered to
* the target window.h or camera.h object.
* 
* Since an object will have part of itself associated with memory objects
* of particular GPUs, it is important to recognize that objects exist within
* a common space in which they are rendered. On top of that, a rendering context
* will indicate which graphics capable device it exists on. Maybe figure out
* how to stream line 
*/

#pragma once
#ifndef GEODESUKA_CORE_OBJECT_H
#define GEODESUKA_CORE_OBJECT_H

#include "object_t.h"
//#include "object_list.h"
#include "object/system_terminal.h"
#include "object/render_target.h"
#include "object/window.h"
#include "object/system_display.h"
#include "object/system_window.h"
#include "object/virtual_window.h"
#include "object/camera.h"
#include "object/camera2d.h"
#include "object/camera3d.h"
#include "object/text.h"

#endif // !GEODESUKA_CORE_OBJECT_H
