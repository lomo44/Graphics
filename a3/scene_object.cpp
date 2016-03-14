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
	if(!ray.intersection.none){
		//std::cout<<"already"<<std::endl;
		return false;
	}
    Point3D neworgin = worldToModel * ray.origin;
    Vector3D newdir =  worldToModel * ray.dir;
    newdir.normalize();
    //std::cout<<newdir<<std::endl;
    double _t = (-neworgin[2])/newdir[2];
    //std::cout<<_t<<std::endl;
    if(_t >= 0 ){
        double _x = neworgin[0] + _t * newdir[0];
        double _y = neworgin[1] + _t * newdir[1];
        if(_x <= 0.5 && _x >= -0.5 && _y <= 0.5 && _y >= -0.5){
            ray.intersection.none = false;
            ray.intersection.t_value = _t;
            Point3D _int(_x*_t,_y*_t,0);
            Vector3D _norm(0,0,1);
            _int =  (modelToWorld) * _int;
            _norm = (modelToWorld.transpose()) * _norm;
            _norm.normalize();
            ray.intersection.point = _int;
            ray.intersection.normal = _norm;
        }
    }
	/* TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.*/
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
	if(!ray.intersection.none)
		return false;
	Point3D neworgin = worldToModel * ray.origin;
	Vector3D newdir =  worldToModel * ray.dir;
	Vector3D posOrgin(neworgin[0],neworgin[1],neworgin[2]);
	newdir.normalize();
	double t = (newdir.dot(posOrgin))*(newdir.dot(posOrgin))-
			(posOrgin.length())*(posOrgin.length()) + 1;
	if(t >= 0){
		//std::cout<<t<<std::endl;
		double d = 0;
		if(t == 0){
			d = -(newdir.dot(posOrgin));
		}
		else{
			double d1 = -(newdir.dot(posOrgin)) + std::sqrt(t);
			double d2 = -(newdir.dot(posOrgin)) - std::sqrt(t);
			//std::cout<<d1<<std::endl;
			//std::cout<<d2<<std::endl;
			if(d1 > 0 && d2 > 0){
				//std::cout<<"w"<<std::endl;
				if(d2 > d1){
					d = d1;
				}
				else{
					d = d2;
				}
			}
			else{
				return false;
			}
		}
		Point3D _newP(neworgin[0]+d*newdir[0],neworgin[1]+d*newdir[1],neworgin[2]+d*newdir[2]);
		Vector3D _norm(_newP[0],_newP[1],_newP[2]);
		ray.intersection.none = false;
		_newP = modelToWorld * _newP;
		_norm = (modelToWorld.transpose()) * _norm;
		_norm.normalize();
		ray.intersection.normal = _norm;
		ray.intersection.point = _newP;
		ray.intersection.t_value = d;
	}
	return !ray.intersection.none;
}

