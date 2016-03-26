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
};

struct Attr_Lighting{
	// TODO: Add Lightning Properties
};

struct Attr_MeshObject{
	Vector4f* m_Normallist;
	Vector4f* m_Vertexlist;
	Vector4f* m_Texturelist;
	Triangle* m_Trianglelist;
	int m_iNormalCount;
	int m_iVertexCount;
	int m_iTextureCount;
	int m_iFaceCount;
};

struct Attr_Intersection{
	Vector4f m_Normal;
	Vector4f m_IntersectionPoint;
	Attr_Material* m_Material;
};

#endif /* ATTRIBUTE_H_ */
