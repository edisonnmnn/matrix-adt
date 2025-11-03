// name: Edison Kuo
// cruzID: edkuo
// assignment: pa4

// MatrixTest.c
// Test client for Matrix ADT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {

    printf("MATRIX TEST:\n\n");

    // Initializing a new matrix and freeing
    Matrix I = newMatrix(5);
    freeMatrix(&I);

    // check equals function on zero matrices
    Matrix zero_A = newMatrix(10);
    Matrix zero_B = newMatrix(10);
    printf("Matrix A equals Matrix B: %d. Should return 1.\n", equals(zero_A, zero_B));

    Matrix zero_C = newMatrix(20);
    Matrix zero_D = newMatrix(12);
    printf("Matrix C equals Matrix D: %d. Should return 0.\n", equals(zero_C, zero_D));
    printf("Matrix A equals Matrix C: %d. Should return 0.\n", equals(zero_A, zero_C));

    freeMatrix(&zero_A);
    freeMatrix(&zero_B);
    freeMatrix(&zero_C);
    freeMatrix(&zero_D);

    // basic comparisons and printing

    Matrix X = newMatrix(5);
    changeEntry(X, 1, 1, 20.1);
    printStdoutMatrix(X);
    changeEntry(X, 1, 2, 20.3);
    printStdoutMatrix(X);
    changeEntry(X, 3, 5, 15.2);
    printf("\n");
    printStdoutMatrix(X);
    changeEntry(X, 1, 1, 0);
    printf("\n");
    printStdoutMatrix(X);
    printf("\n");

    Matrix Y = newMatrix(5);
    changeEntry(Y, 1, 2, 20.3);
    changeEntry(Y, 3, 5, 15.2);
    printStdoutMatrix(Y);
    printf("\n\n");

    printf("dimension X: %d. dimension Y: %d. nnz X: %d. nnz Y: %d\n", dimension(X), dimension(Y), numNonZero(X), numNonZero(Y));
    printf("Matrix X equals Matrix Y: %d. Should return 1.\n\n", equals(X, Y));

    changeEntry(X, 3, 3, 2.2);
    changeEntry(X, 3, 4, 55.2);
    changeEntry(X, 3, 5, 12.2);
    changeEntry(X, 3, 1, 0);
    printStdoutMatrix(X);
    printf("\n\n");

    // Testing copy()
    Matrix X_copy = copy(X);
    printf("Matrix X:\n");
    printStdoutMatrix(X);
    printf("\n");
    printf("Matrix Copy of X:\n");
    printStdoutMatrix(X_copy);
    printf("\n");

    // Testing transpose()
    Matrix X_transpose = transpose(X);
    printf("Matrix Transpose of X:\n");
    printStdoutMatrix(X_transpose);
    printf("\n");
    
    // Testing scalarMult()
    Matrix X_scalarMult = scalarMult(1.5, X);
    printf("Matrix Scalar multiplied by 2.5:\n");
    printStdoutMatrix(X_scalarMult);
    printf("\n\n");

    // Testing product()
    Matrix A = copy(X);
    Matrix B = copy(X);
    printf("Matrix A:\n");
    printStdoutMatrix(A);
    printf("Matrix B:\n");
    printStdoutMatrix(B);
    Matrix B_trans = transpose(B);
    printf("Matrix B TRANSPOSED:\n");
    printStdoutMatrix(B_trans);
    printf("\n\n");
    Matrix AB = product(A, B);
    printf("Matrix Product between A and B:\n");
    printStdoutMatrix(AB);
    printf("\n");

    // Test product() from MatrixClient.c
    printf("MatrixClient Test\n");
    int n=100000;
    Matrix C = newMatrix(n);
    Matrix D = newMatrix(n);

    changeEntry(C, 1,1,1); changeEntry(D, 1,1,1);
    changeEntry(C, 1,2,2); changeEntry(D, 1,2,0);
    changeEntry(C, 1,3,3); changeEntry(D, 1,3,1);
    changeEntry(C, 2,1,4); changeEntry(D, 2,1,0);
    changeEntry(C, 2,2,5); changeEntry(D, 2,2,1);
    changeEntry(C, 2,3,6); changeEntry(D, 2,3,0);
    changeEntry(C, 3,1,7); changeEntry(D, 3,1,1);
    changeEntry(C, 3,2,8); changeEntry(D, 3,2,1);
    changeEntry(C, 3,3,9); changeEntry(D, 3,3,1);
    Matrix G = product(D, D);
    printf("numNonZero(G): %d\n", numNonZero(G));
    printMatrix(stdout, G);
    printf("\n\n");

    // Test sum()
    Matrix AB_sum = sum(A, B);
    printf("Sum of A and B:\n");
    printStdoutMatrix(AB_sum);
    printf("\n");

    // Test product() from MatrixClient.c
    Matrix F = sum(C, D);
    printf("nnz(F): %d\n", numNonZero(F));
    printMatrix(stdout, F);
    printf("\n\n");

    // Test diff()
    Matrix A_times_3 = scalarMult(3, A);
    Matrix AB_diff = diff(A_times_3, B);
    printf("Diff of A and B:\n");
    printStdoutMatrix(AB_diff);
    printf("\n");

    freeMatrix(&X);
    freeMatrix(&X_copy);
    freeMatrix(&X_transpose);
    freeMatrix(&X_scalarMult);
    freeMatrix(&Y);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&B_trans);
    freeMatrix(&AB);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&G);
    freeMatrix(&AB_sum);
    freeMatrix(&F);
    freeMatrix(&A_times_3); 
    freeMatrix(&AB_diff);

    return EXIT_SUCCESS;
}

