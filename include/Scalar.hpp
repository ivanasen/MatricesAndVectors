#pragma once

#include "Matrix.hpp"

namespace linalg {

	template<class T>
	class Scalar : public Matrix<T> {
	public:
		explicit Scalar(const T &value) : Matrix<T>(std::vector<std::vector<T>>(1, std::vector<T>(1, value))) {
		}

		explicit Scalar(const Matrix<T> &source) : Matrix<T>(
				std::vector<std::vector<T>>(1, std::vector<T>(1, source[0][0]))) {
		}

		friend Matrix<T> operator+(Matrix<T> matrix, Scalar<T> &scalar) {
			T value = scalar.value();
			return matrix + value;
		}

		friend Matrix<T> operator+(Scalar<T> &scalar, Matrix<T> &matrix) {
			T value = scalar.value();
			return matrix + value;
		}

		friend Matrix<T> operator*(Matrix<T> matrix, Scalar<T> &scalar) {
			T value = scalar.value();
			return matrix * value;
		}

		friend Matrix<T> operator*(Scalar<T> &scalar, Matrix<T> matrix) {
			T value = scalar.value();
			return matrix * value;
		}

		friend Matrix<T> operator/(Matrix<T> matrix, Scalar<T> &scalar) {
			T value = scalar.value();
			return matrix / value;
		}

		friend Matrix<T> operator/(Scalar<T> &scalar, Matrix<T> matrix) {
			throw std::invalid_argument("Can\'t divide scalars by matrices.");
		}

		friend const Scalar operator*(Matrix<T> &matrix, Scalar &Scalar) {
			auto ScalarMatrix = static_cast<Matrix<T>>(Scalar);
			return Scalar(matrix * ScalarMatrix);
		}

		T value() {
			return (*this)[0][0];
		}
	};

}
