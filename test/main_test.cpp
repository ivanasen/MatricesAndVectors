#include <gtest/gtest.h>
#include <Vector.hpp>
#include "Matrix.hpp"

TEST(TestMatrix, ShouldCreateMatrixCorrectly) {
	std::vector<std::vector<int>> values{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};
	linalg::Matrix<int, 3, 3> matrix(values);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(matrix[i][j], values[i][j]);
		}
	}
}

TEST(TestMatrix, ShouldAddTwoMatrices) {
	linalg::Matrix<int, 3, 3> first{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	linalg::Matrix<int, 3, 3> second{
			{12, 21, 31},
			{42, 51, 61},
			{72, 81, 91}
	};

	linalg::Matrix result = first + second;

	for (int i = 0; i < result.height(); i++) {
		for (int j = 0; j < result.width(); j++) {
			ASSERT_EQ(result[i][j], first[i][j] + second[i][j]);
		}
	}
}

TEST(TestMatrix, ShouldMutliplyWithScalar) {
	linalg::Matrix<int, 3, 3> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	double scalar = 3;
	linalg::Matrix<int, 3, 3> result = matrix * scalar;

	for (int i = 0; i < result.height(); i++) {
		for (int j = 0; j < result.width(); j++) {
			ASSERT_EQ(result[i][j], matrix[i][j] * scalar);
		}
	}
}

TEST(TestMatrix, ShouldMutliplyWithMatrix) {
	linalg::Matrix<int, 3, 3> matrix1{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	linalg::Matrix<int, 3, 3> matrix2{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
	};

	linalg::Matrix<int, 3, 3> result = matrix1 * matrix2;

	for (int i = 0; i < result.height(); i++) {
		for (int j = 0; j < result.width(); j++) {
			int cell = 0;
			for (int k = 0; k < result.height(); k++) {
				cell += matrix1[i][k] * matrix2[k][j];
			}
			ASSERT_EQ(result[i][j], cell);
		}
	}
}

TEST(TestMatrix, ShouldCalculateDeterminant) {
	linalg::Matrix<double, 2, 2> matrix{
			{2, 43},
			{1, 2},
	};
	ASSERT_EQ(-39, matrix.determinant());
}

TEST(TestMatrix, ShouldKnowIfMatrixIsOdd) {
	linalg::Matrix<double, 2, 3> matrix{
			{2, 43, 23},
			{1, 2,  2323},
	};
	ASSERT_EQ(true, matrix.isOdd());
}

TEST(TestMatrix, ShouldReturnZeroDeterminant) {
	linalg::Matrix<double, 3, 3> matrix1{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
	};
	ASSERT_EQ(0, matrix1.determinant());

	linalg::Matrix<double, 2, 3> matrix2{
			{2, 43, 23},
			{1, 2,  2323},
	};
	ASSERT_EQ(0, matrix2.determinant());
}

TEST(TestMatrix, ShouldTransposeMatrix) {
	linalg::Matrix<int, 3, 4> matrix{
			{1, 2, 3, 2},
			{4, 5, 6, 5},
			{7, 8, 9, 5}
	};
	linalg::Matrix<int, 4, 3> transposed = matrix.transpose();
	for (int i = 0; i < matrix.height(); i++) {
		for (int j = 0; j < matrix.width(); j++) {
			ASSERT_EQ(matrix[i][j], transposed[j][i]);
		}
	}
}

TEST(TestMatrix, ShouldErrorIfNoInverse) {
	linalg::Matrix<int, 3, 4> matrix{
			{1, 2, 3, 2},
			{4, 5, 6, 5},
			{7, 8, 9, 5}
	};
	EXPECT_THROW(matrix.invert(), std::invalid_argument);
}

TEST(TestVector, ShouldCalculateMagnitudeCorrectly) {
	linalg::Vector<double, 3> vector{1, 2, 2};
	ASSERT_EQ(3, vector.magnitude());
}

TEST(TestVector, ShouldNormalizeVectorCorrectly) {
	linalg::Vector<double, 3> vector{34, 12, 3};
	double magnitude = vector.magnitude();
	vector.normalize();
	ASSERT_EQ(vector[0], 34 / magnitude);
	ASSERT_EQ(vector[1], 12 / magnitude);
	ASSERT_EQ(vector[2], 3 / magnitude);
}

TEST(TestVector, ShouldCalculateScalarProductCorrectly) {
	linalg::Vector<double, 3> vector1{3, 12, 12};
	linalg::Vector<double, 3> vector2{23, 1, 11};
	double result = vector1.scalar(vector2);
	double expected = vector1[0] * vector2[0] +
	                  vector1[1] * vector2[1] +
	                  vector1[2] * vector2[2];
	ASSERT_EQ(result, expected);
}

TEST(TestVector, ShouldCalculateCrossProductCorrectly) {
	linalg::Vector<double, 3> vector1{3, 12, 12};
	linalg::Vector<double, 3> vector2{23, 87, 11};
	linalg::Vector<double, 3> product = vector1.cross(vector2);
	linalg::Vector<double, 3> expected{-912, 243, -15};
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(product[i], expected[i]);
	}
};
