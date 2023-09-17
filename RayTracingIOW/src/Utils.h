#pragma once

#include <limits>
#include <random>

namespace rtx {
	constexpr float infinity = std::numeric_limits<float>::infinity();
	constexpr float pi = 3.1415926535897932385f;

	constexpr float degreesToRadians(float degrees);
	constexpr float radiansToDegrees(float radians);
	
	/// <summary>
	/// Returns a random float in the range [0, 1).
	/// </summary>
	/// <returns>The random float in the range [0, 1).</returns>
	float randomFloat();
}