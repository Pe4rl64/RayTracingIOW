#include <iostream>
#include <fstream>

#include "Vec3.h"
#include "Color.h"
#include "Point3.h"

int main()
{
	// Image
	std::ofstream image("res/image.ppm");

	constexpr uint32_t IMAGE_WIDTH = 256;
	constexpr uint32_t IMAGE_HEIGHT = 256;

	// Render
	image << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		std::cout << "Scanlines remaining: " << IMAGE_WIDTH - i << "\n";

		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			Color pixelColor = Color(float(i) / (IMAGE_HEIGHT - 1),
				float(j) / (IMAGE_WIDTH - 1),
				0.5f);
			
			image << pixelColor << '\n';
		}
	}

	image.close();
	std::cout << "Finished rendering.";
	
	std::cin.get();
}