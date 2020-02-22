#include <iostream>

#include <RayTracerLib/Tuple.h>
#include <RayTracerLib/RayMath.h>

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
	Projectile projectile(Tuple::CreatePoint(0.0f, 1.0f, 0.0f), Tuple::CreateVector(1.0f, 1.0f, 0.0f).Normalize());
	// gravity -0.1 unit/tick, and wind is -0.1 unit/tick
	const Environment environment(Tuple::CreateVector(0.0f, -0.1f, 0.0f), Tuple::CreateVector(-0.01f, 0.0f, 0.0f));

	int tickCount = 0;
	std::cout << "Tick" << tickCount << ": Position " << ToString(projectile.position) << std::endl;
	while (projectile.position.y >= 0)
	{	++tickCount;
		projectile = Tick(environment, projectile);
		std::cout << "Tick " << tickCount << ": Position " << ToString(projectile.position) << std::endl;
	}
	
	return 0;
}