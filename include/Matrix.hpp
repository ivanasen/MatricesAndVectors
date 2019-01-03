#pragma once

#include <ostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <type_traits>


namespace matrices {

	template<class T, unsigned int Height, unsigned int Width>
	class Matrix {
	private:
		std::vector<T> m_values;
		std::vector<int> m_shape;
	public:
		Matrix(const std::initializer_list<T> &values) : m_values(values) {
		}

		explicit Matrix(const std::vector<T> &values) : m_values(values) {
		}

		Matrix(const Matrix &source) : m_values(source.getRawValues()) {
		}

		const std::vector<T> &getRawValues() const {
			return m_values;
		}

		Matrix add(const Matrix &other) const {
			std::vector<T> resultValues = m_values;
			std::vector<T> otherValues = other.getRawValues();
			for (int i = 0; i < m_values.size(); i++) {
				resultValues[i] = m_values[i] + otherValues[i];
			}
			auto result = Matrix<T>(resultValues);
			return result;
		}

		Matrix operator+(const Matrix &other) const {
			Matrix<T> result = add(other);
			return result;
		}

		Matrix multiply(double scalar) const {
			std::vector<T> resultValues = m_values;
			for (T &val : resultValues) {
				val *= scalar;
			}
			auto result = Matrix<T>{resultValues};
			return result;
		}

		Matrix multiply(Matrix other) const {
			// TODO: Implement mulitplication
		}

		Matrix operator*(double scalar) const {
			Matrix<T> result = multiply(scalar);
			return result;
		}

		std::string to_string() const {
			std::string result;
			result += "[ ";
			for (const T &val : m_values) {
				result += val + ", ";
			}
			result += " ] ";
			return result;
		}

		template<class U>
		friend std::ostream &operator<<(std::ostream &stream, const Matrix<U> &Matrix) {
			stream << Matrix.to_string();
			return stream;
		}


	};

}
