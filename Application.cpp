#include "GE/GraphicsEngine.h"

using namespace GE;

int main()
{
    Scene scene(1920, 1080);

    Camera camera;
    camera.setSpeed(5.0f);
    camera.setUp(5.0f,60.0f, 1920.0f / 1080.0f, 1.0f, 100.0f);
    
    SceneObject modelObject;
    Model modelComponent("C:\\SampleProjects\\OpenGL\\OpenGLChapter3FinishingProject\\GraphicsEngineTest\\GE_Test\\Res\\Models\\Sheep\\sheep-bl.obj", UNLIT_SHADER);
    modelObject.addComponent(&modelComponent);
    modelObject.transform.position = glm::vec3(5.0f, 0.0f, 0.0f);

    SceneObject modelObject1;
    Model modelComponent1("C:\\SampleProjects\\OpenGL\\OpenGLChapter3FinishingProject\\GraphicsEngineTest\\GE_Test\\Res\\Models\\backpack\\backpack.obj", LIT_SHADER);
    modelObject1.addComponent(&modelComponent1);
    modelObject1.transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);

    SceneObject pointLight;
    PointLight pointLightComponent(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), 0.14f, 0.07f);
    pointLight.addComponent(&pointLightComponent);
    pointLight.transform.position = glm::vec3(0.0f, 0.0f, 10.0f);

    SceneObject directionalLight;
    DirectionalLight directionalLightComponent(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight.addComponent(&directionalLightComponent);
    directionalLight.transform.rotation = glm::vec3(-0.5f, -1.0f, 0.0f);

    SceneObject directionalLight1;
    DirectionalLight directionalLightComponent1(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight1.addComponent(&directionalLightComponent1);
    directionalLight1.transform.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    scene.AddObject(&modelObject);
    scene.AddObject(&modelObject1);
    scene.AddObject(&pointLight);
    scene.AddObject(&directionalLight);
    scene.AddObject(&camera);

    scene.Start();
}