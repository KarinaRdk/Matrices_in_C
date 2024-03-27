#include <check.h>

#include "s21_matrix.h"

START_TEST(create_matrix_1) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(4, 2, &A), 0);
  ck_assert_int_eq(A.rows, 4);
  ck_assert_int_eq(A.columns, 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(4, 1, &A), 0);
  ck_assert_int_eq(A.rows, 4);
  ck_assert_int_eq(A.columns, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_3) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(4, -2, &A), 1);
}
END_TEST

START_TEST(create_matrix_4) {
  matrix_t A;
  ck_assert_int_eq(s21_create_matrix(-4, 2, &A), 1);
}
END_TEST

START_TEST(remove_matrix_1) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.rows, 0);
}
END_TEST

START_TEST(remove_matrix_2) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(eq_matrix_00) {
  matrix_t A, B;
  s21_create_matrix(4, 4, &A);
  A.rows = -1;
  s21_create_matrix(4, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_0) {
  matrix_t A, B;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(4, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_1) {
  matrix_t A, B;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(4, 2, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t A, B;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(2, 4, &B);
  B.matrix[1][1] = 0.5;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t A, B;
  s21_create_matrix(18, 40, &A);
  s21_create_matrix(18, 40, &B);
  B.matrix[17][5] = 0.5;
  B.matrix[16][10] = 8.5;
  B.matrix[0][39] = 1000;
  B.matrix[0][0] = -1000;
  A.matrix[17][5] = 0.5;
  A.matrix[16][10] = 8.5;
  A.matrix[0][39] = 1000;
  A.matrix[0][0] = -1000;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t A, B, C, D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  B.matrix[0][0] = 100;
  B.matrix[0][1] = 50;
  B.matrix[1][0] = 75;
  B.matrix[1][1] = 0;
  C.matrix[0][0] = 101;
  C.matrix[0][1] = 52;
  C.matrix[1][0] = 78;
  C.matrix[1][1] = 0;
  s21_sum_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t A, B, C;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t A, B, C;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  A.columns = -1;
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t A, B, C, D;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &C);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 0;

  C.matrix[0][0] = 0;
  C.matrix[0][1] = 0;
  C.matrix[1][0] = 0;
  C.matrix[1][1] = 0;
  s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A, B, C;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &C);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t A, B, C;
  s21_create_matrix(4, 2, &A);
  s21_create_matrix(4, 2, &B);
  A.columns = -1;
  s21_create_matrix(3, 2, &C);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t A, result, B;
  double num = 0;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &result);
  s21_mult_number(&A, num, &B);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  result.matrix[0][0] = 0;
  result.matrix[0][1] = 0;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 0;
  ck_assert_int_eq(s21_eq_matrix(&B, &result), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A, result, B;
  double num = 0.5;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &result);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  result.matrix[0][0] = 0.5;
  result.matrix[0][1] = 1;
  result.matrix[1][0] = 1.5;
  result.matrix[1][1] = 0;
  s21_mult_number(&A, num, &B);
  ck_assert_int_eq(s21_eq_matrix(&B, &result), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test) {
  matrix_t test1, result;
  s21_create_matrix(4, 6, &test1);
  s21_create_matrix(4, 6, &result);
  for (int i = 0; i < 50; i++) {
    random_init(&test1);
    double number = (rand() % 100) + (rand() % 100 / 100.0);
    int result_mult = s21_mult_number(&test1, number, &result);
    ck_assert_int_eq(0, result_mult);
    for (int a = 0; a < test1.rows; a++) {
      for (int b = 0; b < test1.rows; b++) {
        ck_assert_ldouble_eq_tol((test1.matrix[a][b] * number),
                                 result.matrix[a][b], 0.000001);
      }
    }
  }
  matrix_t test3, test4;
  s21_create_matrix(3, 6, &test3);
  s21_create_matrix(4, 6, &test4);
  int fail_1 = s21_mult_number(&test1, 1.1, &test3);
  ck_assert_int_eq(0, fail_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test3);
  s21_remove_matrix(&test4);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t mat_1, mat_2, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(3, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(3, 2, &res_org);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(2, 7, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  s21_transpose(&A, &B);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 3;
  C.matrix[1][0] = 2;
  C.matrix[1][1] = 0;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A, B, C;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_transpose(&A, &B);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 2;
  C.matrix[0][2] = 3;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = 5;
  C.matrix[1][2] = 6;

  ck_assert_int_eq(s21_eq_matrix(&B, &C), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t mat_1, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  mat_1.matrix[0][0] = 1;
  mat_1.matrix[0][1] = 2;
  mat_1.matrix[1][0] = 3;
  mat_1.matrix[1][1] = 4;
  res_org.matrix[0][0] = 1;
  res_org.matrix[0][1] = 3;
  res_org.matrix[1][0] = 2;
  res_org.matrix[1][1] = 4;
  int ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  double matrix[2][2] = {
      {1, 2},
      {3, 4},
  };
  double res[2][2] = {{1, 3}, {2, 4}};
  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      res_org.matrix[i][j] = res[i][j];
    }
  }
  ret = s21_transpose(&mat_1, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(determinant_0) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  double result = 0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[1][3] = 8;
  A.matrix[2][0] = 9;
  A.matrix[2][1] = 10;
  A.matrix[2][2] = 11;
  A.matrix[2][3] = 12;
  A.matrix[3][0] = 13;
  A.matrix[3][1] = 14;
  A.matrix[3][2] = 15;
  A.matrix[3][3] = 16;

  s21_determinant(&A, &result);
  ck_assert_float_eq(result, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double res = 0.0;
  A.matrix[0][0] = 73;
  A.matrix[0][1] = 7;
  A.matrix[0][2] = 6;
  A.matrix[1][0] = 110;
  A.matrix[1][1] = 16;
  A.matrix[1][2] = 19;
  A.matrix[2][0] = 148;
  A.matrix[2][1] = 10;
  A.matrix[2][2] = 7;
  s21_determinant(&A, &res);
  ck_assert_float_eq(res, 992);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double res = 0.0;
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 7;
  A.matrix[0][2] = 9;
  A.matrix[1][0] = 11;
  A.matrix[1][1] = 13;
  A.matrix[1][2] = 15;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = 4;
  s21_determinant(&A, &res);
  ck_assert_float_eq(res, -216);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);
  double res = 0.0;
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 7;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 11;
  A.matrix[1][0] = 13;
  A.matrix[1][1] = 15;
  A.matrix[1][2] = 17;
  A.matrix[1][3] = 19;
  A.matrix[2][0] = 22;
  A.matrix[2][1] = 25;
  A.matrix[2][2] = 28;
  A.matrix[2][3] = 1;
  A.matrix[3][0] = 30;
  A.matrix[3][1] = 1;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 9;
  s21_determinant(&A, &res);
  ck_assert_float_eq(res, -15840);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A;
  double result = 0.0;
  s21_create_matrix(5, 5, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 7;
  A.matrix[0][2] = 9;
  A.matrix[0][3] = 11;
  A.matrix[0][4] = 11;
  A.matrix[1][0] = 13;
  A.matrix[1][1] = 15;
  A.matrix[1][2] = 17;
  A.matrix[1][3] = 19;
  A.matrix[1][4] = 19;
  A.matrix[2][0] = 22;
  A.matrix[2][1] = 25;
  A.matrix[2][2] = 28;
  A.matrix[2][3] = 1;
  A.matrix[2][4] = 1;
  A.matrix[3][0] = -10;
  A.matrix[3][1] = 1;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 9;
  A.matrix[3][4] = 9;
  A.matrix[4][0] = 30;
  A.matrix[4][1] = 1;
  A.matrix[4][2] = 5;
  A.matrix[4][3] = 9;
  A.matrix[4][4] = -11;
  s21_determinant(&A, &result);
  ck_assert_float_eq(result, -67200);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {  //  FAIL Segmentation fault
  matrix_t A;
  double result = 0;
  double expected = 11;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = -2;
  A.matrix[1][1] = 5;
  s21_determinant(&A, &result);
  ck_assert_float_eq(result, expected);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_6) {
  matrix_t a;
  double result = 0;
  double expected = -7.;
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 1;
  a.matrix[0][1] = 0;
  a.matrix[0][2] = -2;
  a.matrix[1][0] = 0.5;
  a.matrix[1][1] = 3;
  a.matrix[1][2] = 1;
  a.matrix[2][0] = 0;
  a.matrix[2][1] = 2;
  a.matrix[2][2] = -1;
  s21_determinant(&a, &result);
  ck_assert_float_eq(result, expected);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(determinant_7) {
  matrix_t matrix;
  s21_create_matrix(3, 3, &matrix);
  int count = 1;
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = count++;
    }
  }
  matrix.matrix[2][2] = 10;
  double res;
  s21_determinant(&matrix, &res);
  ck_assert_float_eq(res, -3);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_9) {
  matrix_t A;
  double result = 0;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  s21_determinant(&A, &result);
  ck_assert_float_eq(result, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_10) {
  matrix_t A;
  double result = 0;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  s21_determinant(&A, &result);
  ck_assert_float_eq(result, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_11) {
  matrix_t A;
  double result = 0;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  s21_determinant(&A, &result);
  ck_assert_float_eq(result, -2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_0) {
  matrix_t A, B, C;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  s21_calc_complements(&A, &B);

  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 4;
  C.matrix[0][1] = -3;
  C.matrix[1][0] = -2;
  C.matrix[1][1] = 1;

  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(calc_complements_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  s21_calc_complements(&A, &B);

  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 10;
  C.matrix[0][2] = -20;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = -14;
  C.matrix[1][2] = 8;
  C.matrix[2][0] = -8;
  C.matrix[2][1] = -2;
  C.matrix[2][2] = 4;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t A, B, C;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  s21_calc_complements(&A, &B);

  s21_create_matrix(4, 4, &C);
  C.matrix[0][0] = 15;
  C.matrix[0][1] = 15;
  C.matrix[0][2] = -15;
  C.matrix[0][3] = -30;
  C.matrix[1][0] = -23;
  C.matrix[1][1] = -7;
  C.matrix[1][2] = -81;
  C.matrix[1][3] = 70;
  C.matrix[2][0] = -39;
  C.matrix[2][1] = 9;
  C.matrix[2][2] = -33;
  C.matrix[2][3] = 30;
  C.matrix[3][0] = 20;
  C.matrix[3][1] = -20;
  C.matrix[3][2] = 60;
  C.matrix[3][3] = -40;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(calc_complements_3) {
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double r[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_calc_complements(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  s21_calc_complements(&A, &B);

  s21_create_matrix(3, 3, &C);

  C.matrix[0][0] = -1;
  C.matrix[0][1] = 38;
  C.matrix[0][2] = -27;
  C.matrix[1][0] = 1;
  C.matrix[1][1] = -41;
  C.matrix[1][2] = 29;
  C.matrix[2][0] = -1;
  C.matrix[2][1] = 34;
  C.matrix[2][2] = -24;

  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(calc_6_test) {
  matrix_t a = {0}, result = {0};
  int res = 0;
  res = s21_calc_complements(&a, &result);
  ck_assert_int_eq(INCORRECT_MATRIX, res);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_1) {  //  from readme
  matrix_t A, B, C, D;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &D);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 5.0;
  A.matrix[2][0] = 3.0;
  A.matrix[2][1] = 6.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[0][2] = 1.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 3.0;
  B.matrix[1][2] = 4.0;
  s21_mult_matrix(&A, &B, &C);

  D.matrix[0][0] = 9.0;
  D.matrix[0][1] = 11.0;
  D.matrix[0][2] = 17.0;
  D.matrix[1][0] = 12.0;
  D.matrix[1][1] = 13.0;
  D.matrix[1][2] = 22.0;
  D.matrix[2][0] = 15.0;
  D.matrix[2][1] = 15.0;
  D.matrix[2][2] = 27.0;

  ck_assert_float_eq(s21_eq_matrix(&C, &D), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t A, B, C;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(3, 2, &B);
  int res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, INCORRECT_CALCULATION);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t mat_1, mat_2, res_mat, res_org;

  s21_create_matrix(2, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(2, 2, &res_org);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat_1.matrix[i][j] = i + j + 1;
      mat_2.matrix[i][j] = i + j + 1;
    }
  }
  res_org.matrix[0][0] = 5;
  res_org.matrix[0][1] = 8;
  res_org.matrix[1][0] = 8;
  res_org.matrix[1][1] = 13;
  int ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(3, 2, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  s21_create_matrix(3, 2, &res_org);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);
  ck_assert_int_eq(ret, 0);

  ret = s21_eq_matrix(&res_mat, &res_org);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
  s21_remove_matrix(&res_mat);
  s21_remove_matrix(&res_org);

  s21_create_matrix(2, 7, &mat_1);
  s21_create_matrix(2, 2, &mat_2);
  ret = s21_mult_matrix(&mat_1, &mat_2, &res_mat);

  ck_assert_int_eq(ret, 2);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_2);
}
END_TEST

START_TEST(inverse_matrix_0) {
  matrix_t A, B, C;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 7;

  s21_inverse_matrix(&A, &B);

  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 7;
  C.matrix[0][1] = -4;
  C.matrix[1][0] = -5;
  C.matrix[1][1] = 3;

  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_matrix_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  s21_inverse_matrix(&A, &B);

  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = -1;
  C.matrix[0][2] = 1;
  C.matrix[1][0] = -38;
  C.matrix[1][1] = 41;
  C.matrix[1][2] = -34;
  C.matrix[2][0] = 27;
  C.matrix[2][1] = -29;
  C.matrix[2][2] = 24;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_matrix_2) {
  matrix_t A, B, C;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 1;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 7;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 4;
  s21_inverse_matrix(&A, &B);
  C.matrix[0][0] = -0.125;
  C.matrix[0][1] = 0.191667;
  C.matrix[0][2] = 0.325;
  C.matrix[0][3] = -0.166667;
  C.matrix[1][0] = -0.125;
  C.matrix[1][1] = 0.058333;
  C.matrix[1][2] = -0.075;
  C.matrix[1][3] = 0.166667;
  C.matrix[2][0] = 0.125;
  C.matrix[2][1] = 0.675;
  C.matrix[2][2] = 0.275;
  C.matrix[2][3] = -0.5;
  C.matrix[3][0] = 0.25;
  C.matrix[3][1] = -0.583333;
  C.matrix[3][2] = -0.25;
  C.matrix[3][3] = 0.333333;
  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t test1, result, check, mult;
  s21_create_matrix(5, 5, &test1);
  s21_create_matrix(5, 5, &result);
  s21_create_matrix(5, 5, &check);
  s21_create_matrix(5, 5, &mult);
  for (int i = 0; i < check.rows; i++) {
    check.matrix[i][i] = 1;
  }
  for (int t1 = 0; t1 < 500; t1++) {
    random_init(&test1);
    s21_inverse_matrix(&test1, &result);
    s21_mult_matrix(&test1, &result, &mult);
    ck_assert_int_eq(1, s21_eq_matrix(&mult, &check));
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&check);
  s21_remove_matrix(&mult);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}

END_TEST

START_TEST(inverse_matrix_5) {
  matrix_t A, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(inverse_matrix_6) {
  double m[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double r[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  matrix_t matrix, res_org, res_my;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res_org);
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      matrix.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < matrix.rows; i++) {
    for (int j = 0; j < matrix.columns; j++) {
      res_org.matrix[i][j] = r[i][j];
    }
  }
  int ret = s21_inverse_matrix(&matrix, &res_my);
  ck_assert_int_eq(ret, 0);
  ret = s21_eq_matrix(&res_org, &res_my);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res_my);
  s21_remove_matrix(&res_org);
}
END_TEST

int main(void) {
  int val = 0;
  Suite *suite = suite_create("UNITS");
  TCase *tcase = tcase_create("TESTS");
  SRunner *srunner = srunner_create(suite);

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, create_matrix_1);
  tcase_add_test(tcase, create_matrix_2);
  tcase_add_test(tcase, create_matrix_3);
  tcase_add_test(tcase, create_matrix_4);

  tcase_add_test(tcase, remove_matrix_1);
  tcase_add_test(tcase, remove_matrix_2);

  tcase_add_test(tcase, eq_matrix_00);
  tcase_add_test(tcase, eq_matrix_0);
  tcase_add_test(tcase, eq_matrix_1);
  tcase_add_test(tcase, eq_matrix_2);
  tcase_add_test(tcase, eq_matrix_3);

  tcase_add_test(tcase, sum_matrix_1);
  tcase_add_test(tcase, sum_matrix_2);
  tcase_add_test(tcase, sum_matrix_3);

  tcase_add_test(tcase, sub_matrix_1);
  tcase_add_test(tcase, sub_matrix_2);
  tcase_add_test(tcase, sub_matrix_3);

  tcase_add_test(tcase, mult_number_1);
  tcase_add_test(tcase, mult_number_2);

  tcase_add_test(tcase, s21_mult_number_test);
  tcase_add_test(tcase, test_s21_mult_matrix);

  tcase_add_test(tcase, transpose_1);
  tcase_add_test(tcase, transpose_2);
  tcase_add_test(tcase, transpose_3);

  tcase_add_test(tcase, determinant_0);
  tcase_add_test(tcase, determinant_1);
  tcase_add_test(tcase, determinant_2);
  tcase_add_test(tcase, determinant_3);
  tcase_add_test(tcase, determinant_4);
  tcase_add_test(tcase, determinant_5);
  tcase_add_test(tcase, determinant_6);
  tcase_add_test(tcase, determinant_7);
  tcase_add_test(tcase, determinant_9);
  tcase_add_test(tcase, determinant_10);
  tcase_add_test(tcase, determinant_11);

  tcase_add_test(tcase, calc_complements_0);
  tcase_add_test(tcase, calc_complements_1);
  tcase_add_test(tcase, calc_complements_2);
  tcase_add_test(tcase, calc_complements_3);
  tcase_add_test(tcase, calc_complements_4);

  tcase_add_test(tcase, calc_6_test);
  tcase_add_test(tcase, mult_matrix_1);
  tcase_add_test(tcase, mult_matrix_2);
  tcase_add_test(tcase, mult_matrix_4);

  tcase_add_test(tcase, inverse_matrix_0);
  tcase_add_test(tcase, inverse_matrix_1);
  tcase_add_test(tcase, inverse_matrix_2);
  tcase_add_test(tcase, inverse_matrix_3);
  tcase_add_test(tcase, inverse_matrix_4);
  tcase_add_test(tcase, inverse_matrix_5);
  tcase_add_test(tcase, inverse_matrix_6);

  srunner_run_all(srunner, CK_VERBOSE);
  val = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return val == 0 ? 0 : 1;
}
