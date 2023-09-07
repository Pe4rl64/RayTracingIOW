#include <iostream>
#include <fstream>

#include "Vec3.h"

int main()
{
	// Image
	std::ofstream image("res/image.ppm");

	constexpr uint32_t IMAGE_WIDTH = 256;
	constexpr uint32_t IMAGE_HEIGHT = 256;
	constexpr uint32_t COLOR_DEPTH = 255;

	// Render
	image << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		std::cout << "Scanlines remaining: " << IMAGE_WIDTH - i << "\n";

		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			float red = 0;
			float green = ((float)i) / COLOR_DEPTH;
			float blue = ((float)j) / COLOR_DEPTH;

			int intRed = static_cast<int>(red * COLOR_DEPTH);
			int intGreen = static_cast<int>(green * COLOR_DEPTH);
			int intBlue = static_cast<int>(blue * COLOR_DEPTH);

			image << intRed << ' ' << intGreen << ' ' << intBlue << '\n';
		}
	}

	image.close();
	std::cout << "Finished rendering.";

	Vec3 v(1, 2, 3);
	v = -v;

	std::cin.get();
}