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
#include "PolygonPlane.h"
#include "Cylinder.h"
#include <string>
#include <string.h>
using namespace std;

int main(int argc, char** argv) {
    
    /*Vector4f tempv(0,0,1);
    Matrix4f temp;
    Matrix4f temp2;
    temp2.loadRotational(eRotationalX,90);
    (temp * temp2).print();
    temp = temp * temp2;
    temp.print();
    temp.Transpose().print();*/
    //fin.Print();
    //std::cout<<fin<<std::endl;
    RayTracer newtracer;
    OBJParser* newparser  = new OBJParser();
    //newparser->parsefile("/home/john/Code/Graphics/model/chair.obj");
    newparser->parsefile("/homes/l/lizhuan1/NetBeansProjects/Graphics/model/chair.obj");
    MeshObject* out = newparser->getOutputObject();
    //out->print();
    Attr_Material* gold = new Attr_Material("gold",Vector4f(0.3,0.3,0.3),
    		Vector4f(0.75164, 0.60648, 0.22648),Vector4f(0.628281, 0.555802, 0.366065),51.2,
    		0,eMaterialType_opague);
    gold->m_pTexturePixelBuffer = newtracer.LoadTexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/wood.bmp");
    Attr_Material* red_glossy = new Attr_Material("gold",Vector4f(0.3,0.1,0.3),
        Vector4f(0.75164, 0.1, 0.22648),Vector4f(0.628281, 0.1, 0.366065),51.2,
        0,eMaterialType_opague);
    red_glossy->m_iGlossySamepleCount = 20;
    
    Attr_Material* metal = new Attr_Material("metal",Vector4f(0.1,0.1,0.1),
            Vector4f(0.1529,0.1529,0.1529),Vector4f(0.6,0.66,0.6),20,0,eMaterialType_opague);
    out->changeMaterial(gold);
    
    Attr_Material* white_mirror = new Attr_Material("white_mirror", Vector4f(0.3,0.3,0.3),
            Vector4f(0.6,0.6,0.6),Vector4f(0.9,0.9,0.9),200,0,eMaterialType_glossy);
    white_mirror->m_iGlossySamepleCount = 20;
      
    Attr_Material* plain_wood = new Attr_Material("plane",Vector4f(0.3,0.3,0.3),
            Vector4f(0.9,0.9,0.9),Vector4f(0.9,0.9,0.9),10,0,eMaterialType_rough);
    //plain_wood->m_pTexturePixelBuffer = newtracer.LoadTexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/wood.bmp");
    //plain_wood->loadtexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/wood.bmp");
    
    Attr_PointLight l1;
    Cylinder* newcylinder = new Cylinder(1.0,3);
    newcylinder->m_MaterialAttr = red_glossy;
    l1.m_AmbientColor = Vector4f(0.9,0.9,0.9);
    l1.m_DefuseColor = Vector4f(0.9,0.9,0.9);
    l1.m_SpecularColor = Vector4f(0.9,0.9,0.9);
    l1.m_LightPosition = Vector4f(0,10,0,1);
    PointLight* newlight = new PointLight(l1);
    PolygonPlane* baseplane = new PolygonPlane;
    baseplane->setAsPolygon(Vector4f(0,1,0),NULL,0);
    baseplane->m_fd = -0.01;
    baseplane->m_MaterialAttr = white_mirror;
    //out->rotate(eRotationalX,90);
    MeshObject* out2 = out->clone();
    out2->rotate(eRotationalY,90);
    out2->getTransform().print();
    out2->getInvTransform().print();
    out2->changeMaterial(plain_wood);
    
    
    newtracer.addLight(newlight);
    newtracer.addObject(out);
    newtracer.addObject(out2);
    newtracer.addObject(baseplane);
    newtracer.addObject(newcylinder);
    
    
    Attr_Render* render = new Attr_Render();
    Attr_ViewFrustrum* view = new Attr_ViewFrustrum();
    view->m_ViewDirection = Vector4f(-1,-1,-1);
    view->m_ViewPoint = Vector4f(3.8,3.8,3.8,1);
    view->m_ViewUpDirection = Vector4f(0,1,0);
    view->m_fFieldOfView = 60;
    render->m_ViewFrustrum = view;
    render->m_iAntiAliasingScale = 1;
    render->m_iRayTracingDepth = 2;
    render->m_iScreenHeight = 200;
    render->m_iScreenWidth = 300;
    render->m_sFileName = "view2.bmp";
    render->m_bShadowEnable = true;
    render->m_bEnvironmentAmbientEnable = true;
    render->m_EnvironmentAmbient = Vector4f(0.1,0.1,0.1);
    newtracer.render(render);
    return 0;
}

