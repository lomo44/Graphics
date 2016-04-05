/*
 * Ray.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */

#include "Ray.h"
#include "Face.h"
#include "Vector.h"
#include <assert.h>
Ray::Ray(Ray* _prior,Line _line, int _time) {
	// TODO Auto-generated constructor stub
	this->m_RayLine = _line;
	m_iRecursiveTime = _time;
	m_color[0] = 0;
	m_color[1] = 0;
	m_color[2] = 0;
	m_color[3] = -1; // will change to 1 if it hit something;
	this->m_isDone = false;
	this->m_pPriorRay = _prior;
	this->m_pReflectedRay = NULL;
	this->m_pRefractedRay = NULL;
	this->m_pIntersectionProperties = NULL;
	this->m_iID = -1;
	this->m_fLightIntensity = 1.0;
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}

bool Ray::checkDone(){
	if(m_isDone){
		return true;
	}
	else{
		if(m_pReflectedRay!=NULL && !m_pReflectedRay->checkDone()){
			return false;
		}
		else if(m_pRefractedRay!=NULL && !m_pRefractedRay->checkDone()){
			return false;
		}
		else if(this->m_iRecursiveTime>0){
			return false;
		}
		else{
			m_isDone = true;
			return true;
		}
	}
}
float Ray::CalculateReflectance(const Vector4f& normal,
			const Vector4f& incident, Attr_Material* from, Attr_Material* to){
	float n1,n2;
	if(from == NULL)
		n1 = 1;
	if(to == NULL)
		n2 = 1;
	if(to->m_eMaterialType == eMaterialType_opague)
		return 1.0;
	float n = n1 / n2;
	float cosI = -(incident.dot(normal));
	float sint2 = n * n* (1.0 - cosI * cosI);
	if(sint2 > 1.0) return 1.0; // TIR
	float cosT = sqrt(1.0 - sint2);
	float rorth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	float rpar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
	return (rorth * rorth + rpar * rpar) / 2;
}

Ray* Ray::reflect(const Vector4f& norm){
    assert(norm[3]==0);
	if(m_pIntersectionProperties != NULL && m_iRecursiveTime > 1){
        //std::cout<<"reflect"<<std::endl;
		float reflectance = Ray::CalculateReflectance(norm,this->m_RayLine.m_Direction,NULL,
				this->m_pIntersectionProperties->m_Material);
		Vector4f dir = this->m_RayLine.m_Direction - (norm * 2.0 * 
                norm.dot(this->m_RayLine.m_Direction));
		Line ref_dir;
		ref_dir.m_Direction = dir;
		ref_dir.m_StartPoint = this->m_pIntersectionProperties->m_IntersectionPoint;
		Ray* newray = new Ray(this, ref_dir , this->m_iRecursiveTime-1);
		newray->m_fLightIntensity = reflectance;
		newray->m_iID = -1;
		this->m_pReflectedRay = newray;
		return newray;
	}
	else{
		m_isDone = true;
		return NULL;
	}
}

Ray* Ray::refract(const Vector4f& norm, Attr_Material* _from){
	if(m_pIntersectionProperties != NULL && m_iRecursiveTime > 1){
		float ni = 0.0;
		float nt = 0.0;
		if(_from == NULL){
			// From Environment To Material;
			ni = 1.0;
			nt = m_pIntersectionProperties->m_Material->m_fRefractiveIndex;

		}
		else{
			// From Material To Environment;
			ni = m_pIntersectionProperties->m_Material->m_fRefractiveIndex;
			nt = 1.0;
		}
		if(m_pReflectedRay->m_fLightIntensity >= 1.0)
			return NULL;
		Vector4f vertical = this->m_pIntersectionProperties->m_InterpolatedNormal.dot(this->m_RayLine.m_Direction) *
				this->m_pIntersectionProperties->m_InterpolatedNormal;
		Vector4f horizontal = ni/nt * (this->m_RayLine.m_Direction - vertical);
		Vector4f dir = vertical + horizontal;
		dir.Normalize();
		Line ref_dir;
		ref_dir.m_Direction = dir;
		ref_dir.m_StartPoint = this->m_pIntersectionProperties->m_IntersectionPoint;
		Ray* newray = new Ray(this,ref_dir,this->m_iRecursiveTime-1);
        newray->m_color = this->m_color;
		newray->m_iID = -1;
        this->m_pRefractedRay = newray;
		return newray;

	}
	else{
		m_isDone = true;
		return NULL;
	}
}

void Ray::RecursiveCollapse(Ray* ray){   
	if(ray->m_pReflectedRay != NULL || ray->m_pReflectedRay != NULL){
		if(m_pReflectedRay != NULL){
            //std::cout<<ray->m_iID<<std::endl;
            //std::cout<<m_pReflectedRay->m_color[0]<<" "<<m_pReflectedRay->m_color[1]<<" "<<m_pReflectedRay->m_color[2]<<std::endl;
			RecursiveCollapse(m_pReflectedRay);
			//m_color *= m_pReflectedRay->m_fLightIntensity * m_pReflectedRay->m_color;
            if(m_pReflectedRay->hasIntersect()){
                m_color[0] = 1.0;
                m_color[1] = 1.0;
                m_color[2] = 1.0;
            }
            else{
                //std::cout<<"no"<<std::endl;
                m_color[0] = 0.0;
                m_color[1] = 0.0;
                m_color[2] = 1.0;
            }
			delete m_pReflectedRay;
		}
		if(m_pRefractedRay != NULL){
			RecursiveCollapse(m_pRefractedRay);
			m_color *= m_pRefractedRay->m_fLightIntensity * m_pRefractedRay->m_color;
			delete m_pRefractedRay;
		}
	}
}
