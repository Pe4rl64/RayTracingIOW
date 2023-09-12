#include <iostream>

#include "Color.h"

Color::Color()
	: r(0.0f), g(0.0f), b(0.0f)
{
}

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

Color Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator-() const
{
	return Color(-r, -g, -b);
}

Color Color::operator-(const Color& other) const
{
	return Color(r - other.r, g - other.g, b - other.b);
}

Color Color::operator*(const Color& other) const
{
	return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*(float scalar) const
{
	return Color(r * scalar, g * scalar, b * scalar);
}

Color operator*(float scalar, const Color& vector)
{
	return vector * scalar;
}

Color Color::operator/(const Color& other) const
{
	return Color(r / other.r, g / other.g, b / other.b);
}

Color Color::operator/(float scalar) const
{
	return (*this) * (1 / scalar);
}

void Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
}

void Color::operator-=(const Color& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
}

void Color::operator*=(const Color& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
}

void Color::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
}

void Color::operator/=(const Color& other)
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
}

void Color::operator/=(float scalar)
{
	r /= scalar;
	g /= scalar;
	b /= scalar;
}

std::ostream& operator<<(std::ostream& stream, const Color& color)
{
	stream << static_cast<int>(color.r * 255)
		<< ' ' << static_cast<int>(color.g * 255) 
		<< ' ' << static_cast<int>(color.b * 255);
	return stream;
}