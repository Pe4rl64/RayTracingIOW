#include "Sphere.h"

rtx::Sphere::Sphere(const Point3& center, float radius, std::shared_ptr<Material> material)
	: m_center(center), m_radius(radius), m_material(material)
{
}

rtx::Hittable::HitRecord rtx::Sphere::hit(const Ray& ray, const Interval& interval) const
{
	HitRecord result;
	result.t = -1;

	Vec3 oc = ray.getOrigin() - m_center; // (A - C)
	float a = ray.getDirection().lengthSquared(); // a . a == length squared
	float halfB = Vec3::dot(ray.getDirection(), oc); // b . (A - C)
	float c = oc.lengthSquared() - m_radius * m_radius; // (A - C) . (A - C) - r^2

	float discriminant = halfB * halfB - a * c; // halfB^2 - ac

	if (discriminant < 0)
		return result;

	float rootedDiscriminant = std::sqrtf(discriminant);

	// Determining the nearest root in range
	float root = (-halfB - rootedDiscriminant) / a;

	if (!interval.surrounds(root))
	{
		root = (-halfB + rootedDiscriminant) / a;

		if (!interval.surrounds(root))
			return result;
	}

	result.t = root;
	result.point = ray.at(result.t);
	result.material = m_material;
	result.setFaceNormal(ray, (result.point - m_center) / m_radius);

	return result;
}