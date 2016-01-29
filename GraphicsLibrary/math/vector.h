/*
 * vector.h
 *
 *  Created on: Jan 28, 2016
 *      Author: c5lizhua
 */

#ifndef VECTOR_H_
#define VECTOR_H_

template<class T_type> class vector4D{
	T_type w;
	T_type x;
	T_type y;
	T_type z;
	inline vector4D<class T_type> operator+(const vector4D<class T_type>& _rhs){
		vector4D<class T_type> _new = new vector4D<class T_type>;
		_new.w = this->w + _rhs.w;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		_new.z = this->z + _rhs.z;
		return _new;
	}
	inline vector4D<class T_type> operator-(const vector4D<class T_type>& _rhs){
		vector4D<class T_type> _new = new vector4D<class T_type>;
		_new.w = this->w - _rhs.w;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		_new.z = this->z - _rhs.z;
		return _new;
	}
};

template<class T_type> class vector3D{
	T_type x;
	T_type y;
	T_type z;
	inline vector3D<class T_type> operator+(const vector3D<class T_type>& _rhs){
		vector3D<class T_type> _new = new vector3D<class T_type>;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		_new.z = this->z + _rhs.z;
		return _new;
	}
	inline vector3D<class T_type> operator-(const vector3D<class T_type>& _rhs){
		vector3D<class T_type> _new = new vector3D<class T_type>;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		_new.z = this->z - _rhs.z;
		return _new;
	}
};

template<class T_type> class vector2D{
	T_type x;
	T_type y;
	inline vector2D<class T_type> operator+(const vector2D<class T_type>& _rhs){
		vector2D<class T_type> _new = new vector2D<class T_type>;
		_new.x = this->x + _rhs.x;
		_new.y = this->y + _rhs.y;
		return _new;
	}
	inline vector2D<class T_type> operator-(const vector2D<class T_type>& _rhs){
		vector2D<class T_type> _new = new vector2D<class T_type>;
		_new.x = this->x - _rhs.x;
		_new.y = this->y - _rhs.y;
		return _new;
	}
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
template<class T_type> inline vector2D<T_type> crossproduct2D(vector2D<T_type> _v1, vector2D<T_type> _v2){
	vector2D<T_type> return_vec = new vector2D<T_type>;
	return_vec.x = _v1.x*_v2.y;
	return_vec.y = _v1.y*_v2.x;
	return return_vec;
}
template<class T_type> inline vector3D<T_type> crossproduct(vector3D<T_type> _v1, vector3D<T_type> _v2){
	vector3D<T_type> return_vec = new vector3D<T_type>;
	return_vec.x = _v1.y*_v2.z-_v1.z*_v2.y;
	return_vec.y = _v1.z*_v2.x-_v1.x*_v2.z;
	return_vec.z = _v1.x*_v2.y-_v1.y*_v2.x;
	return return_vec;
}


#endif /* VECTOR_H_ */
