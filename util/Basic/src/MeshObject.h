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
#include <list>
#include <vector>


class Triangle;
class MeshObject{
public:
    MeshObject(Attr_MeshObject _attr);
    ~MeshObject();
    void print();
    void changeMaterial(Attr_Material _m);
private:
    Attr_MeshObject m_Attribute;
};


#endif /* MESHOBJECT_H */

