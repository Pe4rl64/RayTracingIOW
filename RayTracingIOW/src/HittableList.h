#pragma once

#include <tuple>
#include <vector>
#include <memory>

#include "Hittable.h"

class Interval;

namespace rtx {
	class HittableList : public Hittable
	{
	public:
		HittableList();

		void clear();
		void add(std::shared_ptr<Hittable> object);

		/// <inheritdoc/>
		std::tuple<bool, HitRecord> hit(const Ray& ray, const Interval& interval) const override;

	private:
		std::vector<std::shared_ptr<Hittable>> m_objects;
	};
}