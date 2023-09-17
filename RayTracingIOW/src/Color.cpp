#include "Color.h"

#include "Interval.h"

namespace rtx {
	Color::Color()
		: r(0.0f), g(0.0f), b(0.0f)
	{
	}

	Color::Color(float r, float g, float b)
		: r(r), g(g), b(b)
	{
	}

	void Color::writeColor(std::ostream& stream) const
	{
		stream << static_cast<int>(r * 255)
			<< ' ' << static_cast<int>(g * 255)
			<< ' ' << static_cast<int>(b * 255);
	}

	void Color::writeColor(std::ostream& stream, int samplesPerPixel) const
	{
		float scaledR = r / samplesPerPixel;
		float scaledG = g / samplesPerPixel;
		float scaledB = b / samplesPerPixel;

		Interval intensity(0, 1);

		stream << static_cast<int>(intensity.clamp(scaledR) * 255)
			<< ' ' << static_cast<int>(intensity.clamp(scaledG) * 255)
			<< ' ' << static_cast<int>(intensity.clamp(scaledB) * 255);
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
		color.writeColor(stream);
		return stream;
	}
}