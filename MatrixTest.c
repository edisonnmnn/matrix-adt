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

    fprintf(stdout, "Matrix Test:\n\n");

    // Initializing a new matrix and freeing
    Matrix I = newMatrix(5);
    freeMatrix(&I);


    return EXIT_SUCCESS;
}