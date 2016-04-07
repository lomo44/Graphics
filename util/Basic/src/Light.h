/*
 * Light.h
 *
 *  Created on: Mar 28, 2016
 *      Author: c5lizhua
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Attribute.h"
#include "Vector.h"
#include <vector>
class Ray;
enum eLightType{
    eLightType_Pointlight,
    eLightType_Squarelight
};   
class Light {    
public:
	Light(){}
	virtual ~Light(){}
    eLightType getType(){
        return m_eLightType;
    }
	virtual void shade(Ray& _ray) = 0;
    virtual std::vector<Vector4f> getVisibleSamplePoint() = 0;
    int m_iID;
    eLightType m_eLightType; 
};

class PointLight : public Light{
public:
	~PointLight();
	PointLight(Attr_PointLight _attr);
	void shade(Ray& _ray);
    std::vector<Vector4f> getVisibleSamplePoint(){
        std::vector<Vector4f> ret;
        ret.push_back(m_LightingAttribute.m_LightPosition);
        return ret;
    }
    Attr_PointLight m_LightingAttribute;
};

class AreaLight : public Light{
    ~AreaLight();
    AreaLight(Attr_AreaLight* _attr);
    void shade(Ray& _ray){};
    std::vector<Vector4f> getVisibleSamplePoint(){};
    Attr_AreaLight* m_pLightingAttr;
};

#endif /* LIGHT_H_ */
