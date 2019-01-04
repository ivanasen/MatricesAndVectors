#pragma once

#include "Matrix.hpp"

namespace matrices {
	template<class T, unsigned int S>
	class Vector : public Matrix<T, 1, S> {
		Vector(const std::initializer_list<std::vector<T>> &values) : Matrix<T, 1, S>(values) {
		}

		explicit Vector(const std::vector<std::vector<T>> &values) : Matrix<T, 1, S>(values) {
		}

		Vector(const Vector &source) : Matrix<T, 1, S>(source) {
		}
	};
}
