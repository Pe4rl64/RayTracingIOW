#include "Camera.h"

#include "Utils.h"

namespace rtx {
	Camera::Camera(float aspectRatio, int imageWidth, int samplesPerPixel, int maxBounces)
		:
		m_imageWidth(imageWidth),
		m_imageHeight(static_cast<int>(imageWidth / aspectRatio)),
		m_aspectRatio(((float)m_imageWidth) / m_imageHeight),
		m_samplesPerPixel(samplesPerPixel),
		m_maxBounces(maxBounces)
	{
		initialize();
	}

	Camera::Camera(int imageWidth, int imageHeight, int samplesPerPixel, int maxBounces)
		:
		m_imageWidth(imageWidth),
		m_imageHeight(imageHeight),
		m_aspectRatio(((float)m_imageWidth) / m_imageHeight),
		m_samplesPerPixel(samplesPerPixel),
		m_maxBounces(maxBounces)
	{
		initialize();
	}

	void Camera::render(std::ostream& stream, const Hittable& world)
	{
		stream << "P3\n" << m_imageWidth << ' ' << m_imageHeight << "\n255\n";

		for (int i = 0; i < m_imageHeight; ++i)
		{
			std::cout << "Scanlines remaining: " << m_imageHeight - i << "\n";

			Point3 pixelCurrentVertical = i * m_pixelDeltaVertical;

			for (int j = 0; j < m_imageWidth; ++j)
			{
				Point3 pixelCurrentHorizontal = j * m_pixelDeltaHorizontal;

				Point3 pixelCurrentCenter = m_pixelUpperLeft + pixelCurrentHorizontal + pixelCurrentVertical;

				// First sample always center
				Vec3 pixelCenterRayDirection = m_cameraCenter + pixelCurrentCenter;
				Color pixelCurrentColor(rayColor(Ray(m_cameraCenter, pixelCenterRayDirection), m_maxBounces, world));

				// Taking samples for antialiasing
				for (int sample = 1; sample < m_samplesPerPixel; ++sample)
				{
					Ray ray = getRay(pixelCurrentCenter);
					pixelCurrentColor += rayColor(ray, m_maxBounces, world);
				}

				pixelCurrentColor.writeColor(stream, m_samplesPerPixel);
				stream << '\n';
			}
		}

		std::cout << "Finished rendering.";
	}

	void Camera::initialize()
	{
		m_cameraCenter = Point3(0, 0, 0);
		float focalLenght = 1.0f;
		float viewportHeight = 2.0f;
		float viewportWidth = viewportHeight * m_aspectRatio; // Viewport width can be less than 1 since real valued. Uses real aspect ratio

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

	Ray Camera::getRay(const Point3& pixelCenter) const
	{
		Point3 pixelSample = pixelCenter + pixelSampleSquare();
		Vec3 rayDirection = m_cameraCenter + pixelSample;

		return Ray(m_cameraCenter, rayDirection);
	}

	Vec3 Camera::pixelSampleSquare() const
	{
		// Between -0.5 and +0.5
		float px = -0.5f + randomFloat(0, 1); 
		float py = -0.5f + randomFloat(0, 1);

		return (px * m_pixelDeltaHorizontal) + (py * m_pixelDeltaVertical);
	}

	Color Camera::rayColor(const Ray& ray, int bounce, const Hittable& world) const
	{
		auto [hit, record] = world.hit(ray, rtx::Interval(0, rtx::infinity));

		if (bounce <= 0)
		{
			return Color(0, 0, 0);
		}

		if (hit)
		{
			Vec3 direction = Vec3::randomOnHemisphere(record.normal);
			// Accounting for hit points inside spheres because of floating point precision errors
			return rayColor(Ray(record.point + record.normal * 0.0001f, direction), bounce - 1, world) / 2;
		}

		rtx::Vec3 unitDirection = ray.getDirection().unitVector();
		float a = (unitDirection.y + 1) / 2;
		return (1 - a) * rtx::Color(1, 1, 1) + a * rtx::Color(0.5f, 0.7f, 1.0f);
	}
}