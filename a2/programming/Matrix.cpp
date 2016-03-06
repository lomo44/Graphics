

#include "Matrix.h"
#include "vector.h"
#include <iostream>
#include <cmath>
#include <assert.h>
#include <cstring>
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
	//f = new float(dim<<2);
	this->d = rhs.getDimension();
	if(rhs.f!=NULL){
		std::memcpy(f,rhs.f,sizeof(float)*(d<<2));
	}
	else{
		f = NULL;
	}
}

void Matrix::loadRotational(eMatrixType _type, float angle){
	_t = _type;
	loadIdentity();
	angle = angle*0.0174532;
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
	f = new float[d<<2];
	int c =0;
	for(int i = 0 ; i < d<<2; i++){
		if(i == c){
			f[i] = 1.0;
			c+=(d+1);
		}
		else{
			f[i] = 0;
		}
	}
	_t = eIdentity;
}

Vector Matrix::getColumn(int i) const{
	assert(i <= 3);
	Vector _ret;
	_ret[0] = f[i];
	i+=4;
	_ret[1] = f[i];
	i+=4;
	_ret[2] = f[i];
	i+=4;
	_ret[3] = f[i];
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
int Matrix::getDimension() const{
	return d;
}

Matrix Matrix::operator *(const Matrix& rhs){
	Matrix _ret;
	_ret.loadIdentity();
	for(int i = 0;i < 4; i++){
		//std::cout<<"a"<<std::endl;
		for(int j = 0; j < 4; j++){
			Vector a = this->getRow(i);
			Vector b = rhs.getColumn(j);
			_ret.f[i*4+j] = Vector::dot(a,b);
		}
	}
	return _ret;
}

Vector Matrix::operator*(const Vector& rhs){
	Vector _ret;
	_ret[0] = Vector::dot(rhs,this->getRow(0));
	_ret[1] = Vector::dot(rhs,this->getRow(1));
	_ret[2] = Vector::dot(rhs,this->getRow(2));
	_ret[3] = Vector::dot(rhs,this->getRow(3));
	return _ret;
}


Vector& Matrix::operator *=(Vector& rhs){
	rhs[0] = Vector::dot(rhs,this->getRow(0));
	rhs[1] = Vector::dot(rhs,this->getRow(1));
	rhs[2] = Vector::dot(rhs,this->getRow(2));
	rhs[3] = Vector::dot(rhs,this->getRow(3));
	return rhs;
}

void Matrix::print(){
	for(int i = 0; i < d<<2;i++){

		std::cout<<f[i]<<",";
		if(i%d== 3){
			std::cout<<std::endl;
		}
	}
	std::cout<<std::endl;
}


