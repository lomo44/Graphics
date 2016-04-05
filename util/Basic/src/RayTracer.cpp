/*
 * RayTracer.cpp
 *
 *  Created on: Mar 28, 2016
 *      Author: c5lizhua
 */
#include <cstring>
#include "RayTracer.h"
#include "Matrix.h"
#include "Ray.h"
#include "RenderObject.h"
#include "Light.h"
#include "bmp_io.h"
#include <limits>
#include <assert.h>
#include <cmath>
RayTracer::RayTracer() {
	// TODO Auto-generated constructor stub
	m_pPixelBuffer = NULL;
	m_pRenderAttribute = NULL;
}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

void RayTracer::render(Attr_Render* _renderAttribute){
	m_pRenderAttribute = _renderAttribute;
	this->InitializePixelBuffer(_renderAttribute->m_iScreenWidth,
			_renderAttribute->m_iScreenHeight);
	InitializeViewToWorldMatrix();
	InitializeRayList();
    for(;m_RayBuffer.size()!=0;){
        std::cout<<"expanding"<<std::endl;
        ExpandRayTracingTree();
        ShadingRay();
    }   
	CollapseRayTracingTree();
	ExtractRayListToPixelBuffer();
	FlushPixelBuffer();
}

void RayTracer::ExpandRayTracingTree(){
	std::cout<<"Starting Expanding Ray Tracing Tree"<<std::endl;
    int inte = 0;
	for(;m_RayBuffer.size()!=0;){
		Ray* tempray = m_RayBuffer.front();
		m_RayBuffer.pop();
        //std::cout<<"check ray"<<std::endl;
        Attr_Intersection* intsec = CalculateIntersection(tempray->m_RayLine);
        if(intsec!=NULL){
            tempray->m_color[0] = 1.0;
            tempray->m_color[1] = 1.0;
            tempray->m_color[2] = 1.0;
            inte++;
            tempray->m_pIntersectionProperties = intsec;
            std::vector<Ray*> reflectray = tempray->reflect(intsec->m_PlanarNormal);
            Ray* refractray = tempray->refract(intsec->m_PlanarNormal,NULL);
            if(tempray->hasReflectedRay()){
                for(unsigned int i =0; i < reflectray.size();i++){
                    m_RayBuffer.push(reflectray[i]);
                }
            }
            if(refractray!=NULL)
                m_RayBuffer.push(refractray);
		}
        tempray->m_isDone = true;
        m_ShadingBuffer.push(tempray);
		//std::cout<<"\rCurrent Ray Remain: "<<m_RayBuffer.size();
	}
	std::cout<<"Expanding Complete, Number Of Ray Intersects: "<<inte<<std::endl;
}

Attr_Intersection* RayTracer::CalculateIntersection(const Line& _l){
	Attr_Intersection* _intersection = NULL;
	float t = std::numeric_limits<float>::max();
	for(unsigned int i = 0; i < m_ObjectList.size();i++){
		Attr_Intersection* temp = m_ObjectList[i]->isIntersect(_l);
		if(temp!=NULL){
			if(temp->m_distance < t){
				_intersection = temp;
				t = temp->m_distance;
			}
		}
	}
	return _intersection;
}

void RayTracer::InitializeRayList(){
	assert(m_pRenderAttribute!=NULL);
	double factor = (double(this->m_pRenderAttribute->m_iScreenHeight)/2)
			/tan(this->m_pRenderAttribute->m_ViewFrustrum->m_fFieldOfView*M_PI/360.0);
	int _height = this->m_pRenderAttribute->m_iScreenHeight;
	int _width = this->m_pRenderAttribute->m_iScreenWidth;
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			// Sets up ray origin and direction in view space,
			// image plane is at z = -1.
			Vector4f origin;
			Vector4f imagePlane;
            origin[3] = 1;
			/** ToDO:
			 * Need to implement anti-aliasing, random sampling.
			 */
			imagePlane[0] = (-double(_width)/2 + 0.5 + j)/factor;
			imagePlane[1] = (-double(_height)/2 + 0.5 + i)/factor;
			imagePlane[2] = -1;
			Vector4f _dir (imagePlane[0],imagePlane[1],imagePlane[2]);
			Vector4f dir = this->m_ViewToWorld * _dir;
			origin = this->m_ViewToWorld * origin;;
			Line newrayline;
			newrayline.m_Direction = dir;
			newrayline.m_StartPoint = origin;
			Ray* newray = new Ray(NULL,newrayline,this->m_pRenderAttribute->m_iRayTracingDepth);
            newray->m_iID = i*_height + j;
			m_RayBuffer.push(newray);
			m_RayList.push_back(newray);
		}
	}
	std::cout<<"Ray List Initialize, Total Number Of Ray: "<<m_RayBuffer.size()<<std::endl;
}

void RayTracer::InitializePixelBuffer(int _width, int _height){
	this->m_pPixelBuffer = new Attr_PixelBuffer();
	m_pPixelBuffer->m_iHeight = _height;
	m_pPixelBuffer->m_iWidth = _width;
	int numbyte = _height * _width * sizeof(unsigned char);
	m_pPixelBuffer->m_Bbuffer = new unsigned char[numbyte];
	m_pPixelBuffer->m_Gbuffer = new unsigned char[numbyte];
	m_pPixelBuffer->m_Rbuffer = new unsigned char[numbyte];
    for(unsigned int i = 0 ; i < _height; i++){
        for(unsigned int j = 0; j < _width; j++){
            m_pPixelBuffer->m_Rbuffer[i*_width + j] = 0;
            m_pPixelBuffer->m_Bbuffer[i*_width + j] = 0;
            m_pPixelBuffer->m_Gbuffer[i*_width + j] = 0;
        }
    }
}

void RayTracer::FlushPixelBuffer(){
	char* name = new char[m_pRenderAttribute->m_sFileName.length()+1];
	strcpy(name,m_pRenderAttribute->m_sFileName.c_str());
	bmp_write(name,
			m_pPixelBuffer->m_iWidth,m_pPixelBuffer->m_iHeight,
			m_pPixelBuffer->m_Rbuffer,
			m_pPixelBuffer->m_Gbuffer,
			m_pPixelBuffer->m_Bbuffer);
}

void RayTracer::InitializeViewToWorldMatrix(){
	assert(m_pRenderAttribute != NULL);
	Vector4f up = m_pRenderAttribute->m_ViewFrustrum->m_ViewUpDirection;
	Vector4f dir = m_pRenderAttribute->m_ViewFrustrum->m_ViewDirection;
	dir.Normalize();
	up = up - (up.dot(dir)) * dir;
	up.Normalize();

	Vector4f w = dir.cross(up);
	this->m_ViewToWorld[0] = w[0];
	this->m_ViewToWorld[4] = w[1];
	this->m_ViewToWorld[8] = w[2];
	this->m_ViewToWorld[1] = up[0];
	this->m_ViewToWorld[5] = up[1];
	this->m_ViewToWorld[9] = up[2];
	this->m_ViewToWorld[2] = -dir[0];
	this->m_ViewToWorld[6] = -dir[1];
	this->m_ViewToWorld[10] = -dir[2];
	this->m_ViewToWorld[3] = m_pRenderAttribute->m_ViewFrustrum->m_ViewPoint[0];
	this->m_ViewToWorld[7] = m_pRenderAttribute->m_ViewFrustrum->m_ViewPoint[1];
	this->m_ViewToWorld[11] = m_pRenderAttribute->m_ViewFrustrum->m_ViewPoint[2];
}

void RayTracer::ShadingRay(){
	//std::cout<<"Start Shading Ray"<<std::endl;
	for(;m_ShadingBuffer.size()!=0;){
		Ray* topray = m_ShadingBuffer.front();
		m_ShadingBuffer.pop();
		for(unsigned int i = 0; i< m_LightList.size();i++){
			m_LightList[i]->shade(*topray);
		}
	}
}

void RayTracer::CollapseRayTracingTree(){
	for(unsigned int i = 0; i < m_RayList.size();i++){
		m_RayList[i]->CollapseRayTracingTree();
	}
}

void RayTracer::ExtractRayListToPixelBuffer(){
	/** TODO:
	 * Modify this part to implement anti-aliasing
	 */
	unsigned int anti_aliasing_limit = 1;
	unsigned int anti_aliasing_counter = 0;
	unsigned int pixel_counter = 0;
	float R = 0.0;
	float G = 0.0;
	float B = 0.0;
	for(unsigned int i = 0; i < m_RayList.size();i++){
		anti_aliasing_counter++;
		R += m_RayList[i]->m_color[0];
		G += m_RayList[i]->m_color[1];
		B += m_RayList[i]->m_color[2];
		if(anti_aliasing_counter % anti_aliasing_limit == 0){
			R = R / anti_aliasing_limit * 255;
			G = G / anti_aliasing_limit * 255;
			B = B / anti_aliasing_limit * 255;
            if(R!=0 && G != 0 && B != 0)
            //std::cout<<int(R)<<" "<<int(G)<<" "<<int(B)<<std::endl;
            //int ID = m_RayList[i]->m_iID;
            // TODO: Bug here
			m_pPixelBuffer->m_Rbuffer[pixel_counter] = int(R);
			m_pPixelBuffer->m_Gbuffer[pixel_counter] = int(G);
			m_pPixelBuffer->m_Bbuffer[pixel_counter] = int(B);
            R = 0;
            G = 0;
            B = 0;
            pixel_counter++;
            anti_aliasing_counter = 0;
		}
	}
}


