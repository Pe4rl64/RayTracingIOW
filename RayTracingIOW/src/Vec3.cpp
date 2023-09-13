#include "Vec3.h"

#include <cmath>
#include <iostream>

Vec3::Vec3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

Vec3::Vec3(float x, float y, float z)
	: x(x), y(y), z(z) 
{
}

Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3& other) const
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator*(float scalar) const
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 operator*(float scalar, const Vec3& vector)
{
	return vector * scalar;
}

Vec3 Vec3::operator/(const Vec3& other) const
{
	return Vec3(x / other.x, y / other.y, z / other.z);
}

Vec3 Vec3::operator/(float scalar) const
{
	return (*this) * (1 / scalar);
}

void Vec3::operator+=(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void Vec3::operator-=(const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void Vec3::operator*=(const Vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void Vec3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void Vec3::operator/=(const Vec3& other) 
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void Vec3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

float Vec3::length() const
{
	return std::sqrtf(lengthSquared());
}

float Vec3::lengthSquared() const
{
	return x * x + y * y + z * z;
}

float Vec3::dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const
{
	return Vec3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vec3 Vec3::unitVector() const
{
	return (*this) / length();
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
{
	stream << vector.x << ' ' << vector.y << ' ' << vector.z;
	return stream;
}