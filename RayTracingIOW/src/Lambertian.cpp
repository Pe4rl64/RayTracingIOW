#include "Lambertian.h"

#include "Hittable.h"

rtx::Lambertian::Lambertian(const Vec4& albedo)
	: m_albedo(albedo)
{
}

rtx::Material::ScatterResult rtx::Lambertian::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
	Vec3 scatterDirection = record.normal + Vec3::randomUnit();

	// Avoid zero ray direction vector
	if (scatterDirection.nearZero(1e-8f))
		scatterDirection = record.normal;

	return ScatterResult(false, Ray(record.point, scatterDirection), m_albedo);
}
