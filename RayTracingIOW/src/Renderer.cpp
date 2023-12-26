#include "Renderer.h"

#include <algorithm>
#include <execution>

#include "Vec4.h"
#include "Ray.h"
#include "Point3.h"
#include "Camera.h"
#include "Material.h"
#include "Utils.h"

rtx::Renderer::Renderer(uint32_t imageWidth, float aspectRatio, uint32_t samples, uint32_t maxBounces)
	:
	m_finalImage(new uint32_t[(size_t)(imageWidth * imageWidth / aspectRatio)]),
	m_imageWidth(imageWidth),
	m_imageHeight((uint32_t)(imageWidth / aspectRatio)),
	m_widthIterator(m_imageWidth),
	m_heightIterator(m_imageHeight),
	m_samples(samples),
	m_maxBounces(maxBounces)
{
	initIterators();
}

rtx::Renderer::Renderer(uint32_t imageWidth, uint32_t imageHeight, uint32_t samples, uint32_t maxBounces)
	:
	m_finalImage(new uint32_t[imageWidth * imageHeight]),
	m_imageWidth(imageWidth),
	m_imageHeight(imageHeight),
	m_widthIterator(m_imageWidth),
	m_heightIterator(m_imageHeight),
	m_samples(samples),
	m_maxBounces(maxBounces)
{
	initIterators();
}

uint32_t* rtx::Renderer::render(const Hittable& world, const Camera& camera)
{
#define MT 1
#if MT == 1
	std::for_each(std::execution::par, m_heightIterator.begin(), m_heightIterator.end(),
		[this, &camera, &world](uint32_t i)
		{
			for (uint32_t j = 0; j < m_imageWidth; ++j)
			{
				perPixel(j, i, camera, world);
			}
		}
	);
#else
	for (uint32_t i = 0; i < m_imageHeight; ++i)
	{
		for (uint32_t j = 0; j < m_imageWidth; ++j)
		{
			perPixel(j, i, camera, world);
		}
	}
#endif

	return m_finalImage;
}

void rtx::Renderer::perPixel(uint32_t x, uint32_t y, const Camera& camera, const Hittable& world)
{
	Vec4 color(0.0f);

	for (uint32_t i = 0; i < m_samples; ++i)
	{
		Point3 pixelSample = pixelSampleSquare(
			camera.getRayDirections()[x + y * m_imageWidth],
			camera.getPixelDeltaHorizontal(),
			camera.getPixelDeltaVertical()
		);

		color += rayColor(Ray(camera.getCenter(), pixelSample), world);
	}

	color /= (float)m_samples;
	Interval interval(0, 1);
	interval.clamp(color);

	m_finalImage[x + y * m_imageWidth] = convertToRGBA(linearToGamma(color));
}

rtx::Vec4 rtx::Renderer::rayColor(Ray ray, const Hittable& world) const
{
	// Gradient for background based on ray direction
	rtx::Vec3 unitDirection = ray.getDirection().unitVector();
	float a = (unitDirection.y + 1) / 2;
	Vec4 color((1 - a) * rtx::Vec3(1.0f, 1.0f, 1.0f) + a * rtx::Vec3(0.5f, 0.7f, 1.0f), 1.0f);

	for (uint32_t i = 0; i < m_maxBounces; ++i)
	{
		// Accounting for hit points inside spheres because of floating point precision errors
		Hittable::HitRecord record = world.hit(ray, Interval(0.0001f, std::numeric_limits<float>::infinity()));

		if (record.t < 0)
			return color;

		Material::ScatterResult result = record.material->scatter(ray, record);

		if (result.absorbed)
			return Vec4(Vec3(0.0f), 1.0f);
		else
			color *= result.attenuation;

		ray = result.scattered;
	}

	return color;
}

rtx::Point3 rtx::Renderer::pixelSampleSquare(const Point3& pixelCenter, const Vec3& horizontalDelta, const Vec3& verticalDelta) const
{
	// Between -0.5 and +0.5
	float px = -0.5f + randomFloat(0, 1);
	float py = -0.5f + randomFloat(0, 1);

	return pixelCenter + (px * horizontalDelta) + (py * verticalDelta);
}

void rtx::Renderer::initIterators()
{
	for (uint32_t i = 0; i < m_imageWidth; ++i)
	{
		m_widthIterator[i] = i;
	}

	for (uint32_t i = 0; i < m_imageHeight; ++i)
	{
		m_heightIterator[i] = i;
	}
}
