#include "Camera.h"

#include "Utils.h"

namespace rtx {
	Camera::Camera(float aspectRatio, int imageWidth)
		:
		m_imageWidth(imageWidth),
		m_imageHeight(static_cast<int>(imageWidth / aspectRatio)),
		m_aspectRatio(aspectRatio),
		m_cameraCenter(0, 0, 0)
	{
		if (m_imageHeight < 1)
			m_imageHeight = 1;

		float focalLenght = 1.0f;
		float viewportHeight = 2.0f;
		float viewportWidth = viewportHeight * (static_cast<float>(m_imageWidth) / m_imageHeight); // Viewport width can be less than 1 since real valued. Uses real aspect ratio

		// Vector across the horizontal edge of the viewport (starting from the top left corner)
		Vec3 viewportHorizontal(viewportWidth, 0, 0);
		// Vector across the vertical edge of the viewport (starting from the top left corner)
		Vec3 viewportVertical(0, -viewportHeight, 0);

		// Horizontal delta vector from pixel to pixel
		m_pixelDeltaHorizontal = viewportHorizontal / m_imageWidth;
		// Vertical delta vector from pixel to pixel
		m_pixelDeltaVertical = viewportVertical / m_imageHeight;

		// Upper left corner of the viewport
		Point3 viewportUpperLeft = m_cameraCenter
			- rtx::Vec3(0, 0, focalLenght)
			- ((viewportHorizontal + viewportVertical) / 2);
		// Upper left pixel 
		m_pixelUpperLeft = viewportUpperLeft
			+ ((m_pixelDeltaHorizontal + m_pixelDeltaVertical) / 2);
	}

	void Camera::render(std::ostream& stream, const Hittable& world)
	{
		stream << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

		for (int i = 0; i < m_imageHeight; i++)
		{
			std::cout << "Scanlines remaining: " << m_imageHeight - i << "\n";

			Point3 pixelCurrentVertical = i * m_pixelDeltaVertical;

			for (int j = 0; j < m_imageWidth; j++)
			{
				Point3 pixelCurrentHorizontal = j * m_pixelDeltaHorizontal;

				Point3 pixelCurrent = m_pixelUpperLeft + pixelCurrentHorizontal + pixelCurrentVertical;
				Vec3 rayDirection = m_cameraCenter + pixelCurrent;
				Ray ray(m_cameraCenter, rayDirection);

				stream << rayColor(ray, world) << '\n';
			}
		}

		std::cout << "Finished rendering.";
	}

	Color Camera::rayColor(const Ray& ray, const Hittable& world)
	{
		auto [hit, record] = world.hit(ray, rtx::Interval(0, rtx::infinity));

		if (hit)
		{
			return (rtx::Color(record.normal.x, record.normal.y, record.normal.z)
				+ rtx::Color(1, 1, 1)) / 2;
		}

		rtx::Vec3 unitDirection = ray.getDirection().unitVector();
		float a = (unitDirection.y + 1) / 2;
		return (1 - a) * rtx::Color(1, 1, 1) + a * rtx::Color(0.5f, 0.7f, 1.0f);
	}
}