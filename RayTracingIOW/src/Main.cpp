#include <iostream>
#include <memory>

#pragma warning(disable : 4996)
#include <stb_image_write/stb_image_write.h>
#pragma warning(default : 4996)

#include "Ray.h"
#include "Vec4.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utils.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Renderer.h"
#include "Timer.h"

int main()
{
	// World
	rtx::HittableList world;

	auto ground = std::make_shared<rtx::Lambertian>(rtx::Vec4(0.8f, 0.8f, 0.0f, 1.0f));
	auto center = std::make_shared<rtx::Lambertian>(rtx::Vec4(0.1f, 0.2f, 0.5f, 1.0f));
	auto left = std::make_shared<rtx::Dielectric>(1.5f);
	auto right = std::make_shared<rtx::Metal>(rtx::Vec4(0.8f, 0.6f, 0.2f, 1.0f), 0.0f);

	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0.0f, -100.5f, -1.0f), 100.0f, ground));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0.0f, 0.0f, -1.0f), 0.5f, center));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(-1.0f, 0.0f, -1.0f), 0.5f, left));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(-1.0f, 0.0f, -1.0f), -0.4f, left)); // Hollow glass sphere
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(1.0f, 0.0f, -1.0f), 0.5f, right));

	uint32_t imageWidth = 1280u, imageHeight = 720u;

	rtx::Point3 lookFrom(0, 0, 0.5f);
	rtx::Point3 lookAt(0, 0, -1);

	// Camera
	rtx::Camera camera(lookFrom, lookAt - lookFrom, rtx::Vec3(0, 1, 0), 1.0f, imageWidth, imageHeight, 120.0f);

	// Rendering
	rtx::Renderer renderer(imageWidth, imageHeight, 8, 8);

	std::cout << "Starting calculations.\n";

	uint32_t* imageBuffer;
	
	{
		rtx::debug::Timer t;
		imageBuffer = renderer.render(world, camera);
	}

	if (stbi_write_png(
		"renders/image.png",
		imageWidth,
		imageHeight,
		4,
		imageBuffer,
		4 * imageWidth
	))
	{
		std::cout << "Successful write to file!\n";
	}
	else
	{
		std::cout << "Failure in writing to file!\n";
	}

	delete[] imageBuffer;

	system("pause");
}