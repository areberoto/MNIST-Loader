#include <iostream>
#include <ctime>
#include <iomanip>
#include <string>
#include "Matrix.h"

using std::cin;
using std::endl;
using std::cout;

//Constructor
Matrix::Matrix()
	: n{ 0 }, m{ 0 }, matrix{ nullptr } {
}

//Constructor with matrix size
Matrix::Matrix(int rows, int columns)
	: Matrix() {
	rows = (rows < 0) ? -rows : rows;
	columns = (columns < 0) ? -columns : columns;

	matrix = new double[rows * columns];
	if (NULL != matrix) {
		n = rows;
		m = columns;
		for (size_t i{ 0 }; i < n * m; i++)
			matrix[i] = 0.0;
	}
}

//Copy constructor using deep copy because of raw pointer
Matrix::Matrix(const Matrix& mtx)
	: Matrix() {

	matrix = new double[mtx.n * mtx.m];
	if (NULL != matrix) {
		n = mtx.n;
		m = mtx.m;
		for (size_t i{ 0 }; i < n * m; i++)
			matrix[i] = mtx.matrix[i];
	}
}

//Destructor
Matrix::~Matrix() {
	if (n != 0)
		delete[] matrix;
}

//Fill matrix by user
void Matrix::setMatrix() {
	cout << "\nPlease fill the matrix: " << endl;
	for (size_t i{ 0 }; i < n; i++) {
		for (size_t j{ 0 }; j < m; j++) {
			cout << '[' << i << "][" << j << "] = ";
			cin >> matrix[i * m + j];
		}
	}
}

//Fill matrix with random numbers
void Matrix::setMatrix(int low, int high) {
	if (low > high) {
		int temp{ low };
		low = high;
		high = temp;
	}
	for (size_t i{ 0 }; i < n * m; i++)
		matrix[i] = static_cast<double>(low) + (rand() % (high - low + 1));
}

//Add two matrices
Matrix Matrix::operator+(const Matrix& mtx) {
	if (m == mtx.m && n == mtx.n) {
		Matrix tempMatrix{ n, m };
		for (size_t i{ 0 }; i < n * m; i++)
			tempMatrix[i] = matrix[i] + mtx.matrix[i];
		return tempMatrix;
	}
	else {
		Matrix tempMatrix;
		cout << "\tMatrix dimensions must agree." << endl;
		return tempMatrix; //returns empty matrix
	}
}

//Add matrix with scalar
Matrix operator+(const Matrix& mtx, double scalar) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] + scalar;
	return tempMatrix;
}

//Add scalar with matrix
Matrix operator+(double scalar, const Matrix& mtx) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] + scalar;
	return tempMatrix;
}

//Substract two matrices
Matrix Matrix::operator-(const Matrix& mtx) {
	if (m == mtx.m && n == mtx.n) {
		Matrix tempMatrix{ n, m };
		for (size_t i{ 0 }; i < n * m; i++)
			tempMatrix[i] = matrix[i] - mtx.matrix[i];
		return tempMatrix;
	}
	else {
		Matrix tempMatrix;
		cout << "\tMatrix dimensions must agree." << endl;
		return tempMatrix; //returns empty matrix
	}
}

//Substract matrix with scalar
Matrix operator-(const Matrix& mtx, double scalar) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] - scalar;
	return tempMatrix;
}

//Substract scalar with matrix
Matrix operator-(double scalar, const Matrix& mtx) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] - scalar;
	return tempMatrix;
}

//Multiply two matrices
Matrix Matrix::operator*(const Matrix& mtx) {
	if (m == mtx.n) {
		Matrix tempMatrix{ n, mtx.m };
		double temp{ 0 };
		for (size_t k{ 0 }; k < n; k++) {
			for (size_t i{ 0 }; i < mtx.m; i++) {
				for (size_t j{ 0 }; j < mtx.n; j++)
					temp += matrix[k * m + j] * mtx.matrix[mtx.m * j + i];
				tempMatrix[k * mtx.m + i] = temp;
				temp = 0;
			}
		}
		return tempMatrix;
	}
	else {
		Matrix tempMatrix;
		cout << "\tMatrix dimensions must agree." << endl;
		return tempMatrix; //returns empty matrix
	}
}

//Multiply matrix with scalar
Matrix operator*(const Matrix& mtx, double scalar) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] * scalar;
	return tempMatrix;
}

//Multiply scalar with matrix
Matrix operator*(double scalar, const Matrix& mtx) {
	Matrix tempMatrix{ mtx.n, mtx.m };
	for (size_t i{ 0 }; i < mtx.n * mtx.m; i++)
		tempMatrix[i] = mtx.matrix[i] * scalar;
	return tempMatrix;
}

//Operator []
double& Matrix::operator[](int index) {
	if (index < 0)
		index = -index;
	if (index < n * m)
		return matrix[index];
	else
		throw std::string{ "\tIndex out of range!" };
}

//Trace operator
double Matrix::operator!() {
	if (n != m)
		throw std::string{ "\tError using trace().\n\tMatrix must be square." };
	else {
		double sum{ 0 };
		for (size_t i{ 0 }; i < n; i++)
			sum += matrix[n * i + i];
		return sum;
	}
}

//Print matrix
std::ostream& operator<<(std::ostream& os, const Matrix& mtx) {
	for (size_t i{ 0 }; i < mtx.n; i++) {
		for (size_t j{ 0 }; j < mtx.m; j++)
			os << std::setw(3) << mtx.matrix[i * mtx.m + j];
		os << endl;
	}
	return os;
}

//Assignment operator
Matrix& Matrix::operator=(const Matrix& rhs) {
	if (this == &rhs) {
		return *this;
	}
	else {
		delete[] matrix;
		n = 0;
		m = 0;
		matrix = new double[rhs.n * rhs.m];
		if (NULL != matrix) {
			n = rhs.n;
			m = rhs.m;
			for (size_t i{ 0 }; i < n * m; i++) {
				matrix[i] = rhs.matrix[i];
			}
			return *this;
		}
	}
}