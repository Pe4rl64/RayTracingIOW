#include "Dielectric.h"

#include <cmath>

#include "Utils.h"

rtx::Dielectric::Dielectric(float indexOfRefraction)
    : m_indexOfRefraction(indexOfRefraction)
{
}

rtx::Material::ScatterResult rtx::Dielectric::scatter(const Ray& input, const Hittable::HitRecord& record) const
{
    Color attenuation(1.0f);

    float refractionRatio = record.frontFace ? (1 / m_indexOfRefraction) : m_indexOfRefraction; // air is always the other medium
    Vec3 unitDirection = input.getDirection().unitVector();

    float cosTetha = Vec3::dot(-unitDirection, record.normal);
    float sinTetha = std::sqrtf(1 - cosTetha * cosTetha);

    Vec3 direction;
    bool reflects = refractionRatio * sinTetha > 1.0f; // Total internal reflection

    // Generating ONLY one scattered ray per hit
    if (reflects || reflectance(cosTetha, refractionRatio) > rtx::randomFloat(0, 1)) 
        direction = Vec3::reflect(unitDirection, record.normal);
    else 
        direction = Vec3::refract(unitDirection, record.normal, refractionRatio);

    return { false, Ray(record.point, direction), attenuation };
}

float rtx::Dielectric::reflectance(float cosine, float refractionIndex)
{
    float temp = (1 - refractionIndex) / (1 + refractionIndex);
    float reflectanceAt0 = temp * temp;
    return reflectanceAt0 + (1 - reflectanceAt0) * std::powf((1 - cosine), 5);
}
