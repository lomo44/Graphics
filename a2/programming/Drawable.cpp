/*
 * Drawable.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: c5lizhua
 */

#include "Drawable.h"
#include <GL/gl.h>

void Drawable::draw(){
	glPushMatrix();
	// Adjust Reference Frame ZNZ;
	glTranslatef(_translate[0],_translate[1],_translate[2]);
	glRotatef(_euler[0],1,0,0); // Alpha
	glRotatef(_euler[1],0,1,0); // Beta
	glRotatef(_euler[2],0,0,1); // Gama
	glScalef(_scale[0],_scale[1],_scale[2]);
	if(this->m_RenderMode == Solid){
		glColor3ub(_colori.R(),_colori.G(),_colori.B());
	}
	else if(this->m_RenderMode == Wireframe){
		//std::cout<<"w"<<std::endl;
		glColor3ub(0,0.5,0);
	}
	else if(this->m_RenderMode == Metallic){
		glColor3ub(_colori.R(),_colori.G(),_colori.B());
	}
	drawObject();
	glPopMatrix();
}
