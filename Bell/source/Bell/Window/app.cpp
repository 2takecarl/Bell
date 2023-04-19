#include "app.h"

App::App(int width, int height, bool debug)
{
	buid_glfw_window(width, height, debug);

	graphicsEngine = new Engine(width, height, window, debug);
}

void App::buid_glfw_window(int width, int height, bool debugMode)
{
	//Initialize glfw
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	if (window = glfwCreateWindow(width, height, "Bell Engine", nullptr, nullptr)) {
		if (debugMode)
			std::cout << "Successfully made a glfw window" << std::endl;
	}
	else {
		if (debugMode)
			std::cout << "GLFW window creation failed" << std::endl;
	}
}

void App::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		graphicsEngine->render();
		calculateFrameRate();
	}
}

void App::calculateFrameRate()
{
	currentTime = glfwGetTime();
	double delta = currentTime - lastTime;

	if (delta >= 1)
	{
		int framerate{ std::max(1, int(numFrames / delta)) };
		std::stringstream title;
		title << "Running at " << framerate << " fps.";
		glfwSetWindowTitle(window, title.str().c_str());
		lastTime = currentTime;
		numFrames = -1;
		frameTime = float(1000.0 / framerate);
	}

	numFrames++;
}

App::~App()
{
	delete graphicsEngine;
}