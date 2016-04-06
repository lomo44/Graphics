/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cylinder.cpp
 * Author: lizhuan1
 * 
 * Created on April 5, 2016, 9:10 PM
 */

#include "Cylinder.h"
#include "PolygonPlane.h"
Cylinder::Cylinder(float _radius, float _height, unsigned int _sample) {
    m_iNumOfSample = _sample;
    m_fRadius = _radius;
    m_fHeight = _height;
}

Cylinder::Cylinder(const Cylinder& orig) {
}

Cylinder::~Cylinder() {
}

Attr_Intersection* Cylinder::isIntersect(const Line& _l){
    Line raydir = _l;
    raydir.m_Direction =   m_Transform * _l.m_Direction;
	raydir.m_StartPoint =  m_Transform * _l.m_StartPoint;    
}
