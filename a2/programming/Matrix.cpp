/*
 * Matrix.cpp
 *
 *  Created on: Feb 28, 2016
 *      Author: c5lizhua
 */

#include "Matrix.h"
#include "vector.h"
#include <iostream>
#include <cmath>
#include <assert.h>
Matrix::Matrix(unsigned int dim) {
	// TODO Auto-generated constructor stub
	this->d = dim;
	f = NULL;
	_t = eNULL;
}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
	delete f;
}

Matrix::Matrix(const Matrix& rhs){
	f = new float(dim<<2);
		this->d = ;
		f = NULL;
		_t = eNULL;
	for(int i = 0 ; i < d<<2; i++){

	}
}

void Matrix::loadRotational(eMatrixType _type, float angle){
	_t = _type;
	loadIdentity();
	if(_type == eRotationalX){
		f[5] = std::cos(angle);
		f[6] = -std::sin(angle);
		f[9] = std::sin(angle);
		f[10] = std::cos(angle);
	}
	else if(_type == eRotationalY){
		f[1] = std::cos(angle);
		f[2] = std::sin(angle);
		f[8] = -std::sin(angle);
		f[10] = std::cos(angle);
	}
	else if(_type == eRotationalZ){
		f[0] = std::cos(angle);
		f[1] = -std::sin(angle);
		f[4] = std::sin(angle);
		f[5] = std::cos(angle);
	}
}
void Matrix::loadTranslational(float x, float y, float z){
	_t = eTranslational;
	loadIdentity();
	f[3] = x;
	f[7] = y;
	f[11] = z;
}
void Matrix::loadIdentity(){
	for(int i = 0 ; i < d<<2; i++){
		if((i & ~d) == 1){
			f[i] = 1.0;
		}
		else{
			f[i] = 0;
		}
	}
	_t = eIdentity;
}

Vector Matrix::getColumn(int i){
	assert(i <= 3);
	Vector _ret;
	_ret[0] = f[i+=4];
	_ret[1] = f[i+=4];
	_ret[2] = f[i+=4];
	_ret[3] = f[i+=4];
	return _ret;
}

Vector Matrix::getRow(int i){
	assert(i <= 3);
	i*=4;
	Vector _ret;
	_ret[0] = f[i];
	_ret[1] = f[i+1];
	_ret[2] = f[i+2];
	_ret[3] = f[i+3];
	return _ret;
}
int Matrix::getDimension(){
	return d;
}

Matrix Matrix::operator *(const Matrix& rhs){
	Matrix _ret;
	for(int i = 0;i < 4; i++){
		for(int j = 0; j < 4; j++){
			Vector a = this->getRow(i);
			Vector b = this->getColumn(j);
			_ret.f[(i<<2)+j] = Vector::dot(a,b);
		}
	}
	return _ret;
}


Matrix& Matrix::operator *=(Matrix& rhs){
	Matrix _ret = *(this)*rhs;
	rhs.f = _ret.f;
	return rhs;
}


