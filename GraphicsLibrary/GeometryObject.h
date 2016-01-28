/*
 * GeometryObject.h
 *
 *  Created on: Jan 28, 2016
 *      Author: c5lizhua
 */

#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

class GeometryObject {
public:
	GeometryObject();
	virtual ~GeometryObject();


	virtual void scale(double _scale) = 0;
	virtual void transform(double _x, double _y) = 0;
	virtual void rotation(double _degree);
	virtual void shear(double _c);
};

#endif /* GEOMETRYOBJECT_H_ */
