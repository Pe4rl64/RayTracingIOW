#pragma once

#include <random>
#include <numbers>

#include "Vec4.h"

namespace rtx {
	/// <summary>
	/// Converts the real valued components of a color to integer valued ones
	/// in the range [0, 255].
	/// </summary>
	/// <param name="color">The color to convert.</param>
	/// <returns>
	/// An unsigned integer containing the components in the following order: RGBA,
	/// with R being least significative byte and A being the most significative.
	/// </returns>
	constexpr uint32_t convertToRGBA(const Vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		return (a << 24) | (b << 16) | (g << 8) | r;
	}

	/// <summary>
	/// Converts input color to gamma space by square rooting its componenets
	/// (except the alfa component), and returns it.
	/// </summary>
	/// <param name="color">The color to convert to gamma space.</param>
	/// <returns>The converted color.</returns>
	Vec4 linearToGamma(const Vec4& color);

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