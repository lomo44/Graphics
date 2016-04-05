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
        float Igreen = 0;
        float Ired = 0;
        float Iblue = 0;
        Vector4f sec2light = this->m_LightingAttribute.m_LightPosition - _ray.m_pIntersectionProperties->m_IntersectionPoint;
        sec2light.Normalize();
        sec2light[3] = 0;
        Vector4f raydir = -_ray.m_RayLine.m_Direction;
        raydir.Normalize();
        raydir[3] = 0;
        Vector4f ref = 2 * sec2light.dot(_ray.m_pIntersectionProperties->m_InterpolatedNormal) * 
                _ray.m_pIntersectionProperties->m_InterpolatedNormal - sec2light;
        float specular = std::pow(std::max(0.0,(double)ref.dot(raydir)),_ray.m_pIntersectionProperties->m_Material->m_fSpecularWeight);
        float diffuse = std::max(0.0,(double)sec2light.dot(_ray.m_pIntersectionProperties->m_InterpolatedNormal));
        Ired = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[0]*this->m_LightingAttribute.m_AmbientColor[0]+
                _ray.m_pIntersectionProperties->m_Material->m_DefuseColor[0]*diffuse*this->m_LightingAttribute.m_DefuseColor[0]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[0]*specular*this->m_LightingAttribute.m_SpecularColor[0];
        Igreen = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[1]*this->m_LightingAttribute.m_AmbientColor[1]+
                _ray.m_pIntersectionProperties->m_Material->m_DefuseColor[1]*diffuse*this->m_LightingAttribute.m_DefuseColor[1]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[1]*specular*this->m_LightingAttribute.m_SpecularColor[1];
        Iblue = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[2]*this->m_LightingAttribute.m_AmbientColor[2]+
                _ray.m_pIntersectionProperties->m_Material->m_DefuseColor[2]*diffuse*this->m_LightingAttribute.m_DefuseColor[2]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[2]*specular*this->m_LightingAttribute.m_SpecularColor[2];
        _ray.m_color[0] *= Ired;
        _ray.m_color[1] *= Igreen;
        _ray.m_color[2] *= Iblue;
        if(_ray.m_color[0]>1) _ray.m_color[0] = 1;
        if(_ray.m_color[1]>1) _ray.m_color[1] = 1;
        if(_ray.m_color[2]>1) _ray.m_color[2] = 1;
        _ray.m_isDone = true;
    }
    else{
        if(_ray.m_iID==-1){
            _ray.m_color[0] = 1;
            _ray.m_color[1] = 1;
            _ray.m_color[2] = 1;
        }
        else{
            _ray.m_color[0] = 0;
            _ray.m_color[1] = 0;
            _ray.m_color[2] = 0;
        }
        
        _ray.m_isDone = true;
    }
		/*Vector4f light_direction = this->m_LightingAttribute.m_LightPosition-
				_ray.m_pIntersectionProperties->m_IntersectionPoint;
        light_direction.Normalize();
		Vector4f ray_direction = _ray.m_RayLine.m_Direction;
		float k = _ray.m_pIntersectionProperties->m_Normal.dot(-light_direction) * 2;
		Vector4f reflect_direction = light_direction - k * _ray.m_pIntersectionProperties->m_Normal;
        reflect_direction.Normalize();
		float diffuse = std::max(0.0,(double)_ray.m_pIntersectionProperties->m_Normal.dot(light_direction));
		float specular = std::pow(std::max(0.0,(double)ray_direction.dot(reflect_direction)),
				_ray.m_pIntersectionProperties->m_Material->m_fSpecularWeight);
        //std::cout<<specular<<std::endl;
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
	}*/
}
