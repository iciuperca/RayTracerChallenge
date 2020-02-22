#include <stdexcept>
#include <cmath>
#include <sstream>
	
#include "../include/RayTracerLib/Tuple.h"
#include "../include/RayTracerLib/RayMath.h"

Tuple::Tuple(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
{
}

bool Tuple::operator==(const Tuple& rhs) const
{
	return Equal(x, rhs.x) &&
		Equal(y, rhs.y) &&
		Equal(z, rhs.z) &&
		Equal(w, rhs.w);
}

bool Tuple::operator!=(const Tuple& rhs) const
{
	return !(*this == rhs);
}

Tuple Tuple::operator+(const Tuple& rhs) const
{
	Tuple result = {};
	result.x = x + rhs.x;
	result.y = y + rhs.y;
	result.z = z + rhs.z;
	result.w = w + rhs.w;
	
	if (result.w >= 2.0f)
		throw std::invalid_argument("Cannot add a point and vector");

	return result;
}

Tuple Tuple::operator-(const Tuple& rhs) const
{
	Tuple result = {};
	result.x = x - rhs.x;
	result.y = y - rhs.y;
	result.z = z - rhs.z;
	result.w = w - rhs.w;
	
	if (result.w < 0.0f)
		throw std::invalid_argument("Cannot subtract a point and vector");

	return result;
}

Tuple Tuple::operator-() const
{
	return {-x, -y, -z, -w};
}

bool Tuple::IsVector() const
{
	return Equal(w, 0.0f);
}

bool Tuple::IsPoint() const
{
	return Equal(w, 1.0f);
}

float Tuple::Magnitude() const
{
	return sqrtf(x*x + y*y + z*z + w*w);
}

Tuple Tuple::Normalize() const
{
	const auto magnitude = Magnitude();
	return {
		x / magnitude,
		y / magnitude,
		z / magnitude,
		w / magnitude
	};
}

Tuple Tuple::CreateVector(const float x, const float y, const float z)
{
	return {x, y, z, 0.0f};
}

Tuple Tuple::CreatePoint(const float x, const float y, const float z)
{
	return {x, y, z, 1.0f};
}

Tuple operator*(const Tuple& lhs, const float rhs)
{
	return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs};
}

Tuple operator*(const float lhs, const Tuple& rhs)
{
	return operator*(rhs, lhs);
}

Tuple operator/(const Tuple& lhs, const float rhs)
{
	return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs};
}

float Dot(const Tuple& lhs, const Tuple& rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

Tuple Cross(const Tuple& lhs, const Tuple& rhs)
{
	return {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x,
		0
	};
}

std::string ToString(const Tuple& tuple)
{
	std::stringstream ss;
	if (tuple.IsVector())
		ss << "Vec ";
	else if (tuple.IsPoint())
		ss << "Point ";
	else
		ss << "Error ";
	
	ss << "{" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << "}";

	return ss.str();
}
