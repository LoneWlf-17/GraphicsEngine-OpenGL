#ifndef INPUT_CALLBACK
#define INPUT_CALLBACK

#include "HelperClasses/Input.h"

int GE::Input::firstMouse = 1;
double GE::Input::lastX = 600.0;
double GE::Input::lastY = 600.0;
double GE::Input::pitch = 0.0;
double GE::Input::yaw = -90.0;

float GE::Input::currentTime = 0.0f;
float GE::Input::deltaTime = 0.0f;
float GE::Input::lastTime = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (GE::Input::firstMouse)
	{
		GE::Input::lastX = xpos;
		GE::Input::lastY = ypos;
		GE::Input::firstMouse = false;
	}
	float xOffset = xpos - GE::Input::lastX;
	float yOffset = GE::Input::lastY - ypos;

	GE::Input::lastX = xpos;
	GE::Input::lastY = ypos;

	float sensitivity = 0.05f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	GE::Input::yaw += xOffset;
	GE::Input::pitch += yOffset;

	if (GE::Input::pitch > 89.0f)
		GE::Input::pitch = 89.0f;
	if (GE::Input::pitch < -89.0f)
		GE::Input::pitch = -89.0f;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

#endif // INPUT_CALLBACK