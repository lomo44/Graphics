/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PolygonPlane.cpp
 * Author: lizhuan1
 * 
 * Created on April 5, 2016, 7:19 PM
 */

#include "PolygonPlane.h"
#include "Face.h"
#include <assert.h>
PolygonPlane::PolygonPlane() {
    ;
}

PolygonPlane::PolygonPlane(const PolygonPlane& orig) {
    ;
}

PolygonPlane::~PolygonPlane() {
    ;
}

void PolygonPlane::setBound(const Vector4f& _normal, Vector4f* _list, int _vertexcount){
    m_Normal = _normal;
    if(_list != NULL){
        assert(_vertexcount >= 3);     
        m_NumOfBoundingPoint = _vertexcount;
        m_pBoundingPoint = _list;
        m_fd =  m_Normal.dot(_list[0]); 
    }

}

Attr_Intersection* PolygonPlane::isIntersect(const Line& _l){
    float t = (m_fd - m_Normal.dot(_l.m_StartPoint))/m_Normal.dot(_l.m_Direction);
    Vector4f intersect_point = _l.getPoint(t);
    int i;
    float m1,m2;
    float anglesum=0;
    Vector4f p1,p2;
    bool isinside = false;
    if(!(t < 0)){
            if(m_NumOfBoundingPoint == 0){
            // infinite bounding plane
            isinside = true;
        }
        else{
            // polygon is bound by something
            for (i=0;i<m_NumOfBoundingPoint;i++) {
                p1[0] = m_pBoundingPoint[i][0] - intersect_point[0];
                p1[1] = m_pBoundingPoint[i][1] - intersect_point[1];
                p1[2] = m_pBoundingPoint[i][2] - intersect_point[2];

                p2[0] = m_pBoundingPoint[(i+1)%m_NumOfBoundingPoint][0] - intersect_point[0];
                p2[1] = m_pBoundingPoint[(i+1)%m_NumOfBoundingPoint][1] - intersect_point[1];
                p2[2] = m_pBoundingPoint[(i+1)%m_NumOfBoundingPoint][2] - intersect_point[2];

                m1 = p1.magnitude(); 
                m2 = p2.magnitude();
                if (m1*m2 <= 0.00001){
                    isinside = true;
                }
                else
                     anglesum += acos(p1.dot(p2)/(m1*m2));
             }
            if(std::fabs(anglesum - 2 * M_PI) < 0.00001){
                isinside = true;

            }
        }
        if(isinside){
            Attr_Intersection* ret = new Attr_Intersection();
            ret->m_InterpolatedNormal = m_Normal;
            ret->m_PlanarNormal = m_Normal;
            ret->m_IntersectionPoint = intersect_point;
            ret->m_Material = m_MaterialAttr;
            ret->m_distance = t;
            ret->m_fIntersectionAngle = 0;
            return ret;
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
    
}