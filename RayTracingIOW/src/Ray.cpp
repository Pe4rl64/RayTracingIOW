#include <utility>

#include "Ray.h"

Ray::Ray()
    : m_origin(), m_direction()
{
}

Ray::Ray(const Point3& origin, const Vec3& direction)
    : m_origin(origin), m_direction(direction)
{
}

Point3 Ray::getOrigin() const
{
    return m_origin;
}

Vec3 Ray::getDirection() const
{
    return m_direction;
}

void Ray::setOrigin(const Point3& origin)
{
    m_origin = origin;
}

void Ray::setDirection(const Vec3& direction)
{
    m_direction = direction;
}

Point3 Ray::at(float t) const
{
    return m_origin + t * m_direction;
}
