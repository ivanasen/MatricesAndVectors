#pragma once

#include <ostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include "Array2DWrapper.hpp"

namespace matrices {

	template<class T, unsigned int H, unsigned int W>
	class Matrix : public Array2DWrapper<T, H, W> {
	public:
		Matrix(const std::initializer_list<std::vector<T>> &values) : Array2DWrapper<T, H, W>(values) {
		}

		explicit Matrix(const std::vector<std::vector<T>> &values) : Array2DWrapper<T, H, W>(values) {
		}

		Matrix(const Matrix &source) : Array2DWrapper<T, H, W>(source) {
		}

		Matrix add(Matrix<T, H, W> &other) {
			std::vector<std::vector<T>> sumMatrix = this->m_array;
			sumMatrix.reserve(H);

			for (int i = 0; i < H; i++) {
				sumMatrix[i].reserve(W);
				for (int j = 0; j < W; j++) {
					sumMatrix[i][j] = this->m_array[i][j] + other[i][j];
				}
			}

			Matrix<T, H, W> sum(sumMatrix);
			return sum;
		}

		Matrix operator+(Matrix<T, H, W> &other) {
			Matrix<T, H, W> sum = add(other);
			return sum;
		}

		Matrix multiply(double scalar) const {
			std::vector<std::vector<T>> resultMatrix = this->m_array;
			for (auto &row : resultMatrix) {
				for (T &val : row) {
					val *= scalar;
				}
			}
			auto result = Matrix<T, H, W>{resultMatrix};
			return result;
		}

		template<unsigned int W2>
		Matrix multiply(Matrix<T, W, W2> &other) const {
			std::vector<std::vector<T>> productMatrix(H, std::vector<T>(W2));

			for (int i = 0; i < W; i++) {
				for (int j = 0; j < W; j++) {
					productMatrix[i][j] = 0;
					for (int k = 0; k < W; k++) {
						productMatrix[i][j] += this->m_array[i][k] * other[k][j];
					}
				}
			}

			Matrix<T, H, W2> product(productMatrix);
			return product;
		}

		// TODO: Implement determinant
		T det() const {
			T det = 0;


			return det;
		}

		Matrix operator*(double scalar) const {
			Matrix<T, H, W> result = multiply(scalar);
			return result;
		}

		template<unsigned int W2>
		Matrix operator*(Matrix<T, W, W2> &other) const {
			Matrix<T, H, W> result = multiply(other);
			return result;
		}


	};

}
