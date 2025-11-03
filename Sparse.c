// name: Edison Kuo
// cruzID: edkuo
// assignment: pa4

// Sparse.c
// Main program for matrix operations on Sparse Matrices

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int n, a, b;
    int row, col;
    double value;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    // Read first line: n, a, b
    fscanf(in, "%d %d %d", &n, &a, &b);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Skip blank line
    fscanf(in, "\n");

    // Read a entries for matrix A
    for (int i = 0; i < a; i++) {
        fscanf(in, "%d %d %f", &row, &col, &value);
        changeEntry(A, row, col, value);
    }

    // Skip blank line
    fscanf(in, "\n");

    // Read b entries for matrix B
    for (int i = 0; i < b; i++) {
        fscanf(in, "%d %d %f", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    // Close input file
    fclose(in);

    fprintf(out, "A has %d non-zero entries:\n", numNonZero(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", numNonZero(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix scalarA = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, scalarA);
    fprintf(out, "\n");

    Matrix sumAB = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, sumAB);
    fprintf(out, "\n");

    Matrix sumAA = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, sumAA);
    fprintf(out, "\n");

    Matrix diffBA = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, diffBA);
    fprintf(out, "\n");

    Matrix diffAA = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, diffAA);
    fprintf(out, "\n");

    Matrix transposeA = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, transposeA);
    fprintf(out, "\n");

    Matrix productAB = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, productAB);
    fprintf(out, "\n");

    Matrix productBB = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, productBB);
    fprintf(out, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalarA);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transposeA);
    freeMatrix(&productAB);
    freeMatrix(&productBB);

    fclose(out);

    return EXIT_SUCCESS;
}