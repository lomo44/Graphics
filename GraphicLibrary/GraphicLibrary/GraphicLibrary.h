#pragma once
#include "GLMainController.h"
#include "GlobalVariable.h"

MainController* GraphicLibraryInit(GeoPlatformType _type) {
	if (_type == OpenGL) {
		g_MainController = new GLMainController();
		g_MainController->Initialization();
		return g_MainController;
	}
	else {
		return NULL;
	}
}

