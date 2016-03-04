/*
 * RenderController.h
 *
 *  Created on: Mar 4, 2016
 *      Author:
 */

#ifndef RENDERCONTROLLER_H_
#define RENDERCONTROLLER_H_

#include <vector>


class Drawable;

enum eRenderMode{
	Solid,
	Wireframe,
	Outlined,
	Unknown
};

class RenderController{
public:
	RenderController(){
		currentmode = Unknown;
		lastmode = Unknown;
	}
	void Render();
	void SetMode(eRenderMode _mode);
	void add(Drawable* _item);
private:
	eRenderMode currentmode;
	eRenderMode lastmode;
	std::vector<Drawable*> _renderqueue;
};

extern RenderController g_RenderController;
#endif /* RENDERCONTROLLER_H_ */
