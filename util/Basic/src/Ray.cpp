/*
 * Ray.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */

#include "Ray.h"
#include "Face.h"
#include "Vector.h"
Ray::Ray(Ray* _prior,Line _line, int _time) {
	// TODO Auto-generated constructor stub
	this->m_RayLine = _line;
	m_iRecursiveTime = _time;
	m_color[0] = 1;
	m_color[1] = 1;
	m_color[2] = 1;
	m_color[3] = 1;
	this->m_isDone = false;
	this->m_pPriorRay = _prior;
	this->m_pReflectedRay = NULL;
	this->m_pRefractedRay = NULL;
	this->m_pIntersectionProperties = NULL;
	this->m_iID = -1;
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

Ray* Ray::reflect(const Vector4f& norm){
	if(m_pIntersectionProperties != NULL && m_iRecursiveTime >= 1){
		float scale = 2 * this->m_pIntersectionProperties->m_Normal.dot(this->m_RayLine.m_Direction);
		Vector4f dir = this->m_RayLine.m_Direction - this->m_pIntersectionProperties->m_Normal * scale;
		dir.Normalize();
		Line ref_dir;
		ref_dir.m_Direction = dir;
		ref_dir.m_StartPoint = this->m_pIntersectionProperties->m_IntersectionPoint;
		Ray* newray = new Ray(this, ref_dir , this->m_iRecursiveTime-1);
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
	if(m_pIntersectionProperties != NULL && m_iRecursiveTime >= 1){
		float ni = 0;
		float nt = 0;
		if(_from == NULL){
			// From Environment To Material;
			ni = 1.0;
			nt = m_pIntersectionProperties->m_Material.m_fRefractiveIndex;

		}
		else{
			// From Material To Environment;
			ni = m_pIntersectionProperties->m_Material.m_fRefractiveIndex;
			nt = 1.0;
		}
		Vector4f vertical = this->m_pIntersectionProperties->m_Normal.dot(this->m_RayLine.m_Direction) *
				this->m_pIntersectionProperties->m_Normal;
		Vector4f horizontal = ni/nt * (this->m_RayLine.m_Direction - vertical);
		Vector4f dir = vertical + horizontal;
		dir.Normalize();
		Line ref_dir;
		ref_dir.m_Direction = dir;
		ref_dir.m_StartPoint = this->m_pIntersectionProperties->m_IntersectionPoint;
		Ray* newray = new Ray(this,ref_dir,this->m_iRecursiveTime-1);
		newray->m_iID = -1;
		return newray;
	}
	else{
		m_isDone = true;
		return NULL;
	}
}
