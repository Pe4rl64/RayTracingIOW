#pragma once

#include "Color.h"
#include "Ray.h"
#include "Hittable.h"

#include <iostream>

namespace rtx {
	class Camera
	{
	public:
		Camera(float aspectRatio, int m_imageWidth);

		void render(std::ostream& stream, const Hittable& world);

	private:
		Color rayColor(const Ray& ray, const Hittable& world);

	private:
		int m_imageWidth, m_imageHeight;
		float m_aspectRatio;
		Point3 m_cameraCenter, m_pixelUpperLeft;
		Vec3 m_pixelDeltaHorizontal, m_pixelDeltaVertical;
	};
}