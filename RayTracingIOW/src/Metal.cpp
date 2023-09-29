#include "Metal.h"

rtx::Metal::Metal(const Color& albedo, float fuzz)
    : m_albedo(albedo), m_fuzz(fuzz)
{
}

rtx::Material::ScatterResult rtx::Metal::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
    Vec3 reflection = input.getDirection().reflect(record.normal)
        + (m_fuzz * Vec3::randomUnit());
    return { Vec3::dot(reflection, record.normal) <= 0, {record.point, reflection}, m_albedo };
}
