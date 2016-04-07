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
PointLight::PointLight(Attr_PointLight _attr){
	this->m_LightingAttribute = _attr;
    this->m_eLightType = eLightType_Pointlight;
    m_LightSamples.push_back(_attr.m_LightPosition);
}
PointLight::~PointLight(){

}
// TODO: Need to pull out the ambient and make it global
void PointLight::shade(Ray& _ray){
    if(_ray.hasIntersect()){
        //std::cout<<(_ray.m_iNumOfLighting)<<std::endl;
        float lightintensity;
        if(_ray.m_bShadowEnabled){
            lightintensity = _ray.m_pLightingIntensity[this->m_iID];
        }else{
            lightintensity = 1.0;
        }
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
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[0]*diffuse*this->m_LightingAttribute.m_DefuseColor[0]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[0]*specular*this->m_LightingAttribute.m_SpecularColor[0]) * lightintensity;
        Igreen = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[1]*this->m_LightingAttribute.m_AmbientColor[1]+
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[1]*diffuse*this->m_LightingAttribute.m_DefuseColor[1]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[1]*specular*this->m_LightingAttribute.m_SpecularColor[1]) * lightintensity;
        Iblue = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[2]*this->m_LightingAttribute.m_AmbientColor[2]+
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[2]*diffuse*this->m_LightingAttribute.m_DefuseColor[2]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[2]*specular*this->m_LightingAttribute.m_SpecularColor[2]) * lightintensity;
        _ray.m_color[0] += Ired;
        _ray.m_color[1] += Igreen;
        _ray.m_color[2] += Iblue;
        if(_ray.m_color[0]>1) _ray.m_color[0] = 1;
        if(_ray.m_color[1]>1) _ray.m_color[1] = 1;
        if(_ray.m_color[2]>1) _ray.m_color[2] = 1;
        _ray.m_isDone = true;
    }
    else{
        if(_ray.m_iID == -1){
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
        return;
    }
}


/*TODO: Need to modify this function*/
AreaLight::AreaLight(Attr_AreaLight* _attr) {
    m_pLightingAttribute = _attr;
    m_eLightType = eLightType_Squarelight;
    m_pLightingAttribute->m_Normal.Normalize();
    m_pLightingAttribute->m_Up.Normalize();
    Vector4f horizontal = m_pLightingAttribute->m_Normal.cross(m_pLightingAttribute->m_Up);
    horizontal.Normalize();
    float delta = m_pLightingAttribute->m_fLength / (float)(m_pLightingAttribute->m_iSampleSize);
    float factor = (_attr->m_fLength/2) + delta;
    Vector4f initpoint = _attr->m_LightPosition + factor * m_pLightingAttribute->m_Up + 
    factor * horizontal;
    for(unsigned int i = 0; i < m_pLightingAttribute->m_iSampleSize; i++){
        for(unsigned int j = 0; j < m_pLightingAttribute->m_iSampleSize;j++){
            Vector4f p = initpoint;
            p -= i* delta * horizontal;
            p -= j* delta * m_pLightingAttribute->m_Up;
            p.Randomize(horizontal, Vector4f(0,0,0,0), m_pLightingAttribute->m_Up,
                delta);
            m_LightSamples.push_back(p);
        }
    }
}

AreaLight::~AreaLight(){
    delete m_pLightingAttribute;
}

void AreaLight::shade(Ray& _ray){
    if(_ray.hasIntersect()){
        //std::cout<<(_ray.m_iNumOfLighting)<<std::endl;
        float lightintensity;
        if(_ray.m_bShadowEnabled){
            lightintensity = _ray.m_pLightingIntensity[this->m_iID];
        }else{
            lightintensity = 1.0;
        }
        float Igreen = 0;
        float Ired = 0;
        float Iblue = 0;
        Vector4f sec2light = this->m_pLightingAttribute->m_LightPosition - _ray.m_pIntersectionProperties->m_IntersectionPoint;
        sec2light.Normalize();
        sec2light[3] = 0;
        Vector4f raydir = -_ray.m_RayLine.m_Direction;
        raydir.Normalize();
        raydir[3] = 0;
        Vector4f ref = 2 * sec2light.dot(_ray.m_pIntersectionProperties->m_InterpolatedNormal) * 
                _ray.m_pIntersectionProperties->m_InterpolatedNormal - sec2light;
        float specular = std::pow(std::max(0.0,(double)ref.dot(raydir)),_ray.m_pIntersectionProperties->m_Material->m_fSpecularWeight);
        float diffuse = std::max(0.0,(double)sec2light.dot(_ray.m_pIntersectionProperties->m_InterpolatedNormal));
        Ired = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[0]*this->m_pLightingAttribute->m_AmbientColor[0]+
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[0]*diffuse*this->m_pLightingAttribute->m_DefuseColor[0]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[0]*specular*this->m_pLightingAttribute->m_SpecularColor[0]) * lightintensity;
        Igreen = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[1]*this->m_pLightingAttribute->m_AmbientColor[1]+
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[1]*diffuse*this->m_pLightingAttribute->m_DefuseColor[1]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[1]*specular*this->m_pLightingAttribute->m_SpecularColor[1]) * lightintensity;
        Iblue = _ray.m_pIntersectionProperties->m_Material->m_AmbientColor[2]*this->m_pLightingAttribute->m_AmbientColor[2]+
                (_ray.m_pIntersectionProperties->m_Material->m_DefuseColor[2]*diffuse*this->m_pLightingAttribute->m_DefuseColor[2]+
                _ray.m_pIntersectionProperties->m_Material->m_SpecularColor[2]*specular*this->m_pLightingAttribute->m_SpecularColor[2]) * lightintensity;
        _ray.m_color[0] += Ired;
        _ray.m_color[1] += Igreen;
        _ray.m_color[2] += Iblue;
        if(_ray.m_color[0]>1) _ray.m_color[0] = 1;
        if(_ray.m_color[1]>1) _ray.m_color[1] = 1;
        if(_ray.m_color[2]>1) _ray.m_color[2] = 1;
        _ray.m_isDone = true;
    }
    else{
        if(_ray.m_iID == -1){
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
        return;
    }
}


