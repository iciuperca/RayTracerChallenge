#ifndef TUPLE_H_
#define TUPLE_H_

#include <string>

struct Tuple
{
	Tuple() = default;
	Tuple(float x, float y, float z, float w);
	bool operator==(const Tuple& rhs) const;
	bool operator!=(const Tuple& rhs) const;
	Tuple operator+(const Tuple& rhs) const;
	Tuple operator-(const Tuple& rhs) const;
	Tuple operator-() const;

	[[ nodiscard ]] bool IsVector() const;
	[[ nodiscard ]] bool IsPoint() const;
	[[ nodiscard ]] float Magnitude() const;
	[[ nodiscard ]] Tuple Normalize() const;

	float x;
	float y;
	float z;
	float w;
	
	static Tuple CreateVector(float x, float y, float z);
	static Tuple CreatePoint(float x, float y, float z);
};

Tuple operator*(const Tuple& lhs, float rhs);
Tuple operator*(float lhs, const Tuple& rhs);
Tuple operator/(const Tuple& lhs, float rhs);
float Dot(const Tuple& lhs, const Tuple& rhs);
Tuple Cross(const Tuple& lhs, const Tuple& rhs);

std::string ToString(const Tuple& tuple);

#endif // TUPLE_H_