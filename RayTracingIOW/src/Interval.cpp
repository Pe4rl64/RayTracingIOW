#include "Interval.h"

#include "Utils.h"

namespace rtx {
	Interval::Interval()
		: minimum(infinity), maximum(-infinity)
	{
	}

	Interval::Interval(float minimum, float maximum)
		: minimum(minimum), maximum(maximum)
	{
	}

	bool Interval::contains(float number) const
	{
		return number >= minimum && number <= maximum;
	}

	bool Interval::surrounds(float number) const
	{
		return number > minimum && number < maximum;
	}

	const Interval Interval::empty(infinity, -infinity);
	const Interval Interval::universe(-infinity, infinity);
}
