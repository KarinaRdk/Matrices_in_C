# Matrices in C
Library for processing numerical matrices in the C programming language. It's designed to perform various matrix operations:

## Features
<ol>
<li>Matrix Creation: Dynamically create matrices of specified dimensions.</li>
<li>Matrix Operations: Perform basic matrix operations like addition, subtraction, and multiplication.</li>
<li> Matrix Transposition: Transpose a matrix, swapping rows with columns.</li>
<li>Matrix Inversion: Calculate the inverse of a matrix, provided it is invertible.</li>
<li>Determinant Calculation: Compute the determinant of a matrix using Gaussian Elimination.</li>
<li>Matrix Complement Calculation: Calculate the matrix of minors and cofactors.</li>
<li>Matrix Equality Check: Check if two matrices are equal.</li>
<li> Matrix Copy: Create a copy of a matrix.</li>
</ol>

## Getting Started

To use the S21 Matrix Library, include the s21_matrix.h header file in your C project. 

## Example Usage:
    

    #include "s21_matrix.h"

    int main() {
    matrix_t A;
    s21_create_matrix(3, 3, &A); // Create a 3x3 matrix

    // Perform operations on the matrix A...

    s21_remove_matrix(&A); // Free the memory allocated for the matrix
    return 0;

    }
