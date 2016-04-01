/*
 * BoundingBox.h
 *
 *  Created on: Apr 1, 2016
 *      Author: c5lizhua
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

class BoundingBox {
public:
	BoundingBox(const Vector4f& _MaxXYZ, const Vector4f& _MinXYZ);
	virtual ~BoundingBox();
private:
	Vector4f m_MaxXYZ;
	Vector4f m_MinXYZ;
};

#endif /* BOUNDINGBOX_H_ */
