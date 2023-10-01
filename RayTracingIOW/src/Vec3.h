#pragma once

#include <iostream>

namespace rtx {
	class Vec3
	{
	public:
		Vec3();

		Vec3(float x, float y, float z);

		static Vec3 random();
		static Vec3 random(float minimum, float maximum);
		static Vec3 randomUnit();

		Vec3 operator+(const Vec3& other) const;
		Vec3 operator-() const;
		Vec3 operator-(const Vec3& other) const;
		Vec3 operator*(const Vec3& other) const;
		Vec3 operator*(float scalar) const;
		Vec3 operator/(const Vec3& other) const;
		Vec3 operator/(float scalar) const;

		void operator+=(const Vec3& other);
		void operator-=(const Vec3& other);
		void operator*=(const Vec3& other);
		void operator*=(float scalar);
		void operator/=(const Vec3& other);
		void operator/=(float scalar);

		bool operator==(const Vec3& other) const = default;

		float length() const;
		float lengthSquared() const;
		float dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;
		Vec3 unitVector() const;
		void normalize();
		bool nearZero();
		Vec3 reflect(const Vec3& normal) const;
		Vec3 refract(const Vec3& normal, float etaiOverEtat) const;

		static float dot(const Vec3& x, const Vec3& y);
		static Vec3 cross(const Vec3& x, const Vec3& y);
		static Vec3 reflect(const Vec3& vector, const Vec3& normal);
		static Vec3 refract(const Vec3& unitVector, const Vec3& normal, float etaiOverEtat);

		float x, y, z;
	};

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector);

	Vec3 operator*(float scalar, const Vec3& vector);
}