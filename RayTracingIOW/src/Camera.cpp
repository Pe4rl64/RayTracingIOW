#include "Camera.h"

#include <limits>
#include <cmath>

#include "Utils.h"
#include "Material.h"

rtx::Camera::Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
	uint32_t imageWidth, float aspectRatio, float horizontalFov,
	float defocusAngle, float focusDistance
)
	:
	m_center(center),
	m_forwardDirection(forwardDirection),
	m_upDirection(upDirection),
	m_imageWidth(imageWidth),
	m_imageHeight((uint32_t)(imageWidth / aspectRatio)),
	m_aspectRatio(aspectRatio),
	m_horizontalFov(horizontalFov),
	m_defocusAngle(defocusAngle),
	m_focusDistance(focusDistance),
	m_pixelDeltaVertical(),
	m_pixelDeltaHorizontal(),
	m_rayDirections()
{
	m_rayDirections.resize((size_t)m_imageWidth * m_imageHeight);
	init();
}

rtx::Camera::Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
	uint32_t imageWidth, uint32_t imageHeight, float horizontalFov,
	float defocusAngle, float focusDistance
)
	:
	m_center(center),
	m_forwardDirection(forwardDirection),
	m_upDirection(upDirection),
	m_imageWidth(imageWidth),
	m_imageHeight(imageHeight),
	m_aspectRatio((float)imageWidth / (float)imageHeight),
	m_horizontalFov(horizontalFov),
	m_defocusAngle(defocusAngle),
	m_focusDistance(focusDistance),
	m_pixelDeltaVertical(),
	m_pixelDeltaHorizontal(),
	m_rayDirections()
{
	m_rayDirections.resize((size_t)m_imageWidth * m_imageHeight);
	init();
}

const rtx::Ray rtx::Camera::getRaySample(uint32_t x, uint32_t y) const
{
	Point3 origin = m_defocusAngle <= 0 ? m_center : defocusDiskSample();
	Vec3 direction = pixelSquareSample(x, y) - origin;

	return Ray(origin, direction);
}

void rtx::Camera::init()
{
	float theta = degreesToRadians(m_horizontalFov);
	float horizontalRatio = std::tan(theta / 2);
	float viewportWidth = 2.0f * horizontalRatio * m_focusDistance;
	float viewportHeight = viewportWidth / m_aspectRatio;

	// Unit basis vectors for the camera coordinate frame
	Vec3 zUnit = -m_forwardDirection.unitVector();
	Vec3 xUnit = Vec3::cross(m_upDirection, zUnit).unitVector();
	Vec3 yUnit = Vec3::cross(zUnit, xUnit);

	// Camera defocus disk unit basis vectors
	float defocusRadius = m_focusDistance * std::tan(degreesToRadians(m_defocusAngle / 2));
	m_xDefocusDiskUnit = xUnit * defocusRadius;
	m_yDefocusDiskUnit = yUnit * defocusRadius;

	// Vector across the horizontal edge of the viewport (starting from the top left corner)
	Vec3 viewportHorizontal = xUnit * (float)viewportWidth;
	// Vector across the vertical edge of the viewport (starting from the top left corner)
	Vec3 viewportVertical = -yUnit * (float)viewportHeight;

	// Horizontal delta vector from pixel to pixel
	m_pixelDeltaHorizontal = viewportHorizontal / (float)m_imageWidth;
	// Vertical delta vector from pixel to pixel
	m_pixelDeltaVertical = viewportVertical / (float)m_imageHeight;

	// Upper left corner of the viewport
	Point3 viewportUpperLeft = m_center
		- (zUnit * m_focusDistance)
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

			m_rayDirections[j + i * m_imageWidth] = pixelCurrentCenter;
		}
	}
}

const rtx::Point3 rtx::Camera::defocusDiskSample() const
{
	Vec3 p = Vec3::randomInUnitDisk();

	return m_center
		+ (p.x * m_xDefocusDiskUnit)
		+ (p.y * m_yDefocusDiskUnit);
}

const rtx::Point3 rtx::Camera::pixelSquareSample(uint32_t x, uint32_t y) const
{
	// Between -0.5 and +0.5
	float px = -0.5f + randomFloat(0, 1);
	float py = -0.5f + randomFloat(0, 1);

	return m_rayDirections[x + y * m_imageWidth]
		+ (px * m_pixelDeltaHorizontal)
		+ (py * m_pixelDeltaVertical);
}
