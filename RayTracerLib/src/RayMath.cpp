#include "../include/RayTracerLib/RayMath.h"

bool Equalf(const float a, const float b)
{
	if (fabsf(a - b) < EPSILON)
		return true;

	return false;
}