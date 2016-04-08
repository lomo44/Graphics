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
#include <stdlib.h>
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
            _t[3] = 0;
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
            if(_t==NULL)
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
        inline Vector4<T> operator*(const Vector4<T>& vec){
            Vector4<T> ret = *this;
            ret[0] *= vec[0];
            ret[1] *= vec[1];
            ret[2] *= vec[2];
            ret[3] *= vec[3];
            return ret;
        }
        inline Vector4<T>& operator*=(T scalar){
            (*this)[0] *= scalar;
            (*this)[1] *= scalar;
            (*this)[2] *= scalar;
            (*this)[3] *= scalar;
            return *this;
        }
        inline Vector4<T>& operator*=(const Vector4<T>& vec){
            (*this)[0] *= vec[0];
            (*this)[1] *= vec[1];
            (*this)[2] *= vec[2];
            (*this)[3] *= vec[3];
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
            _t[0] /= scalar;
            _t[1] /= scalar;
            _t[2] /= scalar;
            _t[3] /= scalar;
            return *this;
        }
        inline Vector4<T> cross(const Vector4<T>& rhs){
            Vector4<T> _new;
            _new[0] = (*this)[1]*rhs[2]-(*this)[2]*rhs[1];
            _new[1] = (*this)[2]*rhs[0]-(*this)[0]*rhs[2];
            _new[2] = (*this)[0]*rhs[1]-(*this)[1]*rhs[0];
            return _new;
        }
        inline T dot(const Vector4<T>& rhs) const{
            return _t[0] * rhs[0] +
            _t[1] * rhs[1] +
            _t[2] * rhs[2] +
           _t[3] * rhs[3];
        }
        inline T magnitude(){
            return sqrt(_t[0]* _t[0]+_t[1]*_t[1]+_t[2]*_t[2]);
        }
        inline T distance(const Vector4<T>& rhs) const{
            return sqrt((_t[0] - rhs[0]) * (_t[0] - rhs[0]) + 
                    (_t[1] - rhs[1]) * (_t[1] - rhs[1]) +
                    (_t[2] - rhs[2]) * (_t[2] - rhs[2]) +
                    (_t[3] - rhs[3]) * (_t[3] - rhs[3])
                    );
        }
        inline void Normalize(){
            T mag = this->magnitude();
            _t[0]/= mag;
            _t[1]/= mag;
            _t[2]/= mag;
        }
        inline void Randomize(const Vector4<T>& m_v1, const Vector4<T>& m_v2,
                const Vector4<T>& m_v3, float limit){
            float random_x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit/2)) - limit;
            float random_y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit/2)) - limit;
            float random_z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/limit/2)) - limit;
            *this += m_v1 * random_x;
            *this += m_v2 * random_y;
            *this += m_v3 * random_z;
        }
        inline void Print() const{
            std::cout<<_t[0]<<"|"<<_t[1]<<"|"<<_t[2]<<"|"<<_t[3]<<"|"<<std::endl;
        }
        inline void clamp(T _uplimit){
            if(_t[0] > _uplimit) _t[0] = _uplimit;
            if(_t[1] > _uplimit) _t[1] = _uplimit;
            if(_t[2] > _uplimit) _t[2] = _uplimit;
            if(_t[3] > _uplimit) _t[3] = _uplimit;
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
template<class T> inline Vector4<T> operator * (const T lhs, const Vector4<T>& rhs){
	return Vector4<T>(lhs*rhs[0],lhs*rhs[1],lhs*rhs[2],lhs*rhs[3]);
}
typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;
typedef Vector4<float> Color;
typedef Vector4<float> Point3D;

#endif /* VECTOR_H */
