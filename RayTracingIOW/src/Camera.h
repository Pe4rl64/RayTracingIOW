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
		/// <param name="focalLength">The distance between the camera center and the viewport.</param>
		/// <param name="imageWidth">The width of the final image.</param>
		/// <param name="aspectRatio">The aspect ratio of image.</param>
		/// <param name="horizontalFov">The horizontal view angle of the camera in degrees.</param>
		Camera(const Vec3& center, const Vec3& forwardDirection, const Vec3& upDirection,
			float focalLength, uint32_t imageWidth, float aspectRatio,
			float horizontalFov
		);

		/// <summary>
		/// Constructs a camera with the given arguments. This version automatically calculates
		/// the aspect ratio o the image based on the width and height.
		/// </summary>
		/// <param name="center">The center of the camera in 3d space.</param>
		/// <param name="forwardDirection">The direction at which the camera is looking at.</param>
		/// <param name="upDirection">The upwards direction relative to the camera.</param>
		/// <param name="focalLength">The distance between the camera center and the viewport.</param>
		/// <param name="imageWidth">The width of the final image.</param>
		/// <param name="imageHeight">The heigth of the final image.</param>
		/// <param name="horizontalFov">The horizontal view angle of the camera in degrees.</param>
		Camera(const Vec3& center, const Vec3& m_forwardDirection, const Vec3& upDirection,
			float focalLength, uint32_t imageWidth, uint32_t imageHeight,
			float horizontalFov
		);

		/// <summary>
		/// Returns the camera center position.
		/// </summary>
		/// <returns>The camera center postion.</returns>
		const Point3& getCenter() const { return m_center; }

		/// <summary>
		/// Returns the vertical delta (distance) between each pixel in the viewport.
		/// </summary>
		/// <returns>The vertical delta.</returns>
		const Vec3& getPixelDeltaVertical() const { return m_pixelDeltaVertical; }

		/// <summary>
		/// Returns the horizontal delta (distance) between each pixel in the viewport.
		/// </summary>
		/// <returns></returns>
		const Vec3& getPixelDeltaHorizontal() const { return m_pixelDeltaHorizontal; }

		/// <summary>
		/// Returns the cached ray directions from the camera center to the viewport pixels.
		/// Beware that they are not normalized.
		/// </summary>
		/// <returns>The not normalized cached ray directions.</returns>
		const std::vector<Vec3>& getRayDirections() const { return m_rayDirections; }

	private:
		/// <summary>
		/// Calculates the ray directions from the camera center to the viewport pixels.
		/// </summary>
		void calculateRayDirections();
		
	private:
		Vec3 m_center;
		Vec3 m_forwardDirection, m_upDirection;
		float m_focalLength;
		uint32_t m_imageWidth, m_imageHeight;
		float m_aspectRatio;
		float m_horizontalFov;

		Vec3 m_pixelDeltaVertical, m_pixelDeltaHorizontal;
		std::vector<Vec3> m_rayDirections;
	};
}