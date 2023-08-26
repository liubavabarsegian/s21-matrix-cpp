#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <utility>

class S21Matrix {
 public:
  // constructors and destructors
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // getters
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  S21Matrix GetMinor(int rows, int cols) const;

  // setters
  void SetRows(int rows);
  void SetCols(int cols);

  // operators overloads
  // assignment operator overload
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  // index operator overload
  double& operator()(int row, int col) const;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double num) const;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);

  // // some public methods
  bool EqMatrix(const S21Matrix& other) const noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // friend function
  friend S21Matrix operator*(const double& value, const S21Matrix& matrix);

 private:
  // attributes
  // rows and columns attributes
  int rows_, cols_;
  // pointer to the memory where the matrix will be allocated
  double** matrix_;
  void createMatrix();
};

#endif  // CPP1_S21_MATRIXPLUS_S21_MATRIX_S21_MATRIX_OOP_H_
