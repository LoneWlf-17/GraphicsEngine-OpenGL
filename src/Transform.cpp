#include "GE/Components/Transform.h"

GE::Transform::Transform()
{
	transform_mat = glm::mat4(1.0f);

	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);

	lastPosition = position;
	lastRotation = rotation;
	lastScale = scale;
}

void GE::Transform::translate(float x, float y, float z)
{
	transform_mat = glm::translate(transform_mat, glm::vec3(x, y, z));
}

void GE::Transform::rotate(float angle, glm::vec3 axis)
{
	transform_mat = glm::rotate(transform_mat, glm::radians(angle), axis);
}

void GE::Transform::scaleTo(float x, float y, float z)
{
	transform_mat = glm::scale(transform_mat, glm::vec3(x, y, z));
}

float* GE::Transform::getModelTransform()
{
	return glm::value_ptr(transform_mat);
}

void GE::Transform::update()
{
	if (lastPosition != position)
	{
		transform_mat = glm::translate(transform_mat, position);
		lastPosition = position;
	}
	if (lastScale != scale)
	{
		transform_mat = glm::scale(transform_mat, scale);
		lastScale = scale;
	}
}
