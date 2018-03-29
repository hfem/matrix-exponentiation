#pragma once

#include <vector>
#include "Matrix.h"
using namespace std;
using BigNum = unsigned __int64;
//MIT license

class Fibonacci {
private:
	vector<Matrix<BigNum>> exponentiationMatrices; 
	BigNum firstValue;
	BigNum secondValue;

	void updateExpMatrices(int n);

public:
	Fibonacci();
	~Fibonacci();

	void setStartValues(BigNum first, BigNum second);
	BigNum findNthTerm(int n);
};
