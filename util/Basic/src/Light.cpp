/*
 * Light.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: c5lizhua
 */

#include "Light.h"
#include "Vector.h"
#include "Ray.h"
#include <cmath>
PointLight::PointLight(Attr_Lighting _attr){
	this->m_LightingAttribute = _attr;
}
PointLight::~PointLight(){

}

void PointLight::shade(Ray& _ray){
	if(_ray.hasIntersect()){
		Vector4f light_direction = this->m_LightingAttribute.m_LightPosition-
				_ray.m_pIntersectionProperties->m_IntersectionPoint;
        light_direction.Normalize();
		Vector4f ray_direction = _ray.m_RayLine.m_Direction;
		float k = _ray.m_pIntersectionProperties->m_Normal.dot(-light_direction) * 2;
		Vector4f reflect_direction = light_direction - k * _ray.m_pIntersectionProperties->m_Normal;
        reflect_direction.Normalize();
		float diffuse = std::max(0.0,(double)_ray.m_pIntersectionProperties->m_Normal.dot(light_direction));
		float specular = std::pow(std::max(0.0,(double)ray_direction.dot(-reflect_direction)),
				_ray.m_pIntersectionProperties->m_Material->m_fSpecularWeight);
		float red = this->m_LightingAttribute.m_AmbientColor[0]*_ray.m_pIntersectionProperties->m_Material->m_AmbientColor[0]+
				this->m_LightingAttribute.m_DefuseColor[0]*_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[0]*diffuse+
				this->m_LightingAttribute.m_SpecularColor[0]*_ray.m_pIntersectionProperties->m_Material->m_SpecularColor[0]*specular;
		float green = this->m_LightingAttribute.m_AmbientColor[1]*_ray.m_pIntersectionProperties->m_Material->m_AmbientColor[1]+
						this->m_LightingAttribute.m_DefuseColor[1]*_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[1]*diffuse+
						this->m_LightingAttribute.m_SpecularColor[1]*_ray.m_pIntersectionProperties->m_Material->m_SpecularColor[1]*specular;
		float blue = this->m_LightingAttribute.m_AmbientColor[2]*_ray.m_pIntersectionProperties->m_Material->m_AmbientColor[2]+
						this->m_LightingAttribute.m_DefuseColor[2]*_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[2]*diffuse+
						this->m_LightingAttribute.m_SpecularColor[2]*_ray.m_pIntersectionProperties->m_Material->m_SpecularColor[2]*specular;
		_ray.m_color[0] *= red;
		_ray.m_color[1] *= green;
		_ray.m_color[2] *= blue;
        if(_ray.m_color[0] > 1){
           _ray.m_color[0] = 1.0;
        }
        if(_ray.m_color[1] > 1){
           _ray.m_color[1] = 1.0;
        }
        if(_ray.m_color[2] > 1){
           _ray.m_color[2] = 1.0;
        }
       // _ray.m_color.Print();
        _ray.m_isDone = true;
	}
	else{
		_ray.m_color[0] = 0;
		_ray.m_color[1] = 0;
		_ray.m_color[2] = 0;
		_ray.m_isDone = true;
	}
}
