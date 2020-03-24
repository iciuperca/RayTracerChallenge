#include <iostream>
#include <fstream>
#include <cmath>
#include <array>

#include <RayTracerLib/Tuple.h>
#include <RayTracerLib/Canvas.h>
#include <RayTracerLib/Matrix.h>
#include <RayTracerLib/RayMath.h>

int main()
{
	const auto identityMatrix = Matrix4x4::Identity();
	std::cout << ToString(identityMatrix) << std::endl;
	const auto inverseMatrix = identityMatrix.Inverse();
	std::cout << ToString(inverseMatrix) << std::endl;

	const Matrix4x4 a = Make4x4Matrix({
		8.0f, 2.0f, 2.0f, 2.0f,
		3.0f, -1.0f, 7.0f, 0.0f,
		7.0f, 0.0f, 5.0f, 4.0f,
		6.0f, -2.0f, 0.0f, 5.0f
	});

	const auto inverseA = a.Inverse();
	const auto transposeA = a.Transpose();

	std::cout << "Transpose:\n" << ToString(transposeA) << std::endl;
	std::cout << "Inverse:\n" << ToString(inverseA) << std::endl;

	std::cout << "Inverse of transpose:\n" << ToString(transposeA.Inverse()) << std::endl;
	std::cout << "Transpose of inverse:\n" << ToString(inverseA.Transpose()) << std::endl;
}
