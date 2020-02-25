#include "../include/RayTracerLib/Matrix.h"
#include "../include/RayTracerLib/RayMath.h"

#include <cassert>
#include <utility>

Matrix::Matrix(const uint32_t columns, const uint32_t rows)	: m_columns(columns), m_rows(rows)
{
	assert(columns > 0);
	assert(rows > 0);
	
	m_elements.reserve(rows);
	for (uint32_t i = 0; i < rows; ++i)
	{
		std::vector<float> cols(columns);
		for (uint32_t j = 0; j < columns; ++j)
		{
			cols.push_back(0.0f);
		}
		
		m_elements.push_back(cols);
	}
}

Matrix::Matrix(const uint32_t columns, const uint32_t rows, MatrixElementsType elements) : m_columns(columns), m_rows(rows), m_elements(
	                                                                               std::move(elements))
{
}

void Matrix::Set(const uint32_t row, const uint32_t column, const float value)
{
	m_elements[row][column] = value;
}

float Matrix::Get(const uint32_t row, const uint32_t column)
{
	return m_elements[row][column];
}

std::vector<float>& Matrix::operator[](const uint32_t row)
{
	return m_elements[row];
}

std::vector<float> Matrix::operator[](const uint32_t row) const
{
	return m_elements[row];
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	return lhs.m_rows == rhs.m_rows &&
		lhs.m_columns == rhs.m_columns &&
		MatrixElementsSame(lhs.m_elements ,rhs.m_elements);
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
	return !(lhs == rhs);
}

bool MatrixElementsSame(const MatrixElementsType& lhs, const MatrixElementsType& rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	for (uint32_t i = 0; i < lhs.size(); ++i)
	{
		const auto lhsCols = lhs[i];
		const auto rhsCols = rhs[i];
		if (lhsCols.size() != rhsCols.size())
			return false;
		
		for (uint32_t j = 0; j < lhsCols.size(); ++j)
		{
			const auto lhsEl = lhs[i][j];
			const auto rhsEl = rhs[i][j];
			if (lhsEl != rhsEl)
				return false;
		}
	}
	
	return true;
}
