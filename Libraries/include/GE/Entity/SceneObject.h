#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "GE/Entity/Object.h"
#include "GE/HelperClasses/Shader.h"
#include "GE/Components/Component.h"
#include "GE/Components/Transform.h"
#include "GE/Components/Model.h"
#include "GE/Components/PointLight.h"
#include "GE/Components/DirectionalLight.h"
#include "GE/Entity/Camera.h"

namespace GE
{

	class SceneObject : public Object
	{
	public:
		std::vector<Component*> Components;
		std::vector<PointLight*> PointLights;
		std::vector<DirectionalLight*> DirectionalLights;

		Transform transform;
		Camera* camera;

		SceneObject();

		virtual void addComponent(Component* component);

		void update() override;
	};

}

