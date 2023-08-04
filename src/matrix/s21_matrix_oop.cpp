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
    if (m.GetRows > 0 && m.GetCols > 0) {
        m.matrix_ = new double*[m.GetRows]();
        for (int i = 0; i < m.GetRows; i++) {
            m.matrix_[i] = new double[m.GetCols]();
        }
    }
}

// copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.GetRows), cols_(other.GetCols) {
    createMatrix(*this);
    std::memcpy(matrix_, other.matrix_, other.GetRows * other.GetCols * sizeof(double));
}

// move constructor
S21Matrix::S21Matrix(S21Matrix&& other) {
    if (rows_ * cols_ != other.GetRows * other.GetCols) {
        deleteMatrix(*this);
        rows_ = other.GetRows;
        cols_ = other.GetCols;
        createMatrix(*this);
    }
    std::memcpy(matrix_, other.matrix_, other.GetCols * other.GetRows * sizeof(double));
    other.matrix_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

void S21Matrix::deleteMatrix(S21Matrix& m){
    if (m.matrix_) {
        for (auto i = 0; i < m.GetRows; i++) {
            delete[] m.matrix_[i];
        }
    }
    delete[] m.matrix_;
    m.GetRows = 0;
    m.GetCols = 0;
}

// destructor
S21Matrix::~S21Matrix() {
    deleteMatrix(*this);
}

//getter of rows
int S21Matrix::GetRows() {
    return rows_;
}

//getter of cols
int S21Matrix::GetCols() {
    return cols_;
}

//setter for rows
void S21Matrix::SetRows(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Rows must be positive");
    }
    rows_ = n;
};

//setter for cols
void S21Matrix::SetCols(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Cols must be positive");
    }
    cols_ = n;
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    bool equal = true;
    if (rows_ != other.GetRows && cols_ != other.GetCols) {
        equal = false;
    }
    else {
        for (auto i = 0; i < rows_; i++) {
            for (auto j = 0; j < cols_; j++) {
                if (matrix_[i][j] != other.matrix_[i][j]) {
                    equal = false;
                }
            }
        }
    }
    return equal;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (rows_ != other.GetRows || cols_ != other.GetCols) {
        throw std::out_of_range(
            "Incorrect input, matrices should have the same size");
    }
    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < cols_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ != other.GetRows || cols_ != other.GetCols) {
        throw std::logic_error(
            "Incorrect input, matrices should have the same size");
    }
    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < cols_; j++) {
            matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num) {
    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (cols_ != other.GetRows) {
        throw std::logic_error(
            "Incorrect input, the number of inputed rows must be equal to the number of columns of the first matrix");
    }
    S21Matrix result(rows_, other.GetCols);
    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < other.GetCols; j++) {
            result.matrix_[i][j] = 0;
            for (auto k = 0; k < cols_; k++) {
                result.matrix_[i][j] += 
            }
        }
    }
    deleteMatrix(*this);
    *this = result;
    deleteMatrix(result);
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix result(cols_, rows_);
    for (auto i = 0; i < rows_; i++) {
        for (auto j = 0; j < cols_; j++;) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

double S21Matrix::Determinant() {
    if (rows_ != cols_) {
        throw std::logic_error("The matrix is not square.");
    }
    double result = 0.0;
    if (rows_ == 1) {
        result = matrix_[0][0];
    }
    else {
        // S21Matrix temp(rows_ - 1, cols_ -1);
        for (auto i = 0; i < rows_; i++) {
            S21Matrix temp = GetMinor(0, i, this);
            result += pow(-1, i) * matrix_[0][i] * temp.Determinant();
            temp.deleteMatrix();
        }
    }
    return result;

}

S21Matrix GetMinor(int rows, int cols, S21Matrix matrix) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }
    S21Matrix result(rows, cols);
    int currentRow = 0;
    for (auto i = 0; i < matrix.GetRows(); i++) {
        if (i == rows) {
            continue;
        }
        int curentCol = 0;
        for (auto j = 0; j < matrix.GetCols(); j++) {
            if (j == cols) {
                continue;
            }
            result.matrix_[currentRow][currentCol] = matrix.matrix_[i][j];
            curentCol++;
        }
        currentRow++;
    }
    return result;
}

S21Matrix S21Matrix::CalcComplements() {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and columns must be positive");
    }

    S21Matrix result(rows_, cols_);
    if (rows_ == 1 && cols_ == 1) {
        result.matrix_[0][0] = matrix_[0][0];
    }
    else {
        for (auto i = 0; i < rows_; i++) {
            for(auto j = 0; j < cols_; j++) {
                S21Matrix minor = GetMinor(i, j, this);
                double det = minor.Determinant();
                result.matrix_[i][j] = det * pow(-1, (i + j));
                minor.deleteMatrix();
            }
        }
    }
    return result;
}

S21Matrix S21Matrix::InverseMatrix() {
    if (rows_ != cols_) {
        throw std::logic_error("The matrix is not square.");
    }
    double det = Determinant();
    if (det == 0) {
        throw std::exception("Zero determinant.");
    }

    S21Matrix complements = CalcComplements();
    S21Matrix transponse = Transpose();
    S21Matrix result = complements.MulMatrix(transponse);

    deleteMatrix(*complements);
    deleteMatrix(*transponse);

    return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    deleteMatrix(*this);
    S21Matrix result(other);
    return result;

}

// index operator overload
double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::logic_error("Incorrect input, index is out of range");

  return matrix_[row][col];
}

// operator + overload
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    // creating result matrix
    S21Matrix result(rows_, cols_);
    result.SumMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix result(rows_, cols_);
    result.SubMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    S21Matrix result(rows_, cols_);
    result.MulMatrix(other);
    return result;
}

S21Matrix S21Matrix::operator*(double num) {
    S21Matrix result(rows_, cols_);
    result.MulNumber(num);
    return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other){
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    MulMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
    MulNumber(number);
    return *this;
}
