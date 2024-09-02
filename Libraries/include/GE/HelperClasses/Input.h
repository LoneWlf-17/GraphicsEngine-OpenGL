#pragma once

#include <iostream>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GE
{
	class Input
	{
	public:
		static int firstMouse;
		static double lastX;
		static double lastY;
		static double pitch;
		static double yaw;

		static float currentTime;
		static float deltaTime;
		static float lastTime;

		static void processInput(GLFWwindow* window, glm::vec3* cameraPos, glm::vec3* cameraFront, glm::vec3* cameraUp, float cameraSpeed);
	};
}
