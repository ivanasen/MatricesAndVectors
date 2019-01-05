#pragma once

#include <ostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include <stdexcept>
#include "Array2DWrapper.hpp"

namespace linalg {


	template<class T>
	class Matrix : public Array2DWrapper<T> {
	public:
		Matrix(const std::initializer_list<std::vector<T>> &values) : Array2DWrapper<T>(values) {
		}

		explicit Matrix(const std::vector<std::vector<T>> &values) : Array2DWrapper<T>(values) {
		}

		Matrix(const unsigned long &height, const unsigned long &width) : Array2DWrapper<T>(height, width) {
		}

		Matrix(const Matrix &source) : Array2DWrapper<T>(source) {
		}

		Matrix add(Matrix &other) {
			std::vector<std::vector<T>> sumMatrix = this->m_array;

			for (int i = 0; i < this->height(); i++) {
				for (int j = 0; j < this->width(); j++) {
					sumMatrix[i][j] = (*this)[i][j] + other[i][j];
				}
			}

			Matrix<T> sum(sumMatrix);
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

		Matrix<T> multiply(Matrix<T> &other) {
			auto height = this->height();
			auto width = this->width();
			auto otherHeight = other.height();
			auto otherWidth = other.width();

			if (width != otherHeight) {
				throw std::invalid_argument("First Matrix's columns have to be the same count as the second\'s rows.");
			}

			std::vector<std::vector<T>> productMatrix(height, std::vector<T>(otherWidth));

			for (int i = 0; i < width; i++) {
				for (int j = 0; j < width; j++) {
					productMatrix[i][j] = 0;
					for (int k = 0; k < width; k++) {
						productMatrix[i][j] += (*this)[i][k] * other[k][j];
					}
				}
			}

			Matrix<T> product(productMatrix);
			return product;
		}

		Matrix<T> transpose() {
			auto width = this->width();
			auto height = this->height();

			std::vector<std::vector<T>> transposedMatrix(width, std::vector<T>(height));
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					transposedMatrix[i][j] = (*this)[j][i];
				}
			}
			Matrix<T> transposed(transposedMatrix);
			return transposed;
		}

		Matrix inverse() {
			if (this->width() != this->height()) {
				throw std::invalid_argument("Matrix must be square in order to have an inverse.");
			}

			T det = determinant();
			if (det == 0) {
				throw std::invalid_argument("Matrix\'s rows are linearly dependant, so it doesn\'t have an inverse");
			}

			Matrix adjoint = getAdjointMatrix();

			unsigned long size = this->height();
			std::vector<std::vector<T>> inverse(size, std::vector<T>(size));

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					inverse[i][j] = adjoint[i][j] / det;
				}
			}

			Matrix inverseMatrix(inverse);
			return inverseMatrix;
		}

		T determinant() {
			if (this->height() != this->width()) {
				return 0;
			}

			if (this->width() == 2) {
				return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			}

			std::vector<std::vector<T>> triangularForm = this->m_array;
			convertToUpperTriangularForm(triangularForm);

			T det = triangularForm[0][0];
			for (int i = 1; i < this->height(); i++) {
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

		Matrix<T> operator*(Matrix<T> &other) {
			Matrix<T> result = multiply(other);
			return result;
		}

		bool isOdd() {
			return determinant() == 0;
		}

		Matrix toDiagonalMatrix() {
			if (this->height() != this->width()) {
				throw std::invalid_argument("Non-Square Matrices don\'t have a diagonal matrix.");
			}
			std::vector<std::vector<T>> triangularArray = this->m_array;
			convertToUpperTriangularForm(triangularArray);

			if (hasZeroRows(triangularArray)) {
				throw std::invalid_argument("Matrices with linearly dependant rows don\'t have a diagonal matrix.");
			}

			convertToLowerTriangularForm(triangularArray);
			if (hasZeroRows(triangularArray)) {
				throw std::invalid_argument("Matrices with linearly dependant rows don\'t have a diagonal matrix.");
			}

			Matrix triangle(triangularArray);
			return triangle;
		}

		static Matrix makeIdentity(unsigned int size) {
			std::vector<std::vector<T>> identity(size, std::vector<T>(size));
			for (int i = 0; i < size; i++) {
				identity[i][i] = 1;
			}
			Matrix<T> identityMatrix(identity);
			return identityMatrix;
		}

		Matrix getCofactor(int rowToRemove, int colToRemove) {
			std::vector<std::vector<T>> cofactor(this->height() - 1, std::vector<T>(this->width() - 1));

			for (int row = 0, cofactorRow = 0; row < this->height(); row++) {
				if (row == rowToRemove) {
					continue;
				}
				for (int col = 0, cofactorCol = 0; col < this->width(); col++) {
					if (col == colToRemove) {
						continue;
					}
					cofactor[cofactorRow][cofactorCol++] = (*this)[row][col];
				}
				cofactorRow++;
			}

			Matrix cofactorMatrix(cofactor);
			return cofactorMatrix;
		}

	private:
		Matrix getAdjointMatrix() {
			auto size = this->height();
			std::vector<std::vector<T>> adjoint(size, std::vector<T>(size));

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					Matrix cofactor = getCofactor(i, j);
					int sign = (i + j) % 2 == 0 ? 1 : -1;
					adjoint[j][i] = sign * cofactor.determinant();
				}
			}

			Matrix adjointMatrix(adjoint);
			return adjointMatrix;
		}

		static void convertToUpperTriangularForm(std::vector<std::vector<T>> &matrix, int colToRemove = 0) {
			if (colToRemove == matrix.size() - 1) {
				return;
			}

			for (int i = colToRemove + 1; i < matrix.size(); i++) {
				double scalar = -(matrix[i][colToRemove] / matrix[colToRemove][colToRemove]);
				for (int j = colToRemove; j < matrix[0].size(); j++) {
					matrix[i][j] += matrix[colToRemove][j] * scalar;
				}
			}

			convertToUpperTriangularForm(matrix, colToRemove + 1);
		}

		static void convertToLowerTriangularForm(std::vector<std::vector<T>> &matrix, int padding = 0) {
			long colToRemove = matrix[0].size() - 1 - padding;

			if (padding == matrix[0].size() - 1) {
				return;
			}

			for (long i = colToRemove - 1; i >= 0; i--) {
				double scalar = -(matrix[i][colToRemove] / matrix[colToRemove][colToRemove]);
				for (long j = colToRemove; j >= 0; j--) {
					matrix[i][j] += matrix[colToRemove][j] * scalar;
				}
			}

			convertToLowerTriangularForm(matrix, padding + 1);
		}

		static bool hasZeroRows(const std::vector<std::vector<T>> &matrix) {
			for (const std::vector<T> &row : matrix) {
				int i = 0;
				while (i < row.size() && row[i] == 0) {
					if (i == row.size() - 1) {
						return true;
					}
					i++;
				}
			}
			return false;
		}
	};

}
