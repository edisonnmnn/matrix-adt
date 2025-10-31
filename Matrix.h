// name: Edison Kuo
// cruzID: edkuo
// assignment: pa4

// Matrix.h
// Header file for Matrix ADT

#pragma once

#include <stdio.h>
#include <stdbool.h>

// Exported-Types -------------------------------------------------------------
typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------

// newMatrix()
// Returns a reference to a new n by n Matrix in the zero state.
Matrix newMatrix(int n);

// freeMatrix()
// Frees all heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM);

// Access functions -----------------------------------------------------------

// dimension()
// Returns the number of rows and columns of square Matrix M.
int dimension(Matrix M);

// numNonZero()
// Returns the number of non-zero elements in M.
int numNonZero(Matrix M);

// equals()
// Returns true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Resets M to the zero Matrix.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to be the value x.
// Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix representing A+B.
// pre: dimension(A)==dimension(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix representing A-B.
// pre: dimension(A)==dimension(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix representing AB
// pre: dimension(A)==dimension(B)
Matrix product(Matrix A, Matrix B);

// Other operations -----------------------------------------------------------

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows are
// not printed. Each non-zero row is represented as a line consisting of the
// row number, followed by a colon, a space, then a space separated list of pairs
// "(col, val)" giving the column numbers and non-zero values in that row. The
// double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);