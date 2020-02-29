#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>


template <typename T, size_t N>
class Matrix
{
public:
	using MatrixRowType = std::array<T, N>;
	using MatrixElementsType = std::array<MatrixRowType, N>;

	explicit Matrix(const T elements[N][N])
	{
		for (uint32_t i = 0; i < N; ++i)
		{
			for (uint32_t j = 0; j < N; ++j)
			{
				m_elements[i][j] = elements[i][j];
			}
		}
	}

	MatrixRowType& operator[](uint32_t row)
	{
		return m_elements[row];
	}

	MatrixRowType operator[](uint32_t row) const
	{
		return m_elements[row];
	}

	friend bool operator==(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs)
	{
		for (uint32_t i = 0; i < N; ++i)
		{
			for (uint32_t j = 0; j < N; ++j)
			{
				if (lhs[i][j] != rhs[i][j])
					return false;
			}
		}

		return true;
	}

	friend bool operator!=(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs)
	{
		return !(lhs == rhs);
	}

	friend Matrix<T, N> operator*(const Matrix<T, N>& lhs, const Matrix<T, N>& rhs)
	{
		T newMatrixEls[N][N];
		for (uint32_t i = 0; i < N; ++i)
		{
			for (uint32_t j = 0; j < N; ++j)
			{
				newMatrixEls[i][j] = 0;
				for (int k = 0; k < N; ++k)
				{
					newMatrixEls[i][j] += lhs[i][k] * rhs[k][j];
				}
			}
		}

		return Matrix<T, N>(newMatrixEls);
	}

	MatrixElementsType m_elements;
};

template <typename T, size_t N>
std::string ToString(const Matrix<T, N>& matrix)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);

	const auto numberLength = [](T number) {
		size_t len = 0;
		if (number < 0)
		{
			number *= -1;
			len++;
		}

		if (number >= 10000000)
			len += 7;
		if (number >= 1000000)
			len += 6;
		if (number >= 100000)
			len += 5;
		if (number >= 10000)
			len += 4;
		if (number >= 1000)
			len += 3;
		if (number >= 100)
			len += 2;
		if (number >= 10)
			len += 1;


		return len;
	};

	size_t widestNumberLen = 0;

	for (uint32_t i = 0; i < N; ++i)
	{
		std::string line;
		for (uint32_t j = 0; j < N; ++j)
		{
			const auto matrixVal = matrix[i][j];
			const auto matrixValLen = numberLength(matrixVal);
			if (matrixValLen > widestNumberLen)
				widestNumberLen = matrixValLen;
		}
	}

	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			const auto matrixVal = matrix[i][j];
			const auto matrixValLen = numberLength(matrixVal);
			const std::string padding(widestNumberLen - matrixValLen, ' ');
			ss << '|' << padding << matrixVal;
		}
		ss << '|';
		if (i != (N - 1))
			ss << '\n';
	}

	return ss.str();
}

using Matrix4x4 = Matrix<float, 4>;
using Matrix3x3 = Matrix<float, 3>;
using Matrix2x2 = Matrix<float, 2>;

#endif // !MATRIX_H_
