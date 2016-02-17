#pragma once

#include "CommonType.h"
#include "Vector.h"

class GeometricObject {
public:
	GeometricObject();
	virtual ~GeometricObject();
	virtual void scale3d(STD_P _x, STD_P _y, STD_P _z) = 0;
	virtual void rotate3d(STD_P _a, STD_P _b, STD_P _c);
	virtual void translate3d(STD_P _x, STD_P _y, STD_P _z);
	virtual void draw();
private:
	GeometricObjectType m_ObjectType;
	uint64_t m_ID;
	vector3D<STD_P> m_centerpoint;
	bool m_bIsVisiable;
};