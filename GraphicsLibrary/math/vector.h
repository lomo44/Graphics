/*
 * vector.h
 *
 *  Created on: Jan 28, 2016
 *      Author: c5lizhua
 */

#ifndef VECTOR_H_
#define VECTOR_H_

template<class T_type> struct vector4D{
	T_type w;
	T_type x;
	T_type y;
	T_type z;
};

template<class T_type> struct vector3D{
	T_type x;
	T_type y;
	T_type z;
};

template<class T_type> struct vector2D{
	T_type x;
	T_type y;
};

template<class T_type> inline T_type dotproduct2D(vector2D<T_type> _v1,vector2D<T_type> _v2){
	return _v1.x * _v2.x + _v1.y*_v2.y;
}
template<class T_type> inline T_type dotproduct3D(vector3D<T_type> _v1,vector3D<T_type> _v2){
	return _v1.x * _v2.x + _v1.y*_v2.y + _v1.z * _v2.z;
}
template<class T_type> inline T_type dotproduct4D(vector4D<T_type> _v1,vector4D<T_type> _v2){
	return _v1.w*_v2.w+_v1.x * _v2.x + _v1.y*_v2.y + _v1.z * _v2.z;
}

#endif /* VECTOR_H_ */
