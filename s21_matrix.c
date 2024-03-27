#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = 0;
  if (rows <= 0 || columns <= 0) {
    code = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
  }
  if (!code) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      code = 2;
    }
  }
  if (!code) {
    for (int i = 0; i < rows; ++i) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        code = 2;
      }
    }
  }
  return code;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!s21_is_ok(A) || !s21_is_ok(B)) {  //  faulty matrix
    result = FAILURE;
  } else if (A->rows != B->rows ||
             A->columns != B->columns) {  //  obviously different matrices
    result = FAILURE;
  } else {
    for (int i = 0; result == SUCCESS && i < A->rows; ++i) {
      for (int j = 0; result == SUCCESS && j < A->columns; ++j) {
        if (s21_are_equal(A->matrix[i][j], B->matrix[i][j]) != true) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

bool s21_are_equal(double a, double b) { return fabs(a - b) < S21_EPS; }

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (!s21_is_ok(A) || !s21_is_ok(B)) {  //  faulty matrix
    code = INCORRECT_MATRIX;
  } else if (!s21_are_matrices_equal(A, B)) {  //  need to be of the same size
    code = INCORRECT_CALCULATION;
  } else {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      code = INCORRECT_MATRIX;
    }
  }
  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (!s21_is_ok(A) || !s21_is_ok(B)) {  //  faulty matrix
    code = INCORRECT_MATRIX;
  } else if (!s21_are_matrices_equal(A, B)) {  //  need to be of the same size
    code = INCORRECT_CALCULATION;
  } else {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      code = INCORRECT_MATRIX;
    }
  }
  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = OK;
  if (!s21_is_ok(A)) {
    return INCORRECT_MATRIX;
  } else {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      code = INCORRECT_MATRIX;
    }
  }
  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (!s21_is_ok(A) || !s21_is_ok(B)) {  //  faulty matrix
    return INCORRECT_MATRIX;
  }
  if (A->columns != B->rows) {
    return INCORRECT_CALCULATION;
  }
  if (s21_create_matrix(A->rows, B->columns, result)) {
    code = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_ok(A)) {  //  faulty matrix
    code = INCORRECT_MATRIX;
  } else {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = 0;
  if (!s21_is_ok(A)) {
    code = INCORRECT_MATRIX;
  } else if (!s21_is_square(A)) {
    code = INCORRECT_CALCULATION;
  } else if (A->rows == 1) {  //  for matrix of 1 element it's co-factor is
                              //  equal to it's single element
    result->matrix[0][0] = A->matrix[0][0];
  } else {  //  need to find table of minors
    s21_create_matrix(A->rows, A->rows, result);  // to allocate memory
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        matrix_t smaller_table = {0};
        double determinant = 0;
        s21_create_matrix(A->rows - 1, A->rows - 1,
                          &smaller_table);  // to allocate memory
        s21_create_smaller_table(A, &smaller_table, i,
                                 j);  //  to fill in smaller table
        s21_determinant(&smaller_table, &determinant);
        result->matrix[i][j] =
            determinant * pow(-1, i + j);  //  fill in the table of minors
        s21_remove_matrix(&smaller_table);
      }
    }
  }
  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  int code = OK;
  int lines_swapped = 0;
  if (!s21_is_ok(A)) {
    code = INCORRECT_MATRIX;
  } else if (!s21_is_square(A)) {
    code = INCORRECT_CALCULATION;
  } else {
    matrix_t copy = {0};  //  otherwise the A matrix would change
    if (!s21_create_copy(A, &copy)) {
      lines_swapped = s21_gauss(&copy);
      s21_multiply_main_diagonal(&copy, result, lines_swapped);
      s21_remove_matrix(&copy);
    } else {
      code = INCORRECT_CALCULATION;
    }
  }
  return code;
}

int s21_gauss(matrix_t *A) {
  int lines_swapped = 0;
  int stop = 1;  //  value changes if there is a null in the main diagonal and
                 //  swap is not possible
  for (int k = 0; stop && k < A->rows; k++) {
    if (round(A->matrix[k][k]) == 0) {
      stop = s21_swap_lines(A, k);
      if (stop) {
        lines_swapped++;
      }
    }
    for (int i = k; stop && i < A->rows; ++i) {
      int j = k;
      double factor = A->matrix[i][j] / A->matrix[k][k];
      for (; j < A->rows; ++j) {
        if (i > k) {
          A->matrix[i][j] = A->matrix[i][j] - (factor * A->matrix[k][j]);
        }
      }
    }
  }
  return lines_swapped;
}

void s21_multiply_main_diagonal(matrix_t *A, double *result,
                                int lines_swapped) {
  *result = A->matrix[0][0];
  for (int k = 1; k < A->rows; ++k) {
    *result = *result * A->matrix[k][k];
  }
  if (lines_swapped % 2 != 0) {
    *result = -*result;
  }
}

int s21_swap_lines(matrix_t *A, int k) {
  int swap_is_possible = 1;
  if (k == A->rows - 1) {
    swap_is_possible = 0;
  } else {  //  find the line with the max element:
    double max_element = fabs(A->matrix[k + 1][k]);
    int line_of_max_element = k + 1;
    for (int i = k + 1; i < A->columns; ++i) {
      if (fabs(A->matrix[i][k]) > max_element) {
        line_of_max_element = i;
      }
    }
    if (max_element == 0) {
      swap_is_possible = 0;
    } else {
      s21_swap_itself(A, k, line_of_max_element);
    }
  }
  return swap_is_possible;
}

void s21_swap_itself(matrix_t *A, int k, int line_of_max_element) {
  for (int j = 0; j < A->rows; ++j) {
    double tmp = A->matrix[k][j];
    A->matrix[k][j] = A->matrix[line_of_max_element][j];
    A->matrix[line_of_max_element][j] = tmp;
  }
}

void s21_create_smaller_table(matrix_t *A, matrix_t *smaller_table,
                              int k_to_skip, int l_to_skip) {
  int k = 0;  //  to store i coordinate of A matrix
  int l = 0;  //  to store j coordinate of A matrix
  int skiped_k = 0;
  for (int i = 0; i < smaller_table->rows; ++i, ++k) {
    int skiped_l = 0;
    for (int j = 0; j < smaller_table->columns; ++j, ++l) {
      if (i == k_to_skip || skiped_k == 1) {
        k = i + 1;
        skiped_k = 1;
      } else {
        k = i;
      }
      if (j == l_to_skip || skiped_l == 1) {
        l = j + 1;
        skiped_l = 1;
      } else {
        l = j;
      }
      smaller_table->matrix[i][j] = A->matrix[k][l];
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = 0;
  double determinant = 0;
  matrix_t complements = {0};
  matrix_t transposed = {0};
  int res = s21_determinant(A, &determinant);
  if (!s21_is_ok(A)) {
    code = INCORRECT_MATRIX;
  } else if (res || fabs(determinant) <= S21_EPS) {
    code = INCORRECT_CALCULATION;
  } else if (s21_calc_complements(A, &complements)) {
    code = INCORRECT_CALCULATION;
  } else if (s21_transpose(&complements, &transposed) ||
             s21_create_matrix(A->rows, A->rows, result)) {
    code = INCORRECT_CALCULATION;
  } else {
    s21_mult_number(&transposed, 1 / determinant, result);
    s21_remove_matrix(&transposed);
    s21_remove_matrix(&complements);
  }
  return code;
}

int s21_create_copy(matrix_t *A, matrix_t *copy) {
  int code = 0;
  if (!s21_create_matrix(A->rows, A->columns, copy)) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        copy->matrix[i][j] = A->matrix[i][j];
      }
    }
  } else {
    code = 1;
  }
  return code;
}

int s21_is_ok(matrix_t *A) {
  int status = 1;
  if (A->rows <= 0 || A->matrix == NULL || A->columns <= 0) {
    status = 0;
  }
  return status;
}

int s21_is_square(matrix_t *A) {
  int status = 1;
  if (A->rows != A->columns) {
    status = 0;
  }
  return status;
}

int s21_are_matrices_equal(matrix_t *A, matrix_t *B) {
  int status = 1;
  if (A->rows != B->rows || A->columns != B->columns) {
    status = 0;
  }
  return status;
}

////////////////////  FOR TESTING AND DEBUGGING PURPOSES ////////////

// void s21_print_structure(matrix_t *A) {
//   for (int i = 0; i < A->rows; ++i) {
//     for (int j = 0; j < A->columns; ++j) {
//       printf("%.3f ", A->matrix[i][j]);
//     }
//     printf("\n");
//   }
//   printf("\n");
// }

void random_init(matrix_t *A) {
  srand(time(NULL));
  double raz = 0, dva = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      raz = (rand() % 30 + 1);
      dva = (rand() % 30 + 1);
      if ((i + j) % 2) {
        A->matrix[i][j] = (raz + dva) * (raz - dva);
      } else {
        A->matrix[i][j] = (raz + dva) * 4 / raz;
      }
    }
  }
}
