/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ObjectGroup.h"
#include "Material.h"
#include "Face.h"

void ObjectGroup::addFace(Face _f){
    this->m_Facelist.push_back(_f);
}