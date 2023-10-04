#pragma once

#include "Material.h"

namespace rtx {
	/// <summary>
	/// Dielectric material (see-through). If both reflection and refraction are possible,
	/// scatters <b>one</b> ray in one of the two directions <b>randomly</b>.
	/// </summary>
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
		/// <summary>
		/// Calculates the reflectivity at a certain angle from the normal using Schlick's approximation.
		/// </summary>
		/// <param name="cosine">The cosine of the angle between the incident ray and the normal.</param>
		/// <param name="refractionIndex">The index of refraction of the  material.</param>
		/// <returns>The reflection coefficient for the light incident light ray.</returns>
		static float reflectance(float cosine, float refractionIndex);
	private:
		float m_indexOfRefraction; // Index of refraction of the material
	};
}