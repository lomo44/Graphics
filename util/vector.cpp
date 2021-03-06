/***********************************************************
             CSC418, Winter 2016
 
                 vector.cpp
                 author: Mike Pratscher

	   Vector class source file

***********************************************************/

#include <assert.h>
#include <math.h>
#include "vector.h"

const float kFloatZero = 0.0001f;


Vector::Vector(int dim)
{
	d = dim;
	v = new float[d];
	for( int i = 0; i < d; i++ )
		v[i] = 0.0;
	v[d-1] = 1;
}
Vector::Vector(float x, float y, float z){
		d = 3;
		v = new float[3];
		v[0] = x;
		v[1] = y;
		v[2] = z;
}
Vector::Vector(const Vector& vec)
{
	d = vec.d;

	v = new float[d];
	for( int i = 0; i < d; i++ )
		v[i] = vec.v[i];
}


Vector::~Vector()
{
	if( v ) delete [] v;
}


Vector&
Vector::operator=(const Vector& vec)
{
	if( d != vec.d )
	{
		d = vec.d;

		if( v ) delete [] v;
		v = new float[d];
	}

	for( int i = 0; i < d; i++ )
		v[i] = vec.v[i];

	return *this;
}


float&
Vector::operator[](int index)
{
	assert( index >= 0 && index < d );
	return v[index];
}

const float&
Vector::operator[](int index) const
{
	assert( index >= 0 && index < d );
	return v[index];
}


Vector
Vector::operator+(const Vector& vec) const
{
	Vector res = *this;

	if( vec.d == d )
	{
		for( int i = 0; i < d; i++ )
			res.v[i] += vec.v[i];
	}
	else
	{
		Vector newVec = makeDim(d, vec);
		for( int i = 0; i < d; i++ )
			res.v[i] += newVec.v[i];
	}

	return res;
}

Vector&
Vector::operator+=(const Vector& vec)
{
	if( vec.d == d )
	{
		*this = *this + vec;
	}
	else
	{
		Vector newVec = makeDim(d, vec);
		*this = *this + newVec;
	}

	return *this;
}


Vector
Vector::operator-(const Vector& vec) const
{
	Vector res = *this;

	if( vec.d == d )
	{
		for( int i = 0; i < d; i++ )
			res.v[i] -= vec.v[i];
	}
	else
	{
		Vector newVec = makeDim(d, vec);
		for( int i = 0; i < d; i++ )
			res.v[i] -= newVec.v[i];
	}

	return res;
}

Vector&
Vector::operator-=(const Vector& vec)
{
	if( vec.d == d )
	{
		*this = *this - vec;
	}
	else
	{
		Vector newVec = makeDim(d, vec);
		*this = *this - newVec;
	}

	return *this;
}


Vector
Vector::operator*(float scalar) const
{
	Vector res = *this;

	for( int i = 0; i < d; i++ )
		res.v[i] *= scalar;

	return res;
}

Vector&
Vector::operator*=(float scalar)
{
	*this = *this * scalar;

	return *this;
}


Vector
Vector::operator/(float scalar) const
{
	Vector res = *this;

	if( fabs(scalar) > kFloatZero )
	{
		for( int i = 0; i < d; i++ )
			res.v[i] /= scalar;
	}

	return res;
}

Vector&
Vector::operator/=(float scalar)
{
	*this = *this / scalar;

	return *this;
}


int
Vector::getDim() const
{
	return d;
}

float*
Vector::getData() const
{
	return v;
}


Vector
Vector::makeDim(int dim, const Vector& vec) const
{
	Vector newVec(dim);

	if( vec.d > dim )
	{
		for( int i = 0; i < dim; i++ )
			newVec.v[i] = vec.v[i];
	}
	else // vec.d <= dim
	{
		int i;
		for( i = 0; i < vec.d; i++ )
			newVec.v[i] = vec.v[i];
		for( ; i < dim; i++ )
			newVec.v[i] = 0.0;
	}

	return newVec;
}

float Vector::dot(const Vector& lhs, const Vector& rhs){
	return lhs[0] * rhs[0] +
			lhs[1] * rhs[1] +
			lhs[2] * rhs[2] +
			lhs[3] * rhs[3];
}

Vector Vector::cross(const Vector& lhs, const Vector& rhs){
	Vector _new;
	_new[0] = lhs[1]*rhs[2]-lhs[2]*rhs[1];
	_new[1] = lhs[2]*rhs[0]-lhs[0]*rhs[2];
	_new[2] = lhs[0]*rhs[1]-lhs[1]*rhs[0];
	return _new;
}

void Vector::Normalize(){
	float length = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0]/=length;
	v[1]/=length;
	v[2]/=length;
}


