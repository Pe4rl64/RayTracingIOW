#pragma once

#include <iosfwd>

class Vec3
{
public:
	Vec3();

	Vec3(float x, float y, float z);

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
	float dot(const Vec3& other) const;
	Vec3 cross(const Vec3& other) const;
	Vec3 unitVector() const;

	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vec3& vector);

Vec3 operator*(float scalar, const Vec3& vector);