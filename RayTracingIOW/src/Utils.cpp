#include "Utils.h"

constexpr float rtx::degreesToRadians(float degrees)
{
	return degrees * rtx::pi / 180;
}

constexpr float rtx::radiansToDegrees(float radians)
{
	return radians * 180 / rtx::pi;
}