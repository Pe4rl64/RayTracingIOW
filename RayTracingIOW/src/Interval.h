#pragma once

namespace rtx {
	class Vec4;

	class Interval
	{
	public:
		/// <summary>
		/// Constructs an interval [minimum, maximum].
		/// </summary>
		/// <param name="minimum">The starting point of the interval.</param>
		/// <param name="maximum">The end point of the interval.</param>
		Interval(float minimum, float maximum);

		/// <summary>
		/// Checks if the interval contains the given number.
		/// </summary>
		/// <param name="number">The number to check against.</param>
		/// <returns>
		/// <b>true</b> if <b>minimum &lt;= number &lt;= maximum</b>, <b>false</b> otherwise.
		/// </returns>
		bool contains(float number) const;

		/// <summary>
		/// Checks if the interval surrounds the given number.
		/// </summary>
		/// <param name="number">The number to check against.</param>
		/// <returns>
		/// <b>true</b> if <b>minimum &lt; number &lt; maximum</b>, <b>false</b> otherwise.
		/// </returns>
		bool surrounds(float number) const;

		/// <summary>
		/// Clamps the given number to the range of this interval.
		/// </summary>
		/// <param name="number">The number to clamp.</param>
		/// <returns>The clamped number.</returns>
		float clamp(float number) const;

		/// <summary>
		/// Clamps the given vector's componenets to the range of this interval,
		/// and returns it.
		/// </summary>
		/// <param name="vector">The vector whose components need to be clamped.</param>
		/// <returns>The vector with the clamped components.</returns>
		Vec4 clamp(const Vec4& vector) const;

		float minimum, maximum;
		static const Interval empty, universe;
	};
}