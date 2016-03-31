/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Vector.h
 * Author: john
 *
 * Created on March 10, 2016, 9:59 PM
 *
 * New Vector Class for future implementations
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdio.h>
#include <cmath>

// 3d affine vectors
template<class T> class Vector4{
    public:
        Vector4(){
            _t = new T[4];
            _t[0] = 0;
            _t[1] = 0;
            _t[2] = 0;
            _t[3] = 0;
        }
        Vector4(T _a, T _b, T _c, T _d){
            _t = new T[4];
            _t[0] = _a;
            _t[1] = _b;
            _t[2] = _c;
            _t[3] = _d;
        }
        Vector4(T _a, T _b, T _c){
            _t = new T[4];
            _t[0] = _a;
            _t[1] = _b;
            _t[2] = _c;
            _t[3] = 1;
        }
        Vector4(const Vector4<T>& rhs){
        	_t = new T[4];
        	_t[0] = rhs[0];
        	_t[1] = rhs[1];
        	_t[2] = rhs[2];
        	_t[3] = rhs[3];
        }
        ~Vector4(){
            delete _t;
        }
        inline Vector4<T>& operator=(const Vector4<T>& rhs){
        	_t = new T[4];
        	_t[0] = rhs[0];
        	_t[1] = rhs[1];
        	_t[2] = rhs[2];
        	_t[3] = rhs[3];
            return *this;
        }
        inline T& operator[](int index){
            return _t[index];
        }
        inline const T operator[](int index) const{
            return _t[index];
        }
        inline Vector4<T>  operator+ (const Vector4<T>& vec) const{
            Vector4<T> ret = *this;
            ret[0] += vec[0];
            ret[1] += vec[1];
            ret[2] += vec[2];
            ret[3] += vec[3];
            return ret;
        }
        inline Vector4<T>& operator+=(const Vector4<T>& vec){
            (*this)[0] += vec[0];
            (*this)[1] += vec[1];
            (*this)[2] += vec[2];
            (*this)[3] += vec[3];
            return *this;
        }
        inline Vector4<T>  operator- (const Vector4<T>& vec) const{
            Vector4<T> ret = *this;
            ret[0] -= vec[0];
            ret[1] -= vec[1];
            ret[2] -= vec[2];
            ret[3] -= vec[3];
            return ret;
        }
        inline Vector4<T>& operator-=(const Vector4<T>& vec){
            (*this)[0] -= vec[0];
            (*this)[1] -= vec[1];
            (*this)[2] -= vec[2];
            (*this)[3] -= vec[3];
            return *this;
        }
        inline Vector4<T>  operator* (T scalar) const{
            Vector4<T> ret = *this;
            ret[0] *= scalar;
            ret[1] *= scalar;
            ret[2] *= scalar;
            ret[3] *= scalar;
            return ret;
        }
        inline Vector4<T>& operator*=(T scalar){
            *this[0] *= scalar;
            *this[1] *= scalar;
            *this[2] *= scalar;
            *this[3] *= scalar;
            return *this;
        }
        inline Vector4<T>  operator/ (T scalar) const{
            Vector4<T> ret = *this;
            ret[0] /= scalar;
            ret[1] /= scalar;
            ret[2] /= scalar;
            ret[3] /= scalar;
            return ret;
        }
        inline Vector4<T>  operator/= (T scalar) const{
            *this[0] /= scalar;
            *this[1] /= scalar;
            *this[2] /= scalar;
            *this[3] /= scalar;
            return *this;
        }
        inline Vector4<T> cross(const Vector4<T>& rhs){
            Vector4<T> _new;
            _new[0] = (*this)[1]*rhs[2]-(*this)[2]*rhs[1];
            _new[1] = (*this)[2]*rhs[0]-(*this)[0]*rhs[2];
            _new[2] = (*this)[0]*rhs[1]-(*this)[1]*rhs[0];
            return _new;
        }
        inline T dot(const Vector4<T>& rhs){
            return _t[0] * rhs[0] +
            _t[1] * rhs[1] +
            _t[2] * rhs[2] +
           _t[3] * rhs[3];
        }
        inline T magnitude(){
            return sqrt(_t[0]* _t[0]+_t[1]*_t[1]+_t[2]*_t[2]);
        }
        inline void Normalize(){
            T mag = this->magnitude();
            _t[0]/= mag;
            _t[1]/= mag;
            _t[2]/= mag;
        }
        inline void Print(){
            std::cout<<_t[0]<<"|"<<_t[1]<<"|"<<_t[2]<<"|"<<_t[3]<<"|"<<std::endl;
        }
    private:
        T* _t;
};
template<class T> inline Vector4<T> operator - (const Vector4<T>& rhs){
	return Vector4<T>(-rhs[0],-rhs[1],-rhs[2],-rhs[3]);
}
template<class T> inline Vector4<T> operator - (const Vector4<T>& lhs, const Vector4<T>& rhs){
	return Vector4<T>(lhs[0]-rhs[0],lhs[1]-rhs[1],lhs[2]-rhs[2],lhs[3]-rhs[3]);
}
template<class T> inline Vector4<T> operator + (const Vector4<T>& lhs, const Vector4<T>& rhs){
	return Vector4<T>(lhs[0]+rhs[0],lhs[1]+rhs[1],lhs[2]+rhs[2],lhs[3]+rhs[3]);
}
template<class T> inline Vector4<T> operator * (const float lhs, const Vector4<T>& rhs){
	return Vector4<T>(lhs*rhs[0],lhs*rhs[1],lhs-rhs[2],lhs-rhs[3]);
}
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;


#endif /* VECTOR_H */
