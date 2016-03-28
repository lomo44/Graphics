/*
 * RayTracer.h
 *
 *  Created on: Mar 28, 2016
 *      Author: c5lizhua
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "Attribute.h"
#include "Matrix.h"
#include <queue>
#include <vector>
class Ray;
class RenderObject;
class Light;

class RayTracer {
public:
	RayTracer();
	virtual ~RayTracer();
	void render(Attr_Render* _renderAttribute);
	void addObject(RenderObject* _obj){
		m_ObjectList.push_back(_obj);
	}
	void addLight(Light* _light){
		m_LightList.push_back(_light);
	}
private:
	void InitializePixelBuffer(int _width, int _height);
	void InitializeRayList();
	void FlushPixelBuffer();
private:
	Matrix4f* m_ViewToWorld;
	std::vector<RenderObject*> m_ObjectList;
	std::vector<Light*> m_LightList;
	std::queue<Ray*> m_RayList;
	Attr_PixelBuffer* m_pPixelBuffer;
	Attr_Render* m_pRenderAttribute;
};

#endif /* RAYTRACER_H_ */
