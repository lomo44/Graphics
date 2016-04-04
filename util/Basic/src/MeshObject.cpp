/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MeshObject.h"
#include "Face.h"
#include "BoundingBox.h"
#include <limits>
#include <cmath>
MeshObject::MeshObject(Attr_MeshObject _attr){
	m_Attribute = _attr;
    Vector4f MaxXYZ = Vector4f(std::numeric_limits<float>::min(),
            std::numeric_limits<float>::min()
            ,std::numeric_limits<float>::min());
    Vector4f MinXYZ = Vector4f(std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max());
    for(unsigned int i = 0; i < m_Attribute.m_iVertexCount; i++){
        Vector4f _t = m_Attribute.m_Vertexlist[i];
        //std::cout<<_t[3]<<std::endl;
        for(unsigned int i = 0 ; i < 3;i++){
            if(_t[i] > MaxXYZ[i])
                MaxXYZ[i] = _t[i];
            if(_t[i] < MinXYZ[i])
                MinXYZ[i] = _t[i];
        }
        m_BoundingBox = new BoundingBox(MaxXYZ,MinXYZ);
    }
    m_BoundingBox->m_MaxXYZ.Print();
    m_BoundingBox->m_MinXYZ.Print();
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
	for(int i = 0; i < m_Attribute.m_iNormalCount;i++){
		m_Attribute.m_Normallist[i].Print();
	}
	for(int i = 0 ; i < m_Attribute.m_iTriangleCount;i++){
		m_Attribute.m_Trianglelist[i].print();
	}
}

void MeshObject::changeMaterial(Attr_Material* _m){
	m_Attribute.m_ObjectMaterial = _m;
}

Attr_Intersection* MeshObject::isIntersect(const Line& _l){
	//std::cout<<"Check Intersection MeshObject"<<std::endl;

	if(!this->m_BoundingBox->checkIntersect(_l))
		return NULL;
	Line temp = _l;
	temp.m_Direction =   m_Transform * temp.m_Direction;
	temp.m_StartPoint =  m_Transform * temp.m_StartPoint;
	float t = std::numeric_limits<float>::max();
	int triangle_index = -1;
	Vector4f _ret_bary;
	for(int i = 0; i < m_Attribute.m_iTriangleCount;i++){
		float _i = Triangle::getSurfaceIntersect(
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]-1],_l);
        //std::cout<<_i<<std::endl;
		if(!(_i< 0)){
			Vector4f _bary = Triangle::toBaryCentric(
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]-1],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]-1],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]-1],_l.getPoint(_i));
            //_bary.Print();
			if(Triangle::isIntersect(_bary)){
				if(_i < t){
					t = _i;
					triangle_index = i;
					_ret_bary = _bary;
				}
			}
		}
	}
	if(triangle_index == -1){
		//std::cout<<"No Intersection" <<std::endl;
		return NULL;
	}
	else{
		Attr_Intersection* ret = new Attr_Intersection();
		ret->m_IntersectionPoint = (m_invTransform) * _l.getPoint(t);
		ret->m_Material = this->m_Attribute.m_ObjectMaterial;
		Vector4f norm = Triangle::Interpolate_Barycentric(
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V1[2]-1],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V2[2]-1],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V3[2]-1],_ret_bary);
		ret->m_Normal = (m_invTransform.Transpose()) * norm;
		ret->m_Normal.Normalize();
		ret->m_fIntersectionAngle = acos(ret->m_Normal.dot(_l.m_Direction));
		ret->m_distance = t;
		return ret;
	}
}
