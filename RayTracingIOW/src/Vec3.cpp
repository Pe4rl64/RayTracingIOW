#include "Vec3.h"

#include <cmath>

#include "Utils.h"

rtx::Vec3::Vec3()
	:x(0.0f), y(0.0f), z(0.0f)
{
}

rtx::Vec3::Vec3(float value)
	: x(value), y(value), z(value)
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

rtx::Vec3 rtx::Vec3::randomInUnitDisk()
{
	Vec3 result(randomFloat(-1, 1), randomFloat(-1, 1), 0);

	if (result.lengthSquared() > 1)
		result.normalize();

	return result;
}

float rtx::Vec3::dot(const Vec3& x, const Vec3& y)
{
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

rtx::Vec3 rtx::Vec3::cross(const Vec3& x, const Vec3& y)
{
	return Vec3(x.y * y.z - x.z * y.y,
		x.z * y.x - x.x * y.z,
		x.x * y.y - x.y * y.x);
}

rtx::Vec3 rtx::Vec3::reflect(const Vec3& vector, const Vec3& normal)
{
	return (vector - 2 * dot(vector, normal) * normal);
}

rtx::Vec3 rtx::Vec3::refract(const Vec3& unitVector, const Vec3& normal, float refractionRatio)
{
	// cos of angle between incident and normal
	float cosTheta = std::fmin(dot(-unitVector, normal), 1.0f);

	// component of the refraction perpendicular to the normal
	Vec3 perpendicularRefraction = refractionRatio * (unitVector + cosTheta * normal);

	// component of the refraction parallel to the normal
	Vec3 parallelRefraction = -std::sqrtf(std::abs(1.0f - perpendicularRefraction.lengthSquared())) * normal;

	return perpendicularRefraction + parallelRefraction;
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
	(*this) = (*this) + other;
}

void rtx::Vec3::operator-=(const Vec3& other)
{
	(*this) = (*this) - other;
}

void rtx::Vec3::operator*=(const Vec3& other)
{
	(*this) = (*this) * other;
}

void rtx::Vec3::operator*=(float scalar)
{
	(*this) = (*this) * scalar;
}

void rtx::Vec3::operator/=(const Vec3& other)
{
	(*this) = (*this) / other;
}

void rtx::Vec3::operator/=(float scalar)
{
	(*this) = (*this) / scalar;
}

float rtx::Vec3::length() const
{
	return std::sqrtf(lengthSquared());
}

float rtx::Vec3::lengthSquared() const
{
	return x * x + y * y + z * z;
}

rtx::Vec3 rtx::Vec3::unitVector() const
{
	return (*this) / length();
}

void rtx::Vec3::normalize()
{
	(*this) /= length();
}

bool rtx::Vec3::nearZero(float zero) const
{
	return (std::abs(x) < zero && std::abs(y) < zero && std::abs(z) < zero);
}

std::ostream& rtx::operator<<(std::ostream& stream, const rtx::Vec3& vector)
{
	stream << vector.x << ' ' << vector.y << ' ' << vector.z;
	return stream;
}