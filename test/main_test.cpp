#include <gtest/gtest.h>
#include "Matrix.hpp"

TEST(TestMatrix, ShouldCreateMatrixCorrectly) {
	std::vector<std::vector<int>> values{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};
	matrices::Matrix<int, 3, 3> matrix(values);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(matrix[i][j], values[i][j]);
		}
	}
}

TEST(TestMatrix, ShouldAddTwoMatrices) {
	matrices::Matrix<int, 3, 3> first{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	matrices::Matrix<int, 3, 3> second{
			{12, 21, 31},
			{42, 51, 61},
			{72, 81, 91}
	};

	matrices::Matrix result = first + second;

	for (int i = 0; i < result.getHeight(); i++) {
		for (int j = 0; j < result.getWidth(); j++) {
			ASSERT_EQ(result[i][j], first[i][j] + second[i][j]);
		}
	}
}

TEST(TestMatrix, ShouldMutliplyWithScalar) {
	matrices::Matrix<int, 3, 3> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	double scalar = 3;
	matrices::Matrix<int, 3, 3> result = matrix * scalar;

	for (int i = 0; i < result.getHeight(); i++) {
		for (int j = 0; j < result.getWidth(); j++) {
			ASSERT_EQ(result[i][j], matrix[i][j] * scalar);
		}
	}
}

TEST(TestMatrix, ShouldMutliplyWithMatrix) {
	matrices::Matrix<int, 3, 3> matrix1{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	matrices::Matrix<int, 3, 3> matrix2{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
	};

	matrices::Matrix<int, 3, 3> result = matrix1 * matrix2;

	for (int i = 0; i < result.getHeight(); i++) {
		for (int j = 0; j < result.getWidth(); j++) {
			int cell = 0;
			for (int k = 0; k < result.getHeight(); k++) {
				cell += matrix1[i][k] * matrix2[k][j];
			}
			ASSERT_EQ(result[i][j], cell);
		}
	}
}

TEST(TestMatrix, ShouldCalculateDeterminant) {
	matrices::Matrix<int, 2, 2> matrix {
			{2, 0},
			{0, 2},
	};
	ASSERT_EQ(4, matrix.det());
}