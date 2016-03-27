/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshObject.h"
#include "Face.h"
MeshObject::MeshObject(Attr_MeshObject _attr){
	m_Attribute = _attr;
}
MeshObject::~MeshObject(){
	delete m_Attribute.m_Normallist;
	delete m_Attribute.m_Texturelist;
	delete m_Attribute.m_Vertexlist;
	delete m_Attribute.m_Trianglelist;
}

void MeshObject::print(){
	for(int i = 0 ; i < m_Attribute.m_iVertexCount;i++){
		m_Attribute.m_Vertexlist[i].Print();
	}
	for(int i = 0 ; i < m_Attribute.m_iFaceCount;i++){
		m_Attribute.m_Trianglelist[i].print();
	}
}

void MeshObject::changeMaterial(Attr_Material _m){
	m_Attribute.m_ObjectMaterial = _m;
}
