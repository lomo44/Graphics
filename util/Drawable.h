/*
 * Drawable.h
 *
 * Base Class For any OpenGL Rendering Object
 *  Created on: Mar 4, 2016
 *      Author:
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "vector.h"
#include "RenderController.h"
#include <iostream>
class Color3B{
public:
	Color3B(){
		this->_c = 0;
		_f = new float[3];
		_f[0] = ARGB[2];
		_f[1] = ARGB[1];
		_f[2] = ARGB[0];
	}
	Color3B(int _hex){
		this->_c = _hex;
		_f = new float[3];
		_f[0] = ARGB[2];
		_f[1] = ARGB[1];
		_f[2] = ARGB[0];
	}
	int B(){return ARGB[0];}
	int G(){return ARGB[1];}
	int R(){return ARGB[2];}
	int A(){return ARGB[3];}
	void set(unsigned _co){_c = _co;}
	float* getRGB3f(){
		return _f;
	}

	Color3B& operator=(const unsigned int _hex){

		return *(this);
	}
	union{
		unsigned int _c;
		unsigned char ARGB[4];
	};
	float* _f;
};

class Drawable{
public:
	Drawable(){
		_scale[0] = 1;
		_scale[1] = 1;
		_scale[2] = 1;
		_euler[0] = 0;
		_euler[1] = 0;
		_euler[2] = 0;
		_translate[0] = 0;
		_translate[1] = 0;
		_translate[2] = 0;
		m_DrawWire = false;
		m_RenderMode = Solid;
	}
	virtual ~Drawable(){;}
	void translate(Vector dir){
		_translate = dir;
	}
	void translate(float x, float y, float z){
		_translate [0] = x;
		_translate[1] = y;
		_translate[2] = z;
	}
	void rotate(Vector euler){
		_euler = euler;
	}
	void rotate(float x, float y, float z){
		_euler[0] = x;
		_euler[1] = y;
		_euler[2] = z;
	}
	void setColor1i(unsigned int _color){
		_colori._c = _color;
	}
	void scale(float x, float y, float z){
		_scale[0] = x;
		_scale[1] = y;
		_scale[2] = z;
	}
	void scale(Vector scale){_scale = scale;}
	void draw();
	virtual void ChangeRenderMode(eRenderMode mode){m_RenderMode = mode;}
	Vector getTranslation(){return _translate;}
	Vector getReferenceCoord(){return _euler;}
	Vector getScale(){return _scale;}
	virtual Drawable* clone() = 0;
protected:
	virtual void drawObject() = 0;
	Vector _translate;
	Vector _euler;
	Vector _scale;
	Color3B _colori;
	bool m_DrawWire;
	eRenderMode m_RenderMode;
};

#endif /* DRAWABLE_H_ */
