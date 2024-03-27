#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define INCORRECT_CALCULATION 2

#define S21_EPS 0.000001L

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

//////////////   MAIN FUNCTIONS   ///////////////////////////////////

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
bool s21_are_equal(double a, double b);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//////////////   SECONDARY FUNCTIONS   ///////////////////////////////////

void s21_create_smaller_table(matrix_t *A, matrix_t *smaller_table,
                              int k_to_skip, int l_to_skip);
int s21_gauss(matrix_t *A);
void s21_multiply_main_diagonal(matrix_t *A, double *result, int lines_swapped);
int s21_swap_lines(matrix_t *A, int k);
void s21_swap_itself(matrix_t *A, int k, int line_of_max_element);
int s21_create_copy(matrix_t *A, matrix_t *copy);
void s21_print_structure(matrix_t *A);
int s21_is_ok(matrix_t *A);
int s21_is_square(matrix_t *A);
int s21_are_matrices_equal(matrix_t *A, matrix_t *B);

//////////////  FOR TESTING AND DEBUGGING PURPOSES    ////////////////////

void init_matrix(matrix_t *A, const double *B);
int is_correct_matrix(matrix_t *A);
void random_init(matrix_t *A);

#endif  // S21_MATRIX_H
