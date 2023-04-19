#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "config.h"
#include "frame.h"

class Engine
{
public:

	Engine(int width, int height, GLFWwindow* winodw, bool debugMode);

	~Engine();

	void render();

private:

	//Wether to print debug messages in functions
	bool debugMode;

	//glfw window parameters
	int width;
	int height;
	GLFWwindow* window;

	//Instance-related variables
	vk::Instance instance{ nullptr };
	vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };
	vk::DispatchLoaderDynamic dldi;
	vk::SurfaceKHR surface;

	//Device-related variables
	vk::PhysicalDevice physicalDevice{ nullptr };
	vk::Device device{ nullptr };
	vk::Queue graphicsQueue{ nullptr };
	vk::Queue presentQueue{ nullptr };
	vk::SwapchainKHR swapchain{ nullptr };
	std::vector<vkUtil::SwapChainFrame> swapchainFrames;
	vk::Format swapchainFormat;
	vk::Extent2D swapchainExtent;

	//Pipeline-related variables
	vk::PipelineLayout layout;
	vk::RenderPass renderpass;
	vk::Pipeline pipeline;

	//Command-related variables
	vk::CommandPool commandPool;
	vk::CommandBuffer mainCommandBuffer;

	//Synchronization-related variables
	vk::Fence inFlightFence;
	vk::Semaphore imageAvailable, renderFinished;

	//Instance setup
	void make_instance();

	//Device setup
	void make_device();

	//Pipeline setup
	void make_pipeline();

	void finalize_setup();

	void record_draw_commands(vk::CommandBuffer commandBuffer, uint32_t imageIndex);
};