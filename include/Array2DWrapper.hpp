#pragma once

#include <vector>
#include <initializer_list>

namespace matrices {

	template<class T, unsigned int H, unsigned int W>
	class Array2DWrapper {
	protected:
		std::vector<std::vector<T>> m_array;
	public:
		Array2DWrapper(const std::initializer_list<std::vector<T>> &values) : m_array(values) {
		}

		explicit Array2DWrapper(const std::vector<std::vector<T>> &values) : m_array(values) {
		}

		Array2DWrapper(const Array2DWrapper &source) : m_array(source.getWrappedArray()) {
		}

		const T &get(const int &row, const int &col) const {
			return m_array[row][col];
		}

		unsigned long getHeight() const {
			return m_array.size();
		}

		unsigned long getWidth() const {
			return m_array[0].size();
		}

		const std::vector<std::vector<T>> &getWrappedArray() const {
			return m_array;
		}

		std::string toString() const {
			std::string result;
			for (auto &row : m_array) {
				for (const T &val : row) {
					result += std::to_string(val) + " ";
				}
				result += '\n';
			}
			result += '\n';
			return result;
		}

		template<class U>
		friend std::ostream &operator<<(std::ostream &stream, const Array2DWrapper<U, H, W> &array) {
			stream << array.toString();
			return stream;
		}

		class Proxy {
		public:
			explicit Proxy(const std::vector<T> &row) : m_row(row) {}

			int operator[](int index) {
				return m_row[index];
			}

		private:
			std::vector<T> m_row;
		};

		Proxy operator[](int index) {
			return Proxy(m_array[index]);
		}
	};
}
