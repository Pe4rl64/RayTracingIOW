#include "Interval.h"

#include <limits>

#include "Utils.h"

rtx::Interval::Interval(float minimum, float maximum)
	: minimum(minimum), maximum(maximum)
{
}

bool rtx::Interval::contains(float number) const
{
	return number >= minimum && number <= maximum;
}

bool rtx::Interval::surrounds(float number) const
{
	return number > minimum && number < maximum;
}

float rtx::Interval::clamp(float number) const
{
	if (number < minimum)
		return minimum;

	if (number > maximum)
		return maximum;
		
	return number;
}

rtx::Vec4 rtx::Interval::clamp(const Vec4& vector) const
{
	float r = clamp(vector.r);
	float g = clamp(vector.g);
	float b = clamp(vector.b);
	float a = clamp(vector.a);

	return Vec4(r, g, b, a);
}

const rtx::Interval rtx::Interval::empty(std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
const rtx::Interval rtx::Interval::universe(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
