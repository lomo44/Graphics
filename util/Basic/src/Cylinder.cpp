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
#include <cmath>
#include <limits>

Cylinder::Cylinder(float _radius, float _height) {
    m_fRadius = _radius;
    m_fHeight = _height;
    m_pTopLid = new PolygonPlane();
    m_pTopLid->setAsCircle(Vector4f(0,1,0),Vector4f(0,_height,0,1),_radius);
    m_pBottomLid = new PolygonPlane();
    m_pBottomLid->setAsCircle(Vector4f(0,-1,0),Vector4f(0,0.0,0,1),_radius);
}

Cylinder::Cylinder(const Cylinder& orig) {
}

Cylinder::~Cylinder() {
}

Attr_Intersection* Cylinder::isIntersect(const Line& _l){
    Line raydir = _l;
    raydir.m_Direction =   m_Transform * _l.m_Direction;
	raydir.m_StartPoint =  m_Transform * _l.m_StartPoint;
    int intersecting_location = -2; // 0->body, -1-> bot lid, 1-> top lid
    // solving the quadratic formula
    float ret_t = std::numeric_limits<float>::max();
    Vector4f ret_intesect;
    float a = raydir.m_Direction[0] * raydir.m_Direction[0] + raydir.m_Direction[2] * raydir.m_Direction[2];
    float b = 2.0 * (raydir.m_StartPoint[0] * raydir.m_Direction[0] + raydir.m_StartPoint[2]*raydir.m_Direction[2]);
    float c = raydir.m_StartPoint[0] * raydir.m_StartPoint[0] + raydir.m_StartPoint[2]*raydir.m_StartPoint[2] - this->m_fRadius *
        this->m_fRadius;
    float b24ac = b * b - 4.0 * a * c;
    if(b24ac < 0.0){
        return NULL;
    }
    else{
        if(std::fabs(b24ac) < 0.0001){
            float t = -b / 2.0 / a;
            if(!(t < 0) && t < ret_t)
                ret_t = t;
        }
        else{
            float t1 = (-b + sqrt(b24ac)) / 2.0 / a;
            float t2 = (-b - sqrt(b24ac)) / 2.0 / a;
            if(!(t1 < 0) && !(raydir.getPoint(t1)[1] <0.0) && raydir.getPoint(t1)[1] < (float)m_fHeight){
                if(t1 < ret_t){
                    ret_t = t1;
                    intersecting_location = 0;
                }
            }
            if(!(t2 < 0) && !(raydir.getPoint(t2)[1] <0.0) && raydir.getPoint(t2)[1] < (float)m_fHeight){
                if(t2 < ret_t){
                    ret_t = t2;
                    intersecting_location = 0;
                } 
            }
        }
        intersecting_location = 0;
    }
    Attr_Intersection* toplid_i = m_pTopLid->isIntersect(raydir);
    if(toplid_i!=NULL){
        if(!(toplid_i->m_distance<0) && toplid_i->m_distance < ret_t){
            ret_t = toplid_i->m_distance;
            intersecting_location = 1;
        }       
    }
    Attr_Intersection* botlid_i = m_pBottomLid->isIntersect(raydir);
    if(botlid_i!=NULL){
        if(!(botlid_i->m_distance<0) && botlid_i->m_distance < ret_t){
            ret_t = botlid_i->m_distance;
            intersecting_location = -1;
        }       
    }
    /** assume unify material (if non uniform materials are need to for toplid
     * and bot lid, modify each one respectively ) **/
    
    if(ret_t == std::numeric_limits<float>::max()){
        return NULL;
    }
    else{
        Vector4f norm;  
        ret_intesect = raydir.getPoint(ret_t);
        if(ret_intesect[1] < 0.0 || ret_intesect[1] > m_fHeight)
            return NULL;
        if(intersecting_location == 0){
            norm[0] = ret_intesect[0];
            norm[2] = ret_intesect[2];
        }
        else if(intersecting_location == -1){
            norm = m_pBottomLid->m_Normal;
        }
        else if(intersecting_location == 1){
            norm = m_pTopLid->m_Normal;
        }
        Attr_Intersection* ret = new Attr_Intersection();
        ret->m_InterpolatedNormal = (m_invTransform.Transpose()) * norm;
        ret->m_IntersectionPoint = m_invTransform * ret_intesect;
        ret->m_Material = this->m_MaterialAttr;
        ret->m_PlanarNormal = ret->m_InterpolatedNormal;
        ret->m_distance = ret_t;
        return ret;
    }
}
