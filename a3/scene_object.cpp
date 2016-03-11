/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
    ray.origin = ray.origin * worldToModel;
    ray.dir = ray.dir * worldToModel;
    double _t = ray.dir.operator [2]/(-ray.origin.operator [2]);
    if(_t >= 0 ){
        double _x = ray.origin.[0] + _t * ray.dir[0];
        double _y = ray.origin.[1] + _t * ray.dir[1];
        if(_x <= 0.5 && _x >= -0.5 && _y <= 0.5 && _y >= -0.5){
            ray.intersection.none = false;
            ray.intersection.t_value = _t;
            Point3D _int(_x*_t,_y*_t,0);
            Point3D _norm(0,0,1);
            _int = _int * (modelToWorld);
            _norm = _norm * (modelToWorld);
            ray.intersection.point = _int;
            ray.intersection.normal = _norm;
        }
    }
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
    ray.dir = ray.dir * modelToWorld;
    ray.origin = ray.origin * modelToWorld;
    return !ray.intersection.none;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.
	
	return false;
}

