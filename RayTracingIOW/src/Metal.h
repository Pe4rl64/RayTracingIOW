#pragma once

#include "Material.h"

namespace rtx {
	class Metal : public Material
	{
	public:
		Metal(const Vec4& albedo, float fuzz);

		ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const override;

	private:
		Vec4 m_albedo;
		float m_fuzz;
	};
}