#define CATCH_CONFIG_MAIN

#include <cmath>

#include <Catch2/catch.hpp>

#include <RayTracerLib/Tuple.h>
#include <RayTracerLib/RayMath.h>

namespace Catch {
    template<>
    struct StringMaker<Tuple> {
        static std::string convert( Tuple const& value ) {
            return ToString(value);
        }
    };
}

TEST_CASE( "tuple is equal", "[tuple]" )
{
    auto a = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    auto b = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    REQUIRE(a == b);
    
    b.x = 2.3f;

    REQUIRE(a != b);
}

TEST_CASE( "A tuple with w = 1.0 is a point", "[tuple]" ) 
{
    const auto a = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    REQUIRE(a.x == Approx(4.3f));
    REQUIRE(a.y == Approx(-4.2f));
    REQUIRE(a.z == Approx(3.1f));
    REQUIRE(a.w == Approx(1.0f));
    REQUIRE(!a.IsVector());
    REQUIRE(a.IsPoint());
}

TEST_CASE( "A tuple with w = 0.0 is a vector", "[tuple]" ) 
{
    const auto a = Tuple(4.3f, -4.2f, 3.1f, 0.0f);
    REQUIRE(a.x == Approx(4.3f));
    REQUIRE(a.y == Approx(-4.2f));
    REQUIRE(a.z == Approx(3.1f));
    REQUIRE(a.w == Approx(0.0f));
    REQUIRE(a.IsVector());
    REQUIRE(!a.IsPoint());
}

TEST_CASE( "point() creates tuples with w = 1.0", "[tuple]" )
{
    const auto p = Tuple::CreatePoint(4.3f, -4.2f, 3.1f);
    REQUIRE(p.IsPoint());
    REQUIRE(Equal(p.w, 1.0f));
}

TEST_CASE( "vector() creates tuples with w = 0.0", "[tuple]" )
{
    const auto p = Tuple::CreateVector(4.3f, -4.2f, 3.1f);
    REQUIRE(p.IsVector());
    REQUIRE(Equal(p.w, 0.0f));
}

TEST_CASE( "substracting a vector from the zero vector", "[tuple]" )
{
    const auto zero = Tuple::CreateVector(0.0f, 0.0f, 0.0f);
    const auto v = Tuple::CreateVector(1.0f, -2.0f, 3.0f);
    REQUIRE((zero - v) ==  Tuple::CreateVector(-1.0f, 2.0f, -3.0f));
}

TEST_CASE( "negating a tuple", "[tuple]" )
{
    const auto a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    REQUIRE(-a == Tuple(-1.0f, 2.0f, -3.0f, 4.0f));
}

TEST_CASE( "multiply a tuble by a scalar", "[tuple]" )
{
    const auto a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    REQUIRE((a * 3.5f) == Tuple(3.5f, -7.0f, 10.5f, -14.0f));
}

TEST_CASE( "multiply a tuble by a fraction", "[tuple]" )
{
    const auto a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    REQUIRE((a * 0.5f) == Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST_CASE( "dividing a tuple by a scalar", "[tuple]" )
{
    const auto a = Tuple(1.0f, -2.0f, 3.0f, -4.0f);
    REQUIRE((a / 2.0f) == Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST_CASE( "computing the magnitude of vector {1.0f, 0.0f, 0.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 0.0f, 0.0f);
    REQUIRE(Equal(a.Magnitude(), 1.0f));
}

TEST_CASE( "computing the magnitude of vector {0.0f, 1.0f, 0.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(0.0f, 1.0f, 0.0f);
    REQUIRE(Equal(a.Magnitude(), 1.0f));
}

TEST_CASE( "computing the magnitude of vector {0.0f, 0.0f, 1.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(0.0f, 0.0f, 1.0f);
    REQUIRE(Equal(a.Magnitude(), 1.0f));
}

TEST_CASE( "computing the magnitude of vector {1.0f, 2.0f, 3.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 2.0f, 3.0f);
    REQUIRE(Equal(a.Magnitude(), sqrtf(14.0f)));
}

TEST_CASE( "computing the magnitude of vector {-1.0f, -2.0f, -3.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(-1.0f, -2.0f, -3.0f);
    REQUIRE(Equal(a.Magnitude(), sqrtf(14.0f)));
}

TEST_CASE( "normalizing vector {4.0f, 0.0f, 0.0f} gives {1.0f, 0.0f, 0.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 0.0f, 0.0f);
    REQUIRE(a.Normalize() == Tuple::CreateVector(1.0f, 0.0f, 0.0f));
}

TEST_CASE( "normalizing vector {1.0f, 2.0f, 3.0f}", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 2.0f, 3.0f);
    REQUIRE(a.Normalize() == Tuple::CreateVector(0.26726, 0.53452f, 0.80178f));
}

TEST_CASE( "The magniture of a normalized vector", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 2.0f, 3.0f);
	const auto norm = a.Normalize();
    REQUIRE(Equal(norm.Magnitude(), 1.0f));
}

TEST_CASE( "The dot product of two tuples", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 2.0f, 3.0f);
    const auto b = Tuple::CreateVector(2.0f, 3.0f, 4.0f);

	REQUIRE(Equal(Dot(a, b), 20.0f));
}

TEST_CASE( "The cross product of two tuples", "[tuple]" )
{
    const auto a = Tuple::CreateVector(1.0f, 2.0f, 3.0f);
    const auto b = Tuple::CreateVector(2.0f, 3.0f, 4.0f);

	REQUIRE(Cross(a, b) == Tuple::CreateVector(-1.0f, 2.0f, -1.0f));
	REQUIRE(Cross(b, a) == Tuple::CreateVector(1.0f, -2.0f, 1.0f));
}
