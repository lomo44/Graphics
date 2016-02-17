#pragma once
class GeometricObjectRenderer;
class MainController;

extern MainController* g_MainController;
extern GeometricObjectRenderer* g_Renderer;

void RenderWrapper();
void ReshapeWrapper(int _x, int _y);