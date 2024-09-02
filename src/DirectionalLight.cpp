#include "GE/Components/DirectionalLight.h"

GE::DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	Direction = glm::vec3(0.0f);

	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
}

float* GE::DirectionalLight::getDirection()
{
	return glm::value_ptr(Direction);
}

void GE::DirectionalLight::update()
{
}
