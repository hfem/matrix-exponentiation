#include "Matrix.h"

// default constructor
template<class T> Matrix<T>::Matrix(void) : values(nullptr), nRows(0), nColumns(0) { }

// initialized matrix constructor
// m < 2^16 and n < 2^16
template<class T> Matrix<T>::Matrix(const unsigned __int16 m, 
	                                const unsigned __int16 n, 
	                                vector<T>& newValues) {
	if (   newValues.empty() 
		|| (m * n) != newValues.size() ) {
		throw invalid_argument("Invalid Matrix Values\n");
	}
	
	nRows = m;
	nColumns = n;
	
	__int32 size = m * n;
	values = new T[size];
	for (__int32 i = 0; i < size; i++) {
		values[i] = newValues[i];
	}
}

// copy constructor
template<class T> Matrix<T>::Matrix(const Matrix<T>& copy) : nRows(copy.nRows), nColumns(copy.nColumns) {
	if (copy.values == nullptr) {
		values = nullptr;
	}
	else {
		__int32 size = copy.nRows * copy.nColumns;
		values = new T[size];

		for (__int32 i = 0; i < size; i++) {
			values[i] = copy.values[i];
		}
	}
}


// destructor
template<class T> Matrix<T>::~Matrix(void) {
	delete[] values;
}

// getter for nRows
template<class T> unsigned __int16 Matrix<T>::getNRows(void) {
	return nRows;
}

// getter for nColumns
template<class T> unsigned __int16 Matrix<T>::getNColumns(void) {
	return nColumns;
}

// getter for any element in the matrix
template<class T> T& Matrix<T>::get(unsigned __int16 row, unsigned __int16 column) {
	string comment;

	if ((row >= nRows) || (column >= nColumns)) {
		comment = "Matrix Element Does Not Exist.\n Invalid Matrix Access\n";
		throw invalid_argument(comment);
	}

	return values[row*nColumns + column];
}

// assignment operator
template<class T> Matrix<T>& Matrix<T>::operator=( Matrix<T> rhs) {
	swap(*this, rhs);

	return *this;
}

// (matrix x matrix) multiplication
// returns a new matrix with size m by n (lhs.nColumns by rhs.nRows)
template<class T> Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs) {
	string comment;

	if (lhs.nColumns != rhs.nRows) {
		comment = "LHS Columns != RHS Rows\n Invalid Matrix Multiplication\n";
		throw invalid_argument(comment);
	}
	if ((lhs.values == nullptr) || (rhs.values == nullptr)) {
		comment = "Unitialized Matrix\n Invalid Matrix Multiplication\n";
		throw invalid_argument(comment);
	}

	__int32 p = lhs.nColumns;           // == rhs.nRows
	__int32 m = lhs.nRows;
	__int32 n = rhs.nColumns;

	// multiplied values array
	vector<T> answer(m * n, T());   // w/initialized values (= 0 if T is int)

	for (__int32 i = 0; i < m; i++) {
		for (__int32 j = 0; j < n; j++) {
			//answer[i*n + j] = T();  
			for (__int32 k = 0; k < p; k++) {
				answer[i*n + j] += lhs.values[i*p + k] * rhs.values[k*n + j];
			}
		}
	}

	return Matrix<T>(m, n, answer);
}

// outputs to ostream and prints each matrix row on one line
// with two spaces in between each element
template<class T> ostream& operator<< (ostream& os, const Matrix<T>& matrix) {
	__int32 rows = matrix.nRows;
	__int32 columns = matrix.nColumns;

	os << rows << " x " << columns << " Matrix " << endl;

	for (__int32 i = 0; i < rows; i++) {
		for (__int32 j = 0; j < columns; j++) {
			os << matrix.values[i*columns + j] << "  ";
		}
		os << endl;
	}
	return os;
}

// swap function for assignment operator
template<class T> void swap(Matrix<T>& lhs, Matrix<T>& rhs) {
	swap(lhs.nColumns, rhs.nColumns);
	swap(lhs.nRows, rhs.nRows);
	swap(lhs.values, rhs.values);
}

using BigNum = unsigned __int64;
template class Matrix<BigNum>;
template Matrix<BigNum> operator* (const Matrix<BigNum>& lhs, const Matrix<BigNum>& rhs);
template ostream& operator<< (ostream& os, const Matrix<BigNum>& value);
template void swap(Matrix<BigNum>& lhs, Matrix<BigNum>& rhs);