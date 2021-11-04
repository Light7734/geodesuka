# Geodesuka Engine

[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.md)
[![forthebadge](https://forthebadge.com/images/badges/works-on-my-machine.svg)](https://forthebadge.com)


[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/no-ragrets.svg)](https://forthebadge.com)

Project Start: 2021/06/01

Branch Birth Date: 2021/10/23

Branch Pull Date: ????/??/??

Version: 0.0.15

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

- context.h now has a properly implemented method of queue selection
at runtime, a simple method of queue selection for now, but it should
minimize over submission to improper queues. Since some queues only
exclusively support certain operations, when that operation is desired,
context.h directs the submission to that, removing traffic from queues
that have multiple types of support. Logically these methods work, but
they need to be tested with actual work loads.

- In engine.cpp, a simple mutex was not sufficient to temporarily suspend
threads to add new contexts, objects, and stages. A simple trap.h class
is just a thread trapper that traps threads in a loop while another thread
can modify the state of the engine and continue running once this operation
is complete.

Added stage class to describe object sets that share the same physical space,
render operations, and interaction methods. canvas.h is designed to be inherited
to describe stages where 2d objects are drawn to window frames directly. scenexd
describes 2D and 3D spaces which objects share.

Added system_terminal.h class to engine, handles input from terminal that started
the engine. Will be used for future debugging efforts and modifying engine at 
runtime. Will most likely be supressed in release.

The directory builtin/ is some basic built in primitives that can be used to 
debug graphics problems and be taken as an example of extended object_t and 
stage_t.

Updated math library namespaces and macro defs. Needed to be done to minimize
macro def collision and interference.

Added timer class.

# To Do List:


- Figure out how to deal with command pools efficiently.

- Add proper constructors to natural vectors.

- Finish buffer.h and texture.h staging buffer backend now that
context.h is complete for command buffer submission.

- Add r1.h, r2.h, r3.h, r4.h, and vector field classes to engine.

- Add asset loading libraries (Assimp, FreeImage, FreeType, ...)

- Add lua support for runtime scripting.

- Update headers guards to minimize probabilty of collision.

- Add built in extension types for file.h to recognize file types
and forward to proper objects.

- Add engine asset manager to prevent double loading.

- Add layering system for window objects, for huds, system stats and so
on.

- Change render_target to new name that makes more sense.

- Add Dynamic Library compilation options.

# Back Burner:

- Change Texture class to image class? The reasoning behind this change
along with how vulkan does it, is that a texture describes the texture
of a particular surface while an image is a generalized concept of a type
of memory.

- Set up compilation unit directories to prevent source name space over writing.

- Add compile support for linux.

- Add memory pool manager. 

# Third Party Libraries

This engine uses the following third party libraries.

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

# Contact Info:
![](https://img.shields.io/badge/Discord-7289DA?style=for-the-badge&logo=discord&logoColor=white) 
ShaderKitty#1696 

![](https://discord.gg/GuqfBzfHgt)

Feel free to contact me through discord if github.com isn't doing any justice on what you would like to convey.
I am mostly available when I am not at work, and if you have any    qws or suggestions feel free to reach out.

# Donations

Feel free to donate if you think this is something worth throwing money at.

BTC: 1AA61gvL4ixzKxyw1vajrcR9qX5xubyiBW
ETH: 0xA5373966219b12B0e51753F5735bb1815d5D7c88
XMR: 42bFDxJ2FjtDN9h3ZS3kmUDs5tD2Zha74SNLEmycUH2CRY6b4bLKu95SpDmoWCysYoXSPNYBsVhfm9qdoNkd44tnQ1HThkc
