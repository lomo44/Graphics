#include "Vector.h"
#include "Vertex.h"
#include <vector>
#include <string>
#include <iostream>
#ifndef FACE_H
#define FACE_H

class Line{
public:
	Line(){
		m_StartPoint[3] = 1;
	}
	~Line(){;}
	Vector4f getPoint(float _t) const{
        Vector4f ret = m_StartPoint + m_Direction * _t;
        ret[3] = 1;
		return ret;
	}
	Vector4f m_StartPoint;
	Vector4f m_Direction;
};

class Triangle{
public:
    Triangle(){};
    ~Triangle(){};
    void print(){
    	m_V1.Print();
    	m_V2.Print();
    	m_V3.Print();
    }
    int m_iShadingGroup;
    Vector4i m_V1;		// coord/texture/normal
    Vector4i m_V2;
    Vector4i m_V3;
    inline static Vector4f toBaryCentric(const Vector4f& _a,
    		const Vector4f& _b, const Vector4f& _c,
    		const Vector4f& _p){
    	//std::cout<<"Checking Bary"<<std::endl;
    	Vector4f v0 = _b - _a;
    	Vector4f v1 = _c - _a;
    	Vector4f v2 = _p - _a;
    	Vector4f ret;
    	float d00 = v0.dot(v0);
    	float d01 = v0.dot(v1);
    	float d11 = v1.dot(v1);
    	float d20 = v2.dot(v0);
    	float d21 = v2.dot(v1);
    	float denome = d00 * d11 - d01 * d01;
    	ret[0] = (d11 * d20 - d00 * d21) / denome;
    	ret[1] = (d00 * d21 - d01 * d20) / denome;
    	ret[2] = 1- ret[0] - ret[1];
    	return ret;

    }
    inline static float getSurfaceIntersect(const Vector4f& _a,
    		const Vector4f& _b, const Vector4f& _c,
    		const Line& L){
    	//std::cout<<"Checking Intersection"<<std::endl;
        /*std::cout<<"A: ";
    	_a.Print();
        std::cout<<" B: ";
    	_b.Print();
        std::cout<<" C: ";
    	_c.Print();
        std::cout<<std::endl;*/
        /*std::cout<<"StartFrom: " <<std::endl;
         L.m_StartPoint.Print();
        std::cout<< "Direction: "<<std::endl;
         L.m_Direction.Print();
        std::cout<<std::endl;*/
    	Vector4f v0 = _a-_b;
    	//v0.Print();
    	Vector4f v1 = _c-_a;
    	//v1.Print();
    	Vector4f Norm = v0.cross(v1);
    	Norm.Normalize();
    	//Norm.Print();
    	float d = Norm.dot(_a);
    	float t = (d - Norm.dot(L.m_StartPoint))/Norm.dot(L.m_Direction);
    	//L.m_Direction.Print();
    	//std::cout<<t<<std::endl;
    	return t;
    }
    inline static bool isIntersect(const Vector4f& _barycorrd){
    	if((_barycorrd[0] >= 0) && (_barycorrd[1] >= 0) && (_barycorrd[2]>=0) &&
    			(_barycorrd[0] + _barycorrd[1] + _barycorrd[2] <1)){
    		return true;
    	}
    	else{
    		return false;
    	}
    }
    inline static Vector4f Interpolate_Barycentric(const Vector4f& _a,
    		const Vector4f& _b, const Vector4f& _c,
    		const Vector4f& _barry){
        //std::cout<<"wow"<<std::endl;
        Vector4f ret = _a * _barry[0] + _b * _barry[1] + _c * _barry[2];
        ret.Normalize();
    	return ret;
        //std::cout<<"wow"<<std::endl;
    }
};

#endif
