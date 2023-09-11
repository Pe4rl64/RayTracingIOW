#include <iostream>

#include "Color.h"

Color::Color()
	: Vec3(), r(x), g(y), b(z) 
{
}

Color::Color(float r, float g, float b)
	: Vec3(r, g, b), r(x), g(y), b(z)
{
}

Color::Color(const Vec3& vector)
	: Vec3(vector), r(x), g(y), b(z)
{
}

std::ostream& operator<<(std::ostream& stream, const Color& color)
{
	stream << static_cast<int>(color.r * 255)
		<< ' ' << static_cast<int>(color.g * 255) 
		<< ' ' << static_cast<int>(color.b * 255);
	return stream;
}