#define CATCH_CONFIG_MAIN

#include <cmath>
#include <sstream>

#include <Catch2/catch.hpp>

#include <RayTracerLib/Tuple.h>
#include <RayTracerLib/RayMath.h>
#include <RayTracerLib/Color.h>
#include <RayTracerLib/Canvas.h>
#include <RayTracerLib/Matrix.h>
#include <RayTracerLib/RayMath.h>

namespace Catch {

	template<>
    struct StringMaker<Tuple> {
        static std::string convert( Tuple const& value ) {
            return ToString(value);
        }
    };

	template<>
    struct StringMaker<Color> {
        static std::string convert( Color const& value ) {
            return ToString(value);
        }
    };

	template<>
    struct StringMaker<Matrix2x2> {
        static std::string convert( Matrix2x2 const& value ) {
            return ToString(value);
        }
    };

	template<>
    struct StringMaker<Matrix3x3> {
        static std::string convert( Matrix3x3 const& value ) {
            return ToString(value);
        }
    };

	template<>
    struct StringMaker<Matrix4x4> {
        static std::string convert( Matrix4x4 const& value ) {
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

TEST_CASE( "Colors are (red, green, blue) tuples", "[color]" )
{
    const auto c = Color(-0.5f, 0.4f, 1.7f);

	REQUIRE(Equal(c.r, -0.5f));
	REQUIRE(Equal(c.g, 0.4f));
	REQUIRE(Equal(c.b, 1.7f));
}

TEST_CASE( "Adding colors", "[color]" )
{
    const auto c1 = Color(0.9f, 0.6f, 0.75f);
    const auto c2 = Color(0.7f, 0.1f, 0.25f);
	REQUIRE((c1 + c2) == Color(1.6f, 0.7f, 1.0f));
}

TEST_CASE( "Substracting colors", "[color]" )
{
    const auto c1 = Color(0.9f, 0.6f, 0.75f);
    const auto c2 = Color(0.7f, 0.1f, 0.25f);
	REQUIRE((c1 - c2) == Color(0.2f, 0.5f, 0.5f));
}

TEST_CASE( "Multiplying a color by a scalar", "[color]" )
{
    const auto c = Color(0.2f, 0.3f, 0.4f);
	REQUIRE((c * 2.0f) == Color(0.4f, 0.6f, 0.8f));
}

TEST_CASE( "Multiplying colors", "[color]" )
{
    const auto c1 = Color(1.0f, 0.2f, 0.4f);
    const auto c2 = Color(0.9f, 1.0f, 0.1f);
	REQUIRE((c1 * c2) == Color(0.9f, 0.2f, 0.04f));
}

TEST_CASE( "Creating a canvas", "[canvas]" )
{
    const auto c = Canvas(10, 20);
	REQUIRE(c.width == 10);
	REQUIRE(c.height == 20);
	REQUIRE(c.pixels.size() == c.width * c.height);

	const Color blackColor = {0.0f, 0.0f, 0.0f};
	for (const auto& pixel : c.pixels)
	{
		REQUIRE(pixel == blackColor);
	}
}

TEST_CASE( "Writing pixels to a canvas", "[canvas]" )
{
	auto c = Canvas(10, 20);
	const auto red = Color(1.0f, 0.0f, 0.0f);
	c.WritePixel(2, 3, red);
	REQUIRE(c.PixelAt(2, 3) == red);

	const auto green = Color(0.0f, 1.0f, 0.0f);
	for (uint32_t y = 0; y < c.height; ++y)
	{
		for (uint32_t x = 0; x < c.width; ++x)
		{
			c.WritePixel(x, y, green);
		}
	}

	for (const auto& pixel : c.pixels)
	{
		REQUIRE(pixel == green);
	}
}

TEST_CASE( "Constructing the PPM header", "[canvas]" )
{
	const Canvas c(5, 3);
	const auto ppm = c.ToPpm();
	std::istringstream iss(ppm);
	std::string line;
	size_t lineNo = 0;
	while (std::getline(iss, line) && lineNo <= 3)
	{
	    switch (lineNo)
	    {
        case 0:
	        {
		        REQUIRE(line == "P3");
	        }   break;
        case 1:
	        {
		        REQUIRE(line == "5 3");
	        }   break;
        case 2:
	        {
		        REQUIRE(line == "255");
	        }   break;
	    }
		
		++lineNo;
	}
}

TEST_CASE( "Constructing the PPM pixel data", "[canvas]" )
{
	Canvas c(5, 3);
	const auto c1 = Color(1.5f, 0.0f, 0.0f);
	const auto c2 = Color(0.0f, 0.5f, 0.0f);
	const auto c3 = Color(-0.5f, 0.0f, 1.0f);

	c.WritePixel(0, 0, c1);
	c.WritePixel(2, 1, c2);
	c.WritePixel(4, 2, c3);
	
	const auto ppm = c.ToPpm();
	std::istringstream iss(ppm);
	std::string line;
	size_t lineNo = 0;
	while (std::getline(iss, line))
	{
	    switch (lineNo)
	    {
        case 3:
	        {
		        REQUIRE(line == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
	        }   break;
        case 4:
	        {
		        REQUIRE(line == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
	        }   break;
        case 5:
	        {
		        REQUIRE(line == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
	        }   break;
	    }

		++lineNo;
	}
}

TEST_CASE( "Splitting long lines in PPM files", "[canvas]" )
{
	Canvas c(10, 2);
	const Color color(1.0f, 0.8f, 0.6f);
	c.Fill(color);

	const auto ppm = c.ToPpm();
	std::istringstream iss(ppm);
	std::string line;
	size_t lineNo = 0;
	while (std::getline(iss, line))
	{
	    switch (lineNo)
	    {
        case 3:
	        {
		        REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	        }   break;
        case 4:
	        {
		        REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");
	        }   break;
        case 5:
	        {
		        REQUIRE(line == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	        }   break;
        case 6:
	        {
		        REQUIRE(line == "153 255 204 153 255 204 153 255 204 153 255 204 153");
	        }   break;
	    }

		++lineNo;
	}
}

TEST_CASE( "Constructing and inspecting a 4x4 matrix", "[matrix]" )
{
	float els[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.5f, 6.5f, 7.5f, 8.5f},
		{9.0f, 10.0f, 11.0f, 12.0f},
		{13.5f, 14.5f, 15.5f, 16.5f},
	};
	const Matrix4x4 m(els);

	REQUIRE(Equal(m[0][0], 1.0f));
	REQUIRE(Equal(m[0][3], 4.0f));
	REQUIRE(Equal(m[1][0], 5.5f));
	REQUIRE(Equal(m[1][2], 7.5f));
	REQUIRE(Equal(m[2][2], 11.0f));
	REQUIRE(Equal(m[3][0], 13.5f));
	REQUIRE(Equal(m[3][2], 15.5f));

	m[3][2] = 12.6f;
	Equal(m[3][2], 12.6f);
}

TEST_CASE( "Constructing and inspecting a 2x2 matrix", "[matrix]" )
{
	float els[2][2] = {
		{-3.0f, 5.0f},
		{1.0f, -2.0f},
	};

	const Matrix2x2 m(els);

	REQUIRE(Equal(m[0][0], -3.0f));
	REQUIRE(Equal(m[0][1], 5.0f));
	REQUIRE(Equal(m[1][0], 1.0f));
	REQUIRE(Equal(m[1][1], -2.0f));
}

TEST_CASE( "Constructing and inspecting a 3x3 matrix", "[matrix]" )
{
	float els[3][3] = {
		{-3.0f, 5.0f, 0.0f},
		{1.0f, -2.0f, -7.0f},
		{0.0f, 1.0f, 1.0f},
	};
	const Matrix3x3 m(els);

	REQUIRE(Equal(m[0][0], -3.0f));
	REQUIRE(Equal(m[0][1], 5.0f));
	REQUIRE(Equal(m[0][2], 0.0f));
	REQUIRE(Equal(m[1][0], 1.0f));
	REQUIRE(Equal(m[1][1], -2.0f));
	REQUIRE(Equal(m[1][2], -7.0f));
	REQUIRE(Equal(m[2][0], 0.0f));
	REQUIRE(Equal(m[2][1], 1.0f));
	REQUIRE(Equal(m[2][2], 1.0f));
}

TEST_CASE( "Matrix equality with identical matrices", "[matrix]" )
{
	float elsA[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.5f, 6.5f, 7.5f, 8.5f},
		{9.0f, 8.0f, 7.0f, 6.0f},
		{5.0f, 4.0f, 3.0f, 2.0f},
	};
	const Matrix4x4 a(elsA);

	float elsB[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.5f, 6.5f, 7.5f, 8.5f},
		{9.0f, 8.0f, 7.0f, 6.0f},
		{5.0f, 4.0f, 3.0f, 2.0f},
	};
	const Matrix4x4 b(elsB);

	REQUIRE(a == b);
}

TEST_CASE( "Matrix equality with different matrices", "[matrix]" )
{
	float elsA[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.0f, 6.0f, 7.0f, 8.0f},
		{9.0f, 8.0f, 7.0f, 6.0f},
		{5.0f, 4.0f, 3.0f, 2.0f},
	};
	const Matrix4x4 a(elsA);

	float elsB[4][4] = {
		{2.0f, 3.0f, 4.0f, 5.0f},
		{6.0f, 7.0f, 8.0f, 9.0f},
		{8.0f, 7.0f, 6.0f, 5.0f},
		{4.0f, 3.0f, 2.0f, 1.0f},
	};
	const Matrix4x4 b(elsB);

	REQUIRE(a != b);
}

TEST_CASE( "Multiplying two matrices", "[matrix]" )
{
	float elsA[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{5.0f, 6.0f, 7.0f, 8.0f},
		{9.0f, 8.0f, 7.0f, 6.0f},
		{5.0f, 4.0f, 3.0f, 2.0f},
	};
	const Matrix4x4 a(elsA);

	float elsB[4][4] = {
		{-2.0f, 1.0f, 2.0f, 3.0f},
		{3.0f, 2.0f, 1.0f, -1.0f},
		{4.0f, 3.0f, 6.0f, 5.0f},
		{1.0f, 2.0f, 7.0f, 8.0f},
	};
	const Matrix4x4 b(elsB);

	float elsC[4][4] = {
		{20.0f, 22.0f, 50.0f, 48.0f},
		{44.0f, 54.0f, 114.0f, 108.0f},
		{40.0f, 58.0f, 110.0f, 102.0f},
		{16.0f, 26.0f, 46.0f, 42.0f},
	};
	const Matrix4x4 c(elsC);

	REQUIRE((a * b) == c);
}

TEST_CASE( "Multiplying a matrix and a tuple", "[matrix]" )
{
	float els[4][4] = {
		{1.0f, 2.0f, 3.0f, 4.0f},
		{2.0f, 4.0f, 4.0f, 2.0f},
		{8.0f, 6.0f, 4.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};
	const Matrix4x4 a(els);

	const Tuple b(1.0f, 2.0f, 3.0f, 1.0);
	const Tuple c(18.0f, 24.0f, 33.0f, 1.0);

	REQUIRE((a * b) == c);
}

TEST_CASE( "Multiplying the identity matrix by a tuple", "[matrix]" )
{
	const Tuple a(1.0f, 2.0f, 3.0f, 4.0);
	REQUIRE((a * Matrix4x4::Identity()) == a);
}

TEST_CASE( "Transposing a matrix", "[matrix]" )
{
	float elsA[4][4] = {
		{0.0f, 9.0f, 3.0f, 0.0f},
		{9.0f, 8.0f, 0.0f, 8.0f},
		{1.0f, 8.0f, 5.0f, 3.0f},
		{0.0f, 0.0f, 5.0f, 8.0f},
	};
	const Matrix4x4 a(elsA);

	float elsB[4][4] = {
		{0.0f, 9.0f, 1.0f, 0.0f},
		{9.0f, 8.0f, 8.0f, 0.0f},
		{3.0f, 0.0f, 5.0f, 5.0f},
		{0.0f, 8.0f, 3.0f, 8.0f},
	};
	const Matrix4x4 b(elsB);

	REQUIRE(a.Transpose() == b);
}

TEST_CASE( "Transpose the identity matrix", "[matrix]" )
{
	REQUIRE(Matrix4x4::Identity().Transpose() == Matrix4x4::Identity());
}

TEST_CASE( "Calculating the determinant of a 2x2 matrix", "[matrix]" )
{
	float els[2][2] = {
		{ 1.0f,  5.0f},
		{-3.0f, 2.0f},
	};
	const Matrix2x2 m(els);

	REQUIRE(Equal(m.Determinant(), 17.0f));
}

TEST_CASE( "A submatrix of a 3x3 matrrix is a 2x2 matrix", "[matrix]" )
{
	const Matrix3x3 m3 = Make3x3Matrix({
		 1.0f, 5.0f, 0.0f,
		-3.0f, 2.0f, 7.0f,
		 0.0f, 6.0f, 3.0f,
	});

	const Matrix2x2 m2 = Make2x2Matrix({
		 -3.0f, 2.0f,
		  0.0f, 6.0f,
	});

	REQUIRE(m3.Submatrix(0, 2) == m2);
}

TEST_CASE( "A submatrix of a 4x4 matrrix is a 3x3 matrix", "[matrix]" )
{
	const Matrix4x4 m4 = Make4x4Matrix({
		-6.0f, 1.0f,  1.0f, 6.0f,
		-8.0f, 5.0f,  8.0f, 6.0f,
		-1.0f, 0.0f,  8.0f, 2.0f,
		-7.0f, 1.0f, -1.0f, 1.0f,
	});

	const Matrix3x3 m3 = Make3x3Matrix({
		-6.0f, 1.0f, 6.0f,
		-8.0f, 8.0f, 6.0f,
		-7.0f,-1.0f, 1.0f,
	});

	REQUIRE(m4.Submatrix(2, 1) == m3);
}

TEST_CASE( "Calculate the minor of a 3x3 matrix", "[matrix]" )
{
	const Matrix3x3 a = Make3x3Matrix({
		3.0f,  5.0f,  0.0f,
		2.0f, -1.0f, -7.0f,
		6.0f, -1.0f,  5.0f,
	});

	const auto b = a.Submatrix(1.0f, 0.0f);
	REQUIRE(Equal(b.Determinant(), 25.0f));
	REQUIRE(Equal(a.Minor(1.0f, 0.0f), 25.0f));
}


TEST_CASE( "Calculate the cofactor of a 3x3 matrix", "[matrix]" )
{
	const Matrix3x3 a = Make3x3Matrix({
		3.0f,  5.0f,  0.0f,
		2.0f, -1.0f, -7.0f,
		6.0f, -1.0f,  5.0f,
	});

	REQUIRE(Equal(a.Minor(0.0f, 0.0f), -12.0f));
	REQUIRE(Equal(a.Cofactor(0.0f, 0.0f), -12.0f));
	REQUIRE(Equal(a.Minor(1.0f, 0.0f), 25.0f));
	REQUIRE(Equal(a.Cofactor(1.0f, 0.0f), -25.0f));
}


TEST_CASE( "Calculate the determinant of a 3x3 matrix", "[matrix]" )
{
	const Matrix3x3 a = Make3x3Matrix({
		 1.0f, 2.0f,  6.0f,
		-5.0f, 8.0f, -4.0f,
	 	 2.0f, 6.0f,  4.0f,
	});

	REQUIRE(Equal(a.Cofactor(0, 0), 56.0f));
	REQUIRE(Equal(a.Cofactor(0, 1), 12.0f));
	REQUIRE(Equal(a.Cofactor(0, 2), -46.0f));
	REQUIRE(Equal(a.Determinant(), -196.0f));
}

TEST_CASE( "Calculate the determinant of a 4x4 matrix", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		-2.0f, -8.0f,  3.0f,  5.0f,
		-3.0f,  1.0f,  7.0f,  3.0f,
	 	 1.0f,  2.0f, -9.0f,  6.0f,
		-6.0f,  7.0f,  7.0f, -9.0f,
	});

	REQUIRE(Equal(a.Cofactor(0, 0), 690.0f));
	REQUIRE(Equal(a.Cofactor(0, 1), 447.0f));
	REQUIRE(Equal(a.Cofactor(0, 2), 210.0f));
	REQUIRE(Equal(a.Cofactor(0, 3), 51.0f));
	REQUIRE(Equal(a.Determinant(), -4071.0f));
}

TEST_CASE( "Testing an invertible matrix for invertibility", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		6.0f,  4.0f, 4.0f, 4.0f,
		5.0f,  5.0f, 7.0f, 6.0f,
	 	4.0f, -9.0f, 3.0f, -7.0f,
		9.0f,  1.0f, 7.0f, -6.0f,
	});

	REQUIRE(Equal(a.Determinant(), -2120.0f));
	REQUIRE(a.IsInvertible());
}

TEST_CASE( "Testing an noninvertible matrix for invertibility", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		-4.0f,  2.0f, -2.0f, -3.0f,
		 9.0f,  6.0f,  2.0f,  6.0f,
	 	 0.0f, -5.0f,  1.0f, -5.0f,
		 0.0f,  0.0f,  0.0f,  0.0f,
	});

	REQUIRE(Equal(a.Determinant(), 0.0f));
	REQUIRE_FALSE(a.IsInvertible());
}

TEST_CASE( "Calculating the inverse of a matrix", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		-5.0f,  2.0f,  6.0f, -8.0f,
		 1.0f, -5.0f,  1.0f,  8.0f,
		 7.0f,  7.0f, -6.0f, -7.0f,
		 1.0f, -3.0f,  7.0f,  4.0f,
	});

	const Matrix4x4 b = a.Inverse();
	REQUIRE(Equal(a.Determinant(), 532.0f));
	REQUIRE(Equal(a.Cofactor(2, 3), -160.0f));
	REQUIRE(Equal(b[3][2], -160.0f/532.0f));
	REQUIRE(Equal(a.Cofactor(3, 2), 105.0f));
	REQUIRE(Equal(b[2][3], 105.0f/532.0f));

	const Matrix4x4 c = Make4x4Matrix({
		 0.21805f,  0.45113f,  0.24060f, -0.04511f,
		-0.80827f, -1.45677f, -0.44361f,  0.52068f,
		-0.07895f, -0.22368f, -0.05263f,  0.19737f,
		-0.52256f, -0.81391f, -0.30075f,  0.30639f,
	});

	REQUIRE(b == c);
}

TEST_CASE( "Calculating the inverse of a another matrix", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		8.0f, -5.0f, 9.0f, 2.0f,
		7.0f, 5.0f,  6.0f, 1.0f,
		-6.0f, 0.0f, 9.0f, 6.0f,
		-3.0f, 0.0f,  -9.0f,  -4.0f,
	});

	const Matrix4x4 b = Make4x4Matrix({
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692, 0.12308, 0.02564, 0.03077,
		0.35897, 0.35897, 0.43590, 0.92308,
		-0.69231, -0.69231, -0.76923, -1.92308
	});

	REQUIRE(a.Inverse() == b);
}

TEST_CASE( "Calculating the inverse of a third matrix", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		9.0f, 3.0f, 0.0f, 9.0f,
		-5.0f, -2.0f, -6.0f, -3.0f,
		-4.0f, 9.0f, 6.0f, 4.0f,
		-7.0f, 6.0f, 6.0f, 2.0f,
	});
	const Matrix4x4 b = Make4x4Matrix({
		-0.04074f, -0.07778f, 0.14444f, -0.22222f,
		-0.07778f, 0.03333f, 0.36667f, -0.33333f,
		-0.02901f, -0.14630f, -0.10926f, 0.12963f,
		0.17778f, 0.06667f, -0.26667f, 0.33333f
	});

	REQUIRE(a.Inverse() == b);
}

TEST_CASE( "Multiplying a product by it's inverse", "[matrix]" )
{
	const Matrix4x4 a = Make4x4Matrix({
		3.0f, -9.0f, 7.0f, 3.0f,
		3.0f, -8.0f, 2.0f, -9.0f,
		-4.0f, 4.0f, 4.0f, 1.0f,
		-6.0f, 5.0f, -1.0f, 1.0f,
	});

	const Matrix4x4 b = Make4x4Matrix({
		8.0f, 2.0f, 2.0f, 2.0f,
		3.0f, -1.0f, 7.0f, 0.0f,
		7.0f, 0.0f, 5.0f, 4.0f,
		6.0f, -2.0f, 0.0f, 5.0f
	});

	const auto c = a * b;
	REQUIRE((c * b.Inverse()) == a);
}
