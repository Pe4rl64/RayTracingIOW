# Ray Tracing in One Weekend

![Some very beautyful balls](/assets/images/many_balls.png)

## A bit of info

This project started out as an attempt at implementing the code of the [Ray Tracing in One Weekend](https://raytracing.github.io/) book series with optimization and styling changes where I would see fit.  

Although such goal has been reached (at least for the first book), I have decided to continue maintaining and expanding the codebase, with the final objective being building a usable gpu ray tracing engine.

## Future goals

At the present time I have come up with a few goals for this project, some of them for the near future others for the long term:
- Switching to **CMake** as build system, and **clang-format** as code formatter
- Switching to **GLM** as graphics math library
- Implementing scene serialization (saving scenes)
- Changing the structure of materials and objects
	- Packaging all the materials and objects into their own respective classes without inheritance for better memory layout
	- Reading **texture** and **triangle mesh** files instead of raw materials and objects
- Moving the rendering pipeline onto the **GPU** using Vulkan/DirectX