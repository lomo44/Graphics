/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cylinder.h
 * Author: lizhuan1
 *
 * Created on April 5, 2016, 9:10 PM
 */

#ifndef CYLINDER_H
#define CYLINDER_H
#include "RenderObject.h"
#include "Attribute.h"

class PolygonPlane;
class Cylinder : public RenderObject {
public:
    Cylinder(float _radius, float _height);
    Cylinder(const Cylinder& orig);
    Attr_Intersection* isIntersect(const Line& _l);
    virtual ~Cylinder();
    Material* m_MaterialAttr;
private:
    float m_fRadius;
    float m_fHeight;
    unsigned int m_iNumOfSample;
    PolygonPlane* m_pTopLid;
    PolygonPlane* m_pBottomLid;
};

#endif /* CYLINDER_H */

