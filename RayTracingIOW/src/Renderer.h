#pragma 

#include <cstdint>
#include <vector>

namespace rtx {
	// Forward declarations for the referenced/pointers objects
	class Camera;
	class Hittable;
	class Vec4;
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
		/// <param name="samples">The samples to take around the center of the pixel.</param>
		/// <param name="maxBounces">The maximum amount of bounces that a ray can do.</param>
		Renderer(uint32_t imageWidth, float aspectRatio, uint32_t samples, uint32_t maxBounces);

		/// <summary>
		/// Constructs a renderer with the given parameters. This version automatically calculates
		/// the aspect ratio of the image based on the width and height.
		/// </summary>
		/// <param name="imageWidth">The width (in pixels) of the output image.</param>
		/// <param name="imageHeight">The heigth (in pixels) of the output image.</param>
		/// <param name="samples">The samples to take around the center of the pixel.</param>
		/// <param name="maxBounces">The maximum amount of bounces that a ray can do.</param>
		Renderer(uint32_t imageWidth, uint32_t imageHeight, uint32_t samples, uint32_t maxBounces);

		/// <summary>
		/// Renders the image into a buffer that contains the pixel data in RGB format.
		/// </summary>
		/// <param name="camera">The camera from which to generate the rays.</param>
		/// <param name="stream">The output stream on which the image data will be written.</param>
		/// <returns>
		/// The image buffer with the pixel data. An index of an arbitrary pixel is: x * imageWidth + y.
		/// </returns>
		uint32_t* render(const Hittable& world, const Camera& camera);

	private:
		/// <summary>
		/// The function to be run for every pixel in the image buffer.
		/// </summary>
		/// <param name="x">The x position of the pixel.</param>
		/// <param name="y">The y position of the pixel.</param>
		/// <param name="camera">The camera from which to generate the rays.</param>
		void perPixel(uint32_t x, uint32_t y, const Camera& camera, const Hittable& world);

		/// <summary>
		/// Returns the color of the given ray after it has traced its path.
		/// </summary>
		/// <param name="ray">The ray to trace.</param>
		/// <param name="world">The world with which the ray interacts.</param>
		/// <returns>The color that the light ray should be.</returns>
		Vec4 rayColor(Ray ray, const Hittable& world) const;

		/// <summary>
		/// Initializes the vector iterator wrappers.
		/// </summary>
		void initIterators();

	private:
		uint32_t* m_finalImage;
		uint32_t m_imageWidth, m_imageHeight;

		std::vector<uint32_t> m_widthIterator, m_heightIterator;

		uint32_t m_samples;
		uint32_t m_maxBounces;
	};
}