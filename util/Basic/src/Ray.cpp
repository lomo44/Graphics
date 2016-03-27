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
	this->m_isDone = false;
	this->m_pPriorRay = _prior;
	this->m_pReflectedRay = NULL;
	this->m_pRefractedRay = NULL;
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
			return true;
		}
	}
}
