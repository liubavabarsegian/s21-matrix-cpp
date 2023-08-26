#include "s21_matrix/s21_matrix_oop.h"

// default constructor
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

// parameterized constructor
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::invalid_argument("Rows and columns must be positive");
  }
  createMatrix();
}

void S21Matrix::createMatrix() {
  if (rows_ == 0 || cols_ == 0) {
    matrix_ = nullptr;
  } else if (rows_ > 0 && cols_ > 0) {
    matrix_ = new double*[rows_];
    for (auto i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  createMatrix();
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      (*this)(i, j) = other(i, j);
    }
  }
}

// move constructor
S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;

  *this = std::move(other);
}

// destructor
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (auto i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

// getter of rows
int S21Matrix::GetRows() const noexcept { return rows_; }

// getter of cols
int S21Matrix::GetCols() const noexcept { return cols_; }

// setter for rows
void S21Matrix::SetRows(int rows) {
  S21Matrix temp(rows, cols_);
  for (auto i = 0; i < rows_ && i < rows; i++) {
    for (auto j = 0; j < cols_; j++) {
      temp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(temp);
};

// setter for cols
void S21Matrix::SetCols(int cols) {
  S21Matrix temp(rows_, cols);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_ && j < cols; j++) {
      temp(i, j) = (*this)(i, j);
    }
  }
  *this = std::move(temp);
};

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    return false;
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(
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
    throw std::logic_error(
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
  *this = std::move(result);
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
    throw std::logic_error("The matrix is not square.");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = (*this)(0, 0);
  } else {
    for (auto i = 0; i < cols_; i++) {
      S21Matrix temp = GetMinor(0, i);
      result += pow(-1, i + 2) * (*this)(0, i) * temp.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinor(int rows, int cols) const {
  if (rows < 0 || cols < 0 || rows >= rows_ || cols >= cols_) {
    throw std::out_of_range("Rows and columns out of range.");
  }
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square.");
  }

  S21Matrix result(rows_ - 1, cols_ - 1);
  int current_row = 0;
  for (auto i = 0; i < rows_; i++) {
    if (i == rows) {
      continue;
    }
    int current_col = 0;
    for (auto j = 0; j < cols_; j++) {
      if (j == cols) {
        continue;
      }
      result(current_row, current_col) = (*this)(i, j);
      current_col++;
    }
    current_row++;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::out_of_range("Rows and columns must be positive.");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    result(0, 0) = 1;
  } else {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        result(i, j) = pow(-1, (i + j)) * GetMinor(i, j).Determinant();
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (std::fabs(det) < 1e-7) {
    throw std::logic_error("Zero determinant.");
  }

  return CalcComplements().Transpose() * (1 / det);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) return *this;

  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    if (matrix_) {
      for (auto i = 0; i < rows_; i++) {
        if (matrix_[i]) delete[] matrix_[i];
      }
      delete[] matrix_;
    }

    rows_ = std::move(other.rows_);
    cols_ = std::move(other.cols_);
    matrix_ = std::exchange(other.matrix_, nullptr);
  }

  return *this;
}
// index operator overload
double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::out_of_range("Incorrect input, index is out of range");

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

bool S21Matrix::operator==(const S21Matrix& other) const noexcept {
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

S21Matrix operator*(const double& value, const S21Matrix& matrix) {
  S21Matrix res(matrix);
  return res *= value;
}
