#pragma once

#include <iosfwd>

#include "Vec3.h"

class Color : public Vec3
{
public:
	Color();

	Color(float r, float g, float b);

	Color(const Vec3& vector);

	float &r, &g, &b;
};

/// <summary>
/// Pushes the translated color values to the output stream [0, 255].
/// </summary>
/// <param name="stream">The output stream.</param>
/// <param name="color">The color to output to the stream.</param>
/// <returns>The output stream with the traslated color values.</returns>
std::ostream& operator<<(std::ostream& stream, const Color& color);