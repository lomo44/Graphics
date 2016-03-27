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
class Ray{
public:
	Ray(Ray* _prior,Line _line, int _time);
	virtual ~Ray();

	void reflect();
	void refract();
	void trace();
	bool checkDone();
public:
	Line m_RayLine;
	Vector4f m_color;
	bool m_isDone;

private:
	int m_iRecursiveTime;
	Ray* m_pPriorRay;
	Ray* m_pReflectedRay;
	Ray* m_pRefractedRay;
};

#endif /* RAY_H_ */
