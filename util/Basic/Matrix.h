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
    Matrix4(T* _t){
        f = _t;
        this->_t = eUnknown;
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
    bool Invert()
    {
        double inv[16], det;
        int i;

        inv[0] = f[5]  * f[10] * f[15] - 
                 f[5]  * f[11] * f[14] - 
                 f[9]  * f[6]  * f[15] + 
                 f[9]  * f[7]  * f[14] +
                 f[13] * f[6]  * f[11] - 
                 f[13] * f[7]  * f[10];

        inv[4] = -f[4]  * f[10] * f[15] + 
                  f[4]  * f[11] * f[14] + 
                  f[8]  * f[6]  * f[15] - 
                  f[8]  * f[7]  * f[14] - 
                  f[12] * f[6]  * f[11] + 
                  f[12] * f[7]  * f[10];

        inv[8] = f[4]  * f[9] * f[15] - 
                 f[4]  * f[11] * f[13] - 
                 f[8]  * f[5] * f[15] + 
                 f[8]  * f[7] * f[13] + 
                 f[12] * f[5] * f[11] - 
                 f[12] * f[7] * f[9];

        inv[12] = -f[4]  * f[9] * f[14] + 
                   f[4]  * f[10] * f[13] +
                   f[8]  * f[5] * f[14] - 
                   f[8]  * f[6] * f[13] - 
                   f[12] * f[5] * f[10] + 
                   f[12] * f[6] * f[9];

        inv[1] = -f[1]  * f[10] * f[15] + 
                  f[1]  * f[11] * f[14] + 
                  f[9]  * f[2] * f[15] - 
                  f[9]  * f[3] * f[14] - 
                  f[13] * f[2] * f[11] + 
                  f[13] * f[3] * f[10];

        inv[5] = f[0]  * f[10] * f[15] - 
                 f[0]  * f[11] * f[14] - 
                 f[8]  * f[2] * f[15] + 
                 f[8]  * f[3] * f[14] + 
                 f[12] * f[2] * f[11] - 
                 f[12] * f[3] * f[10];

        inv[9] = -f[0]  * f[9] * f[15] + 
                  f[0]  * f[11] * f[13] + 
                  f[8]  * f[1] * f[15] - 
                  f[8]  * f[3] * f[13] - 
                  f[12] * f[1] * f[11] + 
                  f[12] * f[3] * f[9];

        inv[13] = f[0]  * f[9] * f[14] - 
                  f[0]  * f[10] * f[13] - 
                  f[8]  * f[1] * f[14] + 
                  f[8]  * f[2] * f[13] + 
                  f[12] * f[1] * f[10] - 
                  f[12] * f[2] * f[9];

        inv[2] = f[1]  * f[6] * f[15] - 
                 f[1]  * f[7] * f[14] - 
                 f[5]  * f[2] * f[15] + 
                 f[5]  * f[3] * f[14] + 
                 f[13] * f[2] * f[7] - 
                 f[13] * f[3] * f[6];

        inv[6] = -f[0]  * f[6] * f[15] + 
                  f[0]  * f[7] * f[14] + 
                  f[4]  * f[2] * f[15] - 
                  f[4]  * f[3] * f[14] - 
                  f[12] * f[2] * f[7] + 
                  f[12] * f[3] * f[6];

        inv[10] = f[0]  * f[5] * f[15] - 
                  f[0]  * f[7] * f[13] - 
                  f[4]  * f[1] * f[15] + 
                  f[4]  * f[3] * f[13] + 
                  f[12] * f[1] * f[7] - 
                  f[12] * f[3] * f[5];

        inv[14] = -f[0]  * f[5] * f[14] + 
                   f[0]  * f[6] * f[13] + 
                   f[4]  * f[1] * f[14] - 
                   f[4]  * f[2] * f[13] - 
                   f[12] * f[1] * f[6] + 
                   f[12] * f[2] * f[5];

        inv[3] = -f[1] * f[6] * f[11] + 
                  f[1] * f[7] * f[10] + 
                  f[5] * f[2] * f[11] - 
                  f[5] * f[3] * f[10] - 
                  f[9] * f[2] * f[7] + 
                  f[9] * f[3] * f[6];

        inv[7] = f[0] * f[6] * f[11] - 
                 f[0] * f[7] * f[10] - 
                 f[4] * f[2] * f[11] + 
                 f[4] * f[3] * f[10] + 
                 f[8] * f[2] * f[7] - 
                 f[8] * f[3] * f[6];

        inv[11] = -f[0] * f[5] * f[11] + 
                   f[0] * f[7] * f[9] + 
                   f[4] * f[1] * f[11] - 
                   f[4] * f[3] * f[9] - 
                   f[8] * f[1] * f[7] + 
                   f[8] * f[3] * f[5];

        inv[15] = f[0] * f[5] * f[10] - 
                  f[0] * f[6] * f[9] - 
                  f[4] * f[1] * f[10] + 
                  f[4] * f[2] * f[9] + 
                  f[8] * f[1] * f[6] - 
                  f[8] * f[2] * f[5];

        det = f[0] * inv[0] + f[1] * inv[4] + f[2] * inv[8] + f[3] * inv[12];

        if (det == 0)
            return false;

        det = 1.0 / det;

        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;

        return true;
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

