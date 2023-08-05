#include <gtest/gtest.h>

#include "../matrix/s21_matrix_oop.hpp"

TEST(get_set, t1) {
  S21Matrix m1(2, 2);
  m1(1, 1) = 123.456;
  EXPECT_EQ(m1.GetCols(), 2);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m1(1, 1), 123.456);
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "ERRORS" << std::endl;
  }
  return RUN_ALL_TESTS();
}
