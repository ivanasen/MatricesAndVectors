#pragma once

#include <cmath>
#include "Matrix.hpp"

namespace matrices {
	template<class T, unsigned int S>
	class Vector : public Matrix<T, 1, S> {
	public:
		Vector(const std::initializer_list<T> &values) : Matrix<T, 1, S>(std::vector<std::vector<T>>(1, values)) {
		}

		explicit Vector(const std::vector<std::vector<T>> &values) : Matrix<T, 1, S>(values) {
		}

		Vector(const Vector &source) : Matrix<T, 1, S>(source) {
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
			T magnitude = magnitude();
			for (T &val : this->m_array) {
				val /= magnitude;
			}
			return *this;
		}

		T scalar(Vector &other) {
			T product = 0;
			for (int i = 0; i < S; i++) {
				product += this->m_array[0][i] * other.get(i);
			}
			return product;
		}

		Vector<T, 3> cross(Vector<T, 3> &other) {
			if (S != 3) {
				throw std::invalid_argument("Cross product is only defined for 3-Dimensional vectors.");
			}

			Vector<T, 3> crossProduct{get(1) * other.get(2) - get(2) * other.get(1),
			                          get(2) * other.get(0) - get(0) * other.get(2),
			                          get(0) * other.get(1) - get(1) * other.get(0)};
			return crossProduct;
		}

		const T &get(const int &index) const {
			return this->m_array[0][index];
		}

		unsigned long size() {
			return this->width();
		}
	};
}
