#pragma once

#include "Material.h"

namespace rtx {
	class Lambertian : public Material
	{
	public:
		Lambertian(const Vec4& albedo);

		ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const override;
	private:
		Vec4 m_albedo;
	};
}