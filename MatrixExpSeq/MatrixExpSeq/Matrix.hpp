//
// Cardiff University | Computer Science
// Module:     CM3203 One Semester Project (40 Credits)
// Title:      Parallelisation of Matrix Exponentials in C++/CUDA for Quantum Control
// Date:       2016
//
// Author:     Peter Davison
// Supervisor: Dr. Frank C Langbein
// Moderator:  Dr. Irena Spasic
//

#ifndef matrix_h
#define matrix_h
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <math.h>

class Matrix {
private:
	// Variables
	std::vector<std::vector<double>> matrix;
	int numRows, numCols;
	bool initialised;
	// Internal Matrix Functions
	static Matrix* taylorMExp(Matrix* A, int k);
	static Matrix* padeMExp(Matrix* A, int k);
	static void PadeApproximantOfDegree(int m, Matrix* A);
	static std::vector<double> getPadeCoefficients(int m);
	static Matrix* diagonalMExp(Matrix* A);
	static Matrix* zeroMExp(Matrix* A);
public:
	// Constructors
	Matrix();
	Matrix(int inNumRowsCols);
	Matrix(int inNumRows, int inNumCols);
	Matrix(std::vector<std::vector<double>>);
	Matrix(const Matrix &obj);
	void init(int inNumRows, int inNumCols);
	// Matrix Operations
	static Matrix* add(Matrix* A, Matrix* B);
	static Matrix* add(Matrix* A, double x);
	static Matrix* sub(Matrix* A, Matrix* B);
	static Matrix* sub(Matrix* A, double x);
	static Matrix* mul(Matrix* A, Matrix* B);
	static Matrix* mul(double x, Matrix* A);
	static Matrix* div(Matrix* A, Matrix* B);
	static Matrix* div(double x, Matrix* A);
	static Matrix* inv(Matrix* A);
	static Matrix* pow(Matrix* A, int x);
	static Matrix* mExp(Matrix* A, char method = ' ', int k = -1);
	// Booleans
	const bool isInitialised();
	const bool isSquare();
	const bool isDiagonal();
	const bool isScalar();
	const bool isIdentity();
	const bool isZero();
	// Getters
	const double getCell(int x, int y);
	const int getNumRows();
	const int getNumCols();
	// Setters
	void setNumRows(int inNumRows);
	void setNumCols(int inNumCols);
	void setMatrix(std::vector<std::vector<double>> inMatrix);
	void setCell(int row, int col, double value);
	void setZero();
	void setIdentity();
	void setRandom(double min, double max);
};

// Operators
std::ostream& operator<< (std::ostream& stream, Matrix* A);

#endif