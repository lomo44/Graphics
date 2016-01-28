/*
 * matrix.h
 *
 *  Created on: Jan 28, 2016
 *      Author: c5lizhua
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <string>
#include <stdlib.h>

template<class T_type> class matrix3D {
public:
	matrix3D(T_type* _matrix);
	virtual ~matrix3D();
	inline T_type getXY(int x, int y);
private:
	T_type* m_matrix;
};

template<class T_type> void matrix3D<class T_type>::matrix3D(T_type* _matrix){
	m_matrix = _matrix;
}

template<class T_type> inline T_type matrix3D<class T_type>::getXY(int x, int y){
	if(m_matrix == NULL){
		return NULL;
	}
	else{
		return ms_matrix[3*(y-1)+(x-1)];
	}
}

template<class T_type> class matrix2D {
public:
	matrix2D(T_type* _matrix);
	virtual ~matrix2D();
	inline T_type getXY(int x, int y);
private:
	T_type* m_matrix;
};

template<class T_type> void matrix2D<class T_type>::matrix2D(T_type* _matrix){
	m_matrix = _matrix;
}

template<class T_type> inline T_type matrix2D<class T_type>::getXY(int x, int y){
	if(m_matrix == NULL){
		return NULL;
	}
	else{
		return ms_matrix[2*(y-1)+(x-1)];
	}
}


template<class T_type> class matrix4D {
public:
	matrix4D(T_type* _matrix);
	virtual ~matrix4D();
	inline T_type getXY(int x, int y);
private:
	T_type* m_matrix;
};

template<class T_type> void matrix4D<class T_type>::matrix4D(T_type* _matrix){
	m_matrix = _matrix;
}

template<class T_type> inline T_type matrix4D<class T_type>::getXY(int x, int y){
	if(m_matrix == NULL){
		return NULL;
	}
	else{
		return ms_matrix[4*(y-1)+(x-1)];
	}
}

#endif /* MATRIX_H_ */

