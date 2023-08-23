#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  // attributes
  // rows and columns attributes
  int rows_, cols_;
  // pointer to the memory where the matrix will be allocated
  double** matrix_;
  void createMatrix() noexcept;
  void deleteMatrix() noexcept;

 public:
  // constructors and destructors
  S21Matrix() noexcept;
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other) noexcept;
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;

  // getters
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  S21Matrix GetMinor(int rows, int cols, S21Matrix matrix) const;

  // setters
  void SetRows(int n);
  void SetCols(int n);

  // operators overloads
  // assignment operator overload
  S21Matrix& operator=(const S21Matrix& other) noexcept;
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  // index operator overload
  double& operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);

  // // some public methods
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
};

#endif
