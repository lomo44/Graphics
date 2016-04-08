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
#include "Light.h"
#include <queue>
#include <vector>
class Ray;
class RenderObject;
class Light;

class RayTracer {
public:
	RayTracer();
	virtual ~RayTracer();
    
    Matrix4f get_m_vw();
    float get_factor();
    int get_height();
    int get_width();

    
	void render(Attr_Render* _renderAttribute);
	void addObject(RenderObject* _obj){
		m_ObjectList.push_back(_obj);
	}
	void addLight(Light* _light){
        _light->m_iID = m_LightList.size();
		m_LightList.push_back(_light);
	}
private:
    
    void initial_hw_factor(int h, int w, double fov);
    Color anti_aliasing(Ray _ray);
    Color anti_aliasing_helper(Point3D imgp, Matrix4f vw, bool intersect);
    
	void InitializePixelBuffer(int _width, int _height);
	void InitializeRayList();
	void InitializeViewToWorldMatrix();
	void ExpandRayTracingTree();
	void CollapseRayTracingTree();
	void ShadingRay();
    // TODO
    void CalculateShadow(Ray* _ray);
	void ExtractRayListToPixelBuffer();
	Attr_Intersection* CalculateIntersection(const Line& _l);
    bool checkIntersection(const Line& _l);
	void FlushPixelBuffer();
    
private:
    
    float _factor;
    int _height;
    int _width;
    
	Matrix4f m_ViewToWorld;
	std::vector<RenderObject*> m_ObjectList;
	std::vector<Light*> m_LightList;
	std::vector<Ray*> m_RayList;
	std::queue<Ray*> m_RayBuffer;
	std::queue<Ray*> m_ShadingBuffer;
	Attr_PixelBuffer* m_pPixelBuffer;
	Attr_Render* m_pRenderAttribute;
};

#endif /* RAYTRACER_H_ */
