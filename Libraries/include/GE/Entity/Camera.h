#pragma once

#include <iostream>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GE/Entity/Object.h"
#include "GE/HelperClasses/Input.h"

namespace GE
{

	class Camera : public Object
	{
	private:
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

	public:
		glm::vec3 cameraPos;
		glm::vec3 cameraUp;
		glm::vec3 cameraFront;
		float cameraSpeed;

		float fov = 45.0f;
		float aspectRatio = 1.0f;
		float nearClipPlane = 1.0f;
		float farClipPlane = 100.0f;

		Camera();
		~Camera();

		void setUp(float cameraSpeed, float fov, float aspectRatio, float near, float far);
		void setAspectRatio(float aspectRatio);
		void setSpeed(float cameraSpeed);

		float* getViewTransform();
		float* getProjectionTransform();

		void update() override;
	};

}

