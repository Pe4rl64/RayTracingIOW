#include "Utils.h"

#include <numbers>

constexpr float rtx::degreesToRadians(float degrees)
{
	return degrees * std::numbers::pi_v<float> / 180;
}

constexpr float rtx::radiansToDegrees(float radians)
{
	return radians * 180 / std::numbers::pi_v<float>;
}