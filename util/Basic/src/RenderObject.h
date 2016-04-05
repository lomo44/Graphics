/*
 * RenderObject.h
 *
 *  Created on: Mar 27, 2016
 *      Author: c5lizhua
 */

#ifndef RENDEROBJECT_H_
#define RENDEROBJECT_H_

#include "Matrix.h"
#include "Attribute.h"
class BoundingBox;
class RenderObject {
public:
	RenderObject(){;}
	virtual ~RenderObject(){;};
	/* TODO: Potential Optimzatoion for the transform function.
	 * */
	void rotate(eTransformType _rotate, float degree){
		m_Transform.Rotate(_rotate,degree);
        std::cout<<"w"<<std::endl;
		m_invTransform.Rotate(_rotate,-degree);
	}
	void transform(float x, float y, float z){
		m_Transform.Transform(x, y, z);
		m_invTransform.Transform(-x,-y,-z);
	}
	void scale(float x, float y, float z){
		m_Transform.Scale(x,y,z);
		m_Transform.Scale(1/x,1/y,1/z);
	}
	const Matrix4f& getTransform(){return m_Transform;}
	const Matrix4f& getInvTransform(){return m_invTransform;}
	virtual Attr_Intersection* isIntersect(const Line& _l) = 0;
protected:
    BoundingBox* m_BoundingBox;
	Matrix4f m_Transform;
	Matrix4f m_invTransform;
};

#endif /* RENDEROBJECT_H_ */
