#include <gtest/gtest.h>
#include "Scalar.hpp"

TEST(TestScalar, ShouldScaleMatrixCorrectly) {
	linalg::Scalar<double> scalar(10);
	linalg::Matrix<double> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};
	linalg::Matrix<double> result = scalar * matrix;
	for (int i = 0; i < matrix.height(); i++) {
		for (int j = 0; j < matrix.width(); j++) {
			ASSERT_EQ(matrix[i][j] * scalar.value(), result[i][j]);
		}
	}
}

TEST(TestScalar, ShouldAddScalarToMatrixCorrectly) {
	linalg::Scalar<double> scalar(10);
	linalg::Matrix<double> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};
	linalg::Matrix<double> result = scalar + matrix;
	for (int i = 0; i < matrix.height(); i++) {
		ASSERT_EQ(matrix[i][i] + scalar.value(), result[i][i]);
	}
}

TEST(TestScalar, ShouldDivideMatrixByScalarCorrectly) {
	linalg::Scalar<double> scalar(10);
	linalg::Matrix<double> matrix{
			{10, 20, 30},
			{40, 50, 60},
			{70, 80, 90}
	};
	linalg::Matrix<double> result = matrix / scalar;
	for (int i = 0; i < matrix.height(); i++) {
		for (int j = 0; j < matrix.width(); j++) {
			ASSERT_EQ(matrix[i][j] / scalar.value(), result[i][j]);
		}
	}
}