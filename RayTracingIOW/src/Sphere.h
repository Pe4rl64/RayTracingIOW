#pragma once

#include "Hittable.h"
#include "Point3.h"

namespace rtx {
	class Sphere : public Hittable
	{
	public:
		Sphere(const Point3& center, float radius, std::shared_ptr<Material> material);

		/// <inheritdoc/>
		HitRecord hit(const Ray& ray, const Interval& interval) const override;

	private:
		Point3 m_center;
		float m_radius;
		std::shared_ptr<Material> m_material;
	};
}