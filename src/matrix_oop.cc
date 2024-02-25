#include "matrix_oop.h"
// constructorsAndDestructors
Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
Matrix::Matrix(int rows, int columns) : rows_(rows), cols_(columns) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument(
        "CreationError: The number of rows or cols cannot be less than 1");
  }
  Allocate_mem();
}
Matrix::Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  Allocate_mem();
  CopyValuesMatrix(other);
}
Matrix::Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
Matrix::~Matrix() { FreeMatrixMemory(); }

// accessorsMutators
int Matrix::GetRows() const { return rows_; }
int Matrix::GetCols() const { return cols_; }
void Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::invalid_argument(
        "SettingColsError: The number of cols cannot be less than 1");
  }
    Matrix sup_matrix(rows_, cols);
  int NewCols = (cols < cols_) ? cols : cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < NewCols; j++) {
      sup_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = sup_matrix;
}
void Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range(
        "SettingRowsError: The number of rows cannot be less than 1");
  }
    Matrix sup_matrix(rows, cols_);
  int NewRows = (rows < rows_) ? rows : rows_;
  for (int i = 0; i < NewRows; i++) {
    for (int j = 0; j < cols_; j++) {
      sup_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = sup_matrix;
}

// operatorsOverload
Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    FreeMatrixMemory();
    rows_ = other.rows_;
    cols_ = other.cols_;
    Allocate_mem();
    CopyValuesMatrix(other);
  }
  return *this;
}
Matrix Matrix::operator+(const Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}
Matrix Matrix::operator-(const Matrix& other) {
    Matrix res(*this);
  res.SubMatrix(other);
  return res;
}
Matrix Matrix::operator*(const Matrix& other) {
    Matrix res(*this);
  res.MulMatrix(other);
  return res;
}
Matrix Matrix::operator*(double num) const {
    Matrix res_matrix(*this);
  res_matrix.MulNumber(num);
  return res_matrix;
}
Matrix operator*(double num, Matrix& matrix) { return matrix * num; }

bool Matrix::operator==(const Matrix& other) { return (EqMatrix(other)); }
Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}
Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}
Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}
Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
double& Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  return matrix_[row][col];
}

double& Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  return matrix_[row][col];
}

// mainMethods
bool Matrix::EqMatrix(const Matrix& other) {
  bool isMatricesEqual = true;
  if (!IsRowsAndColsEqual(other)) {
    return false;
  }
  for (int i = 0; i < rows_ && isMatricesEqual; i++) {
    for (int j = 0; j < cols_ && isMatricesEqual; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-16)
        isMatricesEqual = false;
    }
  }
  return isMatricesEqual;
}
void Matrix::SumMatrix(const Matrix& other) {
  if (!IsRowsAndColsEqual(other)) {
    throw std::range_error("SumMatrixError: Matrices of different dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}
void Matrix::SubMatrix(const Matrix& other) {
  if (!IsRowsAndColsEqual(other)) {
    throw std::range_error("SumMatrixError: Matrices of different dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}
void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}
void Matrix::MulMatrix(const Matrix& other) {
  if (rows_ != other.cols_) {
    throw std::range_error(
        "MulMatrixError: Incorrect dimensions to multiply two matrices");
  }
    Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double res_sum = 0;
      for (int k = 0; k < cols_; k++) {
        res_sum += matrix_[i][k] * other.matrix_[k][j];
      }
      res.matrix_[i][j] = res_sum;
    }
  }
  *this = res;
}
Matrix Matrix::Transpose() {
    Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}
Matrix Matrix::CalcComplements() {
  if (!IsMatrixSquare()) {
    throw std::range_error("CalcComplementsError: The matrix must be square");
  }
    Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      int sign = i % 2 == 0 ? 1 : -1;
      for (int j = 0; j < cols_; j++) {
          Matrix minor(GetMinor(i, j));
        res.matrix_[i][j] = sign * minor.Determinant();
        sign = -sign;
      }
    }
  }

  return res;
}
double Matrix::Determinant() {
  if (!IsMatrixSquare()) {
    throw std::range_error("DeterminantError: The matrix must be square");
  }

  double num = 0;
  if (rows_ == 1) {
    num = matrix_[0][0];
  } else if (rows_ == 2) {
    num = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    int sign = 1;
    for (int i = 0; i < cols_; i++) {
        Matrix minor(GetMinor(0, i));
      num += sign * matrix_[0][i] * minor.Determinant();
      sign = -sign;
    }
  }
  return num;
}
Matrix Matrix::InverseMatrix() {
  double determinant = Determinant();
  if (!Determinant() || !IsMatrixSquare()) {
    throw std::range_error(
        "InverseError: Incompatible matrix sizes to search inverse matrix");
  }

    Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    res = CalcComplements().Transpose();
    res.MulNumber(1 / determinant);
  }
  return res;
}

// supportFunctions
void Matrix::Allocate_mem() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0.0;
    }
  }
}
void Matrix::CopyValuesMatrix(const Matrix& other) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}
void Matrix::FreeMatrixMemory() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}
bool Matrix::IsRowsAndColsEqual(Matrix a1) {
  return (rows_ == a1.rows_ && cols_ == a1.cols_);
}
bool Matrix::IsMatrixSquare() { return (rows_ == cols_); }
Matrix Matrix::GetMinor(int rows, int cols) {
    Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0, minor_row = 0; i < rows_; i++) {
    if (i != rows) {
      for (int j = 0, minor_col = 0; j < cols_; j++) {
        if (j != cols) {
          minor.matrix_[minor_row][minor_col] = matrix_[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
  return minor;
}