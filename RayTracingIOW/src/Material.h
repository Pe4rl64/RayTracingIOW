#pragma once

#include "Color.h"
#include "Ray.h"

namespace rtx {
	class Hittable
	{
	public:
		struct HitRecord;
	};

	class Material
	{
	public:
		struct ScatterResult
		{
			Ray scattered;
			Color attenuation;
		};

		virtual ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const = 0;

		virtual ~Material() = default;
	};
}