//
// Created by Carisa Braxton on 1/26/24.
//
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "../matrix_oop.h"

class MatrixTest : public testing::Test {
 protected:
    Matrix *matrix_1x1;
    Matrix *matrix_2x3;
    Matrix *matrix_5x5;
    Matrix *matrix_12x21;
    Matrix *matrix_21x21;

  void SetUp();
  void TearDown();
  void FillMatrixWithRandomDouble(Matrix &matrix);
  void PrintMatrix(const Matrix &matrix);
};
#endif  //UNIT_TEST_H
