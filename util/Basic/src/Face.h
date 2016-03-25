#include "Vector.h"
#include "Vertex.h"

#ifndef FACE_H
#define FACE_H
class Face{
public:
    Face(){};
    ~Face(){};
    int m_iGroupNumber;
    int m_iShadingGroup;
    void addVertex(Vertexi _v){
        m_Vertexlist.push_back(_v);
    }
private:
    std::vector<Vertexi> m_Vertexlist;
};

#endif