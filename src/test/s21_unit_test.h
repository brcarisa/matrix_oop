//
// Created by Carisa Braxton on 1/26/24.
//
#ifndef S21_MATRIX_S21_UNIT_TEST_H
#define S21_MATRIX_S21_UNIT_TEST_H

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "../matrix_oop.h"

class S21MatrixTest : public testing::Test {
 protected:
  S21Matrix *matrix_1x1;
  S21Matrix *matrix_2x3;
  S21Matrix *matrix_5x5;
  S21Matrix *matrix_12x21;
  S21Matrix *matrix_21x21;

  void SetUp();
  void TearDown();
  void FillMatrixWithRandomDouble(S21Matrix &matrix);
  void PrintMatrix(const S21Matrix &matrix);
};
#endif  // S21_MATRIX_S21_UNIT_TEST_H
