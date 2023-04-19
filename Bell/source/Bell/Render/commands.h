#pragma once
#include <Engine/config.h>
#include <Engine/queue_families.h>

namespace vkInit
{
	struct commandBufferInputChunk
	{
		vk::Device device;
		vk::CommandPool commandPool;
		std::vector<vkUtil::SwapChainFrame>& frames;
	};

	vk::CommandPool make_command_pool(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug)
	{
		vkUtil::QueueFamilyIndices queueFamilyIndices = vkUtil::findQueueFamilies(physicalDevice, surface, debug);

		vk::CommandPoolCreateInfo poolInfo = {};
		poolInfo.flags = vk::CommandPoolCreateFlags() | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		try
		{
			return device.createCommandPool(poolInfo);
		}
		catch (vk::SystemError)
		{
			if (debug)
				std::cout << "Failed to create Command Pool" << std::endl;
			return nullptr;
		}
	}

	vk::CommandBuffer make_command_buffers(commandBufferInputChunk inputChunk, bool debug)
	{
		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = inputChunk.commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = 1;

		for (int i = 0; i < inputChunk.frames.size(); i++)
		{
			try
			{
				inputChunk.frames[i].commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

				if (debug)
				{
					std::cout << "Allocated command buffer for frame " << i << std::endl;
				}
			}
			catch (vk::SystemError err)
			{
				if (debug)
					std::cout << "Failed to allocate command buffer for frame " << i << std::endl;
			}
		}
		try
		{
			vk::CommandBuffer commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

			if (debug)
			{
				std::cout << "Allocated main command buffer" << std::endl;
			}
			
			return commandBuffer;
		}
		catch (vk::SystemError err)
		{
			if (debug)
				std::cout << "Failed to allocate main command buffer" << std::endl;

			return nullptr;
		}
	}
}