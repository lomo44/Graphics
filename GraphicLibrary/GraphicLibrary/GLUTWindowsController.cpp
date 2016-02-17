#include "GLUTWindowsController.h"
#include <gl/glut.h>

int GLUTWindowsController::CreateAWindow(const WindowAttribute& _new) const {

	// Create window
	glutInitWindowPosition(_new.pos_x, _new.pos_y);
	glutInitWindowSize(_new.size_x, _new.size_y);
	int windowID = glutCreateWindow(_new.name.c_str());
	return windowID;
}

void GLUTWindowsController::Initialization() const {
	// Set video mode: double-buffered, color, depth-buffered
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
}