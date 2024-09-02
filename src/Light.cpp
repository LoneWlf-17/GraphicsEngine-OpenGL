#include "GE/Components/Light.h"

GE::Light::Light()
{
	Ambient = glm::vec3(0.2f, 0.2f, 0.2f); 
	Diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	Specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

GE::Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
}

float* GE::Light::getAmbient()
{
	return glm::value_ptr(Ambient);
}

float* GE::Light::getDiffuse()
{
	return glm::value_ptr(Diffuse);
}

float* GE::Light::getSpecular()
{
	return glm::value_ptr(Specular);
}

void GE::Light::update()
{
}
