#include "Metal.h"

rtx::Metal::Metal(const Vec4& albedo, float fuzz)
    : m_albedo(albedo), m_fuzz(fuzz)
{
}

rtx::Material::ScatterResult rtx::Metal::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
    Vec3 reflection = Vec3::reflect(input.getDirection(), record.normal);
    Ray scattered(record.point, reflection + m_fuzz * Vec3::randomUnit());

    return ScatterResult(Vec3::dot(reflection, record.normal) <= 0, scattered, m_albedo);
}
