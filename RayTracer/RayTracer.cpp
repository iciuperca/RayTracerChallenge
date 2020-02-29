#include <iostream>
#include <fstream>
#include <cmath>
#include <array>

#include <RayTracerLib/Tuple.h>
#include <RayTracerLib/Canvas.h>
#include <RayTracerLib/Matrix.h>

struct Projectile
{
	Projectile(const Tuple& pos, const Tuple& vel) : position(pos), velocity(vel)
	{
	}
	
	Tuple position;
	Tuple velocity;
};

struct Environment
{
	Environment(const Tuple& g, const Tuple& w) : gravity(g), wind(w)
	{
	}
	
	Tuple gravity;
	Tuple wind;
};

Projectile Tick(const Environment& environment, const Projectile& projectile)
{
	const auto position = projectile.position + projectile.velocity;
	const auto velocity = projectile.velocity + environment.gravity + environment.wind;

	return Projectile(position, velocity);
}


int main()
{
	// projectile starts one unit above the origin
	// velocity is normalized to 1 unit/tick
//	Projectile projectile(Tuple::CreatePoint(0.0f, 1.0f, 0.0f), Tuple::CreateVector(1.0f, 1.8f, 0.0f).Normalize() * 11.25);
//	// gravity -0.1 unit/tick, and wind is -0.1 unit/tick
//	const Environment environment(Tuple::CreateVector(0.0f, -0.1f, 0.0f), Tuple::CreateVector(-0.01f, 0.0f, 0.0f));
//	Canvas canvas(900, 550);
//	const Color projectileColor(1.0f, 0.0f, 0.0f);
//
//
//	int tickCount = 0;
//	std::cout << "Tick" << tickCount << ": Position " << ToString(projectile.position) << std::endl;
//	while (projectile.position.y >= 0)
//	{	++tickCount;
//		projectile = Tick(environment, projectile);
//		std::cout << "Tick " << tickCount << ": Position " << ToString(projectile.position) << std::endl;
//		auto x = static_cast<uint32_t>(std::roundf(projectile.position.x));
//		auto y = static_cast<uint32_t>(std::roundf(canvas.height - projectile.position.y));
//		x = std::clamp(x, static_cast<uint32_t>(0), canvas.width - 1);
//		y = std::clamp(y, static_cast<uint32_t>(0), canvas.height - 1);
//
//		canvas.WritePixel(x, y, projectileColor);
//	}
//
//	std::ofstream fileStream;
//	fileStream.open("out.ppm", std::ios::out | std::ios::trunc);
//	fileStream << canvas.ToPpm();
//	fileStream.close();

	float arr[4][4] = {
		{1.0f,  2.0f,  3.0f,  4.0f },
		{5.0f,  6.0f,  7.0f,  8.0  },
		{9.0f,  10.0f, 11.0f, 12.0f},
		{13.0f, 14.0f, 15.0f, 16.0f},
	};

	Matrix4x4 mat(arr);
	std::cout << ToString(mat) << std::endl;

	
	return 0;
}
