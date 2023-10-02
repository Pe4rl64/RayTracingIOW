#include "Dielectric.h"

rtx::Dielectric::Dielectric(float indexOfRefraction)
    : m_indexOfRefraction(indexOfRefraction)
{
}

rtx::Material::ScatterResult rtx::Dielectric::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
    Color attenuation(1.0f);

    float refractionRatio = record.frontFace ? (1 / m_indexOfRefraction) : m_indexOfRefraction; // air is always the other medium
    Vec3 unitDirection = input.getDirection().unitVector();

    Vec3 refraction = Vec3::refract(unitDirection, record.normal, refractionRatio);

    return { false, Ray(record.point, refraction), attenuation };
}
