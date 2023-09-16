#include <iostream>
#include <fstream>

#include "Ray.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utils.h"


static rtx::Color rayColor(const rtx::Ray& ray, const rtx::Hittable& world)
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

int main()
{
	// Image
	std::ofstream image("renders/image.ppm");

	float aspectRatio = 16.0f / 9.0f; // ideal aspect ratio
	int imageWidth = 800;

	// Calculating image height, which must be at least 1
	int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	
	if (imageHeight < 1)
		imageHeight = 1;

	// Camera
	float focalLenght = 1.0f;
	float viewportHeight = 2.0f;
	float viewportWidth = viewportHeight * (static_cast<float>(imageWidth) / imageHeight); // Viewport width can be less than 1 since real valued. Uses real aspect ratio
	rtx::Point3 cameraCenter(0, 0, 0);

	// Vector across the horizontal edge of the viewport (starting from the top left corner)
	rtx::Vec3 viewportHorizontal(viewportWidth, 0, 0);
	// Vector across the vertical edge of the viewport (starting from the top left corner)
	rtx::Vec3 viewportVertical(0, -viewportHeight, 0);

	// Horizontal delta vector from pixel to pixel
	rtx::Vec3 pixelDeltaHorizontal = viewportHorizontal / imageWidth;
	// Vertical delta vector from pixel to pixel
	rtx::Vec3 pixelDeltaVertical = viewportVertical / imageHeight;

	// Upper left corner of the viewport
	rtx::Point3 viewportUpperLeft = cameraCenter 
		- rtx::Vec3(0, 0, focalLenght)
		- ((viewportHorizontal + viewportVertical) / 2);
	// Upper left pixel 
	rtx::Point3 pixelUpperLeft = viewportUpperLeft
		+ ((pixelDeltaHorizontal + pixelDeltaVertical) / 2);

	// World
	rtx::HittableList world;

	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0, 0, -1), 0.5f));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0, -100.5f, -1), 100));

	// Render
	image << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::cout << "Scanlines remaining: " << imageHeight - i << "\n";

		rtx::Point3 pixelCurrentVertical = i * pixelDeltaVertical;

		for (int j = 0; j < imageWidth; j++)
		{
			rtx::Point3 pixelCurrentHorizontal = j * pixelDeltaHorizontal;

			rtx::Point3 pixelCurrent = pixelUpperLeft + pixelCurrentHorizontal + pixelCurrentVertical;
			rtx::Vec3 rayDirection = cameraCenter + pixelCurrent;
			rtx::Ray ray(cameraCenter, rayDirection);

			image << rayColor(ray, world) << '\n';
		}
	}

	image.close();
	std::cout << "Finished rendering.";
	
	std::cin.get();
}