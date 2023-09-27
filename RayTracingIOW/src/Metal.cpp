#include "Metal.h"

rtx::Metal::Metal(const Color& albedo)
    : m_albedo(albedo)
{
}

rtx::Material::ScatterResult rtx::Metal::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
    Vec3 reflection = input.getDirection().reflect(record.normal);
    return { false, { record.point, reflection }, m_albedo };
}
