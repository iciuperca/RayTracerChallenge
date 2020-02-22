#include "../include/RayTracerLib/RayMath.h"

bool Equal(const float a, const float b)
{
	if (fabsf(a - b) < EPSILON)
		return true;

	return false;
}