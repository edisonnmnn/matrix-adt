// name: Edison Kuo
// cruzID: edkuo
// assignment: pa4

// Matrix.c
// Implementation of Matrix ADT

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "List.h"
#include "Matrix.h"

// private structs, functions, and constants ----------------------------------

typedef struct Entry {
    int column;
    double value;
} Entry;

typedef struct MatrixObj {
    List* row;
    int size;
    int nnz; // number of nonzero elements
} MatrixObj;

Entry* newEntry(int column, double value) {
    Entry *E;
    E = malloc(sizeof(Entry));
    assert(E != NULL);
    E->column = column;
    E->value = value;
    return E;
}

int dot(List P, List Q); 

// Constructors-Destructors ---------------------------------------------------

// newMatrix()
// Returns a reference to a new n by n Matrix in the zero state.
Matrix newMatrix(int n) {
    Matrix M;

    M = malloc(sizeof(MatrixObj));
    assert (M != NULL);

    // Rows are pointer to an array of pointers to ListObj
    M->row = calloc(n + 1, sizeof(List));
    assert(M->row != NULL);

    for (int i = 1; i <= n; i++) {
        M->row[i] = newList(); // List remains empty because entries are zero
    }

    M->size = n;
    M->nnz = 0;
    return M;
}


// freeMatrix()
// Frees all heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= ((*pM)->size); i++ ){
            freeList(&((*pM)->row[i]));
        }

        free((*pM)->row);
        free(*pM);
        *pM = NULL;
    }
}

// Access functions -----------------------------------------------------------

// dimension()
// Returns the number of rows and columns of square Matrix M.
int dimension(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: dimension(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    return (M->size);
}

// numNonZero()
// Returns the number of non-zero elements in M.
int numNonZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: numNonZero(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    return (M->nnz);
}

// equals()
// Returns true if matrices A and B are equal, false otherwise.
bool equals(Matrix A, Matrix B) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: equals(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "Matrix Error: equals(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if ((dimension(A) != dimension(B)) || (numNonZero(A) != numNonZero(B))) {
        return false;
    }

    // TODO: Recheck this after creation of non-zero matrices
    for (int i = 1; i <= dimension(A); i++) {
        List list_A = A->row[i];
        List list_B = B->row[i];

        if (length(list_A) != length(list_B)) {
            return false;
        }

        moveFront(list_B);
        for (moveFront(list_A); position(list_A) >= 0; moveNext(list_A)) {
            Entry* entry_A = (get(list_A));
            Entry* entry_B = (get(list_B));

            if (((entry_A->column) != (entry_B->column)) || 
            ((entry_A->value) != (entry_B->value))) {
                return false;
            }

            moveNext(list_B);
        }
    }

    return true;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Resets M to the zero Matrix.
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: makeZero(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= dimension(M); i++) {
        freeList(&(M->row[i]));
    }

}

// changeEntry()
// Changes the ith row, jth column of M to be the value x.
// Pre: 1<=i<=dimension(M), 1<=j<=dimension(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: changeEntry(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (i < 1 || i > dimension(M)) {
        fprintf(stderr, "Matrix Error: changeEntry(): Row %d is out of bounds: 1<=i<=dimension(M)\n ", i);
    }

    if (j < 1 || j > dimension(M)) {
         fprintf(stderr, "Matrix Error: changeEntry(): Column %d is out of bounds: 1<=j<=dimension(M)\n ", j);       
    }
    
    if (!(isEmptyList(M->row[i]))) {
        for (moveFront(M->row[i]); position(M->row[i]) <= 0; moveNext(M->row[i])) {
            Entry *E = get(M->row[i]);
            if (E->column > j) {
                if (!(x == 0)) {
                    Entry* newElement = newEntry(j, x);
                    insertBefore(M->row[i], newElement);
                    M->nnz++;
                    return; // C3: (i, j) = 0, x != 0. insert element
                } else {
                    return; // C1: (i, j) = 0, x = 0: do nothing 
                }
            } else if (E->column == j) {
                if (!(x == 0)) {
                    E->value = x;
                    return; // C2: (i, j) != 0, x = 0, delete element
                } else {
                    delete(M->row[i]);
                    M->nnz--;
                    return; // C4: (i, j) != 0, x != 0, overwrite element
                }
            }
        }
    }
    // Append to end of row if position not found
    if (!(x == 0)) {
        Entry* newElement = newEntry(j, x);
        append(M->row[i], newElement);
        return;
    } else {
        return;
    }

}

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
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: printMatrix(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    // row: (col, val)
    for (int i = 1; i <= dimension(M); i++) {
        List list_M = (M->row[i]);
        if (!isEmptyList(list_M)) {
            fprintf(out, "%d: ", i);   
            for (moveFront(list_M); position(list_M) >= 0; moveNext(list_M)) {
                Entry *E = get(list_M);
                fprintf(out, "(%d, %f) ", E->column, E->value);
            }

            fprintf(out, "\n");
        }
    }
}