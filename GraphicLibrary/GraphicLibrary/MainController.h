#pragma once
#include "CommonType.h"
#include "GeometricObjectRenderer.h"

class MainController {
public:
	MainController() {};
	virtual ~MainController() {};
	virtual void Initialization() = 0;
	virtual int CreateNewWindow(const WindowAttribute& _new) = 0;
	virtual void MainLoop() = 0;
};



