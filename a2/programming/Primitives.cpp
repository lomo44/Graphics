/*
 * Primitives.cpp
 *
 *
 *  Created on: Mar 4, 2016
 *      Author:
 */

#include "Primitives.h"
#include <iostream>

void Polygon::SetVertex(Vector* vertexlist, int d, bool _isDrawReverse){
	nofv = d;
	float a = 0;
	float b = 0;
	float c = 0;
	int start = 0;
	int end = nofv;
	int increment = 1;
	isDrawReverse = _isDrawReverse;
	if(isDrawReverse){
		start = nofv-1;
		end = -1;
		increment = -1;
	}
	Vector normal = Vector::cross(vertexlist[1]-vertexlist[0],vertexlist[2]-vertexlist[1]);
	normal.Normalize();
	std::cout<<"X"<<normal[0]<<"Y"<<normal[1]<<"Z"<<normal[2]<<std::endl;
	for(int i = start; i != end; i += increment){
		//std::cout<<vertexlist[i][0]<<"|"<<vertexlist[i][1]<<"|"<<vertexlist[i][2]<<std::endl;
		_vertexlist.push_back(vertexlist[i][0]);
		_vertexlist.push_back(vertexlist[i][1]);
		_vertexlist.push_back(vertexlist[i][2]);
		_normallist.push_back(normal[0]);
		_normallist.push_back(normal[1]);
		_normallist.push_back(normal[2]);
		a += vertexlist[i][0];
		b += vertexlist[i][1];
		c += vertexlist[i][2];
	}
	a = a/d;
	b = b/d;
	c = c/d;
	mid[0] = a;
	mid[1] = b;
	mid[2] = c;
}

void Polygon::SetReverse(bool _b){
	if(_b != isDrawReverse)
	{
		isDrawReverse = _b;
		std::reverse(_vertexlist.begin(),_vertexlist.end());
		for(unsigned int i = 0; i < _vertexlist.size();i+=3){
			GLfloat a = _vertexlist[i];
			_vertexlist[i] = _vertexlist[i+2];
			_vertexlist[i+2] = a;
		}
		for(unsigned int i = 0 ; i < _normallist.size();i++){
			_normallist[i] *= -1;
		}
	}
}

Polygon* Polygon::clone(){
	Polygon* _clone = new Polygon();
	Vector* _newvec = new Vector[nofv];
	for(int i = 0 ; i < nofv; i++){
		_newvec[i] = _vertexlist[i];
	}
	_clone->SetVertex(_newvec,nofv,isDrawReverse);
	_clone->translate(this->getTranslation());
	_clone->rotate(this->getReferenceCoord());
	_clone->scale(this->getScale());
	return _clone;
}

void Polygon::drawObject(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&_vertexlist[0]);
	glNormalPointer(GL_FLOAT,0,&_normallist[0]);
	glDrawArrays(GL_POLYGON,0,nofv);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void LoftedPolygon::Setfaces(Polygon* face1, Polygon* face2){
	if(face1->GetMid()[3] > face2->GetMid()[3]){
		_face1 = face1;
		_face2 = face2;
	}
	else{
		_face1 = face2;
		_face2 = face1;
	}
	vecGLfloat& _v1 = _face1->GetVertexlist();
	vecGLfloat& _v2 = _face2->GetVertexlist();
	int vc1 = _face1->GetVertexCount();
	int vc2 = _face2->GetVertexCount();
	assert(vc1 == vc2);
	Vector a;
	Vector b;
	Vector c;
	for(int i = 0; i < (vc1-1)*3; i+=3){
		a[0] = _v1[i+3];
		a[1] = _v1[i+4];
		a[2] = _v1[i+5];

		b[0] = _v1[i];
		b[1] = _v1[i+1];
		b[2] = _v1[i+2];

		c[0] = _v2[i];
		c[1] = _v2[i+1];
		c[2] = _v2[i+2];

		Vector norm = Vector::cross(b-a,c-b);
		norm.Normalize();
		addVertex(_v1[i+3],_v1[i+4],_v1[i+5]);
		addVertex(_v1[i],_v1[i+1],_v1[i+2]);
		addVertex(_v2[i],_v2[i+1],_v2[i+2]);
		addVertex(_v2[i+3],_v2[i+4],_v2[i+5]);
		addNormal(norm[0],norm[1],norm[2]);
		addNormal(norm[0],norm[1],norm[2]);
		addNormal(norm[0],norm[1],norm[2]);
		addNormal(norm[0],norm[1],norm[2]);
	}
	a[0] = _v1[0];
	a[1] = _v1[1];
	a[2] = _v1[2];
	b[0] = _v1[vc1*3-3];
	b[1] = _v1[vc1*3-2];
	b[2] = _v1[vc1*3-1];
	c[0] = _v2[vc1*3-3];
	c[1] = _v2[vc1*3-2];
	c[2] = _v2[vc1*3-1];

	Vector norm = Vector::cross(b-a,c-b);
	norm.Normalize();
	addNormal(norm[0],norm[1],norm[2]);
	addNormal(norm[0],norm[1],norm[2]);
	addNormal(norm[0],norm[1],norm[2]);
	addNormal(norm[0],norm[1],norm[2]);
	addVertex(_v1[0],_v1[1],_v1[2]);
	addVertex(_v1[vc1*3-3],_v1[vc1*3-2],_v1[vc1*3-1]);
	addVertex(_v2[vc1*3-3],_v2[vc1*3-2],_v2[vc1*3-1]);
	addVertex(_v2[0],_v2[1],_v2[2]);
	_face1->SetReverse(false);
	_face2->SetReverse(true);
}

void LoftedPolygon::drawObject(){
	_face1->setColor1i(_colori._c);
	_face1->draw();
	_face2->setColor1i(_colori._c);
	_face2->draw();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&_vertexlist[0]);
	glNormalPointer(GL_FLOAT,0,&_normallist[0]);
	glDrawArrays(GL_QUADS,0,(int)(_vertexlist.size()/3));
	glDisableClientState(GL_VERTEX_ARRAY);
}

void ExtrudedPolygon::SetBase(Polygon* face){
	vecGLfloat& _vec = face->GetVertexlist();
	Polygon* newface = new Polygon();
	*(newface) = *(face);
	vecGLfloat& newvec = newface->GetVertexlist();
	Matrix* _new = new Matrix();
	//depth.print();
	_new->loadTranslational(depth[0],depth[1],depth[2]);
	//_new->print();
	Vector _temp;
	for(unsigned int i = 0 ; i <= (_vec.size()-3);i+=3){
		_temp[0] = _vec[i];
		_temp[1] = _vec[i+1];
		_temp[2] = _vec[i+2];
		_temp = *(_new)*=_temp;
		newvec[i] = (_temp[0]);
		newvec[i+1]=(_temp[1]);
		newvec[i+2] =(_temp[2]);
	}
	Vector& mid = newface->GetMid();
	mid = *(_new)*=mid;
	//vecGL
	//newface->translate(depth);
	//newface->SetReverse(true);
	this->Setfaces(face,newface);
}
