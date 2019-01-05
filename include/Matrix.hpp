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
			Matrix sum(*this);

			for (int i = 0; i < this->height(); i++) {
				for (int j = 0; j < this->width(); j++) {
					sum[i][j] += other[i][j];
				}
			}

			return sum;
		}

		Matrix scale(double scalar) const {
			Matrix scaled(*this);
			for (auto &row : scaled) {
				for (T &val : row) {
					val *= scalar;
				}
			}
			return scaled;
		}

		Matrix<T> multiply(Matrix<T> &other) {
			auto height = this->height();
			auto width = this->width();
			auto otherHeight = other.height();
			auto otherWidth = other.width();

			if (width != otherHeight) {
				throw std::invalid_argument("First Matrix's columns have to be the same count as the second\'s rows.");
			}

			Matrix product(height, otherWidth);

			for (int i = 0; i < width; i++) {
				for (int j = 0; j < width; j++) {
					product[i][j] = 0;
					for (int k = 0; k < width; k++) {
						product[i][j] += (*this)[i][k] * other[k][j];
					}
				}
			}

			return product;
		}

		Matrix<T> transpose() {
			auto width = this->width();
			auto height = this->height();

			Matrix transposed(width, height);
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < height; j++) {
					transposed[i][j] = (*this)[j][i];
				}
			}
			return transposed;
		}

		Matrix invert() {
			if (this->width() != this->height()) {
				throw std::invalid_argument("Matrix must be square in order to have an inverse.");
			}

			T determinant = det();
			if (determinant == 0) {
				throw std::invalid_argument("Matrix\'s rows are linearly dependant, so it doesn\'t have an inverse");
			}

			Matrix adjoint = getAdjointMatrix();

			unsigned long size = this->height();
			Matrix inverse(size, size);

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					inverse[i][j] = adjoint[i][j] / determinant;
				}
			}

			return inverse;
		}

		T det() {
			if (this->height() != this->width()) {
				return 0;
			}

			if (this->width() == 2) {
				return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			}

			Matrix triangularForm(*this);
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
			return det() == 0;
		}

		Matrix toDiagonalMatrix() {
			if (this->height() != this->width()) {
				throw std::invalid_argument("Non-Square Matrices don\'t have a diagonal matrix.");
			}

			Matrix triangular(*this);
			convertToUpperTriangularForm(triangular);

			if (hasZeroRows(triangular)) {
				throw std::invalid_argument("Matrices with linearly dependant rows don\'t have a diagonal matrix.");
			}

			convertToLowerTriangularForm(triangular);
			if (hasZeroRows(triangular)) {
				throw std::invalid_argument("Matrices with linearly dependant rows don\'t have a diagonal matrix.");
			}

			return triangular;
		}

		Matrix getCofactor(int rowToRemove, int colToRemove) {
			Matrix cofactor(this->height() - 1, this->width() - 1);

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

			return cofactor;
		}

		static Matrix makeIdentity(unsigned int size) {
			Matrix identity(size, size);
			for (int i = 0; i < size; i++) {
				identity[i][i] = 1;
			}
			return identity;
		}

	private:
		Matrix getAdjointMatrix() {
			auto size = this->height();
			Matrix adjoint(size, size);

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					Matrix cofactor = getCofactor(i, j);
					int sign = (i + j) % 2 == 0 ? 1 : -1;
					adjoint[j][i] = sign * cofactor.det();
				}
			}
			return adjoint;
		}

		static void convertToUpperTriangularForm(Matrix &matrix, int colToRemove = 0) {
			if (colToRemove == matrix.height() - 1) {
				return;
			}

			for (int i = colToRemove + 1; i < matrix.height(); i++) {
				double scalar = -(matrix[i][colToRemove] / matrix[colToRemove][colToRemove]);
				for (int j = colToRemove; j < matrix.width(); j++) {
					matrix[i][j] += matrix[colToRemove][j] * scalar;
				}
			}

			convertToUpperTriangularForm(matrix, colToRemove + 1);
		}

		static void convertToLowerTriangularForm(Matrix &matrix, int padding = 0) {
			long colToRemove = matrix.width() - 1 - padding;

			if (padding == matrix.width() - 1) {
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

		static bool hasZeroRows(const Matrix &matrix) {
			for (auto &row : matrix) {
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
