/*
 * vector.h
 *
 *  Created on: Jan 28, 2016
 *      Author: c5lizhua
 */

#ifndef VECTOR_H_
#define VECTOR_H_

template<class T_type> struct vector4D{
	T_type* w;
	T_type* x;
	T_type* y;
	T_type* Z;
};

template<class T_type> struct vector3D{
	T_type* x;
	T_type* y;
	T_type* z;
};

template<class T_type> struct vector2D{
	T_type* x;
	T_type* y;
};

struct vector2Dd{
	double x;
	double y;
};

struct vector2Df{
	float x;
	float y;
};

struct vector2Dl{
	long x;
	long y;
};

struct vector2Di{
	int x;
	int y;
};

struct vector3Dd{
	double x;
	double y;
	double z;
};

struct vector3Df{
	float x;
	float y;
	float z;
};

struct vector3Dl{
	long x;
	long y;
	long z;
};

struct vector3Di{
	int x;
	int y;
	int z;
};

struct vector4Dd{
	double w;
	double x;
	double y;
	double z;
};

struct vector4Df{
	float w;
	float x;
	float y;
	float z;
};

struct vector4Dl{
	long w;
	long x;
	long y;
	long z;
};

struct vector4Di{
	int w;
	int x;
	int y;
	int z;
};



#endif /* VECTOR_H_ */
