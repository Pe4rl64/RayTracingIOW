#include "HittableList.h"

rtx::HittableList::HittableList()
	: m_objects()
{
}

void rtx::HittableList::clear()
{
	m_objects.clear();
}

void rtx::HittableList::add(std::shared_ptr<Hittable> object)
{
	m_objects.push_back(object);
}

rtx::Hittable::HitRecord rtx::HittableList::hit(const Ray& ray, const Interval& interval) const
{
	HitRecord result;
	result.t = -1;
	float closest = interval.maximum;

	for (const auto& object : m_objects)
	{
		HitRecord temporary = object->hit(ray, Interval(interval.minimum, closest));

		if (temporary.t >= 0)
		{
			closest = temporary.t;
			result = temporary;
		}
	}

	return result;
}