#include "Interval.h"

#include "Utils.h"

rtx::Interval::Interval()
	: minimum(infinity), maximum(-infinity)
{
}

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

const rtx::Interval rtx::Interval::empty(infinity, -infinity);
const rtx::Interval rtx::Interval::universe(-infinity, infinity);
