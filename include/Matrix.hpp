#pragma once

#include <ostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdexcept>
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

		T determinant() {
			if (H != W) {
				return 0;
			}

			std::vector<std::vector<T>> triangularForm = this->m_array;
			convertToUpperTriangularForm(triangularForm);

			T det = triangularForm[0][0];
			for (int i = 1; i < H; i++) {
				det *= triangularForm[i][i];
			}

			return det;
		}

		static void convertToUpperTriangularForm(std::vector<std::vector<T>> &matrix, int colToRemove = 0) {
			if (colToRemove == H - 1) {
				return;
			}

			for (int i = colToRemove + 1; i < H; i++) {
				double scalar = -(matrix[i][colToRemove] / matrix[colToRemove][colToRemove]);
				for (int j = colToRemove; j < W; j++) {
					matrix[i][j] += matrix[colToRemove][j] * scalar;
				}
			}

			convertToUpperTriangularForm(matrix, colToRemove + 1);
		}


		Matrix<T, W, H> transpose() const {
			std::vector<std::vector<T>> transposedMatrix(W, std::vector<T>(H));
			for (int i = 0; i < W; i++) {
				for (int j = 0; j < H; j++) {
					transposedMatrix[i][j] = this->m_array[j][i];
				}
			}
			Matrix<T, W, H> transposed(transposedMatrix);
			return transposed;
		}

		Matrix<T, W, H> inverse() const {

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

		bool isOdd() {
			return determinant() == 0;
		}
	};

}
