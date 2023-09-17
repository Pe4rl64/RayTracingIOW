#include "Utils.h"

namespace rtx {
	constexpr float degreesToRadians(float degrees)
	{
		return degrees * pi / 180;
	}

	constexpr float radiansToDegrees(float radians)
	{
		return radians * 180 / pi;
	}

	float randomFloat()
	{
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;
		return distribution(generator);
	}
}