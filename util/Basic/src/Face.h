#include "Vector.h"
#include "Vertex.h"
#include <vector>
#include <string>
#ifndef FACE_H
#define FACE_H
class Face{
public:
    Face(){};
    ~Face(){};
    int m_iShadingGroup;
    Vector4i m_V1;
    Vector4i m_V2;
    Vector4i m_V3;
};

#endif
