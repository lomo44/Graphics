/*Singel File For Graphic Library*/


#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <memory>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>


#include <queue>
#include <vector>
#include <string>
typedef double STD_P;

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

enum GeometricObjectType {
	Geo_Lines,
	Geo_Polygons,
};

/*Global Variable*/

class GeometricObject {
public:
	GeometricObject();
	virtual ~GeometricObject();
	virtual void scale3d(STD_P _x, STD_P _y, STD_P _z) = 0;
	virtual void rotate3d(STD_P _a, STD_P _b, STD_P _c);
	virtual void translate3d(STD_P _x, STD_P _y, STD_P _z);
	virtual void draw();
private:
	GeometricObjectType m_ObjectType;
	uint64_t m_ID;
	vector3D<STD_P> m_centerpoint;
	bool m_bIsVisiable;
};

class GeometricObjectRenderer {
public:
	void Render();
	void Reshape();
	void ClearStack();
private:
	std::queue<GeometricObject> m_drawstack;
};

class GeometricObjectFactory {
public:
	uint64_t createLine(STD_P _x, STD_P _y, STD_P _z);
private:
	std::vector<uint64_t> m_ObjectIDList;
};

struct WindowAttribute {
	int pos_x;
	int pos_y;
	int size_x;
	int size_y;
	std::string name;
};

class WindowsController {
public:
	WindowsController();
	virtual ~WindowsController();
	virtual void InitializeWindow() = 0;
	virtual int CreateAWindow(const WindowAttribute& _new) = 0;
};

class GLUTWindowsController : public WindowsController {
public:
	GLUTWindowsController();
	virtual ~GLUTWindowsController();
	void Initialize();
	int CreateAWindow(const WindowAttribute& _new);
private:
	GeometricObjectRenderer m_Renderer;
	std::vector<int> m_WindowList;
};


GLUTWindowsController* g_GlutWindowsController;


/*global variable*/

int main() {
	std::cout << "Hellow World" << std::endl;
	return 0;
}