<img src="https://github.com/ShaderKitty/Geodesuka/blob/d20220521-v0.0.20/res/github/gsdgiusdu2_2k.png" align="left" height="128" width="128" alt="Geodesuka Engine">

## Geodesuka Engine v0.0.20

<p align="center">
  <a href="https://discord.gg/WhwHUMV"> <img src="https://img.shields.io/discord/380484403458998276?logo=discord"> </a>
</p>

[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.md)
[![forthebadge](https://forthebadge.com/images/badges/works-on-my-machine.svg)](https://forthebadge.com)

![](https://github.com/ShaderKitty/Geodesuka/blob/master/res/github/glcringe.jpg)

# State of the Engine

Currently what is being worked on is the rendering scheduler, as it will attempt to honor
the requested frame rate/refresh rate of each render target. Looking at other people's engines,
they seem to use a one and done renderer to prop up images on the screen as quickly as possible
while this engine gives a lot of render choices to the object implementations themselves. This
could nerf performance, but won't know until various scenes have been constructed and are being
actively rendered by the engine. Since the way this engine is designed, this could severely impair
performance. But wont't really know until I test it.

Since OpenCL 3.0 specification has been released by the Khronos group, it turns out that it might
still be possible to combine the kernel execution model of various GPGPU compute apis with graphics
rasterization apis like Vulkan.
https://www.khronos.org/blog/khronos-releases-opencl-3.0-extensions-for-neural-network-inferencing-and-opencl-vulkan-interop

# Description

The name "Geodesuka" has it's origins from a General Relativity class I took with a friend in 2017. It was
an ambitious project of building a real time relativistic renderer for the classes final project. We wanted
to utilize GPU computing for ray marching in curved space time to visually capture what an observer would
see in curved space time. This involved calculating light paths (null geodesics) with a particular metric
that described the curvature of a particular space and time. So we called the project a "Geodesic Renderer",
but then I had taken the liberty to weebify it and every once and a while change the window title to 
"Geodesuka Renderer". Needless to say, he was not impressed with the change. That is where the name "Geodesuka"
comes from, a weebified variant of the word "Geodesic", which is generally defined to be the shortest path within
a space.

After my first programming class I had taken an interest in GPU computing, not neccessarily for AI purposes, but
tasks outside of just rasterization and fixed pipeline rendering. What started out as a hobby project to more 
efficiently do expensive numerical computations such as fluid sims, vector field math, and large particles systems
is now being developed as a generalized API for GPGPU computation api for a game engine.

That is the final goal of this engine is to fully utilized general gpu usage into the backend of a game engine 
that can be used for purposes beyond just simple raster graphics or even hardware accelerated ray tracing. Perhaps
still an ambitious goal for a single person, but it is still a fun project to work on during the weekends.

# Updated List:

- engine.cpp Added backend update and render thread code. Engine will now process all contexts, objects, and stages.

# To Do List:

- context.h will support TRANSFER, GRAPHICS_AND_COMPUTE, and PRESENT operation
queues. Graphics and Compute will be treated as the same operation, which is
computational work being performed on the GPU.

- math.h will be re worked to include fields.

- Create System Terminal Class for engine debug commands in engine backend.

- Rewrite math library for more coherent primitive data types, then construct
natural, integer, and real types from it.

- Add r1.h, r2.h, r3.h, r4.h, and vector field classes to engine.

- Add layering system for window objects, for huds, system stats and so
on. (Will be done with canvas class, and window as target.)

- Resolve issue with object being used in multiple stages simultaneously.

# Back Burner:

- File System stuff.

- Add built in extension types for file.h to recognize file types
and forward to proper objects.

- Add lua support for runtime scripting.

- Add asset loading libraries (Assimp, FreeImage, FreeType, ...)

- Add engine asset manager to prevent double loading.

- Add Dynamic Library compilation options.

- Change Texture class to image class? The reasoning behind this change
along with how vulkan does it, is that a texture describes the texture
of a particular surface while an image is a generalized concept of a type
of memory.

- Set up compilation unit directories to prevent source name space over writing.

- Add compile support for linux.

- Add memory pool manager. 

# Third Party Libraries

This engine uses the following third party libraries.

Vulkan - Used for graphics.

OpenCL - https://software.intel.com/content/www/us/en/develop/tools/opencl-sdk.html
    The OpenCL SDK Developed by intel is used in this project. Must be installed before usage.
    If you wish to use another OpenCL SDK, just change the proper directories associated with
    the project files to do so. Otherwise go to the link provided to download Intel's OpenCL.

GLFW - https://github.com/glfw/glfw
    GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
    It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, 
    handling events, etc.

glslang: - https://github.com/KhronosGroup/glslang
    Is backend compiler to SPIRV in this project.

# Reference Specifications:

Vulkan:
https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html

OpenCL:
https://www.khronos.org/registry/OpenCL/specs/3.0-unified/html/OpenCL_API.html#_the_opencl_architecture

# Donate

Feel free to donate if you think this is something worth throwing money at.

BTC: 1AA61gvL4ixzKxyw1vajrcR9qX5xubyiBW

ETH: 0xA5373966219b12B0e51753F5735bb1815d5D7c88
