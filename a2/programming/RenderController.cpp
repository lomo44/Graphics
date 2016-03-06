/*
 * RenderController.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: c5lizhua
 */
#include <GL/gl.h>
#include "RenderController.h"
#include <iostream>
#include "Drawable.h"

void RenderController::Render(){
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//glEnable(GL_CULL_FACE);

	if(currentmode == Outlined){
		glPolygonMode(GL_FRONT,GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		for(unsigned int i = 0; i < _renderqueue.size();i++){
			_renderqueue[i]->ChangeRenderMode(Solid);
			_renderqueue[i]->draw();
		}
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT,GL_LINE);
		for(unsigned int i = 0; i < _renderqueue.size();i++){
			_renderqueue[i]->ChangeRenderMode(Wireframe);
			_renderqueue[i]->draw();
		}
	}
	else{
		for(unsigned int i = 0; i < _renderqueue.size();i++)
			_renderqueue[i]->draw();
	}
}

void RenderController::SetMode(eRenderMode _mode){
	if(_mode != currentmode){
		if(_mode == Wireframe){
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			for(unsigned int i = 0; i < _renderqueue.size();i++){
				_renderqueue[i]->ChangeRenderMode(Wireframe);
			}
		}
		else if(_mode == Solid){
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);;
			glEnable(GL_CULL_FACE);
			for(unsigned int i = 0; i < _renderqueue.size();i++){
				_renderqueue[i]->ChangeRenderMode(Solid);
			}
		}
		else if(_mode == Outlined){
			//glDisable(GL_COLOR_MATERIAL);
			glPolygonOffset(4,4);
		}
		else if(_mode == Metallic){
			for(unsigned int i = 0; i < _renderqueue.size();i++){
				_renderqueue[i]->ChangeRenderMode(Metallic);
			}
			glEnable(GL_CULL_FACE);
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
			glPolygonMode(GL_FRONT,GL_FILL);
			GLfloat shineness[1] = {150.0f};
			GLfloat specular[4] = {0.7f,0.7f,0.7f,1.0};
			glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,shineness);
		}
		else if(_mode == Matte){
			glEnable(GL_CULL_FACE);
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
			glPolygonMode(GL_FRONT,GL_FILL);
			GLfloat shineness[1] = {0.0f};
			GLfloat specular[4] = {0.0f,0.0f,0.0f,1.0};
			glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,shineness);
		}
		lastmode = currentmode;
		currentmode = _mode;
	}
}

void RenderController::add(Drawable* _item){
		_renderqueue.push_back(_item);
}

RenderController g_RenderController;
