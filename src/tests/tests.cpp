#include <gtest/gtest.h>

#include "../matrix/s21_matrix_oop.hpp"

TEST(constructors, negative) { EXPECT_ANY_THROW(S21Matrix m(-1, -2)); }

TEST(getters, get_cols_get_rows) {
  S21Matrix m1(2, 2);
  m1(1, 1) = 123.456;
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 123.456);
}

TEST(setters, set_cols) {
  S21Matrix m(2, 2);
  m(1, 1) = 123.456;
  m.SetCols(3);
  m(1, 2) = 999.999;
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 123.456);
  EXPECT_DOUBLE_EQ(m(1, 2), 999.999);
  m.SetCols(2);
  EXPECT_EQ(m.GetCols(), 2);
}

TEST(setters, setrows) {
  S21Matrix m1(2, 2);
  m1(1, 0) = 123.456;
  m1.SetRows(3);
  m1(2, 0) = m1(1, 0);
  EXPECT_EQ(m1.GetRows(), 3);
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 0), m1(2, 0));
}

TEST(constructors, all_types) {
  S21Matrix m1;
  EXPECT_EQ(m1.GetCols(), 0);
  EXPECT_EQ(m1.GetRows(), 0);

  S21Matrix m2(2, 2);
  m2(1, 1) = 123.456;
  EXPECT_EQ(m2.GetCols(), 2);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m2(1, 1), 123.456);

  S21Matrix m3(m2);
  EXPECT_EQ(m2.EqMatrix(m3), true);

  S21Matrix m4(std::move(m3));
  EXPECT_EQ(m3.GetCols(), 0);
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m4.GetRows(), 2);
  EXPECT_EQ(m4.GetCols(), 2);
  EXPECT_EQ(m4(1, 1), m2(1, 1));
}

TEST(functions, eq) {
  S21Matrix m1(123, 123);
  S21Matrix m2(m1);

  EXPECT_EQ(m1.EqMatrix(m2), true);
}

TEST(functions, sum) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 2) = 2;
  m1(2, 0) = 3;

  m2.SumMatrix(m1);

  EXPECT_EQ(m2(0, 0), 1);
  EXPECT_EQ(m2(0, 2), 2);
  EXPECT_EQ(m2(2, 0), 3);
}

TEST(functions, sub) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 2) = 2;
  m1(2, 0) = 3;

  m2.SubMatrix(m1);

  EXPECT_EQ(m2(0, 0), -1);
  EXPECT_EQ(m2(0, 2), -2);
  EXPECT_EQ(m2(2, 0), -3);
}

TEST(functions, mulnum) {
  S21Matrix m2(3, 3);

  m2(0, 0) = 1.3;
  m2(0, 2) = 2.1;
  m2(2, 0) = 3.3;

  m2.MulNumber(0.412);

  EXPECT_EQ(m2(0, 0), 1.3 * 0.412);
  EXPECT_EQ(m2(0, 2), 2.1 * 0.412);
  EXPECT_EQ(m2(2, 0), 3.3 * 0.412);
}

TEST(functions, mulmat) {
  S21Matrix m1(2, 1);
  S21Matrix m2(1, 2);

  m1(0, 0) = 32;
  m1(1, 0) = 12;

  m2(0, 0) = 2;
  m2(0, 1) = 3;

  m1.MulMatrix(m2);

  EXPECT_DOUBLE_EQ(m1(0, 0), 32 * 2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 12 * 3);
}

TEST(functions, transpose) {
  int rows = 2;
  int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix res(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++, c++) {
      m(i, j) = c;
      res(j, i) = c;
    }
  }

  m = m.Transpose();

  ASSERT_TRUE(m == res);
}

TEST(functions, complements_with_errors) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(functions, det) {
  S21Matrix m(5, 5);

  for (uint32_t i = 0; i < 5; i++)
    for (uint32_t j = 0; j < 5; j++) m(i, j) = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(functions, det2) {
  int size = 5;
  S21Matrix m(size, size);

  m(0, 1) = 6;
  m(0, 2) = -2;
  m(0, 3) = -1;
  m(0, 4) = 5;
  m(1, 3) = -9;
  m(1, 4) = -7;
  m(2, 1) = 15;
  m(2, 2) = 35;
  m(3, 1) = -1;
  m(3, 2) = -11;
  m(3, 3) = -2;
  m(3, 4) = 1;
  m(4, 0) = -2;
  m(4, 1) = -2;
  m(4, 2) = 3;
  m(4, 4) = -2;

  double res = m.Determinant();
  ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(functions, det3) {
  int size = 3;
  S21Matrix m(size, size);

  m(0, 0) = 2;
  m(0, 1) = 3;
  m(0, 2) = 1;
  m(1, 0) = 7;
  m(1, 1) = 4;
  m(1, 2) = 1;
  m(2, 0) = 9;
  m(2, 1) = -2;
  m(2, 2) = 1;

  double res = m.Determinant();
  ASSERT_NEAR(res, -32, 1e-6);
}

TEST(functions, complements) {
  int rows = 3;
  int cols = 3;

  S21Matrix given(rows, cols);
  S21Matrix expected(rows, cols);

  given(0, 0) = 1.0;
  given(0, 1) = 2.0;
  given(0, 2) = 3.0;
  given(1, 0) = 0.0;
  given(1, 1) = 4.0;
  given(1, 2) = 2.0;
  given(2, 0) = 5.0;
  given(2, 1) = 2.0;
  given(2, 2) = 1.0;

  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;

  S21Matrix res = given.CalcComplements();

  ASSERT_TRUE(res == expected);
}

TEST(functions, inverse) {
  int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);

  expected(0, 0) = 44300.0 / 367429.0;
  expected(0, 1) = -236300.0 / 367429.0;
  expected(0, 2) = 200360.0 / 367429.0;
  expected(1, 0) = 20600.0 / 367429.0;
  expected(1, 1) = 56000.0 / 367429.0;
  expected(1, 2) = -156483.0 / 367429.0;
  expected(2, 0) = 30900.0 / 367429.0;
  expected(2, 1) = 84000.0 / 367429.0;
  expected(2, 2) = -51010.0 / 367429.0;

  given(0, 0) = 2.8;
  given(0, 1) = 1.3;
  given(0, 2) = 7.01;
  given(1, 0) = -1.03;
  given(1, 1) = -2.3;
  given(1, 2) = 3.01;
  given(2, 0) = 0;
  given(2, 1) = -3;
  given(2, 2) = 2;

  ASSERT_TRUE(expected.InverseMatrix() == given);
}

TEST(functions, inverse2) {
  int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  given(0, 0) = 2.0;
  given(0, 1) = 5.0;
  given(0, 2) = 7.0;
  given(1, 0) = 6.0;
  given(1, 1) = 3.0;
  given(1, 2) = 4.0;
  given(2, 0) = 5.0;
  given(2, 1) = -2.0;
  given(2, 2) = -3.0;

  ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(getters, default) {
  S21Matrix m;
  EXPECT_EQ(m.GetCols(), 0);
  EXPECT_EQ(m.GetRows(), 0);
}

TEST(getters, getters2) {
  S21Matrix m(11, 11);
  EXPECT_EQ(m.GetCols(), 11);
  EXPECT_EQ(m.GetRows(), 11);
  EXPECT_EQ(m(10, 10), 0);
}

TEST(getters, getters3) {
  S21Matrix m1(123, 123);

  S21Matrix m2(m1);

  EXPECT_EQ(m1.GetCols(), m2.GetCols());
  EXPECT_EQ(m1.GetRows(), m2.GetRows());
}

TEST(getters, getters4) {
  S21Matrix m1(123, 123);

  S21Matrix m2(std::move(m1));

  EXPECT_EQ(m1.GetCols(), 0);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m2.GetCols(), 123);
  EXPECT_EQ(m2.GetRows(), 123);
}

TEST(operator, plus) {
  int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  S21Matrix given_1(size, size);

  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  given(0, 0) = 2.0;
  given(0, 1) = 5.0;
  given(0, 2) = 7.0;
  given(1, 0) = 6.0;
  given(1, 1) = 3.0;
  given(1, 2) = 4.0;
  given(2, 0) = 5.0;
  given(2, 1) = -2.0;
  given(2, 2) = -3.0;

  given_1(0, 0) = 2.0 + 1.0;
  given_1(0, 1) = 5.0 + -1.0;
  given_1(0, 2) = 7.0 + 1.0;
  given_1(1, 0) = 6.0 + -38.0;
  given_1(1, 1) = 3.0 + 41.0;
  given_1(1, 2) = 4.0 + -34.0;
  given_1(2, 0) = 5.0 + 27.0;
  given_1(2, 1) = -2.0 + -29.0;
  given_1(2, 2) = -3.0 + 24.0;

  EXPECT_TRUE(given_1 == (given + expected));
  given += expected;
  EXPECT_TRUE(given == given_1);
}

TEST(operator, sub) {
  int size = 3;
  S21Matrix given(size, size);
  S21Matrix expected(size, size);
  S21Matrix given_1(size, size);

  expected(0, 0) = 1.0;
  expected(0, 1) = -1.0;
  expected(0, 2) = 1.0;
  expected(1, 0) = -38.0;
  expected(1, 1) = 41.0;
  expected(1, 2) = -34.0;
  expected(2, 0) = 27.0;
  expected(2, 1) = -29.0;
  expected(2, 2) = 24.0;

  given(0, 0) = 2.0;
  given(0, 1) = 5.0;
  given(0, 2) = 7.0;
  given(1, 0) = 6.0;
  given(1, 1) = 3.0;
  given(1, 2) = 4.0;
  given(2, 0) = 5.0;
  given(2, 1) = -2.0;
  given(2, 2) = -3.0;

  given_1(0, 0) = 2.0 - 1.0;
  given_1(0, 1) = 5.0 - -1.0;
  given_1(0, 2) = 7.0 - 1.0;
  given_1(1, 0) = 6.0 - -38.0;
  given_1(1, 1) = 3.0 - 41.0;
  given_1(1, 2) = 4.0 - -34.0;
  given_1(2, 0) = 5.0 - 27.0;
  given_1(2, 1) = -2.0 - -29.0;
  given_1(2, 2) = -3.0 - 24.0;

  EXPECT_TRUE(given_1 == (given - expected));
  given -= expected;
  EXPECT_TRUE(given == given_1);
}

TEST(operator, mul) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  for (int i = 0; i < m1.GetRows(); ++i)
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = (i + 1) * j + 1;
      m2(i, j) = (i + 1) * j + 1;
    }
  S21Matrix m4 = m1 * m2;
  S21Matrix m5(m1);
  m1.MulMatrix(m2);

  m5 *= m2;
  EXPECT_EQ(1, m1 == m4);
  EXPECT_EQ(1, m1 == m5);
  EXPECT_EQ(3, m1.GetCols());
  EXPECT_EQ(3, m1.GetRows());
  for (int i = 0; i < m1.GetRows(); ++i)
    for (int j = 0; j < m1.GetCols(); ++j)
      if (j == 0)
        EXPECT_DOUBLE_EQ(6 + 3 * i, m1(i, j));
      else if (j == 1)
        EXPECT_DOUBLE_EQ(20 + 11 * i, m1(i, j));
      else
        EXPECT_DOUBLE_EQ(34 + 19 * i, m1(i, j));

  S21Matrix m3(3, 1);
  ASSERT_ANY_THROW(m3.MulMatrix(m2));

  for (int i = 0; i < m3.GetRows(); ++i) m3(i, 0) = 2;
  m2.MulMatrix(m3);
  EXPECT_EQ(1, m2.GetCols());
  EXPECT_EQ(3, m2.GetRows());
  for (int i = 0; i < m2.GetRows(); ++i) EXPECT_DOUBLE_EQ(12 + 6 * i, m2(i, 0));
}

TEST(Test, operator_mulNumbereq) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  S21Matrix C(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  C = B * 2;
  B *= 2;

  EXPECT_EQ(1, B == A);
  EXPECT_EQ(1, C == B);
}

TEST(errors, error1) {
  S21Matrix A(2, 3);
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}

TEST(errors, error3) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}

TEST(errors, error6) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}
TEST(errors, error7) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 2);
  EXPECT_THROW(A.SumMatrix(B), std::invalid_argument);
}
TEST(errors, error8) {
  S21Matrix A(1, 4);
  S21Matrix B(4, 1);
  EXPECT_THROW(A.SubMatrix(B), std::invalid_argument);
}
TEST(errors, set_cols_error) {
  S21Matrix A;
  EXPECT_THROW(A.SetCols(-1), std::invalid_argument);
}
TEST(errors, set_rows_error) {
  S21Matrix A;
  EXPECT_THROW(A.SetRows(-1), std::invalid_argument);
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "ERRORS" << std::endl;
  }
  return RUN_ALL_TESTS();
}
