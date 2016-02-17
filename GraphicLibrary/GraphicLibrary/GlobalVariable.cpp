#include "GlobalVariable.h"
#include "GeometricObjectRenderer.h"
#include "MainController.h"
GeometricObjectRenderer* g_Renderer;
MainController* g_MainController;

void RenderWrapper() {
	g_Renderer->Render();
}
void ReshapeWrapper(int _x, int _y) {
	g_Renderer->Reshape(_x, _y);
}