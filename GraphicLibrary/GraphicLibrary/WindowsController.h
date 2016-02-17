#pragma once
#include "CommonType.h"

class WindowsController {
public:
	WindowsController() {};
	virtual ~WindowsController() {};
	virtual void Initialization() const = 0;
	virtual int CreateAWindow(const WindowAttribute& _new) const = 0;
};