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

double dot(List P, List Q) {
    double sum = 0;

    moveFront(P);
    moveFront(Q);
    while (position(P) >= 0 && position(Q) >= 0) {
        // compare P and Q columns
        Entry *entry_P = get(P);
        Entry *entry_Q = get(Q);
        int column_P = entry_P->column;
        int column_Q = entry_Q->column;

        if (column_P > column_Q) {
            moveNext(Q);
        } else if (column_P < column_Q) {
            moveNext(P);
        } else {
            sum += (entry_P->value * entry_Q->value);
            moveNext(Q);
            moveNext(P);
        }
    }

    return sum;
}

List vector_sum(List P, List Q) {
    List L = newList();
    moveFront(P);
    moveFront(Q);

    while (position(P) >= 0 && position(Q) >= 0) {
        Entry *entry_P = get(P);
        Entry *entry_Q = get(Q);

        if (entry_P->column < entry_Q->column) {
            append(L, newEntry(entry_P->column, entry_P->value));
            moveNext(P);
        } 
        else if (entry_Q->column < entry_P->column) {
            append(L, newEntry(entry_Q->column, entry_Q->value));
            moveNext(Q);
        } 
        else {
            double sumVal = entry_P->value + entry_Q->value;
            if (sumVal != 0)
                append(L, newEntry(entry_P->column, sumVal));
            moveNext(P);
            moveNext(Q);
        }
    }

    while (position(P) >= 0) {
        Entry *entry_P = get(P);
        append(L, newEntry(entry_P->column, entry_P->value));
        moveNext(P);
    }

    while (position(Q) >= 0) {
        Entry *entry_Q = get(Q);
        append(L, newEntry(entry_Q->column, entry_Q->value));
        moveNext(Q);
    }

    return L;
}


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
            List curr = ((*pM)->row[i]);
            moveFront(curr);
            while(position(curr) >= 0) {
                Entry *E = get(curr);
                free(E);
                moveNext(curr);
            }
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
        M->row[i] = newList();
    }

    M->nnz = 0;
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
        exit(EXIT_FAILURE);
    }

    if (j < 1 || j > dimension(M)) {
         fprintf(stderr, "Matrix Error: changeEntry(): Column %d is out of bounds: 1<=j<=dimension(M)\n ", j);   
         exit(EXIT_FAILURE);    
    }
    
    if (!(isEmptyList(M->row[i]))) {
        for (moveFront(M->row[i]); position(M->row[i]) >= 0; moveNext(M->row[i])) {
            Entry *E = get(M->row[i]);
            if (E->column > j) {
                if (!(x == 0)) {
                    Entry* newElement = newEntry(j, x);
                    insertBefore(M->row[i], newElement);
                    M->nnz++;
                } 
                return;
            } 
            if (E->column == j) {
                if (!(x == 0)) {
                    E->value = x;
                    return; // C2: (i, j) != 0, x = 0, delete element
                } else {
                    free(E);
                    delete(M->row[i]);
                    M->nnz--;
                }
                return;
            }
        }
    }
    // Append to end of row if position not found
    if (x != 0) {
        Entry* newElement = newEntry(j, x);
        append(M->row[i], newElement);
        M->nnz++;
    }

}

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix having the same entries as A.
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: copy(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix B = newMatrix(dimension(A));
    B->size = dimension(A);
    B->nnz = numNonZero(A);

    for (int i = 1; i <= dimension(A); i++) {
        if (!(isEmptyList(A->row[i]))) {
            List list_A = A->row[i];
            for (moveFront(list_A); position(list_A) >= 0; moveNext(list_A)) {
                Entry *entry_A = get(list_A);
                Entry *entry_B = newEntry(entry_A->column, entry_A->value);
                append(B->row[i], entry_B);
            }
        }
    }

    return B;
}

// transpose()
// Returns a reference to a new Matrix representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: transpose(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(dimension(A));
    B->size = dimension(A);
    B->nnz = numNonZero(A);

    for (int i = 1; i <= dimension(A); i++) {
        if (!(isEmptyList(A->row[i]))) {
            List list_A = A->row[i];
            for (moveFront(list_A); position(list_A) >= 0; moveNext(list_A)) {
                Entry *entry_A = get(list_A);
                Entry *entry_B = newEntry(i, entry_A->value);
                append(B->row[entry_A->column], entry_B);
            }
        }
    }

    return B;
}

// scalarMult()
// Returns a reference to a new Matrix representing xA.
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: scalarMult(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix B = newMatrix(dimension(A));

    for (int i = 1; i <= dimension(A); i++) {
        if (!(isEmptyList(A->row[i]))) {
            List list_A = A->row[i];
            for (moveFront(list_A); position(list_A) >= 0; moveNext(list_A)) {
                Entry *entry_A = get(list_A);
                double scaled_val = entry_A->value * x;
                if (scaled_val != 0) {
                    Entry *entry_B = newEntry(entry_A->column, scaled_val);
                    append(B->row[i], entry_B);
                    B->nnz++;
                }
            }
        }
    }

    return B;
}

// sum()
// Returns a reference to a new Matrix representing A+B.
// pre: dimension(A)==dimension(B)
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: sum(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "Matrix Error: sum(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: sum(): Dimension A does not match Dimension B: both matrices must be of same dimension\n");
        exit(EXIT_FAILURE);
    }

    // Special case: if A and B are the same matrix, return 2*A
    if (A == B) {
        return scalarMult(2.0, A);
    }

    Matrix AB = newMatrix(dimension(A));
    
    for (int i = 1; i <= dimension(A); i++) {
        if (!(isEmptyList(A->row[i])) || !(isEmptyList(B->row[i]))) {
            freeList(&(AB->row[i]));
            AB->row[i] = vector_sum(A->row[i], B->row[i]);
            AB->nnz += length(AB->row[i]);
        }
    }

    return AB;
}

// diff()
// Returns a reference to a new Matrix representing A-B.
// pre: dimension(A)==dimension(B)
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: diff(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "Matrix Error: diff(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: diff(): Dimension A does not match Dimension B: both matrices must be of same dimension\n");
        exit(EXIT_FAILURE);
    }

    Matrix neg_B = scalarMult(-1, B);
    Matrix result = sum(A, neg_B);
    freeMatrix(&neg_B);  
    return result;
}

// product()
// Returns a reference to a new Matrix representing AB
// pre: dimension(A)==dimension(B)
Matrix product(Matrix A, Matrix B) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: product(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (B == NULL) {
        fprintf(stderr, "Matrix Error: product(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    if (dimension(A) != dimension(B)) {
        fprintf(stderr, "Matrix Error: product(): Dimension A does not match Dimension B: both matrices must be of same dimension\n");
    }

    Matrix AB = newMatrix(dimension(A));
    Matrix B_transpose = transpose(B);
    
    for (int i = 1; i <= dimension(A); i++) {
        if (!(isEmptyList(A->row[i]))) {
            for (int j = 1; j <= dimension(A); j++) {
                if (!isEmptyList(B_transpose->row[j])) {
                    Entry *dot_entry = newEntry(j, dot(A->row[i], B_transpose->row[j]));
                    if (dot_entry->value != 0) {
                        append(AB->row[i], dot_entry);
                        AB->nnz++;
                    } else {
                        free(dot_entry);
                    }
                }
            }
        }
    }

    freeMatrix(&B_transpose);
    return AB;
}

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
                fprintf(out, "(%d, %.1f) ", E->column, E->value);
            }

            fprintf(out, "\n");
        }
    }
}

// Test function for printMatrix to stdout
void printStdoutMatrix(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: printMatrix(): NULL Matrix Reference\n");
        exit(EXIT_FAILURE);
    }

    // row: (col, val)
    for (int i = 1; i <= dimension(M); i++) {
        List list_M = (M->row[i]);
        if (!isEmptyList(list_M)) {
            fprintf(stdout, "%d: ", i);   
            for (moveFront(list_M); position(list_M) >= 0; moveNext(list_M)) {
                Entry *E = get(list_M);
                fprintf(stdout, "(%d, %.1f) ", E->column, E->value);
            }

            fprintf(stdout, "\n");
        }
    }
}