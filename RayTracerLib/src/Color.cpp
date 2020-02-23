#include "../include/RayTracerLib/Color.h"
#include "../include/RayTracerLib/RayMath.h"

#include <sstream>

Color operator*(const Color& lhs, const float rhs)
{
	return {lhs.r * rhs, lhs.g * rhs, lhs.b * rhs};
}

Color operator*(const float lhs, const Color& rhs)
{
	return operator*(rhs, lhs);
}

std::string ToString(const Color& color)
{
	std::stringstream ss;
	ss << "Color: {" << color.r << ", " << color.g << ", " << color.b << "}";

	return ss.str();
}

Color HadamardProduct(const Color& lhs, const Color& rhs)
{
	return {lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b};
}

Color Color::operator+(const Color& rhs) const
{
	return {r + rhs.r, g + rhs.g, b + rhs.b};
}

Color Color::operator-(const Color& rhs) const
{
	return {r - rhs.r, g - rhs.g, b - rhs.b};
}

Color Color::operator*(const Color& rhs) const
{
	return HadamardProduct(*this, rhs);
}

bool operator==(const Color& lhs, const Color& rhs)
{
	return Equal(lhs.r, rhs.r)
		&& Equal(lhs.g, rhs.g)
		&& Equal(lhs.b, rhs.b);
}

bool operator!=(const Color& lhs, const Color& rhs)
{
	return !(lhs == rhs);
}
