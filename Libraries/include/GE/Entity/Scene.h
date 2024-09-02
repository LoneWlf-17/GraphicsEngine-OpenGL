#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "GE/Entity/SceneObject.h"
#include "GLFW/glfw3.h"

namespace GE
{
	class Scene : public Object
	{
	private:
		std::vector<SceneObject*> sceneObjects = std::vector<SceneObject*>();
		std::vector<Camera*> cameras = std::vector<Camera*>();
		std::vector<Light*> lights = std::vector<Light*>();

		int ScreenWidth;
		int ScreenHeight;


		GLFWwindow* window;
	public:
		//int windowClose = 0;

		Scene();
		Scene(int screenWidth, int screenHeight);

		void AddObject(Object* object);

		int Start();

		void update() override;
	};

}

#endif