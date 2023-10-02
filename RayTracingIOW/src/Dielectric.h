#pragma once

#include "Material.h"

namespace rtx {
	class Dielectric : public Material
	{
	public:
		/// <summary>
		/// Initializes the material with the given indexOfRefraction.
		/// </summary>
		/// <param name="indexOfRefraction">
		/// The index of refraction of this dielectric material (e.g. window glass 1.52).
		/// </param>
		Dielectric(float indexOfRefraction);
	public:
		ScatterResult scatter(const Ray& input, const Hittable::HitRecord& record) const override;
	private:
		float m_indexOfRefraction;
	};
}