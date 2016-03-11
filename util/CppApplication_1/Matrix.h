/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Matrix.h
 * Author: john
 *
 * Created on March 11, 2016, 11:06 AM
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <assert.h>
enum eMatrixType{
	eRotationalX,
	eRotationalY,
	eRotationalZ,
	eTranslational,
	eIdentity,
	eUnknown,
	eNULL
};

template<class T> class Matrix4 {
public:
	Matrix4(){
            loadIdentity();
        }
	Matrix4(const Matrix4<T>& rhs){
            memcpy(f,rhs.f,sizeof(T)*(16));
        }
	~Matrix4(){
            delete f;
        }
	void loadRotational(eMatrixType _type, T angle){
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
	void loadTranslational(T x, T y, T z){
            _t = eTranslational;
            f[3] = x;
            f[7] = y;
            f[11] = z;
        }
	void loadIdentity(){
            f = new T[16];
            int c =0;
            for(int i = 0 ; i < 16; i++){
                    if(i == c){
                            f[i] = 1.0;
                            c+=(4+1);
                    }
                    else{
                            f[i] = 0;
                    }
            }
            _t = eIdentity;
        }
	Vector4<T> getColumn(int i) const{
            assert(i <= 3);
            Vector4<T> _ret;
            _ret[0] = f[i];
            i+=4;
            _ret[1] = f[i];
            i+=4;
            _ret[2] = f[i];
            i+=4;
            _ret[3] = f[i];
            return _ret;
        }
	Vector4<T> getRow(int i){
            assert(i <= 3);
            i*=4;
            Vector4<T> _ret;
            _ret[0] = f[i];
            _ret[1] = f[i+1];
            _ret[2] = f[i+2];
            _ret[3] = f[i+3];
            return _ret;
        }
        T& operator[](int i){
            return f[i];
        }
	Matrix4<T>  operator* (const Matrix4<T>& rhs){
            Matrix4<T> _ret;
            for(int i = 0;i < 4; i++){
                    for(int j = 0; j < 4; j++){
                            Vector4<T> a = this->getRow(i);
                            Vector4<T> b = rhs.getColumn(j);
                            _ret.f[i*4+j] = a.dot(b);
                    }
            }
            return _ret;
        }
	Matrix4<T>&  operator*=(Matrix4<T>& rhs){
            for(int i = 0;i < 4; i++){
                    for(int j = 0; j < 4; j++){
                            Vector4<T> a = this->getRow(i);
                            Vector4<T> b = rhs.getColumn(j);
                            f[i*4+j] = a.dot(b);
                    }
            }
            return *this;
        }
	Vector4<T>  operator* (const Vector4<T>& rhs){
            Vector4<T> _ret;
            _ret[0] = _ret.dot(this->getRow(0));            
            _ret[1] = _ret.dot(this->getRow(1));
            _ret[2] = _ret.dot(this->getRow(2));
            _ret[3] = _ret.dot(this->getRow(3));
            return _ret;
        }
	Vector4<T>&  operator*=(Vector4<T>& rhs){
            rhs[0] = rhs.dot(this->getRow(0));
            rhs[1] = rhs.dot(this->getRow(1));
            rhs[2] = rhs.dot(this->getRow(2));
            rhs[3] = rhs.dot(this->getRow(3));
            return rhs;
        }
	void print(){
            for(int i = 0; i < 4;i++){

		std::cout<<f[i]<<",";
		if(i % 4== 3){
			std::cout<<std::endl;
		}
            }
            std::cout<<std::endl;
        }
	
private:
        T* f;
	eMatrixType _t;
};



#endif /* MATRIX_H */

