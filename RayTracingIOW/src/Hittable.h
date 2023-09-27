#pragma once

#include "Point3.h"
#include "Ray.h"
#include "Interval.h"

namespace rtx {
	class Hittable
	{
	public:
		/// <summary>
		/// The result of an intersection. If no intersection occured then t = -1.
		/// </summary>
		struct HitRecord
		{
			Point3 point; // The point of intersection
			Vec3 normal; // The normal of the surface
			float t; // The t (time point) at which the ray intersects the object, -1 if no intersection occurred.
			bool frontFace; // true if the intersection occurred with the front face, false otherwise.

			/// <summary>
			/// Calculates the normal vector based on the face that was intersected.
			/// </summary>
			/// <param name="ray">The intersecting ray.</param>
			/// <param name="outwardNormal">The normal of the surface that always points outward, <b>assumed normalized</b>.</param>
			void setFaceNormal(const Ray& ray, const Vec3& outwardNormal);
		};

		/// <summary>
		/// Checks if there are any intersections along the path of the given ray to the current object,
		/// given a search range for the <b>t</b> value.
		/// If a intersection occurs returns true and a HitRecord with the intersection info of the closest one.
		/// </summary>
		/// <param name="ray">The ray to check against.</param>
		/// <param name="interval">The interval in which to search for intersections.</param>
		/// <returns>
		/// A HitRecord, which contains the intersection info. If there was no intersection t = -1.
		/// </returns>
		virtual HitRecord hit(const Ray& ray, const Interval& interval) const = 0;

		virtual ~Hittable() = default;
	};
}