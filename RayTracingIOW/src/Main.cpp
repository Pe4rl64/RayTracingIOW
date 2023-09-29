#include <iostream>
#include <fstream>

#include "Ray.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utils.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"

int main()
{
	// Image
	std::ofstream image("renders/image.ppm");

	// World
	rtx::HittableList world;

	auto ground = std::make_shared<rtx::Lambertian>(rtx::Color(0.8f, 0.8f, 0.0f));
	auto center = std::make_shared<rtx::Lambertian>(rtx::Color(0.7f, 0.3f, 0.3f));
	auto left = std::make_shared<rtx::Metal>(rtx::Color(0.8f, 0.8f, 0.8f), 0.3f);
	auto right = std::make_shared<rtx::Metal>(rtx::Color(0.8f, 0.6f, 0.2f), 1.0f);

	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0.0f, -100.5f, -1.0f), 100.0f, ground));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0.0f, 0.0f, -1.0f), 0.5f, center));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(-1.0f, 0.0f, -1.0f), 0.5f, left));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(1.0f, 0.0f, -1.0f), 0.5f, right));

	// Camera
	rtx::Camera camera(16.0f / 9.0f, 1024, 100, 50);

	// Rendering
	camera.render(image, world);
	
	image.close();
	std::cin.get();
}