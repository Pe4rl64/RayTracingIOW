#pragma once

#include <tuple>

#include "Hittable.h"
#include "Point3.h"

namespace rtx {
	class Sphere : public Hittable
	{
	public:
		Sphere();

		Sphere(const Point3& center, float radius);

		/// <inheritdoc/>
		HitRecord hit(const Ray& ray, const Interval& interval) const override;

	private:
		Point3 m_center;
		float m_radius;
	};
}