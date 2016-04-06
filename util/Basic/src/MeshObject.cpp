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
MeshObject::MeshObject(Attr_MeshObject& _attr){
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

void MeshObject::printMeshObjectInfo(){
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
        //_l.m_StartPoint.Print();
	Line temp = _l;
        //m_Transform.print();
	temp.m_Direction =   m_Transform * _l.m_Direction;
	temp.m_StartPoint =  m_Transform * _l.m_StartPoint;
        //m_Transform.print();
    if(!this->m_BoundingBox->isIntersect(temp))
    return NULL;
	float t = std::numeric_limits<float>::max();
	int triangle_index = -1;
	Vector4d _ret_bary;
	for(int i = 0; i < m_Attribute.m_iTriangleCount;i++){
		float _i = Triangle::getSurfaceIntersect(
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]-1],temp);
        //std::cout<<_i<<std::endl;
		if(!(_i< 0)){
			Vector4d _bary = Triangle::toBaryCentric(
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V1[0]-1],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V2[0]-1],
					m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[i].m_V3[0]-1],temp.getPoint(_i));
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
		ret->m_IntersectionPoint = (m_invTransform) * temp.getPoint(t);
		ret->m_Material = this->m_Attribute.m_ObjectMaterial;
        Vector4f _bbray = Vector4f((float)_ret_bary[0],(float)_ret_bary[1],(float)_ret_bary[2]);
		Vector4f norm = Triangle::Interpolate_Barycentric(
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V1[2]-1],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V2[2]-1],
				m_Attribute.m_Normallist[m_Attribute.m_Trianglelist[triangle_index].m_V3[2]-1],_bbray);
        norm.Normalize();
        /*if(m_Attribute.m_ObjectMaterial->m_bHasTexture && m_Attribute.m_iTextureCount > 0){
            Vector4f Texture = Triangle::Interpolate_Barycentric(
            m_Attribute.m_Texturelist[m_Attribute.m_Trianglelist[triangle_index].m_V1[1]-1],
            m_Attribute.m_Texturelist[m_Attribute.m_Trianglelist[triangle_index].m_V2[1]-1],
            m_Attribute.m_Texturelist[m_Attribute.m_Trianglelist[triangle_index].m_V3[1]-1],_bbray);
            ret->m_IntersectionColor = m_Attribute.m_ObjectMaterial->getTextureColor(Texture[0],Texture[1]);
        }*/
        Vector4f norm1 = Triangle::getPlanarNormal(
                m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[triangle_index].m_V1[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[triangle_index].m_V2[0]-1],
				m_Attribute.m_Vertexlist[m_Attribute.m_Trianglelist[triangle_index].m_V3[0]-1]);
        if(norm.dot(norm1) < 0)
            norm1 = -norm1;
		ret->m_InterpolatedNormal = (m_invTransform.Transpose()) * norm;
        assert(norm1[3] == 0);
        ret->m_PlanarNormal = (m_invTransform.Transpose()) *norm1;
        ret->m_PlanarNormal[3] = 0;
        assert(ret->m_PlanarNormal[3] == 0);
		ret->m_distance = t;
		return ret;
	}
}

MeshObject* MeshObject::clone(){
    MeshObject* newmesh = new MeshObject(this->m_Attribute);
    newmesh->m_Transform = this->m_Transform;
    newmesh->m_invTransform = this->m_invTransform;
    return newmesh;
}