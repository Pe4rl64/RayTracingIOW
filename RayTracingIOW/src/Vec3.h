#pragma once

class Vec3
{
public:
	Vec3()
		: x(0), y(0), z(0) {}

	Vec3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-() const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;
	
	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);
	void operator*=(const Vec3& other);
	void operator/=(const Vec3& other);

	float length() const;

	float x, y, z;
};

namespace std {
	class ostream;
}

std::ostream& operator<<(std::ostream& stream, const Vec3& vector);