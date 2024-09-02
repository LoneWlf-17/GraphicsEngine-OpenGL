#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GE/Components/Component.h"
#include "GE/HelperClasses/Shader.h"

namespace GE
{

	class Transform : public Component
	{
	private:
		glm::mat4 transform_mat;

		glm::vec3 lastPosition;
		glm::vec3 lastRotation;
		glm::vec3 lastScale;
	public:

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform();

		void translate(float x, float y, float z);
		void rotate(float angle, glm::vec3 axis);
		void scaleTo(float x, float y, float z);
		float* getModelTransform();

		void update() override;
	};

}

