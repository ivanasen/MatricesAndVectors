#include <gtest/gtest.h>
#include "Matrix.hpp"

TEST(TestMatrix, ShouldCreateMatrixCorrectly) {
	std::vector<std::vector<int>> values{
			{1, 22,  3},
			{4, 5,   6434},
			{7, 824, 9}
	};
	linalg::Matrix<int> matrix(values);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ASSERT_EQ(matrix[i][j], values[i][j]);
		}
	}
}

TEST(TestMatrix, ShouldModifyMatrixCellsCorrectly) {
	linalg::Array2DWrapper<int> array{
			{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1}
	};
	int expectedValue = 56;
	array[2][0] = expectedValue;

	ASSERT_EQ(array[2][0], expectedValue);
}

TEST(TestMatrix, ShouldAddTwoMatrices) {
	linalg::Matrix<int> first{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	linalg::Matrix<int> second{
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
	linalg::Matrix<int> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	double scalar = 3;
	linalg::Matrix<int> result = scalar * matrix;

	for (int i = 0; i < result.height(); i++) {
		for (int j = 0; j < result.width(); j++) {
			ASSERT_EQ(result[i][j], matrix[i][j] * scalar);
		}
	}
}

TEST(TestMatrix, ShouldDivideByScalar) {
	linalg::Matrix<double> matrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	double scalar = 3;
	linalg::Matrix<double> result = matrix / scalar;

	for (int i = 0; i < result.height(); i++) {
		for (int j = 0; j < result.width(); j++) {
			ASSERT_EQ(result[i][j], matrix[i][j] / scalar);
		}
	}
}

TEST(TestMatrix, ShouldMutliplyWithMatrix) {
	linalg::Matrix<int> matrix1{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9}
	};

	linalg::Matrix<int> matrix2{
			{1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
	};

	linalg::Matrix<int> result = matrix1 * matrix2;

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
	linalg::Matrix<double> matrix{
			{2, 43},
			{1, 2},
	};
	ASSERT_EQ(-39, matrix.det());
}

TEST(TestMatrix, ShouldKnowIfMatrixIsOdd) {
	linalg::Matrix<double> matrix{
			{2, 43, 23},
			{1, 2,  2323},
	};
	ASSERT_EQ(true, matrix.isOdd());
}

TEST(TestMatrix, ShouldReturnZeroDeterminant) {
	linalg::Matrix<double> matrix1{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
	};
	ASSERT_EQ(0, matrix1.det());


	linalg::Matrix<double> matrix2{
			{2, 43, 23},
			{1, 2,  2323},
	};
	ASSERT_EQ(0, matrix2.det());
}

TEST(TestMatrix, ShouldTransposeMatrix) {
	linalg::Matrix<int> matrix{
			{1, 2, 3, 2},
			{4, 5, 6, 5},
			{7, 8, 9, 5}
	};
	linalg::Matrix<int> transposed = matrix.transpose();
	for (int i = 0; i < matrix.height(); i++) {
		for (int j = 0; j < matrix.width(); j++) {
			ASSERT_EQ(matrix[i][j], transposed[j][i]);
		}
	}
}


TEST(TestMatrix, ShouldConvertToDiagonalMatrix) {
	linalg::Matrix<int> rectMatrix{
			{1, 2, 3, 2},
			{4, 5, 6, 5},
			{7, 8, 9, 5}
	};
	EXPECT_THROW(rectMatrix.toDiagonalMatrix(), std::invalid_argument);

	linalg::Matrix<double> squareMatrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 10}
	};

	auto diagonalMatrix = squareMatrix.toDiagonalMatrix();

	for (int i = 0; i < diagonalMatrix.height(); i++) {
		for (int j = 0; j < diagonalMatrix.width(); j++) {
			if (i == j) {
				ASSERT_NE(0, diagonalMatrix[i][j]);
			} else {
				ASSERT_EQ(0, diagonalMatrix[i][j]);
			}
		}
	}
}

TEST(TestMatrix, ShouldErrorIfNoInverse) {
	linalg::Matrix<int> matrix{
			{1, 2, 3, 2},
			{4, 5, 6, 5},
			{7, 8, 9, 5}
	};
	EXPECT_THROW(matrix.invert(), std::invalid_argument);
}

TEST(TestMatrix, ShouldFindInverseOfMatrix) {
	linalg::Matrix<double> rectMatrix{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 10}
	};

	linalg::Matrix<double> inverse = rectMatrix.invert();
	ASSERT_NE(0, inverse.det());
}