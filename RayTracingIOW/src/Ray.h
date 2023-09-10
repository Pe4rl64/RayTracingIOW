#pragma once

#include "Vec3.h"
#include "Point3.h"

class Ray
{
public:
	Ray();

	Ray(const Point3& origin, const Vec3& direction);

	Ray(Point3&& origin, Vec3&& direction);

	Point3 getOrigin() const;
	Vec3 getDirection() const;

	void setOrigin(const Point3& origin);
	void setOrigin(Point3&& origin);
	void setDirection(const Vec3& direction);
	void setDirection(Vec3&& direction);

	Point3 at(float t) const;

private:
	Point3 m_origin;
	Vec3 m_direction;
};