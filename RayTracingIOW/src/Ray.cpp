#include "Ray.h"

rtx::Ray::Ray()
    : m_origin(), m_direction()
{
}

rtx::Ray::Ray(const Point3& origin, const Vec3& direction)
    : m_origin(origin), m_direction(direction)
{
}

void rtx::Ray::setOrigin(const Point3& origin)
{
    m_origin = origin;
}

void rtx::Ray::setDirection(const Vec3& direction)
{
    m_direction = direction;
}

rtx::Point3 rtx::Ray::at(float t) const
{
    return m_origin + t * m_direction;
}