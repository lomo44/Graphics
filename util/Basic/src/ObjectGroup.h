/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ObjectGroup.h
 * Author: john
 *
 * Created on March 23, 2016, 8:54 PM
 */

#ifndef OBJECTGROUP_H
#define OBJECTGROUP_H
#include <string>
#include <vector>

class Material;
class Face;

class ObjectGroup{
public:
    ObjectGroup(){;}
    ~ObjectGroup(){;}
    Material* m_GroupMaterial;
    std::string m_sGroupName;
    void addFace(Face _f);
private:
    std::vector<Face> m_Facelist;
    
    
};


#endif /* OBJECTGROUP_H */

