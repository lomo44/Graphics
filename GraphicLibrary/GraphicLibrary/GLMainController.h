#pragma once
#include "MainController.h"
#include "GLUTWindowsController.h"
#include "GLObjectRenderer.h"

class GLMainController : public MainController {
public:
	GLMainController() {};
	~GLMainController() {};
	void Initialization();
	int CreateNewWindow(const WindowAttribute& _new);
	void MainLoop();
private:
	GLUTWindowsController m_windowController;
	GLObjectRenderer m_ObjectRenderer;
};
