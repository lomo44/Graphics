/*
 * Primitives.h
 *
 *  Created on: Mar 4, 2016
 *      Author: c5lizhua
 */

#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <vector>
#include <GL/gl.h>
#include <algorithm>
#include "Drawable.h"
#include "vector.h"
#include "assert.h"
#include "Matrix.h"

typedef std::vector<GLfloat> vecGLfloat;

class Drawable;
class Vector;

// 2D Primitives

class Polygon : public Drawable{
public:
	Polygon(){nofv = 0; isDrawReverse = false;}
	virtual ~Polygon(){}
	void SetVertex(Vector* vertexlist, int d, bool _isDrawReverse);
	void SetReverse(bool _b);
	Polygon* clone();
	vecGLfloat& GetVertexlist(){return _vertexlist;}
	int GetVertexCount(){return nofv;}
	Vector& GetMid(){return mid;}
	void SetMid(Vector _v){mid = _v;}
	void ChangeRenderMode(eRenderMode mode){
		//std::cout<<"Polygon"<<std::endl;
		Drawable::ChangeRenderMode(mode);
	}
protected:
	void drawObject();
private:
	vecGLfloat _vertexlist;
	vecGLfloat _normallist;
	Vector mid;
	int nofv;
	bool isDrawReverse;
};

// Basic Primitives for Rendering
class LoftedPolygon : public Drawable{
// Note: Lofted Polygon Must Have same number of vertex for each face;
public:
	LoftedPolygon(){
		_face1 = NULL;
		_face2 = NULL;
	}
	~LoftedPolygon(){
		delete _face1;
		delete _face2;
	}
	void Setfaces(Polygon* face1, Polygon* face2);
	void ChangeRenderMode(eRenderMode mode){
		_face1->ChangeRenderMode(mode);
		Drawable::ChangeRenderMode(mode);
		_face2->ChangeRenderMode(mode);
	}
protected:
	void drawObject();
	LoftedPolygon* clone(){
		LoftedPolygon* _new = new LoftedPolygon();
		_new->Setfaces(_face1->clone(),_face2->clone());
		return _new;
	}

private:
	void addVertex(GLfloat x, GLfloat y, GLfloat z){
		_vertexlist.push_back(x);
		_vertexlist.push_back(y);
		_vertexlist.push_back(z);
	}
	void addNormal(GLfloat x, GLfloat y, GLfloat z){
		_normallist.push_back(x);
		_normallist.push_back(y);
		_normallist.push_back(z);
	}
	Polygon* _face1;
	Polygon* _face2;
	vecGLfloat _vertexlist;
	vecGLfloat _normallist;
};
class ExtrudedPolygon : public LoftedPolygon{
public:
	ExtrudedPolygon(){;
	}
	~ExtrudedPolygon(){}
	void SetBase(Polygon* face);
	void SetDepth(Vector _depth){
		//_depth.print();
		depth = _depth;
	}
	void drawObject(){
		LoftedPolygon::drawObject();
	}
	void ChangeRenderMode(eRenderMode mode){
		LoftedPolygon::ChangeRenderMode(mode);
	}
private:
	Vector depth;
};
#endif /* PRIMITIVES_H_ */
