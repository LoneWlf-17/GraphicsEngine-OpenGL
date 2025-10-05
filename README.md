# GraphicsEngine-OpenGL

An OpenGL-based **Graphics Engine** built for rendering 3D scenes with lighting, models, and camera control.  
This engine provides a simple and modular way to create, load, and render 3D content using modern OpenGL practices.

---

## 🚀 Features

- 🧱 **Scene System** — Create and manage multiple scene objects easily.  
- 🧭 **Camera System** — FPS-style camera with adjustable speed, FOV, and clipping planes.  
- 💡 **Lighting** — Supports Point Lights and Directional Lights with configurable color and attenuation.  
- 🎨 **Shaders** — Includes support for **LIT** and **UNLIT** shaders.  
- 🧩 **Components** — Modular component-based architecture for easy extension.  
- 📦 **Model Loading** — Supports loading 3D models (e.g., `.obj`) with textures.  

---

## 🧠 Example Usage

Here’s a simple example demonstrating how to set up a scene with models, lighting, and a camera:

```cpp
#include <GE/GraphicsEngine.h>

using namespace GE;

int main()
{
    // Create scene with 1920x1080 resolution
    Scene scene(1920, 1080);

    // Setup camera
    Camera camera;
    camera.setSpeed(5.0f);
    camera.setUp(5.0f, 60.0f, 1920.0f / 1080.0f, 1.0f, 100.0f);

    // Load an unlit sheep model
    SceneObject sheep;
    Model sheepModel("C:\\Projects\\Sample\\Res\\Models\\Sheep\\sheep-bl.obj", UNLIT_SHADER);
    sheep.addComponent(&sheepModel);
    sheep.transform.position = glm::vec3(5.0f, 0.0f, 0.0f);

    // Load a lit backpack model
    SceneObject backpack;
    Model backpackModel("C:\\Projects\\Sample\\Res\\Models\\backpack\\backpack.obj", LIT_SHADER);
    backpack.addComponent(&backpackModel);
    backpack.transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);

    // Add a point light
    SceneObject pointLight;
    PointLight pointLightComponent(
        glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f), 0.14f, 0.07f
    );
    pointLight.addComponent(&pointLightComponent);
    pointLight.transform.position = glm::vec3(0.0f, 0.0f, 10.0f);

    // Add a directional light
    SceneObject dirLight;
    DirectionalLight dirLightComp(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f));
    dirLight.addComponent(&dirLightComp);
    dirLight.transform.rotation = glm::vec3(-0.5f, -1.0f, 0.0f);

    // Add everything to the scene
    scene.AddObject(&sheep);
    scene.AddObject(&backpack);
    scene.AddObject(&pointLight);
    scene.AddObject(&dirLight);
    scene.AddObject(&camera);

    // Start render loop
    scene.Start();

    return 0;
}
