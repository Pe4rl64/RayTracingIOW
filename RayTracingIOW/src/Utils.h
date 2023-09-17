#pragma once

#include <limits>
#include <random>

namespace rtx {
	constexpr float infinity = std::numeric_limits<float>::infinity();
	constexpr float pi = 3.1415926535897932385f;

	constexpr float degreesToRadians(float degrees);
	constexpr float radiansToDegrees(float radians);
	float randomFloat();
}