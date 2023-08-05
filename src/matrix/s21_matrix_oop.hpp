#ifndef __S21MATRIX_HPP__
#define __S21MATRIX_HPP__

#include <iostream>
#include <cmath>
#include <cstring>

class S21Matrix {
private:
    // attributes
    // rows and columns attributes
    int rows_, cols_;
    // pointer to the memory where the matrix will be allocated
    double **matrix_;
    void createMatrix(S21Matrix& matrix);
    void deleteMatrix();
public:
    //constructors and destructors
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    //getters
    int GetRows() const;
    int GetCols() const;
    S21Matrix GetMinor(int rows, int cols, S21Matrix matrix) const;

    //setters
    void SetRows(int n);
    void SetCols(int n);

    // operators overloads
    // assignment operator overload
    S21Matrix& operator=(const S21Matrix& other);
    // index operator overload
    double& operator()(int row, int col) const;
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(double num);
    bool operator==(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(double num);

    // // some public methods
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();
};

#endif
