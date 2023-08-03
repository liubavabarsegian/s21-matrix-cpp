#include "s21_matrix_oop.hpp"

// default constructor
S21Matrix::S21Matrix() : rows_(3), cols_(3) {
    createMatrix(*this);
}

// parameterized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }
    createMatrix(*this);
}

void S21Matrix::createMatrix(S21Matrix& m) {
    if (m.rows_ > 0 && m.cols_ > 0) {
        m.matrix_ = new double*[m.rows_]();
        for (int i = 0; i < m.rows_; i++) {
            m.matrix_[i] = new double[m.cols_]();
        }
    }
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    createMatrix(*this);
    std::memcpy(matrix_, other.matrix_, other.rows_ * other.cols_ * sizeof(double));
}

// move constructor
S21Matrix::S21Matrix(S21Matrix&& other) {
    if (rows_ * cols_ != other.rows_ * other.cols_) {
        deleteMatrix(*this);
        rows_ = other.rows_;
        cols_ = other.cols_;
        createMatrix(*this);
    }
    std::memcpy(matrix_, other.matrix_, other.cols_ * other.rows_ * sizeof(double));
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

void S21Matrix::deleteMatrix(S21Matrix& m){
    if (m.matrix_) {
        for (unsigned int i = 0; i < m.rows_; i++) {
            delete[] m.matrix_[i];
        }
    }
    delete[] m.matrix_;
    m.rows_ = 0;
    m.cols_ = 0;
}

// destructor
S21Matrix::~S21Matrix() {
    deleteMatrix(*this);
}

// S21Matrix::sum_matrix(const S21Matrix& o) {
//     // exception throwing example
//     if (rows_ != other.rows_ || cols_ != other.cols_) {
//         throw std::out_of_range(
//             "Incorrect input, matrices should have the same size");
//     }
//     for (auto i = 0; i < rows_ + cols_; i++) {
//         matrix_[i] = matrix_[i] + other.matrix_[i];
//     }
// }

// // operator overload example
// S21Matrix S21Matrix::operator+(const S21Matrix& o) {
//     // creating result matrix
//     S21Matrix res(rows_, cols_);
//     res.sum_matrix(o);
//     return res;
// }

// // index operator overload
// int& CMatrix::operator()(int row, int col) {
//     if (row >= rows_ || col >= cols_) {
//         throw std::out_of_range("Incorrect input, index is out of range");
//     }
//     return matrix_[row * cols_ + col];
// }
