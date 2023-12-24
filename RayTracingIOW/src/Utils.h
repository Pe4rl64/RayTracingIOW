#pragma once

#include <random>
#include <numbers>

#include "Vec4.h"

namespace rtx {
	constexpr uint32_t convertToRGBA(const Vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		return (a << 24) | (b << 16) | (g << 8) | r;
	}

	constexpr float degreesToRadians(float degrees)
	{
		return degrees * std::numbers::pi_v<float> / 180;
	}

	constexpr float radiansToDegrees(float radians)
	{
		return radians * 180 / std::numbers::pi_v<float>;
	}

	/// <summary>
	/// Returns a random float.
	/// </summary>
	/// <returns>A random float.</returns>
	inline float randomFloat()
	{
		static std::uniform_real_distribution<float> distribution;
		static std::mt19937 generator;
		return distribution(generator);
	}
	
	/// <summary>
	/// Returns a random float in range [minimum, maximum).
	/// </summary>
	/// <param name="minimum">The minimum value for the float (included).</param>
	/// <param name="maximum">The maximum value for the float (excluded).</param>
	/// <returns>A random float in range [minimum, maximum).</returns>
	inline float randomFloat(float minimum, float maximum)
	{
		static std::uniform_real_distribution<float> distribution(minimum, maximum);
		static std::mt19937 generator;
		return distribution(generator);
	}
}