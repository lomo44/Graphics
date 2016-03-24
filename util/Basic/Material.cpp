/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Material.h"

Material::Material(std::string _name, Attr_Material _attr){
    m_aMaterialAttribute = _attr;
    m_sMaterialName = _name;
}

Material::~Material(){
    
}