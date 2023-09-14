#pragma once

#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable
{
public:
	HittableList();

	void clear();
	void add(std::shared_ptr<Hittable> object);

	/// <inheritdoc/>
	std::tuple<bool, HitRecord> hit(const Ray& ray, float minT, float maxT) const override;

private:
	std::vector<std::shared_ptr<Hittable>> m_objects;
};