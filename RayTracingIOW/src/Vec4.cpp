#include "Vec4.h"

#include <cmath>

#include "Interval.h"
#include "Vec3.h"

rtx::Vec4::Vec4()
	: r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{
}

rtx::Vec4::Vec4(float value)
	: r(value), g(value), b(value), a(value)
{
}

rtx::Vec4::Vec4(const Vec3& vector, float a)
	: r(vector.x), g(vector.y), b(vector.z), a(a)
{
}

rtx::Vec4::Vec4(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{
}

float rtx::Vec4::linearToGamma(float linearComponent)
{
	return std::sqrt(linearComponent);
}

rtx::Vec4 rtx::Vec4::operator+(const Vec4& other) const
{
	return Vec4(r + other.r, g + other.g, b + other.b, a + other.a);
}

rtx::Vec4 rtx::Vec4::operator-() const
{
	return Vec4(-r, -g, -b, -a);
}

rtx::Vec4 rtx::Vec4::operator-(const Vec4& other) const
{
	return Vec4(r - other.r, g - other.g, b - other.b, a - other.a);
}

rtx::Vec4 rtx::Vec4::operator*(const Vec4& other) const
{
	return Vec4(r * other.r, g * other.g, b * other.b, a * other.a);
}

rtx::Vec4 rtx::Vec4::operator*(float scalar) const
{
	return Vec4(r * scalar, g * scalar, b * scalar, a * scalar);
}

rtx::Vec4 rtx::operator*(float scalar, const rtx::Vec4& vector)
{
	return vector * scalar;
}

rtx::Vec4 rtx::Vec4::operator/(const Vec4& other) const
{
	return Vec4(r / other.r, g / other.g, b / other.b, a / other.a);
}

rtx::Vec4 rtx::Vec4::operator/(float scalar) const
{
	return (*this) * (1 / scalar);
}

void rtx::Vec4::operator+=(const Vec4& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
	a += other.a;
}

void rtx::Vec4::operator-=(const Vec4& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
	a -= other.a;
}

void rtx::Vec4::operator*=(const Vec4& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
	a *= other.a;
}

void rtx::Vec4::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
	a *= scalar;
}

void rtx::Vec4::operator/=(const Vec4& other)
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
	a /= other.a;
}

void rtx::Vec4::operator/=(float scalar)
{
	r /= scalar;
	g /= scalar;
	b /= scalar;
	a /= scalar;
}
