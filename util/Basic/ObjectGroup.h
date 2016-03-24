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
#include "Material.h"
#include "Face.h"

class ObjectGroup{
public:
    ObjectGroup(){;}
    ~ObjectGroup(){;}
    std::string m_sGroupName;
    Material m_GroupMaterial;
    void addFace(Face _f){
        m_Facelist.push_back(_f);
    }
private:
    std::vector<Face> m_Facelist;
};


#endif /* OBJECTGROUP_H */

