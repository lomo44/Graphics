/*Singel File For Graphic Library*/


#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <memory>

template<class T_type> class matrix3D {
public:
	matrix3D(T_type* _matrix) {
		m_matrix = _matrix;
	}
	matrix3D() {
		m_matrix = new T_type[9];
	}
	virtual ~matrix3D();
	inline T_type getXY(int x, int y) {
		if (m_matrix == NULL) {
			return NULL;
		}
		else {
			return m_matrix[3 * (y - 1) + (x - 1)];
		}
	}
	inline  T_type operator*(const matrix3D& _rhs) {
		matrix3D<class T_type> return_m;
		return_m.m_matrix[0] = this->m_matrix[0] * _rhs.m_matrix[0] + this->m_matrix[1] * _rhs.m_matrix[3] + this->m_matrix[2] * _rhs.m_matrix[6];
		return_m.m_matrix[1] = this->m_matrix[0] * _rhs.m_matrix[1] + this->m_matrix[1] * _rhs.m_matrix[4] + this->m_matrix[2] * _rhs.m_matrix[7];
		return_m.m_matrix[2] = this->m_matrix[0] * _rhs.m_matrix[2] + this->m_matrix[1] * _rhs.m_matrix[5] + this->m_matrix[2] * _rhs.m_matrix[8];
		return_m.m_matrix[3] = this->m_matrix[3] * _rhs.m_matrix[0] + this->m_matrix[4] * _rhs.m_matrix[3] + this->m_matrix[5] * _rhs.m_matrix[6];
		return_m.m_matrix[4] = this->m_matrix[3] * _rhs.m_matrix[1] + this->m_matrix[4] * _rhs.m_matrix[4] + this->m_matrix[5] * _rhs.m_matrix[7];
		return_m.m_matrix[5] = this->m_matrix[3] * _rhs.m_matrix[2] + this->m_matrix[4] * _rhs.m_matrix[5] + this->m_matrix[5] * _rhs.m_matrix[8];
		return_m.m_matrix[6] = this->m_matrix[6] * _rhs.m_matrix[0] + this->m_matrix[7] * _rhs.m_matrix[3] + this->m_matrix[8] * _rhs.m_matrix[6];
		return_m.m_matrix[7] = this->m_matrix[6] * _rhs.m_matrix[1] + this->m_matrix[7] * _rhs.m_matrix[4] + this->m_matrix[8] * _rhs.m_matrix[7];
		return_m.m_matrix[8] = this->m_matrix[6] * _rhs.m_matrix[2] + this->m_matrix[7] * _rhs.m_matrix[5] + this->m_matrix[8] * _rhs.m_matrix[8];
		return return_m;
	}

public:
	T_type* m_matrix;
};
template<class T_type> class matrix2D {
public:
	matrix2D(T_type* _matrix) {
		m_matrix = _matrix;
	}
	virtual ~matrix2D();
	inline T_type getXY(int x, int y) {
		if (m_matrix == NULL) {
			return NULL;
		}
		else {
			return m_matrix[2 * (y - 1) + (x - 1)];
		}
	}
	inline T_type operator*(const matrix2D& _rhs) {
		matrix2D<class T_type> return_m;
		return_m.m_matrix[0] = this->m_matrix[0] * _rhs.m_matrix[0] + this->m_matrix[1] * _rhs.m_matrix[2];
		return_m.m_matrix[0] = this->m_matrix[0] * _rhs.m_matrix[2] + this->m_matrix[1] * _rhs.m_matrix[3];
		return_m.m_matrix[0] = this->m_matrix[2] * _rhs.m_matrix[0] + this->m_matrix[3] * _rhs.m_matrix[2];
		return_m.m_matrix[0] = this->m_matrix[2] * _rhs.m_matrix[0] + this->m_matrix[3] * _rhs.m_matrix[2];
		return return_m;
	}
public:
	T_type* m_matrix;
};
template<class T_type> class matrix4D {
public:
	matrix4D(T_type* _matrix) {
		m_matrix = _matrix;
	}
	virtual ~matrix4D() {
		delete m_matrix;
	}
	inline T_type getXY(int x, int y) {
		if (m_matrix == NULL) {
			return NULL;
		}
		else {
			return ms_matrix[4 * (y - 1) + (x - 1)];
		}
	}
	T_type* m_matrix;
};
template<class T_type> inline matrix3D<T_type> getHomogeneousTranslationMatrix(T_type _x, T_type _y) {
	T_type* matrix = new T_type[9];
	matrix[0] = 1;
	matrix[1] = 0;
	matrix[2] = _x;
	matrix[3] = 0;
	matrix[4] = 1;
	matrix[5] = _y;
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[9] = 1;
	return new matrix3D<T_type>(matrix);
}
template<class T_type> inline matrix3D<T_type> getHomogeneousRotationalMatrix(T_type _angle) {
	T_type* matrix = new T_type[9];
	matrix[0] = std::cos(_angle);
	matrix[1] = std::sin(_angle);
	matrix[2] = 0;
	matrix[3] = -matrix[1];
	matrix[4] = matrix[0];
	matrix[5] = 0;
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[8] = 1;
}
template<class T_type> inline matrix3D<T_type> getHomogeneousScallingMatrix(T_type _power) {
	T_type* matrix = new T_type[9];
	matrix[0] = _power;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 0;
	matrix[4] = _power;
	matrix[5] = 0;
	matrix[6] = 0;
	matrix[7] = 0;
	matrix[8] = 1;
}



class GeometricObject {

};


int main() {
	std::cout << "w" << std::endl;
	return 0;
}


