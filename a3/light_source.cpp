/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.  

	Vector3D LightDirection (this->_pos[0]-ray.intersection.point[0],
			this->_pos[1]-ray.intersection.point[1],
			this->_pos[2]-ray.intersection.point[2]);
	/*Vector3D LightDirection (-this->_pos[0]+ray.intersection.point[0],
				-this->_pos[1]+ray.intersection.point[1],
				-this->_pos[2]+ray.intersection.point[2]);*/

	LightDirection.normalize();

	double projection = std::max(0.0,LightDirection.dot(ray.intersection.normal));
	Colour _ret;
	// Ambient
	_ret[0] += _col_ambient[0] * ray.intersection.mat->ambient[0];
	_ret[1] += _col_ambient[1] * ray.intersection.mat->ambient[1];
	_ret[2] += _col_ambient[2] * ray.intersection.mat->ambient[2];
	// diffuse
	_ret[0] += _col_diffuse[0] * projection * ray.intersection.mat->diffuse[0];
	_ret[1] += _col_diffuse[1] * projection * ray.intersection.mat->diffuse[1];
	_ret[2] += _col_diffuse[2] * projection * ray.intersection.mat->diffuse[2];
	// Specular
	Vector3D specularDir = -LightDirection + 2 *
			(ray.intersection.normal.dot(LightDirection)*LightDirection);
	projection = std::max(0.0,specularDir.dot(LightDirection));

	_ret[0] += _col_specular[0] * projection * ray.intersection.mat->specular[0];
	_ret[1] += _col_specular[1] * projection * ray.intersection.mat->specular[1];
	_ret[2] += _col_specular[2] * projection * ray.intersection.mat->specular[2];


	_ret.clamp();
	ray.col[0] += _ret[0];
	ray.col[1] += _ret[1];
	ray.col[2] += _ret[2];

}

