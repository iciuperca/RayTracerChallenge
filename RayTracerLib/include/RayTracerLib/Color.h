#ifndef COLOR_H_
#define COLOR_H_

#include <string>
#include <cstdint>
#include <algorithm>
#include <cmath>

constexpr uint8_t MINIMUM_COLOR_VALUE = 0;
constexpr uint8_t MAXIMUM_COLOR_VALUE = 255;

inline uint8_t ColorFloatToUint8(const float color)
{
	float newColor = std::clamp(color * MAXIMUM_COLOR_VALUE, static_cast<float>(MINIMUM_COLOR_VALUE), static_cast<float>(MAXIMUM_COLOR_VALUE));	
	return static_cast<uint8_t>(std::roundf(newColor));
}

constexpr uint8_t ColorUint8ToFloat(const uint8_t color)
{
	return static_cast<float>(color) / static_cast<float>(MAXIMUM_COLOR_VALUE);
}

struct Color
{
	Color() = default;
	Color(const float red, const float green, const float blue) : r(red), g(green), b(blue) {}

	Color operator+(const Color& rhs) const;
	Color operator-(const Color& rhs) const;
	Color operator*(const Color& rhs) const;

	friend bool operator==(const Color& lhs, const Color& rhs);
	friend bool operator!=(const Color& lhs, const Color& rhs);

	float r;
	float g;
	float b;
};

Color operator*(const Color& lhs, float rhs);
Color operator*(float lhs, const Color& rhs);

[[ nodiscard ]] std::string ToString(const Color& color);
[[ nodiscard ]] Color HadamardProduct(const Color& lhs, const Color& rhs);

#endif // !COLOR_H_ 
