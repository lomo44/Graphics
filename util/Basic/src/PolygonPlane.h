/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PolygonPlane.h
 * Author: lizhuan1
 *
 * Created on April 5, 2016, 7:19 PM
 */

#ifndef POLYGONPLANE_H
#define POLYGONPLANE_H
#include "Attribute.h"
#include "RenderObject.h"

class Line;
class PolygonPlane : public RenderObject{
public:
    PolygonPlane();
    PolygonPlane(const PolygonPlane& orig);
    void setBound(const Vector4f& _normal, Vector4f* _list, int _vertexcount);
    Attr_Intersection* isIntersect(const Line& _l);
    virtual ~PolygonPlane();
    Attr_Material* m_MaterialAttr;
    Vector4f m_Normal;
    float m_fd;
private:
    int m_NumOfBoundingPoint;
    Vector4f* m_pBoundingPoint;
};

#endif /* POLYGONPLANE_H */

