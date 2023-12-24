#pragma once

#include "Vec4.h"
#include "Ray.h"
#include "Hittable.h"

namespace rtx {
	class Material
	{
	public:
		struct ScatterResult
		{
			bool absorbed; // True if the input ray was completely absorbed.
			Ray scattered; // Output scattered ray.
			Vec4 attenuation; // Attenuation of the output scattered ray.
		};

		virtual ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const = 0;

		virtual ~Material() = default;
	};
}