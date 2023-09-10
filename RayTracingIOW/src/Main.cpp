#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Point3.h"
#include "Ray.h"

Color rayColor(const Ray& ray)
{
	return Color(0, 0, 0);
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
	uint32_t imageWidth = 400;

	// Calculating image height, which must be at least 1
	uint32_t imageHeight = static_cast<int>(imageWidth / aspectRatio);
	
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

		for (int j = 0; j < imageWidth; j++)
		{
			Point3 pixelCurrent = pixelUpperLeft + (j * pixelDeltaHorizontal) + (i * pixelDeltaVertical);
			Vec3 rayDirection = cameraCenter + pixelCurrent;
			Ray ray(cameraCenter, rayDirection);
			
			image << randomRayColor(ray) << '\n';
		}
	}

	image.close();
	std::cout << "Finished rendering.";
	
	std::cin.get();
}