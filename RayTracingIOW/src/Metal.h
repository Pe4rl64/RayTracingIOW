#pragma once

#include "Material.h"

namespace rtx {
	class Metal : public Material
	{
	public:
		Metal(const Color& albedo, float fuzz);

		ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const override;

	private:
		Color m_albedo;
		float m_fuzz;
	};
}