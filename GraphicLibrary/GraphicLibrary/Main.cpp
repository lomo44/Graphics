/*Singel File For Graphic Library*/


#include <iostream>

#include "CommonType.h"
#include "GraphicLibrary.h"

int main() {
	WindowAttribute newwindow;
	newwindow.name = "ww";
	newwindow.pos_x = 0;
	newwindow.pos_y = 0;
	newwindow.size_x = 300;
	newwindow.size_y = 300;
	MainController* controller = GraphicLibraryInit(OpenGL);
	controller->CreateNewWindow(newwindow);
	controller->MainLoop();
	return 0;
}


// Function Implementation




