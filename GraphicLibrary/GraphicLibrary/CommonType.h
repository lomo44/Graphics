#pragma once
#include <string>
typedef double STD_P;

enum GeometricObjectType {
	Geo_Lines,
	Geo_Polygons,
};

enum GeoPlatformType {
	OpenGL,
};

struct WindowAttribute {
	int pos_x;
	int pos_y;
	int size_x;
	int size_y;
	std::string name;
};