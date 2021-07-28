#ifndef FONT_H
#define FONT_H

// OpenGL
#include "opengl.h"

// OpenCL
#include "opencl.h"

#include "texture.h"

class font {
public:

	static bool initialize();
	static bool terminate();

	texture SymbolSet;

	int m, n, l;
	void *hptr;
	float *sx;
	float *sy;
	float *bx;
	float *by;
	float *ax;
	float *ay;

	font();
	~font();

	bool read(const char* Path);
	bool load();
	bool clear();

};
#endif // !FONT_H