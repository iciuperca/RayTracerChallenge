#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <iomanip>


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

	MatrixRowType& operator[](uint32_t row)
	{
		return m_elements[row];
	}

	MatrixRowType operator[](uint32_t row) const
	{
		return m_elements[row];
	}

	friend bool operator==(const Matrix<N>& lhs, const Matrix<N>& rhs)
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

	friend bool operator!=(const Matrix<N>& lhs, const Matrix<N>& rhs)
	{
		return !(lhs == rhs);
	}

	friend Matrix<N> operator*(const Matrix<N>& lhs, const Matrix<N>& rhs)
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

	constexpr size_t Width()
	{
		return N;
	}

	constexpr static size_t MatrixWidth()
	{
		return N;
	}

	constexpr Matrix<N> Transpose() const
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

	constexpr Matrix<N-1> Submatrix(size_t row, size_t column) const
	{
		static_assert(N >= 2);
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

	static constexpr Matrix<N> Identity()
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

	MatrixElementsType m_elements;
};

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

using Matrix4x4 = Matrix<4>;
using Matrix3x3 = Matrix<3>;
using Matrix2x2 = Matrix<2>;

Matrix2x2 Make2x2Matrix(const std::array<float, Matrix2x2::MatrixWidth()*Matrix2x2::MatrixWidth()>& elements)
{
	Matrix2x2::MatrixElementsType matrixElements;
	matrixElements[0][0] = elements[0];
	matrixElements[0][1] = elements[1];
	matrixElements[1][0] = elements[2];
	matrixElements[1][1] = elements[3];

	return Matrix2x2(matrixElements); 
}

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

Tuple operator*(const Matrix4x4& lhs, const Tuple& rhs)
{
	const float x = rhs.x * lhs[0][0] + rhs.y * lhs[0][1] + rhs.z * lhs[0][2] + rhs.w * lhs[0][3];
	const float y = rhs.x * lhs[1][0] + rhs.y * lhs[1][1] + rhs.z * lhs[1][2] + rhs.w * lhs[1][3];
	const float z = rhs.x * lhs[2][0] + rhs.y * lhs[2][1] + rhs.z * lhs[2][2] + rhs.w * lhs[2][3];
	const float w = rhs.x * lhs[3][0] + rhs.y * lhs[3][1] + rhs.z * lhs[3][2] + rhs.w * lhs[3][3];

	return {x, y, z, w};
}

Tuple operator*(const Tuple& lhs, const Matrix4x4& rhs)
{
	return operator*(rhs, lhs);
}

float Determinant(const Matrix<2>& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

float Minor(const Matrix<3>& matrix, size_t row, size_t col)
{
	const auto subMatrix = matrix.Submatrix(row, col);
	return Determinant(subMatrix);
}

float Cofactor(const Matrix<3>& matrix, size_t row, size_t col)
{
	const auto minor = Minor(matrix, row, col);
	if (((row + col) % 2) != 0)
		return -minor;

	return minor;
}

#endif // !MATRIX_H_
