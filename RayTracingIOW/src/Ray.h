#pragma once

#include "Vec3.h"
#include "Point3.h"

class Ray
{
public:
	Ray();

	Ray(const Point3& origin, const Vec3& direction);

	Point3 getOrigin() const;
	Vec3 getDirection() const;

	void setOrigin(const Point3& origin);
	void setDirection(const Vec3& direction);

	Point3 at(float t) const;

private:
	Point3 m_origin;
	Vec3 m_direction;
};

inline Point3 Ray::getOrigin() const
{
	return m_origin;
}

inline Vec3 Ray::getDirection() const
{
	return m_direction;
}