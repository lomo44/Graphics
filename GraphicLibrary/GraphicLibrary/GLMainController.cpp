#include "GLMainController.h"
#include "GlobalVariable.h"

void GLMainController::Initialization()
{
	g_Renderer = &m_ObjectRenderer;
	g_Renderer->Initialization();
	m_windowController.Initialization();
}

int GLMainController::CreateNewWindow(const WindowAttribute& _new)
{
	return m_windowController.CreateAWindow(_new);

}

void GLMainController::MainLoop()
{
	glutReshapeFunc(ReshapeWrapper);
	glutDisplayFunc(RenderWrapper);
	glutMainLoop();
}
