/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshObject.h"

void MeshObjectSet::setNormallist(Vector4f* _list, int _count){
    this->m_pNormallist = _list;
    this->m_iNormalCount = _count;
}
void MeshObjectSet::setVertexlist(Vector4f* _list, int _count){
    this->m_pVertexlist = _list;
    this->m_iVertexCount = _count;
}
void MeshObjectSet::setTexturelist(Vector4f* _list, int _count){
    this->m_pTexturelist = _list;
    this->m_iTextureCount = _count;
}
void MeshObjectSet::setTrianglelist(Vector4v* _list, int _count){
    this->m_iTrianglelist = _list;
    this->m_iTriangleCount = _count;
}