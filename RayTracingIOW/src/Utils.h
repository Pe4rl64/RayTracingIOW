#pragma once

#include <limits>
#include <numbers>

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = std::numbers::pi;

constexpr float degreesToRadians(float degrees);
constexpr float radiansToDegrees(float radians);