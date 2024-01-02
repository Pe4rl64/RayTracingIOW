#include "Utils.h"

rtx::Vec4 rtx::linearToGamma(const Vec4& color)
{
	float r = sqrtf(color.r);
	float g = sqrtf(color.g);
	float b = sqrtf(color.b);

	return Vec4(r, g, b, color.a);
}
