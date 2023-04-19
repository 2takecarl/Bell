#pragma once
#include <Engine/config.h>
#include <Engine/engine.h>

class App
{
private:
	Engine* graphicsEngine;
	GLFWwindow* window;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;

	void buid_glfw_window(int width, int height, bool debugMode);

	void calculateFrameRate();

public:
	App(int width, int height, bool debug);
	~App();
	void run();
};