#include "s21_matrix_oop.h"

// default constructor
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

// parameterized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::invalid_argument("1 Rows and columns must be positive");
  }
  this->createMatrix();
}

void S21Matrix::createMatrix() noexcept {
  if (rows_ == 0 && cols_ == 0) {
    matrix_ = nullptr;
  } else if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    if (matrix_) {
      for (auto i = 0; i < rows_; i++) {
        matrix_[i] = new double[cols_]();
      }
    }
  }
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  this->createMatrix();
  for (auto i = 0; i < this->rows_; i++) {
    for (auto j = 0; j < this->cols_; j++) {
      (*this)(i, j) = other(i, j);
    }
  }
}

// move constructor
S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  *this = std::move(other);
}

void S21Matrix::deleteMatrix() noexcept {
  if (matrix_) {
    for (auto i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
}

// destructor
S21Matrix::~S21Matrix() { this->deleteMatrix(); }

// getter of rows
int S21Matrix::GetRows() const noexcept { return rows_; }

// getter of cols
int S21Matrix::GetCols() const noexcept { return cols_; }

// setter for rows
void S21Matrix::SetRows(int n) {
  if (n < 0) {
    throw std::invalid_argument("Rows must be positive.");
  }
  S21Matrix temp(n, cols_);
  for (auto i = 0; i < rows_ && i < n; i++) {
    for (auto j = 0; j < cols_; j++) {
      temp(i, j) = (*this)(i, j);
    }
  }
  for (auto i = rows_; i < n; i++) {
    for (auto j = 0; j < cols_; j++) {
      temp(i, j) = 0.0;
    }
  }
  *this = temp;
};

// setter for cols
void S21Matrix::SetCols(int n) {
  if (n < 0) {
    throw std::invalid_argument("Cols must be positive.");
  }
  S21Matrix temp(rows_, n);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_ && j < n; j++) {
      temp(i, j) = (*this)(i, j);
    }
    for (auto j = cols_; j < n; j++) {
      temp(i, j) = 0.0;
    }
  }
  *this = temp;
};

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool equal = true;
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    equal = false;
  } else {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        if (std::fabs((*this)(i, j) - other(i, j)) > 1e-7) {
          equal = false;
        }
      }
    }
  }
  return equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size.");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Incorrect input, matrices should have the same size.");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "Incorrect input, the number of inputed rows must be equal to the "
        "number of columns of the first matrix.");
  }
  S21Matrix result(rows_, other.cols_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < other.cols_; j++) {
      result(i, j) = 0;
      for (auto k = 0; k < cols_; k++) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::length_error("The matrix is not square.");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = (*this)(0, 0);
  } else {
    for (auto i = 0; i < cols_; i++) {
      S21Matrix temp = GetMinor(0, i, *this);
      result += pow(-1, i + 2) * (*this)(0, i) * temp.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinor(int rows, int cols, S21Matrix matrix) const {
  if (rows < 0 || cols < 0 || rows >= matrix.rows_ || cols >= matrix.cols_) {
    throw std::length_error("Rows and columns must be positive.");
  }
  S21Matrix result(matrix.rows_ - 1, matrix.cols_ - 1);
  int currentRow = 0;
  for (auto i = 0; i < matrix.rows_; i++) {
    if (i == rows) {
      continue;
    }
    int currentCol = 0;
    for (auto j = 0; j < matrix.cols_; j++) {
      if (j == cols) {
        continue;
      }
      result(currentRow, currentCol) = matrix(i, j);
      currentCol++;
    }
    currentRow++;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::length_error("Rows and columns must be positive.");
  }

  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result(0, 0) = (*this)(0, 0);
  } else {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        S21Matrix minor = GetMinor(i, j, *this);
        double det = minor.Determinant();
        result(i, j) = det * pow(-1, (i + j));
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square.");
  }
  double det = Determinant();
  if (det == 0) {
    throw std::logic_error("Zero determinant.");
  }

  S21Matrix complements = this->CalcComplements();
  S21Matrix transponse(complements.Transpose());
  transponse.MulNumber(1 / det);
  S21Matrix result(transponse);

  // complements.deleteMatrix();
  // transponse.deleteMatrix();

  return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) noexcept {
  if (this == &other) return *this;

  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }

  return *this;
}
// index operator overload
double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::logic_error("Incorrect input, index is out of range");

  return matrix_[row][col];
}

// operator + overload
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}
