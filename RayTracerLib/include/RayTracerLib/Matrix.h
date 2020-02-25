#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstdint>
#include <vector>

using MatrixElementsType = std::vector<std::vector<float>>;

struct Matrix
{
	Matrix(uint32_t columns, uint32_t rows);
	Matrix(uint32_t columns, uint32_t rows, MatrixElementsType elements);
	
	void Set(uint32_t row, uint32_t column, float value);
	float Get(uint32_t row, uint32_t column);
	std::vector<float>& operator[](uint32_t row);
	std::vector<float> operator[](uint32_t row) const;

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

	uint32_t m_columns;
	uint32_t m_rows;
	MatrixElementsType m_elements;
};

bool MatrixElementsSame(const MatrixElementsType& lhs, const MatrixElementsType& rhs);

#endif // !MATRIX_H_