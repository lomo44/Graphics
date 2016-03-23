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
#include <vector>
class MeshObjectSet{
public:
    MeshObjectSet();
    ~MeshObjectSet();
    void setVertexlist(Vector4f* _list, int _count);
    void setNormallist(Vector4f* _list, int _count);
    void setTexturelist(Vector4f* _list, int _count);
    void setTrianglelist(Vector4v* _list, int _count);
private:
    Vector4f* m_pVertexlist;
    Vector4f* m_pNormallist;
    Vector4f* m_pTexturelist;
    Vector4v* m_iTrianglelist;
    int m_iVertexCount;
    int m_iNormalCount;
    int m_iTextureCount;
    int m_iTriangleCount;
};


#endif /* MESHOBJECT_H */

