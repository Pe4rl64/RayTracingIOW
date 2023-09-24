#pragma once

#include "Color.h"
#include "Ray.h"
#include "Hittable.h"

#include <iostream>

namespace rtx {
	class Camera
	{
	public:
		Camera(float aspectRatio, int imageWidth, int samplesPerPixel, int maxBounces);

		Camera(int imageWidth, int imageHeight, int samplesPerPixel, int maxBounces);

		void render(std::ostream& stream, const Hittable& world);

	private:
		void initialize();

		Ray getRay(const Point3& pixelCenter) const;

		Vec3 pixelSampleSquare() const;

		Color rayColor(const Ray& ray, int bounce, const Hittable& world) const;
		
	private:
		int m_imageWidth, m_imageHeight;
		float m_aspectRatio;
		int m_samplesPerPixel;
		int m_maxBounces;

		Point3 m_cameraCenter;
		Vec3 m_pixelDeltaHorizontal, m_pixelDeltaVertical;
		Point3 m_pixelUpperLeft;
	};
}