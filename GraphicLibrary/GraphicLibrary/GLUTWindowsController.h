#pragma once
#include <vector>
#include "CommonType.h"
#include "WindowsController.h"
class GLUTWindowsController : public WindowsController {
public:
	GLUTWindowsController() {};
	virtual ~GLUTWindowsController() {};
	void Initialization() const;
	int CreateAWindow(const WindowAttribute& _new) const;
private:
	std::vector<int> m_WindowList;
};