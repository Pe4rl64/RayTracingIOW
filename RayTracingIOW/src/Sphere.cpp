#include "Sphere.h"

#include <cmath>

namespace rtx {
	Sphere::Sphere()
		: m_center(), m_radius(0.0f)
	{
	}

	Sphere::Sphere(const Point3& center, float radius)
		: m_center(center), m_radius(radius)
	{
	}

	std::tuple<bool, HitRecord> Sphere::hit(const Ray& ray, float minT, float maxT) const
	{
		Vec3 oc = ray.getOrigin() - m_center; // (A - C)
		float a = ray.getDirection().lengthSquared(); // a . a == length squared
		float halfB = Vec3::dot(ray.getDirection(), oc); // b . (A - C)
		float c = oc.lengthSquared() - m_radius * m_radius; // (A - C) . (A - C) - r^2

		float discriminant = halfB * halfB - a * c; // halfB^2 - ac

		if (discriminant < 0)
			return std::make_tuple<bool, HitRecord>(false, HitRecord());

		float rootedDiscriminant = std::sqrtf(discriminant);

		// Determining the nearest root in range
		float root = (-halfB - rootedDiscriminant) / a;

		if (root <= minT || root >= maxT)
		{
			root = (-halfB + rootedDiscriminant) / a;

			if (root <= minT || root >= maxT)
				return std::make_tuple<bool, HitRecord>(false, HitRecord());
		}

		Point3 intersect = ray.at(root);

		return std::make_tuple<bool, HitRecord>(true, HitRecord(
			intersect,
			root,
			ray,
			(intersect - m_center) / m_radius
		));
	}

}