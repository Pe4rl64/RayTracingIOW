#pragma once

#include "Color.h"
#include "Ray.h"
#include "Hittable.h"

#include <iostream>

namespace rtx {
	class Camera
	{
	public:
		Camera(float aspectRatio, int imageWidth, int samplesPerPixel);

		void render(std::ostream& stream, const Hittable& world);

	private:
		Ray getRay(const Point3& pixelCenter) const;

		Vec3 pixelSampleSquare() const;

		Color rayColor(const Ray& ray, const Hittable& world) const;
		
	private:
		int m_imageWidth, m_imageHeight, m_samplesPerPixel;
		float m_aspectRatio;
		Point3 m_cameraCenter, m_pixelUpperLeft;
		Vec3 m_pixelDeltaHorizontal, m_pixelDeltaVertical;
	};
}