/*
 * attribute.h
 *
 *  Created on: Mar 25, 2016
 *      Author: c5lizhua
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_
#include <string>
#include "Face.h"
struct Attr_Material{
    // TODO: Add Material Propteries
	std::string m_MaterialName;
	Vector4f m_DefuseColor;
	Vector4f m_AmbientColor;
	Vector4f m_SpecularColor;
	float m_fSpecularWeight;
	float m_fRefractiveIndex;
};

struct Attr_Lighting{
	// TODO: Add Lightning Properties
	Vector4f m_DefuseColor;
	Vector4f m_AmbientColor;
	Vector4f m_SpecularColor;
	Vector4f m_LightPosition;
};

struct Attr_MeshObject{
	Vector4f* m_Normallist;
	Vector4f* m_Vertexlist;
	Vector4f* m_Texturelist;
	Triangle* m_Trianglelist;
	int m_iNormalCount;
	int m_iVertexCount;
	int m_iTextureCount;
	int m_iTriangleCount;
	Attr_Material m_ObjectMaterial;
};

struct Attr_Intersection{
	Vector4f m_Normal;
	Vector4f m_IntersectionPoint;
	Attr_Material m_Material;
	float m_distance; // t
};

struct Attr_ViewFrustrum{
	Vector4f m_ViewPoint;
	Vector4f m_ViewDirection;
	Vector4f m_ViewUpDirection;
	float m_fFieldOfView;
};

struct Attr_Render{
	int m_iScreenWidth;
	int m_iScreenHeight;
	Attr_ViewFrustrum m_ViewFrustrum;
	std::string m_sFileName;
};

struct Attr_PixelBuffer{
	int m_iWidth;
	int m_iHeight;
	unsigned char* m_Rbuffer;
	unsigned char* m_Gbuffer;
	unsigned char* m_Bbuffer;
};
#endif /* ATTRIBUTE_H_ */
