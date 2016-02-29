
#ifndef MATRIX_H_
#define MATRIX_H_

enum eMatrixType{
	eRotationalX,
	eRotationalY,
	eRotationalZ,
	eTranslational,
	eIdentity,
	eNULL
};


class Vector;
class Matrix {
public:
	Matrix(unsigned int dim = 4);
	virtual ~Matrix();
	void loadRotational(eMatrixType _type, float angle);
	void loadTranslational(float x, float y, float z);
	void loadIdentity();
	Vector getColumn(int i);
	Vector getRow(int i);
	int getDimension();
	Matrix  operator* (const Matrix& rhs);
	Matrix&  operator*=(Matrix& rhs);
	float* f;
private:
	int d;
	eMatrixType _t;
};

#endif /* MATRIX_H_ */
