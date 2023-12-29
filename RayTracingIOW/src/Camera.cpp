#include "Camera.h"

#include <limits>
#include <cmath>

#include "Utils.h"
#include "Material.h"

rtx::Camera::Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
	float focalLength, uint32_t imageWidth, float aspectRatio, float horizontalFov
)
	:
	m_center(center),
	m_forwardDirection(forwardDirection),
	m_upDirection(upDirection),
	m_focalLength(focalLength),
	m_imageWidth(imageWidth),
	m_imageHeight((uint32_t)(imageWidth / aspectRatio)),
	m_aspectRatio(aspectRatio),
	m_horizontalFov(horizontalFov),
	m_pixelDeltaVertical(),
	m_pixelDeltaHorizontal(),
	m_rayDirections()
{
	m_rayDirections.resize((size_t)m_imageWidth * m_imageHeight);
	calculateRayDirections();
}

rtx::Camera::Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
	float focalLength, uint32_t imageWidth, uint32_t imageHeight, float horizontalFov
)
	:
	m_center(center),
	m_forwardDirection(forwardDirection),
	m_upDirection(upDirection),
	m_focalLength(focalLength),
	m_imageWidth(imageWidth),
	m_imageHeight(imageHeight),
	m_aspectRatio((float)imageWidth / (float)imageHeight),
	m_horizontalFov(horizontalFov),
	m_pixelDeltaVertical(),
	m_pixelDeltaHorizontal(),
	m_rayDirections()
{
	m_rayDirections.resize((size_t)m_imageWidth * m_imageHeight);
	calculateRayDirections();
}

void rtx::Camera::calculateRayDirections()
{
	float theta = degreesToRadians(m_horizontalFov);
	float horizontalRatio = std::tanf(theta / 2);
	float viewportWidth = 2.0f * horizontalRatio * m_focalLength;
	float viewportHeight = viewportWidth / m_aspectRatio;

	Vec3 zUnit = -m_forwardDirection.unitVector();
	Vec3 xUnit = Vec3::cross(m_upDirection, zUnit).unitVector();
	Vec3 yUnit = Vec3::cross(zUnit, xUnit);

	// Vector across the horizontal edge of the viewport (starting from the top left corner)
	Vec3 viewportHorizontal = xUnit * (float)viewportWidth;
	// Vector across the vertical edge of the viewport (starting from the top left corner)
	Vec3 viewportVertical = -yUnit * (float)viewportHeight;

	// Horizontal delta vector from pixel to pixel
	m_pixelDeltaHorizontal = viewportHorizontal / m_imageWidth;
	// Vertical delta vector from pixel to pixel
	m_pixelDeltaVertical = viewportVertical / m_imageHeight;

	// Upper left corner of the viewport
	Point3 viewportUpperLeft = m_center
		- (zUnit * m_focalLength)
		- ((viewportHorizontal + viewportVertical) / 2);
	
	// Upper left pixel
	Point3 pixelUpperLeft = viewportUpperLeft
		+ ((m_pixelDeltaHorizontal + m_pixelDeltaVertical) / 2);

	for (uint32_t i = 0; i < m_imageHeight; ++i)
	{
		Point3 pixelCurrentVertical = ((float)i) * m_pixelDeltaVertical;

		for (uint32_t j = 0; j < m_imageWidth; ++j)
		{
			Point3 pixelCurrentHorizontal = ((float)j) * m_pixelDeltaHorizontal;

			Point3 pixelCurrentCenter = pixelUpperLeft + pixelCurrentHorizontal + pixelCurrentVertical;

			m_rayDirections[j + i * m_imageWidth] = m_center + pixelCurrentCenter;
		}
	}
}