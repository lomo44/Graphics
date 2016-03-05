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
	if(this->m_RenderMode == Solid)
		glColor3ub(_colori.R(),_colori.G(),_colori.B());
	else if(this->m_RenderMode == Wireframe){
		//std::cout<<"w"<<std::endl;
		glColor3ub(0,0.5,0);
	}
	else if(this->m_RenderMode == Metallic){
		GLfloat shineness[1] = {1000.0f};
		GLfloat specular[4] = {1.0,1.0,1.0,1.0};
		GLfloat Ambient[4] = {0,0,0,1};
		GLfloat emiision[4] = {0,0,0,1};
		glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shineness);
		glMaterialfv(GL_FRONT,GL_AMBIENT,Ambient);
		glMaterialfv(GL_FRONT,GL_EMISSION,emiision);
		glColor3ub(_colori.R(),_colori.G(),_colori.B());
	}
	drawObject();
	glPopMatrix();
}
