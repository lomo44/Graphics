/*
 * Light.h
 *
 *  Created on: Mar 28, 2016
 *      Author: c5lizhua
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Attribute.h"
class Ray;
class Light {
public:
	Light(){}
	virtual ~Light(){}
	virtual void shade(Ray& _ray) = 0;
protected:
	Attr_Lighting m_LightingAttribute;
};

class PointLight : public Light{
public:
	~PointLight();
	PointLight(Attr_Lighting _attr);
	void shade(Ray& _ray);
private:
};

#endif /* LIGHT_H_ */
