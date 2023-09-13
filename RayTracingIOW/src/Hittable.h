#pragma once

#include <tuple>

#include "Ray.h"

struct HitRecord
{
	Point3 point;
	Vec3 normal;
	float t;
};

class Hittable
{
public:
	/// <summary>
	/// Checks if there are any collisions along the path of the given ray to the current object,
	/// given a search range for the <b>t</b> value.
	/// If a collision occurs returns true and a HitRecord with the collision info of the closest one.
	/// </summary>
	/// <param name="ray">The ray to check against.</param>
	/// <param name="minT">The minimum value of <b>t</b> under which collisions don't count.</param>
	/// <param name="maxT">The maximum value of <b>t</b> over which collisions don't count.</param>
	/// <returns>
	/// A tuple countaining: a boolean, <b>true</b> if there was a collision along the path,
	/// <b>false</b> otherwise; and a HitRecord, which contains the collision info if there was one.
	/// </returns>
	virtual std::tuple<bool, HitRecord> hit(const Ray& ray, float minT, float maxT) const = 0;

	virtual ~Hittable() = default;
};