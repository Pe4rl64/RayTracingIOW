#include <iostream>
#include <fstream>

#include "Ray.h"
#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Utils.h"
#include "Camera.h"

int main()
{
	// Image
	std::ofstream image("renders/image.ppm");

	// World
	rtx::HittableList world;

	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0, 0, -1), 0.5f));
	world.add(std::make_shared<rtx::Sphere>(rtx::Point3(0, -100.5f, -1), 100));

	// Camera
	rtx::Camera camera(16.0f / 9.0f, 800);

	// Rendering
	camera.render(image, world);

	image.close();
	std::cin.get();
}