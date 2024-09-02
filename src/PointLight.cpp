#include "GE/Components/PointLight.h"


GE::PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float linear, float quadratic)
{
	Position = glm::vec3(0.0f);
	this->linear = linear;
	this->quadratic = quadratic;

	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
}

float* GE::PointLight::getPosition()
{
	return glm::value_ptr(Position);
}

float GE::PointLight::getLinear() const
{
	return linear;
}

float GE::PointLight::getQuadratic() const
{
	return quadratic;
}

void GE::PointLight::update()
{
}
