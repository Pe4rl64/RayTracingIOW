#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Point3.h"
#include "Ray.h"

bool hitSphere(const Point3& center, float radius, const Ray& ray)
{
	Vec3 oc = ray.getOrigin() - center; // (A - C)
	float a = ray.getDirection().dot(ray.getDirection()); // a . a
	float b = 2.0f * ray.getDirection().dot(oc); // 2b . (A - C)
	float c = oc.dot(oc) - radius * radius; // (A - C) . (A - C) - r^2

	float discriminant = b * b - 4 * a * c; // b^2 - 4ac

	return discriminant >= 0;
}

Color rayColor(const Ray& ray)
{
	if (hitSphere(Point3(0, 0, -1), 0.5f, ray))
		return Color(1, 0, 0);

	Vec3 unitDirection = ray.getDirection().unitVector();
	float a = (unitDirection.y + 1) / 2;
	return (1 - a) * Color(1, 1, 1) + a * Color(0.5f, 0.7f, 1.0f);
}

Color randomRayColor(const Ray& ray)
{
	return Color(static_cast<float>((rand() % 256)) / 255, static_cast<float>((rand() % 256)) / 255, static_cast<float>((rand() % 256)) / 255);
}

int main()
{
	// Image
	std::ofstream image("res/image.ppm");

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
	Point3 cameraCenter(0, 0, 0);

	// Vector across the horizontal edge of the viewport (starting from the top left corner)
	Vec3 viewportHorizontal(viewportWidth, 0, 0);
	// Vector across the vertical edge of the viewport (starting from the top left corner)
	Vec3 viewportVertical(0, -viewportHeight, 0);

	// Horizontal delta vector from pixel to pixel
	Vec3 pixelDeltaHorizontal = viewportHorizontal / imageWidth;
	// Vertical delta vector from pixel to pixel
	Vec3 pixelDeltaVertical = viewportVertical / imageHeight;

	// Upper left corner of the viewport
	Point3 viewportUpperLeft = cameraCenter 
		- Vec3(0, 0, focalLenght)
		- ((viewportHorizontal + viewportVertical) / 2);
	// Upper left pixel 
	Point3 pixelUpperLeft = viewportUpperLeft
		+ ((pixelDeltaHorizontal + pixelDeltaVertical) / 2);

	// Render
	image << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int i = 0; i < imageHeight; i++)
	{
		std::cout << "Scanlines remaining: " << imageHeight - i << "\n";

		Point3 pixelCurrentVertical = i * pixelDeltaVertical;

		for (int j = 0; j < imageWidth; j++)
		{
			Point3 pixelCurrentHorizontal = j * pixelDeltaHorizontal;

			Point3 pixelCurrent = pixelUpperLeft + pixelCurrentHorizontal + pixelCurrentVertical;
			Vec3 rayDirection = cameraCenter + pixelCurrent;
			Ray ray(cameraCenter, rayDirection);

			image << rayColor(ray) << '\n';
		}
	}

	image.close();
	std::cout << "Finished rendering.";
	
	std::cin.get();
}