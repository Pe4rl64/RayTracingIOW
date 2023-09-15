#pragma once

#include <tuple>

#include "Ray.h"

namespace rtx {
	struct HitRecord
	{
		Point3 point;
		float t;
		bool frontFace;
		Vec3 normal;

		HitRecord()
			: point(), t(0), frontFace(false), normal()
		{
		}

		/// <summary>
		/// Initializes the HitRecord and calculates the normal vector based on the face that was intersected.
		/// </summary>
		/// <param name="point">The intersection point.</param>
		/// <param name="t">The parameter to give to the Ray::at(t) function to reach the intersect.</param>
		/// <param name="ray">The intersecting ray.</param>
		/// <param name="outwardNormal">The normal of the surface that always points outward, <b>assumed normalized</b></param>
		HitRecord(Point3 point, float t, const Ray& ray, const Vec3& outwardNormal)
			: point(point),
			t(t),
			frontFace(Vec3::dot(ray.getDirection(), outwardNormal) < 0),
			normal(frontFace ? outwardNormal : -outwardNormal)
		{
		}
	};

	class Hittable
	{
	public:
		/// <summary>
		/// Checks if there are any intersections along the path of the given ray to the current object,
		/// given a search range for the <b>t</b> value.
		/// If a intersection occurs returns true and a HitRecord with the intersection info of the closest one.
		/// </summary>
		/// <param name="ray">The ray to check against.</param>
		/// <param name="minT">The minimum value of <b>t</b> under which intersections don't count.</param>
		/// <param name="maxT">The maximum value of <b>t</b> over which intersections don't count.</param>
		/// <returns>
		/// A tuple countaining: a boolean, <b>true</b> if there was a intersection along the path,
		/// <b>false</b> otherwise; and a HitRecord, which contains the intersection info if there was one.
		/// </returns>
		virtual std::tuple<bool, HitRecord> hit(const Ray& ray, float minT, float maxT) const = 0;

		virtual ~Hittable() = default;
	};
}