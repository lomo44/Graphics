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
    std::vector<Vector4f>& getVisibleSamplePoint(){
        return m_LightSamples;
    }
    int m_iID;
    eLightType m_eLightType;
protected:
    std::vector<Vector4f> m_LightSamples;
};

class PointLight : public Light{
public:
	~PointLight();
	PointLight(Attr_PointLight _attr);
	void shade(Ray& _ray);
    Attr_PointLight m_LightingAttribute;
};

class AreaLight : public Light{
public:
    ~AreaLight();
    AreaLight(Attr_AreaLight* _attr);
    void shade(Ray& _ray);
    Attr_AreaLight* m_pLightingAttribute;
};

#endif /* LIGHT_H_ */
