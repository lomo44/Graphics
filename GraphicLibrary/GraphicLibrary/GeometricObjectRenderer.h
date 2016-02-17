#pragma once
#include <queue>

#include "GeometricObject.h"

class GeometricObjectRenderer {
public:
	GeometricObjectRenderer() {};
	~GeometricObjectRenderer() {};
	virtual void Reshape(int width, int height) = 0;
	virtual void Initialization() = 0;
	void Render();
	void ClearStack();
private:
	std::queue<GeometricObject> m_drawstack;
};