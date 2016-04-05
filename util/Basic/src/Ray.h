/*
 * Ray.h
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */
#ifndef RAY_H_
#define RAY_H_

#include <queue>
#include "Face.h"
#include "Vector.h"
#include "Attribute.h"

class Ray{
public:
	Ray(Ray* _prior,Line _line, int _time);
    Ray();
	virtual ~Ray();
	std::vector<Ray*>& reflect(const Vector4f& norm);
	Ray* refract(const Vector4f& norm, Attr_Material* _from);
	inline void CollapseRayTracingTree(){
		RecursiveCollapse(this);
	}
	inline bool hasIntersect(){
		return m_pIntersectionProperties!=NULL;
	}
    inline bool hasReflectedRay(){
        return m_pReflectedRayList.size()!=0;
    }
    inline bool hasRefractedRay(){
        return m_pRefractedRay != NULL;
    }
	static float CalculateReflectance(const Vector4f& normal,
			const Vector4f& incident, Attr_Material* from, Attr_Material* to);
    inline Vector4f getColor(){
        return m_fLightIntensity * m_color;
    }
public:
	Line m_RayLine;
	Vector4f m_color;
	bool m_isDone;
	Attr_Intersection* m_pIntersectionProperties;
	int m_iID;
	float m_fLightIntensity;
    int m_iRecursiveTime;
private:
	void RecursiveCollapse(Ray* ray);
	Ray* m_pPriorRay;
	std::vector<Ray*> m_pReflectedRayList;
	Ray* m_pRefractedRay;
};

#endif /* RAY_H_ */
