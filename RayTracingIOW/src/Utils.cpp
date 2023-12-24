#include "Utils.h"

/// <summary>
/// Converts input color to gamma space by square rooting its componenets
/// (except the alfa component), and returns it.
/// </summary>
/// <param name="color">The color to convert to gamma space.</param>
/// <returns>The converted color.</returns>
rtx::Vec4 rtx::linearToGamma(const Vec4& color)
{
	float r = sqrtf(color.r);
	float g = sqrtf(color.g);
	float b = sqrtf(color.b);

	return Vec4(r, g, b, color.a);
}
