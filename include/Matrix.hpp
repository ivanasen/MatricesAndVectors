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

		Matrix add(Matrix &other) {
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

		Matrix scale(double scalar) const {
			std::vector<std::vector<T>> resultMatrix = this->m_array;
			for (auto &row : resultMatrix) {
				for (T &val : row) {
					val *= scalar;
				}
			}
			Matrix result{resultMatrix};
			return result;
		}

		template<unsigned int W2>
		Matrix<T, W, W2> multiply(Matrix<T, W, W2> &other) const {
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

		// TODO: Implement matrix inversion
		Matrix invert() const {
			if (W != H) {
				throw std::invalid_argument("Matrix must be square in order to have an inverse.");
			}
			Matrix result(this->m_array);
			return result;
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

		Matrix operator+(Matrix &other) {
			Matrix sum = add(other);
			return sum;
		}

		Matrix operator*(double scalar) const {
			Matrix result = scale(scalar);
			return result;
		}

		template<unsigned int W2>
		Matrix<T, H, W2> operator*(Matrix<T, W, W2> &other) const {
			Matrix<T, H, W2> result = multiply(other);
			return result;
		}

		bool isOdd() {
			return determinant() == 0;
		}

		Matrix getUpperTriangularForm() {
			std::vector<std::vector<T>> triangularArray = this->m_array;
			convertToUpperTriangularForm(triangularArray);
			Matrix triangle(triangularArray);
			return triangle;
		}

	private:
		void convertToUpperTriangularForm(std::vector<std::vector<T>> &matrix, int colToRemove = 0) {
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
	};

}
