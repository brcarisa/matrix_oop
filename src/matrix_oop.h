#ifndef MATRIX_OOP_H
#define MATRIX_OOP_H
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  // supportFunctions
  void Allocate_mem();
  bool IsRowsAndColsEqual(Matrix a1);
  bool IsMatrixSquare();
  S21Matrix GetMinor(int rows_new, int cols_new);
  void CopyValuesMatrix(const Matrix& other);
  void FreeMatrixMemory();

 public:
  // constructorsAndDestructors
  Matrix();
  Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
  ~Matrix();

  // accessorsMutators
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // operatorsOverload
  Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*(double num) const;
  friend Matrix operator*(double, Matrix& matrix);
  bool operator==(const Matrix& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const double num);
  double& operator()(int row, int col);
  double& operator()(int row, int col) const;

  // mainMethods
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
    Matrix Transpose();
    Matrix CalcComplements();
  double Determinant();
    Matrix InverseMatrix();
};

#endif  //MATRIX_OOP_H
