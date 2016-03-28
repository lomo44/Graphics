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
RayTracer::RayTracer() {
	// TODO Auto-generated constructor stub

}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

void RayTracer::render(Attr_Render* _renderAttribute){
	m_pRenderAttribute = _renderAttribute;
	this->InitializePixelBuffer(_renderAttribute->m_iScreenWidth,
			_renderAttribute->m_iScreenHeight);
}

void RayTracer::InitializePixelBuffer(int _width, int _height){
	this->m_pPixelBuffer = new Attr_PixelBuffer();
	m_pPixelBuffer->m_iHeight = _height;
	m_pPixelBuffer->m_iWidth = _width;
	int numbyte = _height * _width * sizeof(unsigned char);
	m_pPixelBuffer->m_Bbuffer = new unsigned char(numbyte);
	m_pPixelBuffer->m_Gbuffer = new unsigned char(numbyte);
	m_pPixelBuffer->m_Rbuffer = new unsigned char(numbyte);
}

void RayTracer::FlushPixelBuffer(){
	char* name = new char[m_pRenderAttribute->m_sFileName.length()+1];
	strcpy(name,m_pRenderAttribute->m_sFileName.c_str());
	bmp_write( name,
			m_pPixelBuffer->m_iWidth,m_pPixelBuffer->m_iHeight,
			m_pPixelBuffer->m_Rbuffer,
			m_pPixelBuffer->m_Rbuffer,
			m_pPixelBuffer->m_Rbuffer );
}
