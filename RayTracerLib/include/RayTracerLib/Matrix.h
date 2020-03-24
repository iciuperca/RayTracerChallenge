#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstdint>
#include <cassert>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>

#include "RayMath.h"


template <size_t N>
class Matrix
{
public:
	using MatrixRowType = std::array<float, N>;
	using MatrixElementsType = std::array<MatrixRowType, N>;

	explicit Matrix(const float elements[N][N])
	{
		for (uint32_t i = 0; i < N; ++i)
		{
			for (uint32_t j = 0; j < N; ++j)
			{
				m_elements[i][j] = elements[i][j];
			}
		}
	}

	explicit Matrix(const MatrixElementsType& elements) : m_elements(elements)
	{
	}

	inline MatrixRowType& operator[](uint32_t row) { return m_elements[row]; }
	inline MatrixRowType operator[](uint32_t row) const { return m_elements[row]; }

	template <size_t M>
	friend bool operator==(const Matrix<M>& lhs, const Matrix<M>& rhs);

	template <size_t M>
	friend bool operator!=(const Matrix<M>& lhs, const Matrix<M>& rhs);

	template <size_t M>
	friend Matrix<M> operator*(const Matrix<M>& lhs, const Matrix<M>& rhs);

	[[nodiscard]] constexpr size_t Width() { return N; }
	[[nodiscard]] Matrix Transpose() const;
	[[nodiscard]] constexpr Matrix<N-1> Submatrix(size_t row, size_t column) const;
	[[nodiscard]] constexpr Matrix Inverse() const;
	[[nodiscard]] constexpr float Determinant() const;
	[[nodiscard]] constexpr float Minor(size_t row, size_t col) const;
	[[nodiscard]] constexpr float Cofactor(size_t row, size_t col) const;
	[[nodiscard]] constexpr bool IsInvertible() const;

	[[nodiscard]] constexpr static size_t MatrixWidth() { return N; }
	[[nodiscard]] constexpr static  Matrix Identity();

	MatrixElementsType m_elements;
};

//----------------------------------------------------------------------------------------------------------------------

using Matrix4x4 = Matrix<4>;
using Matrix3x3 = Matrix<3>;
using Matrix2x2 = Matrix<2>;

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
constexpr Matrix<N-1> Matrix<N>::Submatrix(size_t row, size_t column) const
{
	static_assert(N >= 3);
	float newMatrixEls[N-1][N-1];

	size_t newRow = 0;
	for (size_t i = 0; i < N; ++i)
	{
		size_t newColumn = 0;
		if (i == row)
			continue;
		for (size_t j = 0; j < N; ++j)
		{
			if (j == column)
				continue;

			newMatrixEls[newRow][newColumn] = m_elements[i][j];
			newColumn++;
		}
		newRow++;
	}

	return Matrix<N-1>(newMatrixEls);
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
bool operator==(const Matrix<N>& lhs, const Matrix<N>& rhs)
{
	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			if (!Equal(lhs[i][j], rhs[i][j]))
				return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
bool operator!=(const Matrix<N>& lhs, const Matrix<N>& rhs)
{
	return !(lhs == rhs);
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
Matrix<N> operator*(const Matrix<N>& lhs, const Matrix<N>& rhs)
{
	float newMatrixEls[N][N];
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

	return Matrix<N>(newMatrixEls);
}

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
Matrix<N> Matrix<N>::Transpose() const
{
	float newMatrixEls[N][N];
	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			newMatrixEls[j][i] = m_elements[i][j];
		}
	}

	return Matrix<N>(newMatrixEls);
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
constexpr Matrix<N> Matrix<N>::Identity()
{
	float newMatrixEls[N][N];
	for (uint32_t i = 0; i < N; ++i)
	{
		for (uint32_t j = 0; j < N; ++j)
		{
			const float val = (i == j) ? 1 : 0;
			newMatrixEls[i][j] = val;
		}
	}

	return Matrix<N>(newMatrixEls);
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
constexpr Matrix<N> Matrix<N>::Inverse() const
{
	assert(IsInvertible());

	Matrix<N>::MatrixElementsType elements = {};
	const auto determinant = Determinant();
	for (size_t row = 0; row < N; ++row)
	{
		for (size_t col = 0; col < N; ++col)
		{
			const auto cofactor = Cofactor(row, col);
			elements[col][row] = cofactor / determinant;
		}
	}

	return Matrix<N>(elements);
}

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
constexpr float Matrix<N>::Determinant() const
{
	static_assert(N > 2);
	float result = 0.0f;
	for (size_t i = 0; i < N; ++i)
	{
		result += m_elements[0][i] * Cofactor(0, i);
	}
	
	return result;
}

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
constexpr float Matrix<N>::Minor(size_t row, size_t col) const
{
	static_assert(N > 2);
	return Submatrix(row, col).Determinant();
}

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
constexpr float Matrix<N>::Cofactor(size_t row, size_t col) const
{
	static_assert(N > 2);
	assert(row < N);
	assert(col < N);

	const auto minor = Minor(row, col);
	if (((row + col) % 2) != 0)
		return -minor;

	return minor;
}

//----------------------------------------------------------------------------------------------------------------------

template<size_t N>
inline constexpr bool Matrix<N>::IsInvertible() const
{
	return !Equal(Determinant(), 0.0f);
}

//----------------------------------------------------------------------------------------------------------------------

template<>
constexpr float Matrix<2>::Determinant() const
{
	return m_elements[0][0] * m_elements[1][1] - m_elements[0][1] * m_elements[1][0];
}

//----------------------------------------------------------------------------------------------------------------------

template <size_t N>
std::string ToString(const Matrix<N>& matrix)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);

	const auto numberLength = [](float number) {
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

//----------------------------------------------------------------------------------------------------------------------

Matrix2x2 Make2x2Matrix(const std::array<float, Matrix2x2::MatrixWidth()*Matrix2x2::MatrixWidth()>& elements)
{
	Matrix2x2::MatrixElementsType matrixElements;
	matrixElements[0][0] = elements[0];
	matrixElements[0][1] = elements[1];
	matrixElements[1][0] = elements[2];
	matrixElements[1][1] = elements[3];

	return Matrix2x2(matrixElements); 
}

//----------------------------------------------------------------------------------------------------------------------

Matrix3x3 Make3x3Matrix(const std::array<float, Matrix3x3::MatrixWidth()*Matrix3x3::MatrixWidth()>& elements)
{
	Matrix3x3::MatrixElementsType matrixElements;
	matrixElements[0][0] = elements[0];
	matrixElements[0][1] = elements[1];
	matrixElements[0][2] = elements[2];

	matrixElements[1][0] = elements[3];
	matrixElements[1][1] = elements[4];
	matrixElements[1][2] = elements[5];

	
	matrixElements[2][0] = elements[6];
	matrixElements[2][1] = elements[7];
	matrixElements[2][2] = elements[8];

	return Matrix3x3(matrixElements); 
}

//----------------------------------------------------------------------------------------------------------------------

Matrix4x4 Make4x4Matrix(const std::array<float, Matrix4x4::MatrixWidth()*Matrix4x4::MatrixWidth()>& elements)
{
	Matrix4x4::MatrixElementsType matrixElements;
	matrixElements[0][0] = elements[0];
	matrixElements[0][1] = elements[1];
	matrixElements[0][2] = elements[2];
	matrixElements[0][3] = elements[3];

	matrixElements[1][0] = elements[4];
	matrixElements[1][1] = elements[5];
	matrixElements[1][2] = elements[6];
	matrixElements[1][3] = elements[7];

	matrixElements[2][0] = elements[8];
	matrixElements[2][1] = elements[9];
	matrixElements[2][2] = elements[10];
	matrixElements[2][3] = elements[11];

	matrixElements[3][0] = elements[12];
	matrixElements[3][1] = elements[13];
	matrixElements[3][2] = elements[14];
	matrixElements[3][3] = elements[15];

	return Matrix4x4(matrixElements); 
}

//----------------------------------------------------------------------------------------------------------------------

Tuple operator*(const Matrix4x4& lhs, const Tuple& rhs)
{
	const float x = rhs.x * lhs[0][0] + rhs.y * lhs[0][1] + rhs.z * lhs[0][2] + rhs.w * lhs[0][3];
	const float y = rhs.x * lhs[1][0] + rhs.y * lhs[1][1] + rhs.z * lhs[1][2] + rhs.w * lhs[1][3];
	const float z = rhs.x * lhs[2][0] + rhs.y * lhs[2][1] + rhs.z * lhs[2][2] + rhs.w * lhs[2][3];
	const float w = rhs.x * lhs[3][0] + rhs.y * lhs[3][1] + rhs.z * lhs[3][2] + rhs.w * lhs[3][3];

	return {x, y, z, w};
}

//----------------------------------------------------------------------------------------------------------------------

Tuple operator*(const Tuple& lhs, const Matrix4x4& rhs)
{
	return operator*(rhs, lhs);
}

//----------------------------------------------------------------------------------------------------------------------

#endif // !MATRIX_H_
