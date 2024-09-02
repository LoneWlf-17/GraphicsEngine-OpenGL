#include "GE/Entity/Camera.h"

GE::Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	cameraSpeed = 2.0f;

	projection = glm::perspective(fov, aspectRatio, nearClipPlane, farClipPlane);
}

GE::Camera::~Camera()
{
}

void GE::Camera::setUp(float cameraSpeed, float fov, float aspectRatio, float near, float far)
{
	this->cameraSpeed = cameraSpeed;
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->nearClipPlane = near;
	this->farClipPlane = far;
}

void GE::Camera::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void GE::Camera::setSpeed(float cameraSpeed)
{
	this->cameraSpeed = cameraSpeed;
}

float* GE::Camera::getViewTransform()
{
	return glm::value_ptr(view);
}

float* GE::Camera::getProjectionTransform()
{
	return glm::value_ptr(projection);
}

void GE::Camera::update()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(Input::yaw)) * cos(glm::radians(Input::pitch));
	direction.y = sin(glm::radians(Input::pitch));
	direction.z = sin(glm::radians(Input::yaw)) * cos(glm::radians(Input::pitch));

	cameraFront = glm::normalize(direction);

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(fov), aspectRatio, nearClipPlane, farClipPlane);


	//std::cout << cameraFront.x << ", " << cameraFront.y << ", " << cameraFront.z << std::endl << std::endl;
}

