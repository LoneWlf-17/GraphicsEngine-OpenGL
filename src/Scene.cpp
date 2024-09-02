#include "GE/Entity/Scene.h"
#include "GE/InputCallbacks.h"

GE::Scene::Scene()
{
	ScreenHeight = 1200;
	ScreenWidth = 1200;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cout << "ERROR::WINDOW::GLFW_IS_NOT_INITIALIZED" << std::endl;
		return;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1200, 1200, "Graphics Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "ERROR::WINDOW::WINDOW_IS_NOT_INITIALIZED" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::OPENGL::Failed to initialize OpenGL context" << std::endl;
		return;
	}

	glViewport(0, 0, 1200, 1200);

}

GE::Scene::Scene(int screenWidth, int screenHeight)
{
	this->ScreenHeight = screenHeight;
	this->ScreenWidth = screenWidth;

	/* Initialize the library */
	if (!glfwInit())
		std::cout << "ERROR::WINDOW::GLFW_IS_NOT_INITIALIZED" << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenWidth, screenHeight, "Graphics Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "ERROR::WINDOW::WINDOW_IS_NOT_INITIALIZED" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR::OPENGL::Failed to initialize OpenGL context" << std::endl;
	}

	glViewport(0, 0, screenWidth, screenHeight);

}

void GE::Scene::AddObject(Object* object)
{
	if (SceneObject* sceneObject = dynamic_cast<SceneObject*>(object))
	{
		sceneObjects.push_back(sceneObject);

		for (int i = 0; i < sceneObjects.size(); i++)
		{
			for (int j = 0; j < sceneObjects[i]->Components.size(); j++)
			{
				if (Light* light = dynamic_cast<Light*>(sceneObjects[i]->Components[j])) 
				{
					lights.push_back(light);
					if (DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(light))
					{
						for (int k = 0; k < sceneObjects.size(); k++)
						{
							sceneObjects[k]->DirectionalLights.push_back(directionalLight);
						}
					}
					else if (PointLight* pointLight = dynamic_cast<PointLight*>(light))
					{
						for (int k = 0; k < sceneObjects.size(); k++)
						{
							sceneObjects[k]->PointLights.push_back(pointLight);
						}
					}
				}
			}
		}

	}
	else if (Camera* camera = dynamic_cast<Camera*>(object))
	{
		cameras.push_back(camera);

	}
}

int GE::Scene::Start()
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i]->camera = cameras[0];
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		update();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void GE::Scene::update()
{
	for (int i = 0; i < cameras.size(); i++)
	{
		GE::Input::processInput(window, &(cameras[i]->cameraPos), &cameras[i]->cameraFront, &cameras[i]->cameraUp, cameras[i]->cameraSpeed);
		cameras[i]->update();
	}
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		sceneObjects[i]->update();
	}
}
