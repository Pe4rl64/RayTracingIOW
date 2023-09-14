#include "Utils.h"

constexpr float degreesToRadians(float degrees)
{
	return degrees * pi / 180;
}

constexpr float radiansToDegrees(float radians)
{
	return radians * 180 / pi;
}