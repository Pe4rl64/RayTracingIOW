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

	auto ground = std::make_shared<rtx::Lambertian>(rtx::Vec4(0.5f, 0.5f, 0.5f, 1.0f));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0.0f, -1000, 0), 1000, ground));

	for (int i = -11; i < 11; ++i)
	{
		for (int j = -11; j < 11; ++j)
		{
			auto chooseMaterial = rtx::randomFloat();
			rtx::Point3 center(i + 0.9f * rtx::randomFloat(), 0.2f, j + 0.9f * rtx::randomFloat());

			if ((center - rtx::Point3(4, 0.2f, 0)).length() > 0.9f)
			{
				std::shared_ptr<rtx::Material> sphereMaterial;

				if (chooseMaterial < 0.8f)
				{
					rtx::Vec4 albedo(rtx::Vec3::random() * rtx::Vec3::random(), 1.0f);
					sphereMaterial = std::make_shared<rtx::Lambertian>(albedo);
					world.add(std::make_shared<rtx::Sphere>(center, 0.2f, sphereMaterial));
				}
				else if (chooseMaterial < 0.95f)
				{
					rtx::Vec4 albedo(rtx::Vec3::random(0.5f, 1), 1.0f);
					float fuzz = rtx::randomFloat(0, 0.5f);
					sphereMaterial = std::make_shared<rtx::Metal>(albedo, fuzz);
					world.add(std::make_shared<rtx::Sphere>(center, 0.2f, sphereMaterial));
				}
				else
				{
					sphereMaterial = std::make_shared<rtx::Dielectric>(1.5f);
					world.add(std::make_shared<rtx::Sphere>(center, 0.2f, sphereMaterial));
				}
			}
		}
	}

	auto material1 = std::make_shared<rtx::Dielectric>(1.5f);
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0, 1, 0), 1.0f, material1));

	auto material2 = std::make_shared<rtx::Lambertian>(rtx::Vec4(0.4f, 0.2f, 0.1f, 1.0f));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(-4, 1, 0), 1.0f, material2));

	auto material3 = std::make_shared<rtx::Metal>(rtx::Vec4(0.7f, 0.6f, 0.5f, 1.0f), 0.0f);
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(4, 1, 0), 1.0f, material3));

	uint32_t imageWidth = 2560u, imageHeight = 1440u;

	rtx::Point3 lookFrom(13, 2, 3);
	rtx::Point3 lookAt(0, 0, 0);

	// Camera
	rtx::Camera camera(lookFrom, lookAt - lookFrom, rtx::Vec3(0, 1, 0),
		imageWidth, imageHeight, 35.5f,
		0.6f, 10.0f);

	// Rendering
	rtx::Renderer renderer(imageWidth, imageHeight, 500, 50);

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
		std::cout<< "Successful write to file!\n";
	}
	else
	{
		std::cout << "Failure in writing to file!\n";
	}

	delete[] imageBuffer;

	system("pause");
}