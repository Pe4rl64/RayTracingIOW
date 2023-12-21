#pragma 

#include <cstdint>

#include "Camera.h"

class Color;

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
	/// <param name="horizontalFov">The horizontal view angle of the image.</param>
	Renderer(uint32_t imageWidth, float aspectRatio, uint32_t samples, uint32_t maxBounces, float horizontalFov);

	/// <summary>
	/// Constructs a renderer with the given parameters. This version automatically calculates
	/// the aspect ratio based on the width and height.
	/// </summary>
	/// <param name="imageWidth">The width (in pixels) of the output image.</param>
	/// <param name="imageHeight">The heigth (in pixels) of the output image.</param>
	/// <param name="samples">The samples to take around the center of the pixel.</param>
	/// <param name="maxBounces">The maximum amount of bounces that a ray can do.</param>
	/// <param name="horizontalFov">The horizontal view angle of the image.</param>
	Renderer(uint32_t imageWidth, uint32_t imageHeight, uint32_t samples, uint32_t maxBounces, float horizontalFov);

	/// <summary>
	/// Renders the image onto the given output stream in .ppm format.
	/// </summary>
	/// <param name="camera">The camera from which to generate the rays.</param>
	/// <param name="stream">The output stream on which the image data will be written.</param>
	void render(const Camera& camera, std::ostream& output) const;
private:

	void perPixel(uint32_t x, uint32_t y);

	void rayColor(const Ray& ray);

private:
	Color* m_imageData;
	
	uint32_t m_imageWidth;
	uint32_t m_imageHeight;
	float m_aspectRatio;
	uint32_t m_samples;
	uint32_t m_maxBounces;
	float m_horizontalFov;
};