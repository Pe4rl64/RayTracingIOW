#pragma once

#include "Point3.h"

namespace rtx {
	class Ray
	{
	public:
		Ray();

		Ray(const Point3& origin, const Vec3& direction);

		const Point3& getOrigin() const { return m_origin; }
		const Vec3& getDirection() const { return m_direction; }

		void setOrigin(const Point3& origin);
		void setDirection(const Vec3& direction);

		Point3 at(float t) const;

	private:
		Point3 m_origin;
		Vec3 m_direction;
	};
}