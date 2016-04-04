/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: john
 *
 * Created on March 10, 2016, 9:55 PM
 */
#include <iostream>
#include <cstdlib>
#include "Vector.h"
#include "Color.h"
#include "Matrix.h"
#include "OBJParser.h"
#include "MeshObject.h"
#include "RayTracer.h"
#include "Light.h"
#include <string>
#include <string.h>
using namespace std;

int main(int argc, char** argv) {
    //fin.Print();
    //std::cout<<fin<<std::endl;
    OBJParser* newparser  = new OBJParser();
    newparser->parsefile("/homes/l/lizhuan1/NetBeansProjects/Graphics/model/chair.obj");
    MeshObject* out = newparser->getOutputObject();
    //out->print();
    Attr_Material* gold = new Attr_Material("gold",Vector4f(0.3,0.3,0.3),
    		Vector4f(0.75164, 0.60648, 0.22648),Vector4f(0.628281, 0.555802, 0.366065),51.2,
    		0,eMaterialType_opague);
    out->changeMaterial(gold);
    Attr_Lighting l1;
    l1.m_AmbientColor = Vector4f(0.9,0.9,0.9);
    l1.m_DefuseColor = Vector4f(0.9,0.9,0.9);
    l1.m_SpecularColor = Vector4f(0.9,0.9,0.9);
    l1.m_LightPosition = Vector4f(0,0,20,1);
    PointLight* newlight = new PointLight(l1);
    RayTracer newtracer;
    newtracer.addLight(newlight);
    newtracer.addObject(out);
    Attr_Render* render = new Attr_Render();
    Attr_ViewFrustrum* view = new Attr_ViewFrustrum();
    view->m_ViewDirection = Vector4f(-1,-1,-1);
    view->m_ViewPoint = Vector4f(10,10,10,1);
    view->m_ViewUpDirection = Vector4f(0,1,0);
    view->m_fFieldOfView = 60;
    render->m_ViewFrustrum = view;
    render->m_iAntiAliasingScale = 1;
    render->m_iRayTracingDepth = 1;
    render->m_iScreenHeight = 800;
    render->m_iScreenWidth = 800;
    render->m_sFileName = "view2.bmp";
    newtracer.render(render);
    return 0;
}

