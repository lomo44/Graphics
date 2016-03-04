/*
 * RenderController.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: c5lizhua
 */
#include <GL/gl.h>
#include "RenderController.h"

#include "Drawable.h"

void RenderController::Render(){
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	    //glEnable(GL_CULL_FACE);
		if(currentmode == Outlined){
			glPolygonMode(GL_FRONT,GL_FILL);
			glEnable(GL_POLYGON_OFFSET_FILL);
			for(unsigned int i = 0; i < _renderqueue.size();i++)
				_renderqueue[i]->draw();
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonMode(GL_FRONT,GL_LINE);
			for(unsigned int i = 0; i < _renderqueue.size();i++)
				_renderqueue[i]->draw();
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
			}
			else if(_mode == Solid){
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				glEnable(GL_CULL_FACE);
			}
			else if(_mode == Outlined){
				glPolygonOffset(1,1);
			}
			lastmode = currentmode;
			currentmode = _mode;
		}
}

void RenderController::add(Drawable* _item){
		_renderqueue.push_back(_item);
}

RenderController g_RenderController;
