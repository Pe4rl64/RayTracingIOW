#include "Lambertian.h"

#include "Hittable.h"

rtx::Lambertian::Lambertian(const Color& albedo)
	: m_albedo(albedo)
{
}

rtx::Material::ScatterResult rtx::Lambertian::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
	Vec3 scatterDirection = record.normal + Vec3::randomUnit();

	// Avoid zero ray direction vector
	if (scatterDirection.nearZero())
		scatterDirection = record.normal;

	return { false, { record.point, scatterDirection }, m_albedo };
}
