#pragma once

namespace rtx {
	class Vec3;

	class Vec4
	{
	public:
		Vec4();

		Vec4(float value);

		Vec4(const Vec3& vector, float a);

		Vec4(float r, float g, float b, float a);

		static float linearToGamma(float linearComponent);

		Vec4 operator+(const Vec4& other) const;
		Vec4 operator-() const;
		Vec4 operator-(const Vec4& other) const;
		Vec4 operator*(const Vec4& other) const;
		Vec4 operator*(float scalar) const;
		Vec4 operator/(const Vec4& other) const;
		Vec4 operator/(float scalar) const;

		void operator+=(const Vec4& other);
		void operator-=(const Vec4& other);
		void operator*=(const Vec4& other);
		void operator*=(float scalar);
		void operator/=(const Vec4& other);
		void operator/=(float scalar);

		bool operator==(const Vec4& other) const = default;

		float r, g, b, a;
	};

	Vec4 operator*(float scalar, const Vec4& vector);
}