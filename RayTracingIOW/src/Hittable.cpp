#include "Hittable.h"

void rtx::Hittable::HitRecord::setFaceNormal(const Ray& ray, const Vec3& outwardNormal)
{
	frontFace = Vec3::dot(ray.getDirection(), outwardNormal) < 0;
	normal = frontFace ? outwardNormal : -outwardNormal;
}