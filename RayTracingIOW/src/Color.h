#pragma once

#include <iostream>

namespace rtx {
	class Color
	{
	public:
		Color();

		Color(float r, float g, float b);

		/// <summary>
		/// Pushes the translated color values to the output stream [0, 255].
		/// </summary>
		/// <param name="stream">The output stream.</param>
		void writeColor(std::ostream& stream) const;

		/// <summary>
		/// Pushes the translated color values to the output stream [0, 255],
		/// taking into account the number of samples from neighboring regions.
		/// </summary>
		/// <param name="stream">The output stream.</param>
		/// <param name="samplesPerPixel">The number of samples taken from neighboring regions.</param>
		void writeColor(std::ostream& stream, int samplesPerPixel) const;

		Color operator+(const Color& other) const;
		Color operator-() const;
		Color operator-(const Color& other) const;
		Color operator*(const Color& other) const;
		Color operator*(float scalar) const;
		Color operator/(const Color& other) const;
		Color operator/(float scalar) const;

		void operator+=(const Color& other);
		void operator-=(const Color& other);
		void operator*=(const Color& other);
		void operator*=(float scalar);
		void operator/=(const Color& other);
		void operator/=(float scalar);

		bool operator==(const Color& other) const = default;

		float r, g, b;
	};

	Color operator*(float scalar, const Color& vector);

	/// <summary>
	/// Pushes the translated color values to the output stream [0, 255].
	/// </summary>
	/// <param name="stream">The output stream.</param>
	/// <param name="color">The color to output to the stream.</param>
	/// <returns>The output stream with the traslated color values.</returns>
	std::ostream& operator<<(std::ostream& stream, const Color& color);
}