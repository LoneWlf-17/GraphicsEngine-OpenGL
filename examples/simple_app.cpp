#include <GE/GraphicsEngine.h>

using namespace GE;

int main()
{
    // Create a scene with window size 1920x1080
    Scene scene(1920, 1080);

    // ------------------ CAMERA SETUP ------------------
    Camera camera;
    camera.setSpeed(5.0f); // Set movement speed for the camera
    camera.setUp(
        5.0f,              // Mouse sensitivity
        60.0f,             // Field of view (FOV)
        1920.0f / 1080.0f, // Aspect ratio
        1.0f,              // Near clipping plane
        100.0f             // Far clipping plane
    );

    // ------------------ MODEL 1 (Unlit Sheep) ------------------
    SceneObject modelObject;
    // Load a sheep model using an UNLIT shader (no lighting applied)
    Model modelComponent("C:\\Projects\\Sample\\Res\\Models\\Sheep\\sheep-bl.obj", UNLIT_SHADER);
    modelObject.addComponent(&modelComponent);
    // Position the sheep slightly to the right
    modelObject.transform.position = glm::vec3(5.0f, 0.0f, 0.0f);

    // ------------------ MODEL 2 (Lit Backpack) ------------------
    SceneObject modelObject1;
    // Load a backpack model using a LIT shader (affected by scene lighting)
    Model modelComponent1("C:\\Projects\\Sample\\Res\\Models\\backpack\\backpack.obj", LIT_SHADER);
    modelObject1.addComponent(&modelComponent1);
    // Position the backpack to the left
    modelObject1.transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);

    // ------------------ POINT LIGHT ------------------
    SceneObject pointLight;
    // Create a point light with ambient, diffuse, specular components and attenuation
    PointLight pointLightComponent(
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient color
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse color
        glm::vec3(1.0f, 1.0f, 1.0f), // Specular color
        0.14f,                       // Linear attenuation
        0.07f                        // Quadratic attenuation
    );
    pointLight.addComponent(&pointLightComponent);
    // Place the light in front of the scene
    pointLight.transform.position = glm::vec3(0.0f, 0.0f, 10.0f);

    // ------------------ DIRECTIONAL LIGHTS ------------------
    SceneObject directionalLight;
    // First directional light (angled down and left)
    DirectionalLight directionalLightComponent(
        glm::vec3(0.1f, 0.1f, 0.1f), // Ambient
        glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse
        glm::vec3(1.0f, 1.0f, 1.0f)  // Specular
    );
    directionalLight.addComponent(&directionalLightComponent);
    directionalLight.transform.rotation = glm::vec3(-0.5f, -1.0f, 0.0f);

    SceneObject directionalLight1;
    // Second directional light (angled differently for balanced lighting)
    DirectionalLight directionalLightComponent1(
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    directionalLight1.addComponent(&directionalLightComponent1);
    directionalLight1.transform.rotation = glm::vec3(0.0f, 1.0f, 0.0f);

    // ------------------ ADD OBJECTS TO SCENE ------------------
    scene.AddObject(&modelObject);
    scene.AddObject(&modelObject1);
    scene.AddObject(&pointLight);
    scene.AddObject(&directionalLight);
    scene.AddObject(&camera);

    // ------------------ START RENDER LOOP ------------------
    // Initializes and starts the engine's main render loop
    scene.Start();

    return 0;
}
