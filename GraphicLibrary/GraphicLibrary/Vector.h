#pragma once
#include <stdlib.h>
#include <iostream>

template<class T_type> class vector4D {
	T_type w;
	T_type x;
	T_type y;
	T_type z;
	inline T_type operator+(const vector4D<T_type>& _rhs) {
		vector4D<class T_type> _new = new vector4D<class T_type>;
		_new.w = this->w + _rhs.w;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		_new.z = this->z + _rhs.z;
		return _new;
	}
	inline T_type operator-(const vector4D<T_type>& _rhs) {
		vector4D<class T_type> _new = new vector4D<class T_type>;
		_new.w = this->w - _rhs.w;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		_new.z = this->z - _rhs.z;
		return _new;
	}
};
template<class T_type> class vector3D {
	T_type x;
	T_type y;
	T_type z;
	inline T_type operator+(const vector3D<T_type>& _rhs) {
		vector3D<class T_type> _new = new vector3D<class T_type>;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		_new.z = this->z + _rhs.z;
		return _new;
	}
	inline T_type operator-(const vector3D<T_type>& _rhs) {
		vector3D<class T_type> _new = new vector3D<class T_type>;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		_new.z = this->z - _rhs.z;
		return _new;
	}
};
template<class T_type> class vector2D {
	T_type x;
	T_type y;
	inline T_type operator+(const vector2D<T_type>& _rhs) {
		vector2D<class T_type> _new = new vector2D<class T_type>;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		return _new;
	}
	inline T_type operator-(const vector2D<T_type>& _rhs) {
		vector2D<class T_type> _new = new vector2D<class T_type>;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		return _new;
	}
};
template<class T_type> inline T_type dotproduct2D(vector2D<T_type> _v1, vector2D<T_type> _v2) {
	return _v1.x * _v2.x + _v1.y*_v2.y;
}
template<class T_type> inline T_type dotproduct3D(vector3D<T_type> _v1, vector3D<T_type> _v2) {
	return _v1.x * _v2.x + _v1.y*_v2.y + _v1.z * _v2.z;
}
template<class T_type> inline T_type dotproduct4D(vector4D<T_type> _v1, vector4D<T_type> _v2) {
	return _v1.w*_v2.w + _v1.x * _v2.x + _v1.y*_v2.y + _v1.z * _v2.z;
}
template<class T_type> inline vector2D<T_type> crossproduct2D(vector2D<T_type> _v1, vector2D<T_type> _v2) {
	vector2D<T_type> return_vec = new vector2D<T_type>;
	return_vec.x = _v1.x*_v2.y;
	return_vec.y = _v1.y*_v2.x;
	return return_vec;
}
template<class T_type> inline vector3D<T_type> crossproduct3D(vector3D<T_type> _v1, vector3D<T_type> _v2) {
	vector3D<T_type> return_vec = new vector3D<T_type>;
	return_vec.x = _v1.y*_v2.z - _v1.z*_v2.y;
	return_vec.y = _v1.z*_v2.x - _v1.x*_v2.z;
	return_vec.z = _v1.x*_v2.y - _v1.y*_v2.x;
	return return_vec;
}

typedef vector3D<uint64_t> vector3Dui64;
typedef vector3D<float> vector3Df;
typedef vector3D<double> vector3Dd;
typedef vector3D<int64_t> vector3Di64;