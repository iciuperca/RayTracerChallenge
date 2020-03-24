#ifndef RAY_MATH_H_
#define RAY_MATH_H_

#include <cmath>
#include <type_traits>

constexpr auto EPSILON = 0.00001f;

bool Equalf(float a, float b);

template <typename T>
T Abs(T val)
{
	return val < 0 ? -val : val;
}

template <typename T>
bool Equal(T a, T b)
{
	return (Abs(a - b) < EPSILON);
}

template <typename T>
T Clamp(T val, T min, T max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;

	return val;
}

#endif // !RAY_MATH_H_
