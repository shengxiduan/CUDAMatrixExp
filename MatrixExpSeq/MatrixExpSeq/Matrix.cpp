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

#include "Matrix.hpp"

// Constructors

Matrix::Matrix() {
	initialised = false;
}

Matrix::Matrix(int inNumRows, int inNumCols) {
	init(inNumRows, inNumCols);
}

Matrix::Matrix(std::vector<std::vector<int>> inMatrix) {
	init((int) inMatrix.size(), (int) inMatrix[0].size());
	setMatrix(inMatrix);
}

Matrix::Matrix(const Matrix &obj) {
	// COPY CONSTRUCTOR NOT COMPLETE
	matrix = obj.matrix;
	numRows = obj.numRows;
	numCols = obj.numCols;
	initialised = obj.initialised;
}

void Matrix::init(int inNumRows, int inNumCols) {
	// Set height/width of matrix
	numRows = inNumRows;
	numCols = inNumCols;
	matrix.resize(numRows);
	for (int i = 0; i < numRows; i++) {
		matrix[i].resize(numCols);
	}
	initialised = true;	
	// Set values to zero
	setZero();
}

// Matrix Functions

Matrix Matrix::add(Matrix matrixB) {
	if (initialised && matrixB.initialised) {
		if (numRows == matrixB.getNumRows() && numCols == matrixB.getNumCols()) {
			Matrix matrixC(numRows, numCols);
			for (int c1 = 0; c1 < numRows; c1++) {
				for (int c2 = 0; c2 < numCols; c2++) {
					matrixC.matrix[c1][c2] = matrix[c1][c2] + matrixB.matrix[c1][c2];
				}
			}
			return matrixC;
		}
		else {
			// Error! Cannot add these matrices
			throw (201);
		}
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

Matrix Matrix::mul(Matrix matrixB) {
	if (initialised && matrixB.initialised) {
		if (numCols == matrixB.getNumRows()) {
			Matrix matrixC(numRows, matrixB.getNumCols());
			int cell;
			for (int c1 = 0; c1 < numRows; c1++) {
				for (int c2 = 0; c2 < matrixB.getNumCols(); c2++) {
					cell = 0;
					for (int c3 = 0; c3 < matrixB.getNumRows(); c3++) {
						cell += matrix[c1][c3] * matrixB.matrix[c3][c2];
					}
					matrixC.matrix[c1][c2] = cell;
				}
			}
			return matrixC;
		}
		else {
			// Error! Cannot multiply these matrices together
			throw (202);
		}
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

Matrix Matrix::mul(double m) {
	if (initialised) {
		Matrix matrixB(numRows, numCols);
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				matrixB.matrix[c1][c2] = matrix[c1][c2] * m;
			}
		}
		return matrixB;
	} else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

Matrix Matrix::pow(int p) {
	if (initialised) {
		Matrix matrixB = *this;
		for (int c1 = 0; c1 < p - 1; c1++) {
			matrixB = matrixB.mul(matrix);
		}
		return matrixB;
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

Matrix Matrix::exp(int k) {
	if (initialised) {
		Matrix A(numRows, numCols);
		for (int n = 1; n <= k; n++) {
			// Use precalculated factorials here
			// Temporary code to calculate on the go
			int nfact = 1;
			for (int c1 = 1; c1 <= n; c1++) {
				nfact *= c1;
			}
			// End of temporary code
			A.add(pow(n).mul(1 / nfact));
			printf(A.toString().c_str());
		}
		return A;
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

void Matrix::setZero() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				matrix[c1][c2] = 0;
			}
		}
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

void Matrix::setIdentity() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				if (c1 == c2) {
					matrix[c1][c2] = 1;
				}
				else {
					matrix[c1][c2] = 0;
				}
			}
		}
	}
	else {
		// Error! Cannot perform matrix operations before initialisation
		throw (101);
	}
}

// Booleans

bool Matrix::isSquare() {
	if (initialised) {
		if (numCols == numRows) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		// Error! Cannot determine if matrix is square before initialisation
		throw (105);
	}
}

bool Matrix::isDiagonal() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				if (c1 != c2 && matrix[c1][c2] != 0) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		// Error! Cannot determine if matrix is diagonal before initialisation
		throw (106);
	}
}

bool Matrix::isScalar() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				if ((c1 != c2 && matrix[c1][c2] != 0) || (c1 == c2 && matrix[c1][c2] != matrix[0][0])) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		// Error! Cannot determine if matrix is scalar before initialisation
		throw (107);
	}
}

bool Matrix::isIdentity() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				if ((c1 != c2 && matrix[c1][c2] != 0) || (c1 == c2 && matrix[c1][c2] != 1)) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		// Error! Cannot determine if matrix is an identity matrix before initialisation
		throw (108);
	}
}

bool Matrix::isZero() {
	if (initialised) {
		for (int c1 = 0; c1 < numRows; c1++) {
			for (int c2 = 0; c2 < numCols; c2++) {
				if (matrix[c1][c2] != 0) {
					return false;
				}
			}
		}
		return true;
	}
	else {
		// Error! Cannot determine if matrix is a zero matrix before initialisation
		throw (109);
	}
}

// Getters

int Matrix::getNumRows() {
	if (initialised) {
		return numRows;
	}
	else {
		// Error! Cannot determine number of rows in matrix before initialisation
		throw (103);
	}
}

int Matrix::getNumCols() {
	if (initialised) {
		return numCols;
	}
	else {
		// Error! Cannot determine number of columns in matrix before initialisation
		throw (104);
	}
}

// Setters

void Matrix::setMatrix(std::vector<std::vector<int>> inMatrix) {
	matrix = inMatrix;
}

void Matrix::setCell(int row, int col, int value) {
	matrix[row][col] = value;
}

// Output

std::string Matrix::toString() {
	if (initialised) {
		std::string output("");
		for (int c1 = 0; c1 < numRows; c1++) {
			output.append("|");
			for (int c2 = 0; c2 < numCols; c2++) {
				if (matrix[c1][c2] >= 0) {
					output.append(" ");
					output.append(std::to_string(matrix[c1][c2]));
				}
				else {
					output.append(" -");
				}
			}
			output.append(" |\n");
		}
		return output;
	}
	else {
		// Error! Cannot print matrix before initialisation
		throw (102);
	}
}