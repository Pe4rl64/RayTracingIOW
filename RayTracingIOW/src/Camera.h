#pragma once

#include <vector>

#include "Hittable.h"

namespace rtx {
	class Camera
	{
	public:
		/// <summary>
		/// Constructs a camera with the given arguments. This version automatically calculates
		/// the image heigth based on the aspect ratio.
		/// </summary>
		/// <param name="center">The center of the camera in 3d space.</param>
		/// <param name="forwardDirection">The direction at which the camera is looking at.</param>
		/// <param name="upDirection">The upwards direction relative to the camera.</param>
		/// <param name="imageWidth">The width of the final image.</param>
		/// <param name="aspectRatio">The aspect ratio of image.</param>
		/// <param name="horizontalFov">The horizontal view angle of the camera in degrees.</param>
		/// <param name="defocusAngle">The variation angle of rays through each pixel in degrees.</param>
		/// <param name="focusDistance">The distance from the camera center to the plane of perfect focus.</param>
		Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
			uint32_t imageWidth, float aspectRatio, float horizontalFov,
			float defocusAngle, float focusDistance
		);

		/// <summary>
		/// Constructs a camera with the given arguments. This version automatically calculates
		/// the aspect ratio o the image based on the width and height.
		/// </summary>
		/// <param name="center">The center of the camera in 3d space.</param>
		/// <param name="forwardDirection">The direction at which the camera is looking at.</param>
		/// <param name="upDirection">The upwards direction relative to the camera.</param>
		/// <param name="imageWidth">The width of the final image.</param>
		/// <param name="imageHeight">The heigth of the final image.</param>
		/// <param name="horizontalFov">The horizontal view angle of the camera in degrees.</param>
		/// <param name="defocusAngle">The variation angle of rays through each pixel in degrees.</param>
		/// <param name="focusDistance">The distance from the camera center to the plane of perfect focus.</param>
		Camera(const Vec3& center, const Vec3& m_forwardDirection, const Vec3& upDirection,
			uint32_t imageWidth, uint32_t imageHeight, float horizontalFov,
			float defocusAngle, float focusDistance
		);

	public:
		/// <summary>
		/// Returns the camera center position.
		/// </summary>
		/// <returns>The camera center postion.</returns>
		const Point3& getCenter() const { return m_center; }

		/// <summary>
		/// Returns a sample ray for a given pixel, with the origin sampled from the camera defocus disk,
		/// and the direction sampled from the square area around the pixel center.
		/// If the defocus angle is &lt;= 0 then the origin will be the camera center.
		/// </summary>
		/// <param name="x">The x coordinate of the pixel (column).</param>
		/// <param name="y">The y coordinate of the pixel (row).</param>
		/// <returns>The sampled ray.</returns>
		const Ray& getRaySample(uint32_t x, uint32_t y) const;

	private:
		/// <summary>
		/// Initializes the camera. To be run every time the options change.
		/// </summary>
		void init();

		const Point3& defocusDiskSample() const;

		const Point3& pixelSquareSample(uint32_t x, uint32_t y) const;
		
	private:
		Vec3 m_center;
		Vec3 m_forwardDirection, m_upDirection;
		uint32_t m_imageWidth, m_imageHeight;
		float m_aspectRatio;
		float m_horizontalFov;
		float m_defocusAngle;
		float m_focusDistance;
		Vec3 m_xDefocusDiskUnit, m_yDefocusDiskUnit;

		Vec3 m_pixelDeltaVertical, m_pixelDeltaHorizontal;
		std::vector<Vec3> m_rayDirections;
	};
}