/*
 * Ray.h
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */
#ifndef RAY_H_
#define RAY_H_

#include <queue>
#include <assert.h>
#include <stdlib.h>
#include "Face.h"
#include "Vector.h"
#include "Attribute.h"

class Ray{
public:
    Ray(Ray* _prior,Line _line, int _time);
    Ray();
    virtual ~Ray();
    std::vector<Ray*>& reflect(const Vector4f& norm);
    Ray* refract(const Vector4f& norm, Material* _from);
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
    inline void enableShadow(unsigned int _numoplightsrc){
        m_bShadowEnabled = true;
        m_iNumOfLighting = _numoplightsrc;
        m_pLightingIntensity = new float[_numoplightsrc];
        for(unsigned int i =0 ; i < _numoplightsrc ; i++){
            m_pLightingIntensity[i] = 0.0;
        }
    }
    inline void disableShadow(){
        m_bShadowEnabled = false;
    }
    inline void setBlockedLight(unsigned int _num, float intensity){
        assert(_num < m_iNumOfLighting && _num >= 0);
        m_pLightingIntensity[_num] = intensity;
    }
    inline bool checkBlockedLight(unsigned int _num){
        assert(_num < m_iNumOfLighting && _num >= 0);
        return m_pLightingIntensity[_num];
    }
    inline bool setAmbientColor(const Vector4f& _color){
        m_color = _color;
    }
    static float CalculateReflectance(const Vector4f& normal,
			const Vector4f& incident, Material* from, Material* to);
    inline Vector4f getColor(){
        return m_fReflectionIntensity * m_color;
    }
    // Jitter the ray, return the direction of the jittered ray;
    inline Vector4f& jitter(const Vector4f& _x, const Vector4f& _y, const Vector4f& _z, float limit){
        // Test if limit is greater than zero
        assert(limit > 0.0);
        // Test for vector;
        assert(_x[3] ==0 && _y[3] == 0 && _z[3] == 0);
        float random_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit));
        float random_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit));
        float random_z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit));
        this->m_RayLine.m_Direction += random_x * _x;
        this->m_RayLine.m_Direction += random_y * _y;
        this->m_RayLine.m_Direction += random_z * _z;
        this->m_RayLine.m_Direction.Normalize();
        return this->m_RayLine.m_Direction;
    }
public:
	Line m_RayLine;
	Vector4f m_color;
	bool m_isDone;
    bool m_bShadowEnabled;
	Attr_Intersection* m_pIntersectionProperties;
	int m_iID;
	float m_fReflectionIntensity;
    int m_iRecursiveTime;
    
    // if the ray can be shade by light 1, then m_bLightingList[1] = true;
    int m_iNumOfLighting;
    float* m_pLightingIntensity;
private:
	static void RecursiveCollapse(Ray* ray);
	Ray* m_pPriorRay;
	std::vector<Ray*> m_pReflectedRayList;
	Ray* m_pRefractedRay;
};

#endif /* RAY_H_ */
