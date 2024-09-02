#include "GE/Entity/SceneObject.h"


GE::SceneObject::SceneObject()
{
	Components = std::vector<Component*>();
	PointLights = std::vector<PointLight*>();
	DirectionalLights = std::vector<DirectionalLight*>();
}

void GE::SceneObject::addComponent(Component* component)
{
	Components.push_back(component);
}

void GE::SceneObject::update()
{
	transform.update();
	for (int i = 0; i < Components.size(); i++)
	{
		if (PointLight* PointLightComponent = dynamic_cast<PointLight*>(Components[i]))
		{
			PointLightComponent->Position = transform.position;
		}
		else if (DirectionalLight* directionalLightComponent = dynamic_cast<DirectionalLight*>(Components[i]))
		{
			directionalLightComponent->Direction = transform.rotation;
		}
		else if (Model* ModelComponent = dynamic_cast<Model*>(Components[i]))
		{
			ModelComponent->shader->Use();
			ModelComponent->shader->SetInt("DirectionalLightNo", DirectionalLights.size());
			for (int i = 0; i < DirectionalLights.size(); i++)
			{
				ModelComponent->shader->SetVec3("directionalLights[" + std::to_string(i) + "].direction", DirectionalLights[i]->getDirection());
				ModelComponent->shader->SetVec3("directionalLights[" + std::to_string(i) + "].ambient", DirectionalLights[i]->getAmbient());
				ModelComponent->shader->SetVec3("directionalLights[" + std::to_string(i) + "].diffuse", DirectionalLights[i]->getDiffuse());
				ModelComponent->shader->SetVec3("directionalLights[" + std::to_string(i) + "].specular", DirectionalLights[i]->getSpecular());
			}

			ModelComponent->shader->SetInt("PointLightNo", PointLights.size());
			for (int i = 0; i < PointLights.size(); i++)
			{
				ModelComponent->shader->SetVec3("pointLights[" + std::to_string(i) + "].ambient", PointLights[i]->getAmbient());
				ModelComponent->shader->SetVec3("pointLights[" + std::to_string(i) + "].diffuse", PointLights[i]->getDiffuse());
				ModelComponent->shader->SetVec3("pointLights[" + std::to_string(i) + "].specular", PointLights[i]->getSpecular());
				ModelComponent->shader->SetVec3("pointLights[" + std::to_string(i) + "].position", PointLights[i]->getPosition());
				ModelComponent->shader->SetFloat("pointLights[" + std::to_string(i) + "].linear", PointLights[i]->getLinear());
				ModelComponent->shader->SetFloat("pointLights[" + std::to_string(i) + "].quadratic", PointLights[i]->getQuadratic());
			}
			ModelComponent->shader->SetMat4("model", transform.getModelTransform());
			ModelComponent->shader->SetMat4("view", camera->getViewTransform());
			ModelComponent->shader->SetMat4("projection", camera->getProjectionTransform());
			//std::cout << camera->cameraPos.x << ", " << camera->cameraPos.y << ", " << camera->cameraPos.z << std::endl;
			//std::cout << camera->getViewTransform()[0] << std::endl;
			ModelComponent->update();
		}

	}
}