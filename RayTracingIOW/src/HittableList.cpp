#include "HittableList.h"

HittableList::HittableList()
    : m_objects()
{
}

void HittableList::clear()
{
    m_objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
    m_objects.push_back(object);
}

std::tuple<bool, HitRecord> HittableList::hit(const Ray& ray, float minT, float maxT) const
{
    bool hitAnything;
    HitRecord result;
    float closest = maxT;

    for (const auto& object : m_objects)
    {
        auto [hit, record] = object->hit(ray, minT, closest);

        if (hit)
        {
            hitAnything = true;
            closest = record.t;
            result = std::move(record);
        }
    }

    return std::make_tuple<bool, HitRecord>(std::move(hitAnything), std::move(result));
}
