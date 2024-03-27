# Matrices in C
Library for processing numerical matrices in the C programming language

It's designed to perform various matrix operations, including creation, manipulation, and mathematical operations such as addition, subtraction, multiplication, and finding the determinant and inverse of a matrix. 

Features
Matrix Creation: Dynamically create matrices of specified dimensions.
Matrix Operations: Perform basic matrix operations like addition, subtraction, and multiplication.
Matrix Transposition: Transpose a matrix, swapping rows with columns.
Matrix Inversion: Calculate the inverse of a matrix, provided it is invertible.
Determinant Calculation: Compute the determinant of a matrix using Gaussian Elimination.
Matrix Complement Calculation: Calculate the matrix of minors and cofactors.
Matrix Equality Check: Check if two matrices are equal.
Matrix Copy: Create a copy of a matrix.
Getting Started
To use the S21 Matrix Library, include the s21_matrix.h header file in your C project. 
Example Usage:
    

    #include "s21_matrix.h"

    int main() {
    matrix_t A;
    s21_create_matrix(3, 3, &A); // Create a 3x3 matrix

    // Perform operations on the matrix A...

    s21_remove_matrix(&A); // Free the memory allocated for the matrix
    return 0;

    }
