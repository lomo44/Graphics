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
};

#endif
