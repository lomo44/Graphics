/*
 * attribute.h
 *
 *  Created on: Mar 25, 2016
 *      Author: c5lizhua
 */

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_
#include <cstring>
#include <assert.h>
#include "Face.h"
#include "bmp_io.h"


enum eMaterialType{
	eMaterialType_opague,
	eMaterialType_transparent,
    eMaterialType_glossy,
    eMaterialType_rough
};



struct Attr_PixelBuffer{
	long unsigned int m_iWidth;
	long int m_iHeight;
	unsigned char* m_Rbuffer;
	unsigned char* m_Gbuffer;
	unsigned char* m_Bbuffer;
};

typedef Attr_PixelBuffer Attr_TextureBuffer;

class Material{
public:
	Material(std::string name, Vector4f ambient, Vector4f diffuse, Vector4f specular, float exp,
			float refractiveIndex, eMaterialType _type) :
			m_MaterialName(name),m_AmbientColor(ambient), m_DefuseColor(diffuse), m_SpecularColor(specular),
			m_fSpecularWeight(exp),m_fRefractiveIndex(refractiveIndex),m_eMaterialType(_type),m_pTexturePixelBuffer(NULL),
            m_bHasTexture(false){}
public:
    inline void loadTexture(std::string filename){
        char* name = new char[filename.length()+1];
        strcpy(name,filename.c_str());
        long unsigned int* width = new long unsigned int();
        long int* height = new long int();

        unsigned char** Rbuffer = new unsigned char*();
        unsigned char** Gbuffer = new unsigned char*();
        unsigned char** Bbuffer = new unsigned char*();
        
        /*unsigned char** Rbuffer = NULL;
        unsigned char** Gbuffer = NULL;
        unsigned char** Bbuffer = NULL;*/

        bool error = bmp_read(name,width,height,Rbuffer,Gbuffer,Bbuffer);
        if(error){
            std::cout<<"Texture Open Fail"<<std::endl;
        }
        else{
            std::cout<<"Texture open success"<<std::endl;
            Attr_TextureBuffer* texture = new Attr_TextureBuffer();
            texture->m_Bbuffer = *Bbuffer;
            texture->m_Gbuffer = *Gbuffer;
            texture->m_Rbuffer = *Rbuffer;
            texture->m_iHeight = *height;
            texture->m_iWidth = *width;
            m_pTexturePixelBuffer = texture;
            m_bHasTexture = true;
        }
    }
    Vector4f getTextureColor(float _u, float v){
        //std::cout<<_u<<std::endl;
        unsigned int x = (unsigned int)(_u * m_pTexturePixelBuffer->m_iWidth);
        unsigned int y = (unsigned int)(v * m_pTexturePixelBuffer->m_iHeight);
        unsigned int pixel_num = y * m_pTexturePixelBuffer->m_iWidth + x;
        float R = m_pTexturePixelBuffer->m_Rbuffer[pixel_num] / 255.0;
        float G = m_pTexturePixelBuffer->m_Gbuffer[pixel_num] / 255.0;
        float B = m_pTexturePixelBuffer->m_Bbuffer[pixel_num] / 255.0;
        Vector4f ret;
        ret[0] = R;
        ret[1] = G;
        ret[2] = B;
        //ret.Print();
        return ret;
    }
    std::string m_MaterialName;
	Vector4f m_AmbientColor;
	Vector4f m_DefuseColor;
	Vector4f m_SpecularColor;
	double m_fSpecularWeight;
	double m_fRefractiveIndex;
    int m_iGlossySamepleCount;
    bool m_bHasTexture;
    Attr_TextureBuffer* m_pTexturePixelBuffer;
	eMaterialType m_eMaterialType;
};

struct Attr_PointLight{
	// TODO: Add Lightning Properties
	Vector4f m_DefuseColor;
	Vector4f m_AmbientColor;
	Vector4f m_SpecularColor;
	Vector4f m_LightPosition;
};

struct Attr_AreaLight{
    Vector4f m_DefuseColor;
	Vector4f m_AmbientColor;
	Vector4f m_SpecularColor;
	Vector4f m_LightPosition;
    Vector4f m_Normal;
    Vector4f m_Up;
    float m_fLength;
    unsigned int m_iSampleSize;
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
	Material* m_ObjectMaterial;
};

struct Attr_Intersection{
	Vector4f m_InterpolatedNormal;
    Vector4f m_PlanarNormal;
	Vector4f m_IntersectionPoint;
    Vector4f m_IntersectionColor;
	float m_fIntersectionAngle;
	Material* m_Material;
	double m_distance; // t
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
	int m_iRayTracingDepth;
	int m_iAntiAliasingScale;
    bool m_bShadowEnable;
    bool m_bEnvironmentAmbientEnable;
	Attr_ViewFrustrum* m_ViewFrustrum;
	std::string m_sFileName;
    Vector4f m_EnvironmentAmbient;
};

//class Color {
//public:
//    float R;
//    float G;
//    float B;
//    
//    Color()
//    { R=0.0;G=0.0;B=0.0; }
//    
//    Color(float rr, float gg, float bb)
//    { R=rr;G=gg;B=bb; }
//    
//    Color& operator =(const Color& other)
//    {
//        R = other.R; G = other.G; B = other.B;
//        return *this;
//    }
//    
//    Color& operator =(const Vector4f& other)
//    {
//        R = other[0]; G = other[1]; B = other[2];
//        return *this;
//    }
//    
//    Color operator *(const Color& other)
//    {
//        return Color(R*other.R, G*other.G, B*other.B);
//    }
//};
//
//Color operator +(const Color& u, const Color& v)
//{
//    return Color(u.R+v.R, u.G+v.G, u.B+v.B);
//}
//
//Color operator *(double s, const Color& c)
//{
//    return Color(s*c.R, s*c.G, s*c.B);
//}
//
//
//class Point3D {
//public:
//    float a;
//    float b;
//    float c;
//    
//    Point3D () {
//        a=0.0;b=0.0;c=0.0;
//    };
//    
//    Point3D (float aa, float bb, float cc) {
//        a=aa;b=bb;c=cc;
//    };
//    
//    Point3D (float cc) {
//        a=0;b=0;c=cc;
//    };
//    
//    Point3D (Point3D wo, Point3D cao) {
//        a = wo.a*cao.a;
//        b = wo.b*cao.b;
//        c = wo.c*cao.c;
//    }
//    
//};

            
/*public:
    void loadtexture(std::string filename){
        
    }
    Vector4f getTextureColor(float _u, float v){
        std::cout<<_u<<std::endl;
        unsigned int x = (unsigned int)(_u * m_pTexturePixelBuffer->m_iWidth);
        unsigned int y = (unsigned int)(v * m_pTexturePixelBuffer->m_iHeight);
        unsigned int pixel_num = y * m_pTexturePixelBuffer->m_iWidth + x;
        //std::cout<<"wow"<<pixel_num<<std::endl;
        float R = m_pTexturePixelBuffer->m_Rbuffer[pixel_num] / 255;
        float G = m_pTexturePixelBuffer->m_Gbuffer[pixel_num] / 255;
        float B = m_pTexturePixelBuffer->m_Bbuffer[pixel_num] / 255;
        return Vector4f(R,G,B,0);
    }*/
#endif /* ATTRIBUTE_H_ */
