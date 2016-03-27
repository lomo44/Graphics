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
	~Line();
	Vector4f getPoint(float _t) const{
		return m_StartPoint + m_Direction * _t;
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
    	Vector4f v0 = _a-_b;
    	Vector4f v1 = _c-_a;
    	Vector4f Norm = v0.cross(v1);
    	float t = - Norm.dot(L.m_StartPoint)/Norm.dot(L.m_Direction);
    	return t;
    }
    inline static bool isIntersect(const Vector4f& _barycorrd){
    	if(_barycorrd[0] >= 0 && _barycorrd[1] >= 0 && _barycorrd[2]>=0 &&
    			_barycorrd[0] + _barycorrd[1] + _barycorrd[2] <1){
    		return true;
    	}
    	else{
    		return false;
    	}
    }
    inline static Vector4f Interpolate_Barycentric(const Vector4f& _a,
    		const Vector4f& _b, const Vector4f& _c,
    		const Vector4f& _barry){
    	return _a * _barry[0] + _b * _barry[1] + _c * _barry[2];
    }
};

#endif
