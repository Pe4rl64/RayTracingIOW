#include "Color.h"

#include <cmath>

#include "Interval.h"

rtx::Color::Color()
	: r(0.0f), g(0.0f), b(0.0f)
{
}

rtx::Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

float rtx::Color::linearToGamma(float linearComponent)
{
	return std::sqrt(linearComponent);
}

void rtx::Color::writeColor(std::ostream& stream) const
{
	stream << static_cast<int>(linearToGamma(r) * 255)
		<< ' ' << static_cast<int>(linearToGamma(g) * 255)
		<< ' ' << static_cast<int>(linearToGamma(b) * 255);
}

void rtx::Color::writeColor(std::ostream& stream, int samplesPerPixel) const
{
	float scaledR = r / samplesPerPixel;
	float scaledG = g / samplesPerPixel;
	float scaledB = b / samplesPerPixel;

	scaledR = linearToGamma(scaledR);
	scaledG = linearToGamma(scaledG);
	scaledB = linearToGamma(scaledB);

	Interval intensity(0, 1);

	stream << static_cast<int>(intensity.clamp(scaledR) * 255)
		<< ' ' << static_cast<int>(intensity.clamp(scaledG) * 255)
		<< ' ' << static_cast<int>(intensity.clamp(scaledB) * 255);
}

rtx::Color rtx::Color::operator+(const Color& other) const
{
	return Color(r + other.r, g + other.g, b + other.b);
}

rtx::Color rtx::Color::operator-() const
{
	return Color(-r, -g, -b);
}

rtx::Color rtx::Color::operator-(const Color& other) const
{
	return Color(r - other.r, g - other.g, b - other.b);
}

rtx::Color rtx::Color::operator*(const Color& other) const
{
	return Color(r * other.r, g * other.g, b * other.b);
}

rtx::Color rtx::Color::operator*(float scalar) const
{
	return Color(r * scalar, g * scalar, b * scalar);
}

rtx::Color rtx::operator*(float scalar, const rtx::Color& vector)
{
	return vector * scalar;
}

rtx::Color rtx::Color::operator/(const Color& other) const
{
	return Color(r / other.r, g / other.g, b / other.b);
}

rtx::Color rtx::Color::operator/(float scalar) const
{
	return (*this) * (1 / scalar);
}

void rtx::Color::operator+=(const Color& other)
{
	r += other.r;
	g += other.g;
	b += other.b;
}

void rtx::Color::operator-=(const Color& other)
{
	r -= other.r;
	g -= other.g;
	b -= other.b;
}

void rtx::Color::operator*=(const Color& other)
{
	r *= other.r;
	g *= other.g;
	b *= other.b;
}

void rtx::Color::operator*=(float scalar)
{
	r *= scalar;
	g *= scalar;
	b *= scalar;
}

void rtx::Color::operator/=(const Color& other)
{
	r /= other.r;
	g /= other.g;
	b /= other.b;
}

void rtx::Color::operator/=(float scalar)
{
	r /= scalar;
	g /= scalar;
	b /= scalar;
}

std::ostream& rtx::operator<<(std::ostream& stream, const rtx::Color& color)
{
	color.writeColor(stream);
	return stream;
}
