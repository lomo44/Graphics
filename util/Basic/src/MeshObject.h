/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MeshObject.h
 * Author: john
 *
 * Created on March 22, 2016, 11:33 PM
 */

#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "Vector.h"
#include "Attribute.h"
#include "RenderObject.h"
#include <list>
#include <vector>


class Triangle;
class Line;
class MeshObject : public RenderObject{
public:
    MeshObject(Attr_MeshObject& _attr);
    ~MeshObject();
    void printMeshObjectInfo();
    void changeMaterial(Material* _m);
    MeshObject* clone();
    Attr_Intersection* isIntersect(const Line& _l);
private:
    Attr_MeshObject m_Attribute;
};


#endif /* MESHOBJECT_H */

