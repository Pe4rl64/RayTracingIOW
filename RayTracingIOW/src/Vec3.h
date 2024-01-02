#pragma once

#include <iostream>

namespace rtx {
	/// <summary>
	/// Represents a three dimensional vector.
	/// </summary>
	class Vec3
	{
	public:
		float x; // The x component of the vector.
		float y; // The y component of the vector.
		float z; // The z component of the vector.
	public:
		/// <summary>
		/// Initializes a zero vector (all components = 0).
		/// </summary>
		Vec3();

		/// <summary>
		/// Initializes all the vector components to the given input value.
		/// </summary>
		/// <param name="value">The value to assign to each component.</param>
		Vec3(float value);

		/// <summary>
		/// Initializes the vector components with the given input values.
		/// </summary>
		/// <param name="x">The value for the x component of the vector.</param>
		/// <param name="y">The value for the y component of the vector.</param>
		/// <param name="z">The value for the z component of the vector.</param>
		Vec3(float x, float y, float z);
	public:
		/// <summary>
		/// Returns a vector with random component values.
		/// </summary>
		/// <returns>A vector with random component values.</returns>
		static Vec3 random();

		/// <summary>
		/// Returns a vector with random component values in [minimum, maximum).
		/// </summary>
		/// <param name="minimum">The mimum value for the components (included).</param>
		/// <param name="maximum">The maximum value for the components (excluded).</param>
		/// <returns>A vector with random component values in [minimum, maximum).</returns>
		static Vec3 random(float minimum, float maximum);

		/// <summary>
		/// Returns a unit vector with random component values.
		/// </summary>
		/// <returns>A unit vector with random component values.</returns>
		static Vec3 randomUnit();

		/// <summary>
		/// Returns a unit vector with random x and y component values. The z component is null (0).
		/// </summary>
		/// <returns>The unit vector.</returns>
		static Vec3 randomInUnitDisk();

		/// <summary>
		/// Calculates the dot product of x and y.
		/// </summary>
		/// <param name="x">Left hand side vector.</param>
		/// <param name="y">Right hand side vector.</param>
		/// <returns>The dot product of x and y.</returns>
		static float dot(const Vec3& x, const Vec3& y);

		/// <summary>
		/// Calculates the cross product of x and y.
		/// </summary>
		/// <param name="x">Left hand side vector.</param>
		/// <param name="y">Right hand side vector.</param>
		/// <returns>The cross product of x and y.</returns>
		static Vec3 cross(const Vec3& x, const Vec3& y);

		/// <summary>
		/// Calculates the reflection of a vector, given the normal of the reflective surface.
		/// </summary>
		/// <param name="vector">The vector to reflect.</param>
		/// <param name="normal">The normal vector of the reflective surface.</param>
		/// <returns>The reflected vector.</returns>
		static Vec3 reflect(const Vec3& vector, const Vec3& normal);

		/// <summary>
		/// Calculates the refraction of an incident unit vector, given the normal of the refractive surface
		/// and the refraction ratio of the two mediums.
		/// </summary>
		/// <param name="unitVector">The incident unit vector to refract.</param>
		/// <param name="normal">The normal vector of the refractive surface.</param>
		/// <param name="refractionRatio">
		/// Refraction index of the incident vector's medium / refraction index of the refracted vector's medium.
		/// </param>
		/// <returns>The refracted vector.</returns>
		static Vec3 refract(const Vec3& unitVector, const Vec3& normal, float refractionRatio);
	public:
		/// <summary>
		/// Calculates the vector addition of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to sum to this one.</param>
		/// <returns>The vector addition of this and the given vector.</returns>
		Vec3 operator+(const Vec3& other) const;

		/// <summary>
		/// Calculates the opposite of this vector.
		/// </summary>
		/// <returns>The opposite of this vector.</returns>
		Vec3 operator-() const;

		/// <summary>
		/// Calculates the vector subtraction of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to subtract to this one.</param>
		/// <returns>The vector subtraction of this and the given vector.</returns>
		Vec3 operator-(const Vec3& other) const;

		/// <summary>
		/// Calculates the vector multiplication of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to multiply to this one.</param>
		/// <returns>The vector multiplication of this and the given vector.</returns>
		Vec3 operator*(const Vec3& other) const;

		/// <summary>
		/// Calculates the scalar multiplication of this vector and the given scalar.
		/// </summary>
		/// <param name="scalar">The scalar to multiply to this vector.</param>
		/// <returns>The scalar multiplication of this vector and the given scalar.</returns>
		Vec3 operator*(float scalar) const;

		/// <summary>
		/// Calculates the scalar multiplication of the given scalar and vector.
		/// </summary>
		/// <param name="scalar">The scalar to multiply to the given vector.</param>
		/// <param name="vector">The vector to multiply by the given scalar.</param>
		/// <returns>The scalar multiplication of the given scalar and vector.</returns>
		friend Vec3 operator*(float scalar, const Vec3& vector);

		/// <summary>
		/// Calculates the vector division of this and the given vector.
		/// </summary>
		/// <param name="other">The divisor vector.</param>
		/// <returns>The vector division of this and the given vector.</returns>
		Vec3 operator/(const Vec3& other) const;

		/// <summary>
		/// Calculates the scalar division (inverse scalar multiplication) of this vector and the given scalar.
		/// </summary>
		/// <param name="scalar">The divisor scalar.</param>
		/// <returns>The scalar division of this vector and the given scalar.</returns>
		Vec3 operator/(float scalar) const;

		/// <summary>
		/// Assigns this vector to the vector addition of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to sum to this one.</param>
		void operator+=(const Vec3& other);

		/// <summary>
		/// Assigns this vector to the vector subtraction of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to subtract to this one.</param>
		void operator-=(const Vec3& other);

		/// <summary>
		/// Assigns this vector to the vector multiplication of this and the given vector.
		/// </summary>
		/// <param name="other">The vector to multiply to this one.</param>
		void operator*=(const Vec3& other);

		/// <summary>
		/// Assigns this vector to the scalar multiplication of this vector and the given scalar.
		/// </summary>
		/// <param name="scalar">The scalar to multiply to this vector.</param>
		void operator*=(float scalar);

		/// <summary>
		/// Assigns this vector to the vector division of this and the given vector.
		/// </summary>
		/// <param name="other">The divisor vector.</param>
		void operator/=(const Vec3& other);

		/// <summary>
		/// Assigns this vector to the scalar division (inverse scalar multiplication)
		/// of this vector and the given scalar.
		/// </summary>
		/// <param name="scalar">The divisor scalar.</param>
		void operator/=(float scalar);

		/// <summary>
		/// Compares this and another vector and returns <b>true</b> if they are the same.
		/// </summary>
		/// <param name="other">The vector to compare against this one.</param>
		/// <returns><b>true</b> if the values of the individual components are the same, <b>false</b> otherwise.</returns>
		bool operator==(const Vec3& other) const = default;

		/// <summary>
		/// Calculates the length of the vector.
		/// </summary>
		/// <returns>The length of the vector.</returns>
		float length() const;

		/// <summary>
		/// Calculates the squared length of the vector.
		/// </summary>
		/// <returns>The squared length of the vector.</returns>
		float lengthSquared() const;

		/// <summary>
		/// Calculates the normalized equivalent of the vector (length = 1).
		/// </summary>
		/// <returns>The normalized equivalent of the vector.</returns>
		Vec3 unitVector() const;

		/// <summary>
		/// Normalizes the vector.
		/// </summary>
		void normalize();

		/// <summary>
		/// Checks if the vector is a zero vector based on an absolute minimum value for the components.
		/// </summary>
		/// <param name="zero">Absolute value under which zero is assumed.</param>
		/// <returns>
		/// <b>true</b> if the absolute values of the individual components are &lt; zero,
		/// <b>false</b> otherwise.
		/// </returns>
		bool nearZero(float zero) const;

		/// <summary>
		/// Outputs a given vector to the given output stream.
		/// </summary>
		/// <param name="stream">The stream to output the vector to.</param>
		/// <param name="vector">The vector to output to the stream.</param>
		/// <returns>The output stream (after having output the vector to it).</returns>
		friend std::ostream& operator<<(std::ostream& stream, const Vec3& vector);
	};
}