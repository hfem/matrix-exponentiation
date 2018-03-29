#include "Fibonacci.h"
#include "Matrix.h"
#include <iostream>
using namespace std;

int main(int c, char* argv[]) {
	Fibonacci Solver;
	BigNum f1, f2, fibonacci;
	int n;
	bool done = false;
	char y;

	while (!done) {
		cout << "Please enter first two numbers in Fibonacci sequence. \n";
		cout << "# # : ";
		cin >> skipws >> dec >> f1 >> f2;
		Solver.setStartValues(f1, f2);

		cout << "Which term would you like to find? \n";
		cout << "# : ";
		cin >> skipws >> dec >> n;
		// does not currently check for overflow
		fibonacci = Solver.findNthTerm(n);
		
		cout << "Fibonacci Sequence: \n";
		cout << f1 << ", " << f2 << ", ... , " << fibonacci << endl;

		cout << "Would you like to find another? \n";
		cout << "y|n : ";
		cin >> skipws >> y;
		(tolower(y) == 'y') ? done = false : done = true;		
	}

	return 0;
}


// [ 1 1   initiializes the list of matrix exponentiations with this matrix
//   1 0]   which is the root for how we will calculate all the others
Fibonacci::Fibonacci() {
	vector<BigNum> initial{ 1, 1, 1, 0 };
	exponentiationMatrices.push_back(Matrix<BigNum>(2, 2, initial));
}

Fibonacci::~Fibonacci() {

}

// sets the first two values of the Fibonacci Sequence
void Fibonacci::setStartValues(BigNum first, BigNum second) {
	firstValue = first;
	secondValue = second;
}

// updates the list of exponentation matrices if finding the Nth term
// needs more exponentiation matrices than currently computed
// n = log of N
// if n >  size : adds exponentation matrices until size = n
//    n <= size : does nothing
void Fibonacci::updateExpMatrices(int n) {
	Matrix<BigNum> last, next;
	n = n + 1;     // N takes (logN + 1) bits to represent
	
	while (n > exponentiationMatrices.size()) {
		last = exponentiationMatrices.back();
		next = last * last;
		exponentiationMatrices.push_back(next);
	}

	return;
}


// calculates the Nth term of this Fibonacci Sequence
BigNum Fibonacci::findNthTerm(int n) {
	if (n <= 0) { return firstValue; }
	if (n == 1) { return secondValue; }

	int logn = (int)(log(n)/log(2));  // log of n with base 2, w/o decimal
	updateExpMatrices(logn);

	vector<BigNum> startValues{ secondValue, firstValue};
	Matrix<BigNum> firstTerms(2, 1, startValues);

	vector<BigNum> identity{ 1, 0, 0, 1 }; // identity matrix 
	Matrix<BigNum> binaryExp(2, 2, identity);

	for (int i = 0, check = 1; i <= logn; i++) {
		if (check & n) {    // if this bit is set, multiply w/that matrix
			binaryExp = binaryExp * exponentiationMatrices[i]; 
		}
		check <<= 1;
	}
	
	Matrix<BigNum> results = binaryExp * firstTerms;

	return results.get(1, 0);
}
