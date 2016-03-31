/*
 * Ray.h
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */
#ifndef RAY_H_
#define RAY_H_

#include "Face.h"
#include "Vector.h"
#include "Attribute.h"

class Ray{
public:
	Ray(Ray* _prior,Line _line, int _time);
	virtual ~Ray();
	Ray* reflect(const Vector4f& norm);
	Ray* refract(const Vector4f& norm, Attr_Material* _from);
	bool checkDone();
	inline bool hasIntersect(){
		return m_pIntersectionProperties!=NULL;
	}
public:
	Line m_RayLine;
	Vector4f m_color;
	bool m_isDone;
	Attr_Intersection* m_pIntersectionProperties;
	int m_iID;
private:
	int m_iRecursiveTime;
	Ray* m_pPriorRay;
	Ray* m_pReflectedRay;
	Ray* m_pRefractedRay;
};

#endif /* RAY_H_ */
