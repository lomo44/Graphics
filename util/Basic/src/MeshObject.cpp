/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshObject.h"
#include "Face.h"
#include <limits>
#include <cmath>
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
	for(int i = 0 ; i < m_Attribute.m_iTriangleCount;i++){
		m_Attribute.m_Trianglelist[i].print();
	}
}

void MeshObject::changeMaterial(Attr_Material _m){
	m_Attribute.m_ObjectMaterial = _m;
}

Attr_Intersection* MeshObject::isIntersect(const Line& _l){
	float t = std::numeric_limits<float>::max();
	int triangle_index = -1;
	Vector4f _ret_bary;
	for(int i = 0; i < m_Attribute.m_iTriangleCount;i++){
		float _i = Triangle::getSurfaceIntersect(
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]],_l);
		if(_i <= 0)
			break;
		else{
			Vector4f _bary = Triangle::toBaryCentric(
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]],_l.getPoint(_i));
			if(Triangle::isIntersect(_bary)){
				if(_i < t){
					_i = t;
					triangle_index = i;
					_ret_bary = _bary;
				}
			}
		}
	}
	if(triangle_index == -1){
		return NULL;
	}
	else{
		Attr_Intersection* ret = new Attr_Intersection();
		ret->m_IntersectionPoint = _l.getPoint(t);
		ret->m_Material = this->m_Attribute.m_ObjectMaterial;
		Vector4f norm = Triangle::Interpolate_Barycentric(
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V1[3]],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V2[3]],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V3[3]],_ret_bary);
		ret->m_Normal = norm;
		ret->m_Normal.Normalize();
		ret->m_fIntersectionAngle = acos(ret->m_Normal.dot(_l.m_Direction));
		ret->m_distance = t;
		return ret;
	}
}
