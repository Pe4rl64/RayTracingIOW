#pragma 

#include <cstdint>
#include <iosfwd>

namespace rtx {
	// Forward declarations for the referenced/pointers objects
	class Camera;
	class Hittable;
	class Color;
	class Ray;
	class Vec3;
	using Point3 = Vec3;

	class Renderer
	{
	public:
		/// <summary>
		/// Constructs a renderer with the given parameters. This version automatically calculates
		/// the image heigth based on the aspect ratio.
		/// </summary>
		/// <param name="imageWidth">The width (in pixels) of the output image.</param>
		/// <param name="aspectRatio">The aspect ratio of the image (width / height).</param>
		/// <param name="horizontalFov">The horizontal view angle of the image.</param>
		/// <param name="samples">The samples to take around the center of the pixel.</param>
		/// <param name="maxBounces">The maximum amount of bounces that a ray can do.</param>
		Renderer(uint32_t imageWidth, float aspectRatio, float horizontalFov, uint32_t samples, uint32_t maxBounces);

		/// <summary>
		/// Constructs a renderer with the given parameters. This version automatically calculates
		/// the aspect ratio based on the width and height.
		/// </summary>
		/// <param name="imageWidth">The width (in pixels) of the output image.</param>
		/// <param name="imageHeight">The heigth (in pixels) of the output image.</param>
		/// <param name="horizontalFov">The horizontal view angle of the image.</param>
		/// <param name="samples">The samples to take around the center of the pixel.</param>
		/// <param name="maxBounces">The maximum amount of bounces that a ray can do.</param>
		Renderer(uint32_t imageWidth, uint32_t imageHeight, float horizontalFov, uint32_t samples, uint32_t maxBounces);

		/// <summary>
		/// Renders the image onto the given output stream in .ppm format.
		/// </summary>
		/// <param name="camera">The camera from which to generate the rays.</param>
		/// <param name="stream">The output stream on which the image data will be written.</param>
		void render(const Camera& camera, const Hittable& world, std::ostream& output);

	private:
		/// <summary>
		/// The function to be run for every pixel in the image buffer.
		/// </summary>
		/// <param name="x">The x position of the pixel.</param>
		/// <param name="y">The y position of the pixel.</param>
		void perPixel(float x, float y);

		/// <summary>
		/// Returns the color of the given ray after it has traced its path.
		/// </summary>
		/// <param name="ray">The ray to trace.</param>
		/// <returns>The color that the light ray should be.</returns>
		Color rayColor(const Ray& ray);

		/// <summary>
		/// Generates and returns a ray that goes from the center of the renderer's camera to the center
		/// of the given pixel.
		/// </summary>
		/// <param name="pixelCenter">The center of the pixel to which the ray will point to.</param>
		/// <returns>The generated ray.</returns>
		Ray generateRay(const Point3& pixelCenter) const;

		/// <summary>
		/// Returns a random point inside the square bounds of a given pixel.
		/// </summary>
		/// <param name="pixelCenter">The center of the pixel from which to take a sample.</param>
		/// <param name="horizontalDelta">The horintal delta (space) vector between each pixel inside the viewport.</param>
		/// <param name="verticalDelta">The vertical delta (space) vector between each pixel inside the viewport.</param>
		/// <returns>The random point.</returns>
		Point3 pixelSampleSquare(const Point3& pixelCenter, const Vec3& horizontalDelta, const Vec3& verticalDelta) const;

	private:
		Color* m_imageData;
		uint32_t m_imageWidth;
		uint32_t m_imageHeight;
		float m_aspectRatio;
		float m_horizontalFov;

		uint32_t m_samples;
		uint32_t m_maxBounces;
	};
}