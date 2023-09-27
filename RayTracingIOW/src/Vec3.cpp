#include "Vec3.h"

#include <cmath>
#include <thread>
#include <chrono>

#include "Utils.h"

rtx::Vec3::Vec3()
	: x(0.0f), y(0.0f), z(0.0f)
{
}

rtx::Vec3::Vec3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

rtx::Vec3 rtx::Vec3::random()
{
	return Vec3(rtx::randomFloat(), rtx::randomFloat(), rtx::randomFloat());
}

rtx::Vec3 rtx::Vec3::random(float minimum, float maximum)
{
	return Vec3(rtx::randomFloat(minimum, maximum),
		rtx::randomFloat(minimum, maximum),
		rtx::randomFloat(minimum, maximum));
}

rtx::Vec3 rtx::Vec3::randomUnit()
{
	return random().unitVector();
}

rtx::Vec3 rtx::Vec3::operator+(const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

rtx::Vec3 rtx::Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

rtx::Vec3 rtx::Vec3::operator-(const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

rtx::Vec3 rtx::Vec3::operator*(const Vec3& other) const
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

rtx::Vec3 rtx::Vec3::operator*(float scalar) const
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

rtx::Vec3 rtx::operator*(float scalar, const rtx::Vec3& vector)
{
	return vector * scalar;
}

rtx::Vec3 rtx::Vec3::operator/(const Vec3& other) const
{
	return Vec3(x / other.x, y / other.y, z / other.z);
}

rtx::Vec3 rtx::Vec3::operator/(float scalar) const
{
	return (*this) * (1 / scalar);
}

void rtx::Vec3::operator+=(const Vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void rtx::Vec3::operator-=(const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void rtx::Vec3::operator*=(const Vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void rtx::Vec3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

void rtx::Vec3::operator/=(const Vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void rtx::Vec3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

float rtx::Vec3::length() const
{
	return std::sqrtf(lengthSquared());
}

float rtx::Vec3::lengthSquared() const
{
	return x * x + y * y + z * z;
}

float rtx::Vec3::dot(const Vec3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

rtx::Vec3 rtx::Vec3::cross(const Vec3& other) const
{
	return Vec3(y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

rtx::Vec3 rtx::Vec3::unitVector() const
{
	return (*this) / length();
}

void rtx::Vec3::normalize()
{
	(*this) /= length();
}

bool rtx::Vec3::nearZero()
{
	float zero = 1e-8f; // absolute value for which zero is assumed
	return (std::abs(x) < zero && std::abs(y) < zero && std::abs(z) < zero);
}

rtx::Vec3 rtx::Vec3::reflect(const Vec3& normal) const
{
	return ((*this) - 2 * dot((*this), normal) * normal);
}

float rtx::Vec3::dot(const Vec3& x, const Vec3& y)
{
	return x.dot(y);
}

rtx::Vec3 rtx::Vec3::cross(const Vec3& x, const Vec3& y)
{
	return x.cross(y);
}

rtx::Vec3 rtx::Vec3::reflect(const Vec3& vector, const Vec3& normal)
{
	return vector.reflect(normal);
}

std::ostream& rtx::operator<<(std::ostream& stream, const rtx::Vec3& vector)
{
	stream << vector.x << ' ' << vector.y << ' ' << vector.z;
	return stream;
}