#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Forward Declarations
template <class T> class Matrix;
template <class T> Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs);
template <class T> ostream& operator<<(ostream& os, const Matrix<T>& value);
template <class T> void swap (Matrix<T>& lhs, Matrix<T>& rhs);

// Matrix Class declaration
template <class T>
class Matrix
{
private:
	T * values;       // row-major order TODO change pointer
	unsigned __int16 nRows;
	unsigned __int16 nColumns; 

public:
	Matrix<T>();
	Matrix<T>(const unsigned __int16 m, 
		      const unsigned __int16 n, 
		      vector<T>& newValues);
	Matrix<T>(const Matrix<T>& copy);
	~Matrix<T>();

	unsigned __int16 getNRows(void);
	unsigned __int16 getNColumns(void);
	//bool init(unsigned __int16 rows, __int32 columns, vector<T>& values); 
	T& get(unsigned __int16 row, unsigned __int16 column);

	Matrix<T>& operator= (Matrix<T> value);
	//Matrix<T>& operator* <> (const T &scalar, const Matrix<T> &matrixM);
	//Matrix<T>& operator*= <> (const Matrix<T> &rhs);

	//friend Matrix<T>& operator* <> (const Matrix<T> &lhs, const Matrix<T> &rhs);
	friend Matrix<T> operator* <> (const Matrix<T> &lhs, const Matrix<T> &rhs);
	friend ostream& operator<< <> (ostream& os, const Matrix<T>& value);
	friend void swap <> (Matrix<T>& lhs, Matrix<T>& rhs);
	//Matrix<T> operator+(Matrix<T> lhs, Matrix<T> rhs);

};
