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
    Material* gold = new Material("gold",Vector4f(0.3,0.3,0.3),
    		Vector4f(0.75164, 0.60648, 0.22648),Vector4f(0.628281, 0.555802, 0.366065),51.2,
    		0,eMaterialType_opague);
    
    
    Material* red_glossy = new Material("gold",Vector4f(0.1,0.3,0.3),
        Vector4f(0.75164, 0.5, 0.22648),Vector4f(0.328281, 0.6, 0.366065),51.2,
        0,eMaterialType_opague);
    red_glossy->m_iGlossySamepleCount = 20;
    
    Material* metal = new Material("metal",Vector4f(0.1,0.1,0.1),
            Vector4f(0.1529,0.1529,0.1529),Vector4f(0.6,0.66,0.6),20,0,eMaterialType_opague);
    out->changeMaterial(gold);
    
    Material* white_mirror = new Material("white_mirror", Vector4f(0.3,0.3,0.3),
            Vector4f(0.6,0.6,0.6),Vector4f(0.9,0.9,0.9),200,0,eMaterialType_glossy);
    white_mirror->m_iGlossySamepleCount = 20;
      
    Material* plain_wood = new Material("plane",Vector4f(0.0,0.0,0.0),
            Vector4f(0.0,0.0,0.0),Vector4f(0.0,0.0,0.0),10,0,eMaterialType_opague);
    //plain_wood->m_pTexturePixelBuffer = newtracer.LoadTexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/wood.bmp");
    plain_wood->loadTexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/green.bmp");
    //plain_wood->loadTexture("/home/john/Code/Graphics/texture/green.bmp");
    //plain_wood->m_pTexturePixelBuffer = newtracer.LoadTexture("/homes/l/lizhuan1/NetBeansProjects/Graphics/texture/wood.bmp");
    //plain_wood->m_bHasTexture = true;
    Attr_PointLight l1;
    l1.m_AmbientColor = Vector4f(0.9,0.9,0.9);
    l1.m_DefuseColor = Vector4f(0.9,0.9,0.9);
    l1.m_SpecularColor = Vector4f(0.9,0.9,0.9);
    l1.m_LightPosition = Vector4f(0,10,0,1);
    
    Attr_AreaLight* l2 = new Attr_AreaLight();
    l2->m_AmbientColor = Vector4f(0.9,0.9,0.9);
    l2->m_DefuseColor = Vector4f(0.9,0.9,0.9);
    l2->m_SpecularColor = Vector4f(0.9,0.9,0.9);
    l2->m_LightPosition = Vector4f(0,10,0,1);
    l2->m_Normal = Vector4f(0,-1,0);
    l2->m_Up = Vector4f(1,0,0);
    l2->m_fLength = 4.0;
    l2->m_iSampleSize = 6;
    
    Cylinder* newcylinder = new Cylinder(1.0,3);
    newcylinder->m_MaterialAttr = red_glossy;
    PointLight* newlight = new PointLight(l1);
    AreaLight* newlight2 = new AreaLight(l2);
    PolygonPlane* baseplane = new PolygonPlane;
    baseplane->setAsInfinitePlane(Vector4f(0,1,0),Vector4f(0,-0,001,0));
    baseplane->m_MaterialAttr = white_mirror;
    //out->rotate(eRotationalX,90);
    MeshObject* out2 = out->clone();
    out2->rotate(eRotationalY,90);
    out2->getTransform().print();
    out2->getInvTransform().print();
    out2->changeMaterial(plain_wood);
    
    
    //newtracer.addLight(newlight);
    newtracer.addLight(newlight2);
    //newtracer.addObject(out);
    //newtracer.addObject(out2);
    newtracer.addObject(baseplane);
    newtracer.addObject(newcylinder);
    
    
    Attr_Render* render = new Attr_Render();
    Attr_ViewFrustrum* view = new Attr_ViewFrustrum();
    view->m_ViewDirection = Vector4f(-4,-2,-4);
    view->m_ViewPoint = Vector4f(5,4,5,1);
    view->m_ViewUpDirection = Vector4f(0,1,0);
    view->m_fFieldOfView = 60;
    render->m_ViewFrustrum = view;
    render->m_iAntiAliasingScale = 1;
    render->m_iRayTracingDepth = 2;
    render->m_iScreenHeight = 600;
    render->m_iScreenWidth = 800;
    render->m_sFileName = "view3.bmp";
    render->m_bShadowEnable = true;
    render->m_bEnvironmentAmbientEnable = true;
    render->m_EnvironmentAmbient = Vector4f(0.1,0.1,0.1);
    newtracer.render(render);
    return 0;
}

