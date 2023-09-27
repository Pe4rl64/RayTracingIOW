#pragma once

#include "Material.h"

namespace rtx {
	class Lambertian : public Material
	{
	public:
		Lambertian(const Color& albedo);

		ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const override;
	private:
		Color m_albedo;
	};
}