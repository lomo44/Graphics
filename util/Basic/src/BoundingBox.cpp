/*
 * BoundingBox.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: c5lizhua
 */

#include "BoundingBox.h"

BoundingBox::BoundingBox(const Vector4f& _MaxXYZ, const Vector4f& _MinXYZ) {
	// TODO Auto-generated constructor stub
	this->m_MaxXYZ = _MaxXYZ;
	this->m_MinXYZ = _MinXYZ;
}

BoundingBox::~BoundingBox() {
	// TODO Auto-generated destructor stub
}

