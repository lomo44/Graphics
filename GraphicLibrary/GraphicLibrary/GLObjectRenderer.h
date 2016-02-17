#pragma once
#include "GeometricObjectRenderer.h"
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

class GLObjectRenderer : public GeometricObjectRenderer {
public:
	GLObjectRenderer() {};
	~GLObjectRenderer() {};
	void Reshape(int width, int height);
	void Initialization();
};
