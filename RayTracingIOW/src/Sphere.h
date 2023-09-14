#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere();

	Sphere(const Point3& center, float radius);

	/// <inheritdoc/>
	std::tuple<bool, HitRecord> hit(const Ray& ray, float minT, float maxT) const override;
	
private:
	Point3 m_center;
	float m_radius;
};