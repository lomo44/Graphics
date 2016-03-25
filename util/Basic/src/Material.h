/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Material.h
 * Author: john
 *
 * Created on March 23, 2016, 8:55 PM
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "Attribute.h"


class Material{
public:
    Material();
    Material(std::string _name, Attr_Material _attr);
    ~Material();
private:
    Attr_Material m_aMaterialAttribute;
    std::string m_sMaterialName;
};

#endif /* MATERIAL_H */

