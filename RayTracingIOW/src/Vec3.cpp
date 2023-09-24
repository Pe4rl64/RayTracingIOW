#include "Vec3.h"

#include <cmath>
#include <thread>
#include <chrono>

#include "Utils.h"

namespace rtx {
	Vec3::Vec3()
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vec3::Vec3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	Vec3 Vec3::random()
	{
		return Vec3(rtx::randomFloat(), rtx::randomFloat(), rtx::randomFloat());
	}

	Vec3 Vec3::random(float minimum, float maximum)
	{
		return Vec3(rtx::randomFloat(minimum, maximum),
			rtx::randomFloat(minimum, maximum),
			rtx::randomFloat(minimum, maximum));
	}

	Vec3 Vec3::randomInUnitSphere()
	{
		while (true)
		{
			Vec3 vector = Vec3::random(-1, 1);
			
			if (vector.lengthSquared() <= 1)
				return vector;
			
			// TODO: figure out why it doesn't work

			using namespace std::chrono_literals;
			//std::this_thread::sleep_for(1s); // To not overstress CPU
		}
	}

	Vec3 Vec3::randomUnit()
	{
		return random().unitVector();
	}

	Vec3 Vec3::randomOnHemisphere(const Vec3& normal)
	{
		Vec3 random = randomInUnitSphere();

		if (dot(random, normal) < 0)
			return -random;

		return random;
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

	void Vec3::normalize()
	{
		(*this) /= length();
	}

	float Vec3::dot(const Vec3& x, const Vec3& y)
	{
		return x.dot(y);
	}

	Vec3 Vec3::cross(const Vec3& x, const Vec3& y)
	{
		return x.cross(y);
	}

	std::ostream& operator<<(std::ostream& stream, const Vec3& vector)
	{
		stream << vector.x << ' ' << vector.y << ' ' << vector.z;
		return stream;
	}
}