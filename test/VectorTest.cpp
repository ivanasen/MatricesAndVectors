#include <gtest/gtest.h>
#include "Vector.hpp"

TEST(TestVector, ShouldCalculateMagnitudeCorrectly) {
	linalg::Vector<double> vector{1, 2, 2};
	ASSERT_EQ(3, vector.magnitude());
}

TEST(TestVector, ShouldNormalizeVectorCorrectly) {
	linalg::Vector<double> vector{34, 12, 3};
	double magnitude = vector.magnitude();
	linalg::Vector normalised = vector.normalise();
	ASSERT_EQ(normalised[0], 34 / magnitude);
	ASSERT_EQ(normalised[1], 12 / magnitude);
	ASSERT_EQ(normalised[2], 3 / magnitude);
}

TEST(TestVector, ShouldCalculateDotProductCorrectly) {
	linalg::Vector<double> vector1{3, 12, 12};
	linalg::Vector<double> vector2{23, 1, 11};
	double result = vector1.dot(vector2);
	double expected = vector1[0] * vector2[0] +
	                  vector1[1] * vector2[1] +
	                  vector1[2] * vector2[2];
	ASSERT_EQ(result, expected);
}

TEST(TestVector, ShouldCalculateCrossProductCorrectly) {
	linalg::Vector<double> vector1{3, 12, 12};
	linalg::Vector<double> vector2{23, 87, 11};
	linalg::Vector<double> product = vector1.cross(vector2);
	linalg::Vector<double> expected{-912, 243, -15};
	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(product[i], expected[i]);
	}
};


TEST(TestVector, ShouldApplyLinearTransformation) {
	linalg::Matrix<double> transformation{
			{2, 0, 0},
			{0, 2, 0},
			{0, 0, 2}
	};
	linalg::Vector<double> vector{1, 23, 4};
	linalg::Vector<double> transformed = transformation * vector;

	for (int i = 0; i < 3; i++) {
		ASSERT_EQ(transformed[i], vector[i] * 2);
	}
}

