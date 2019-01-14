#pragma once

#include <cmath>
#include "Matrix.hpp"

namespace linalg {
	template<class T>
	class Vector : public Matrix<T> {
	public:
		Vector(const std::initializer_list<T> &values) : Matrix<T>(std::vector<std::vector<T>>(1, values)) {
		}

		explicit Vector(const std::vector<std::vector<T>> &values) : Matrix<T>(values) {
		}

		explicit Vector(const std::vector<T> &values) : Matrix<T>(std::vector<std::vector<T>>(1, values)) {
		}

		Vector(const Matrix<T> &source) : Matrix<T>(source) {
		}

		T magnitude() {
			T magnitude = 0;
			for (T &val : this->m_array[0]) {
				magnitude += val * val;
			}
			magnitude = std::sqrt(magnitude);
			return magnitude;
		}

		Vector normalize() {
			T vectorMagnitude = magnitude();
			for (T &val : this->m_array[0]) {
				val /= vectorMagnitude;
			}
			return *this;
		}

		T scalar(Vector &other) {
			T product = 0;
			for (int i = 0; i < this->size(); i++) {
				product += (*this)[i] * other[i];
			}
			return product;
		}

		Vector cross(Vector &other) {
			if (this->size() != 3) {
				throw std::invalid_argument("Cross product is only defined for 3-Dimensional vectors.");
			}

			Vector crossProduct{(*this)[1] * other[2] - (*this)[2] * other[1],
			                    (*this)[2] * other[0] - (*this)[0] * other[2],
			                    (*this)[0] * other[1] - (*this)[1] * other[0]};
			return crossProduct;
		}

		const T &operator[](int index) {
			return this->m_array[0][index];
		}

		unsigned long size() {
			return this->width();
		}
	};
}
