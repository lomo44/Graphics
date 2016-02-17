#include "GLObjectRenderer.h"


void GLObjectRenderer::Reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
	glViewport(0, 0, width, height);
}

void GLObjectRenderer::Initialization()
{
	int argc = 0;
	char* argv[1];
	argv[0] = "";
	glutInit(&argc, argv);
}
