#ifndef RAY_MATH_H_
#define RAY_MATH_H_

#include <cmath>

constexpr auto EPSILON = 0.00001f;

#define FLOAT_EQ(a, b) ((fabs((a) - (b)) < EPSILON) ? true : false)

bool Equal(float a, float b);

#endif // !RAY_MATH_H_
