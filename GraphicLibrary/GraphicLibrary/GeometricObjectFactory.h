#pragma once
#include "CommonType.h"
#include <vector>
#include <iostream>

class GeometricObjectFactory {
public:
	uint64_t createLine(STD_P _x, STD_P _y, STD_P _z);
private:
	std::vector<uint64_t> m_ObjectIDList;
}; 
